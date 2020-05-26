#include "yaoosl_method.h"
#include "yaoosl_code.h"
#include <malloc.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

yaooslmethodgrouphandle yaoosl_method_group_create(const char* name)
{
	size_t len;
	yaooslmethodgrouphandle handle = malloc(sizeof(yaoosl_method_group));
	if (handle)
	{
		// Set title
		len = strlen(name);
		handle->title = malloc(sizeof(char) * (len + 1));
		if (!handle->title)
		{
			free(handle);
			return NULL;
		}
		strncpy(handle->title, name, len);
		handle->title[len] = '\0';

		// Set fields not requiring allocation
		handle->methods_capacity = 0;
		handle->methods_size = 0;
		handle->methods = 0;
	}
	return handle;
}

bool yaoosl_method_group_push_back(yaooslmethodgrouphandle grouphandle, yaooslmethodhandle methodhandle)
{
	yaooslmethodhandle* method_handles;
	if (!grouphandle || !methodhandle)
	{
		return false;
	}
	if (grouphandle->methods_size == grouphandle->methods_capacity)
	{
		method_handles = realloc(grouphandle->methods, sizeof(yaooslmethodhandle) * (grouphandle->methods_capacity * grouphandle->methods_capacity + 1));
		if (!method_handles)
		{
			return false;
		}
		grouphandle->methods = method_handles;
		grouphandle->methods_capacity = grouphandle->methods_capacity * grouphandle->methods_capacity + 1;
	}
	grouphandle->methods[grouphandle->methods_size++] = methodhandle;
	return true;
}

void yaoosl_method_group_destroy(yaooslmethodgrouphandle handle)
{
	unsigned int i;
	if (handle)
	{
		for (i = 0; i < handle->methods_size; i++)
		{
			yaoosl_method_destroy(handle->methods[i]);
		}
		free(handle->methods);
		free(handle->title);
		free(handle);
	}
}

yaooslmethodhandle yaoosl_method_create(const char* name, struct yaoosl_class* returntype, struct yaoosl_code* codehandle)
{
	size_t len;
	yaooslmethodhandle handle = malloc(sizeof(yaoosl_method));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_method));
		// Set title
		len = strlen(name);
		handle->title = malloc(sizeof(char) * (len + 1));
		if (!handle->title)
		{
			free(handle);
			return NULL;
		}
		strncpy(handle->title, name, len);
		handle->title[len] = '\0';

		// Set fields not requiring allocation
		handle->args_capacity = 0;
		handle->args_size = 0;
		handle->args = 0;
		handle->contents = codehandle;
		handle->returntype = returntype;
	}
	return handle;
}

yaooslmethodhandle yaoosl_method_group_get_method(yaooslmethodgrouphandle handle, struct yaoosl_class* returntype, unsigned int arg_count, ...)
{
	va_list argp;
	unsigned int i;
	struct yaoosl_class** types = alloca(sizeof(struct yaoosl_class*) * arg_count);
	va_start(argp, arg_count);
	for (i = 0; i < arg_count; i++)
	{
		types[i] = va_arg(argp, struct yaoosl_class*);
	}
	va_end(argp);
	return yaoosl_method_group_get_method2(handle, returntype, arg_count, types);
}
yaooslmethodhandle yaoosl_method_group_get_method2(yaooslmethodgrouphandle handle, struct yaoosl_class* returntype, unsigned int arg_count, struct yaoosl_class** args)
{
	unsigned int i, j;
	yaooslmethodhandle method;
	for (i = 0; i < handle->methods_size; i++)
	{
		method = handle->methods[i];
		if ((returntype != ((void*)~0LL) && method->returntype != returntype) || method->args_size != arg_count)
		{
			continue;
		}
		for (j = 0; j < arg_count; j++)
		{
			if (method->args[j]->type != args[j])
			{
				break;
			}
		}
		if (j == arg_count)
		{
			return method;
		}
	}
	return NULL;
}

bool yaoosl_method_push_arg(yaooslmethodhandle methodhandle, yaooslarghandle arghandle)
{
	yaooslarghandle* arg_handles;
	if (!methodhandle || !arghandle)
	{
		return false;
	}
	if (methodhandle->args_size == methodhandle->args_capacity)
	{
		arg_handles = realloc(methodhandle->args, sizeof(yaooslarghandle) * (methodhandle->args_capacity * methodhandle->args_capacity + 1));
		if (!arg_handles)
		{
			return false;
		}
		methodhandle->args = arg_handles;
		methodhandle->args_capacity = methodhandle->args_capacity * methodhandle->args_capacity + 1;
	}
	methodhandle->args[methodhandle->args_size++] = arghandle;
	return true;
}

void yaoosl_method_destroy(yaooslmethodhandle handle)
{
	unsigned int i;
	if (handle)
	{
		for (i = 0; i < handle->args_size; i++)
		{
			yaoosl_arg_destroy(handle->args[i]);
		}
		free(handle->args);
		if (handle->prefixes_size > 0)
		{
			for (i = 0; i < handle->prefixes_size; i++)
			{
				free(handle->prefixes[i]);
			}
			free(handle->prefixes);
		}
		if (handle->contents->bytes_size)
		{
			free(handle->contents->bytes);
		}
		free(handle->contents);
		free(handle->title);
		free(handle);
	}
}

yaooslarghandle yaoosl_arg_create(const char* name, struct yaoosl_class* type)
{
	size_t len;
	yaooslarghandle handle = malloc(sizeof(yaoosl_arg));
	if (handle)
	{
		len = strlen(name);
		handle->title = malloc(sizeof(char) * (len + 1));
		if (!handle->title)
		{
			free(handle);
			return NULL;
		}
		strncpy(handle->title, name, len);
		handle->title[len] = '\0';
		handle->type = type;
	}
	return handle;
}

void yaoosl_arg_destroy(yaooslarghandle handle)
{
	if (handle)
	{
		free(handle->title);
		free(handle);
	}
}


PRINT__YAOOSL_MTHD_PUSH_VALUE2(method, yaooslmethodhandle, method_handle, char*, prefix, prefixes);
PRINT__YAOOSL_MTHD_POP_VALUE2(method, yaooslmethodhandle, method_handle, char*, prefix, prefixes);