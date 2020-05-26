#include "yaoosl_context.h"
#include "yaoosl_instance.h"
#include "yaoosl_code.h"
#include "yaoosl_class.h"
#include "yaoosl.h"
#include "string_map.h"

#include <malloc.h>
#include <string.h>

yaooslcontexthandle yaoosl_context_create(void)
{
	yaooslcontexthandle handle = malloc(sizeof(yaoosl_context));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_context));
		handle->value_stack = malloc(sizeof(yaooslinstancehandle) * YAOOSL_DEFAULT_VALUE_STACK_SIZE);
		handle->value_stack_capacity = YAOOSL_DEFAULT_VALUE_STACK_SIZE;
		if (!handle->value_stack)
		{
			free(handle);
			return NULL;
		}
		handle->scopes = malloc(sizeof(yaooslscopehandle) * YAOOSL_DEFAULT_SCOPES_SIZE);
		handle->scopes_capacity = YAOOSL_DEFAULT_SCOPES_SIZE;
		if (!handle->value_stack)
		{
			free(handle->value_stack);
			free(handle);
			return NULL;
		}
		handle->exception_handlers = malloc(sizeof(yaoosl_exception_handler) * YAOOSL_DEFAULT_EXCEPTION_HANDLERS_SIZE);
		handle->exception_handlers_capacity = YAOOSL_DEFAULT_EXCEPTION_HANDLERS_SIZE;
		if (!handle->value_stack)
		{
			free(handle->value_stack);
			free(handle->scopes);
			free(handle);
			return NULL;
		}
	}
	return handle;
}

void yaoosl_context_destroy(yaooslcontexthandle handle)
{
	if (!handle) { return; }
	unsigned int i;
	for (i = 0; i < handle->value_stack_size; i++)
	{
		yaoosl_instance_dec_ref(handle->value_stack[i]);
	}
	free(handle->value_stack);
	for (i = 0; i < handle->scopes_size; i++)
	{
		yaoosl_scope_destroy(handle->scopes[i]);
	}
	free(handle->scopes);
	// No need to do anything on this as it is merely a organizational
	// structure.
	free(handle->exception_handlers);
	free(handle);
}

yaooslscopehandle yaoosl_scope_create(void)
{
	yaooslscopehandle handle = malloc(sizeof(yaoosl_scope));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_scope));
	}
	return handle;
}

void yaoosl_scope_destroy(yaooslscopehandle handle)
{
	if (!handle) { return; }
	unsigned int i;
	if (handle->destroy_code)
	{
		if (handle->codehandle->bytes_size > 0)
		{
			free(handle->codehandle->bytes);
		}
		free(handle->codehandle);
	}
	for (i = 0; i < handle->locals_size; i++)
	{
		yaoosl_instance_dec_ref(handle->locals[i]);
	}
	for (i = 0; i < handle->blocks_size; i++)
	{
		yaoosl_block_destroy(handle->blocks[i]);
	}
	free(handle);
}

yaooslblockhandle yaoosl_block_create(void)
{
	yaooslblockhandle handle = malloc(sizeof(yaoosl_block));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_block));
	}
	return handle;
}

void yaoosl_block_destroy(yaooslblockhandle handle)
{
	size_t i;
	if (!handle) { return; }
	if (handle->catchhandles_capacity > 0)
	{
		free(handle->catchhandles);
	}
	if (handle->prefixes_size > 0)
	{
		for (i = 0; i < handle->prefixes_size; i++)
		{
			free(handle->prefixes[i]);
		}
		free(handle->prefixes);
	}
	free(handle);
}
yaooslscopehandle yaoosl_context_top_scope(yaooslcontexthandle context)
{
	if (context->scopes_size == 0)
	{
		return NULL;
	}
	return context->scopes[context->scopes_size - 1];
}

bool yaoosl_context_peek(yaooslcontexthandle context, uint8_t offset, uint8_t* out_value)
{
	yaooslscopehandle scope;
	if (context->scopes_size == 0)
	{
		return false;
	}
	scope = context->scopes[context->scopes_size - 1];
	if (scope->offset + offset >= scope->codehandle->bytes_size)
	{
		return false;
	}
	*out_value = scope->codehandle->bytes[scope->offset + offset];
	return true;
}

bool yaoosl_context_try_next(yaooslcontexthandle context, uint8_t* out_value)
{
	yaooslscopehandle scope;
	if (context->scopes_size == 0)
	{
		return false;
	}
	scope = context->scopes[context->scopes_size - 1];
	if (scope->offset >= scope->codehandle->bytes_size)
	{
		yaoosl_scope_destroy(scope);
		context->scopes_size--;
		return yaoosl_context_try_next(context, out_value);
	}
	*out_value = scope->codehandle->bytes[scope->offset++];
	return true;
}
uint8_t yaoosl_context_next(yaooslcontexthandle context, bool* out_success_optional)
{
	uint8_t out;
	if (out_success_optional && !(*out_success_optional = yaoosl_context_try_next(context, &out)))
	{
		out = 0;
	}
	else if (!out_success_optional && !yaoosl_context_try_next(context, &out))
	{
		out = 0;
	}
	return out;
}

yaoosl_code* yaoosl_context_current_code(yaooslcontexthandle context)
{
	yaooslscopehandle scope = yaoosl_context_top_scope(context);
	if (scope)
	{
		return scope->codehandle;
	}
	else
	{
		return NULL;
	}
}

yaoosl_class* yaoosl_context_resolve_type(yaooslcontexthandle context, struct yaoosl* yaoosl, const char* classname)
{
	size_t i, j, k;
	yaooslscopehandle scope = yaoosl_context_top_scope(context);
	yaooslclasshandle classhandle;
	char *concat = 0, *tmp;
	size_t concat_cap = 0;
	size_t cn_len;
	if (scope)
	{
		cn_len = strlen(classname) + 1;
		for (i = scope->blocks_size - 1; i != ~(size_t)0; i--)
		{
			for (j = 0; j < scope->blocks[i]->prefixes_size; j++)
			{
				k = strlen(scope->blocks[i]->prefixes[j]);
				if (concat_cap < k)
				{
					tmp = realloc(concat, sizeof(char) * (k * 2  + cn_len + 1));
					if (!tmp)
					{
						if (concat)
						{
							free(concat);
						}
						return 0;
					}
					concat_cap = (k * 2 + cn_len + 1);
					concat = tmp;
				}
				tmp = concat;
				strncpy(tmp, scope->blocks[i]->prefixes[j], k);
				tmp += k;
				tmp[0] = '.';
				tmp++;
				strncpy(tmp, classname, cn_len);
				tmp[cn_len] = '\0';
				if (classhandle = yaoosl_map_get_value(yaoosl->classes_map, concat))
				{
					return classhandle;
				}
			}
		}
	}
	return yaoosl_map_get_value(yaoosl->classes_map, classname);
}

bool yaoosl_context_move(yaooslcontexthandle context, int32_t offset)
{
	yaooslscopehandle scope;
	if (context->scopes_size == 0)
	{
		return false;
	}
	scope = context->scopes[context->scopes_size - 1];
	if (scope->offset + offset >= 0 && scope->offset + offset < scope->codehandle->bytes_size)
	{
		scope->offset += offset;
		return true;
	}
	return false;
}

bool yaoosl_context_handle_exception(yaooslcontexthandle context, struct yaoosl_class* type, yaooslstacktracehandle* out_stacktrace, yaoosl_catch_handle* out_catch_handle)
{
	size_t i, j, k = 0;
	int32_t hit_relation = INT32_MAX, tmp;
	yaooslblockhandle codeblock;
	yaooslscopehandle scope = 0;
	*out_stacktrace = malloc(sizeof(yaoosl_stacktrace));
	if (!*out_stacktrace)
	{
		return false;
	}
	for (i = context->exception_handlers_size; i > 0; i--)
	{
		codeblock = context->exception_handlers[i - 1].block;
		for (j = 0; j < codeblock->catchhandles_size; j++)
		{
			if (tmp = yaoosl_class_is_type(type, codeblock->catchhandles[j].type))
			{
				if (type == codeblock->catchhandles[j].type)
				{
					k = i;
					scope = context->exception_handlers[i - 1].scope;
					*out_catch_handle = codeblock->catchhandles[j];
					break;
				}
				else if (tmp < hit_relation)
				{
					k = i;
					scope = context->exception_handlers[i - 1].scope;
					*out_catch_handle = codeblock->catchhandles[j];
				}
			}
		}
	}
	(*out_stacktrace)->scopes_size = 0;
	for (i = k; i < context->exception_handlers_size; i++)
	{
		(*out_stacktrace)->scopes_size++;
	}
	(*out_stacktrace)->scopes = malloc(sizeof(yaooslscopehandle) * (*out_stacktrace)->scopes_size);
	if (!(*out_stacktrace)->scopes)
	{
		return false;
	}
	for (i = (*out_stacktrace)->scopes_size, j = 0; i > 0; i--, j++)
	{
		(*out_stacktrace)->scopes[j] = context->exception_handlers[i - 1].scope;
	}
	return true;
}

PRINT__YAOOSL_MTHD_PUSH_VALUE(context, yaooslcontexthandle, context_handle, yaooslscopehandle, scope, scopes);
PRINT__YAOOSL_MTHD_POP_VALUE(context, yaooslcontexthandle, context_handle, yaooslscopehandle, scope, scopes);

PRINT__YAOOSL_MTHD_PUSH_VALUE(context, yaooslcontexthandle, context_handle, struct yaoosl_instance*, value, value_stack);
PRINT__YAOOSL_MTHD_POP_VALUE(context, yaooslcontexthandle, context_handle, struct yaoosl_instance*, value, value_stack);

PRINT__YAOOSL_MTHD_PUSH_VALUE2(context, yaooslcontexthandle, context_handle, yaoosl_exception_handler, exception_handler, exception_handlers);
PRINT__YAOOSL_MTHD_POP_VALUE2(context, yaooslcontexthandle, context_handle, yaoosl_exception_handler, exception_handler, exception_handlers);

PRINT__YAOOSL_MTHD_PUSH_VALUE(scope, yaooslscopehandle, scope_handle, yaooslblockhandle, block, blocks);
PRINT__YAOOSL_MTHD_POP_VALUE(scope, yaooslscopehandle, scope_handle, yaooslblockhandle, block, blocks);

PRINT__YAOOSL_MTHD_PUSH_VALUE2(block, yaooslblockhandle, block_handle, yaoosl_catch_handle, catch_handle, catchhandles);
PRINT__YAOOSL_MTHD_POP_VALUE2(block, yaooslblockhandle, block_handle, yaoosl_catch_handle, catch_handle, catchhandles);

PRINT__YAOOSL_MTHD_PUSH_VALUE2(block, yaooslblockhandle, block_handle, char*, prefix, prefixes);
PRINT__YAOOSL_MTHD_POP_VALUE2(block, yaooslblockhandle, block_handle, char*, prefix, prefixes);