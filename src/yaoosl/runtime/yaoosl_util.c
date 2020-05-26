#include "yaoosl_util.h"
#include "yaoosl.h"
#include "yaoosl_instance.h"
#include "yaoosl_context.h"
#include "yaoosl_knowntypes.h"
#include "yaoosl_class.h"
#include "yaoosl_code.h"
#include "string_op.h"


#include <string.h>
#include <malloc.h>
#include <stddef.h>


#define PRINT__yaoosl_PUSH_EXTENSIONS(TYPE, NAME, ENUM) PRINT__yaoosl_PUSH_EXTENSIONS2(TYPE, NAME, NAME, ENUM)
#define PRINT__yaoosl_PUSH_EXTENSIONS2(TYPE, NAME, NAME2, ENUM)\
bool yaoosl_util_push_ ## NAME(yaoosl* yaoosl, yaoosl_context* context, TYPE value)\
{\
	yaooslinstancehandle handle = yaoosl_instance_create(yaoosl->classes[ENUM]);\
	handle->additional.NAME2 = value;\
	yaoosl_instance_inc_ref(handle);\
	if (!yaoosl_context_push_value(context, handle))\
	{\
		yaoosl_instance_dec_ref(handle);\
		return false;\
	}\
	return true;\
}


struct yaoosl_instance* yaoosl_util_create_array(struct yaoosl* yaoosl, int32_t size, struct yaoosl_class* type)
{
	yaooslinstancehandle value;
	value = yaoosl_instance_create(yaoosl->classes[ARRAY]);
	if (!value)
	{
		return NULL;
	}
	if (!yaoosl_change_type(value->fields[yaoosl_knowntypes_propertyindex_array_Type], yaoosl->classes[TYPE]))
	{
		yaoosl_instance_destroy(value);
		return NULL;
	}
	if (!yaoosl_change_type(value->fields[yaoosl_knowntypes_propertyindex_array_Length], yaoosl->classes[INT32]))
	{
		yaoosl_instance_destroy(value);
		return NULL;
	}
	if (!(value->additional.ptr = malloc(sizeof(yaooslinstancehandle) * size)))
	{
		yaoosl_instance_destroy(value);
		return NULL;
	}
	value->fields[yaoosl_knowntypes_propertyindex_array_Type]->additional.ptr = type;
	value->fields[yaoosl_knowntypes_propertyindex_array_Length]->additional.int32 = size;
	return value;
}

yaoosl_instance* yaoosl_util_create_stackframe_array(struct yaoosl* yaoosl, struct yaoosl_context* context)
{
	yaooslinstancehandle array;
	yaooslinstancehandle frame;
	size_t i;
	array = yaoosl_util_create_array(yaoosl, (int32_t)context->scopes_size, yaoosl->classes[STACKFRAME_CLASS]);
	if (!array)
	{
		return NULL;
	}
	for (i = 0; i < context->scopes_size; i++)
	{
		frame = yaoosl_instance_create(yaoosl->classes[STACKFRAME_CLASS]);
		if (!frame)
		{
			i--;
			break;
		}
		yaoosl_instance_inc_ref(frame);
		if (!yaoosl_change_type(frame->fields[yaoosl_knowntypes_propertyindex_stackframe_Method], yaoosl->classes[TYPE]))
		{
			break;
		}
		if (!yaoosl_change_type(frame->fields[yaoosl_knowntypes_propertyindex_stackframe_Line], yaoosl->classes[INT32]))
		{
			break;
		}
		if (!yaoosl_change_type(frame->fields[yaoosl_knowntypes_propertyindex_stackframe_Column], yaoosl->classes[INT32]))
		{
			break;
		}
		if (!yaoosl_change_type(frame->fields[yaoosl_knowntypes_propertyindex_stackframe_File], yaoosl->classes[STRING]))
		{
			break;
		}
		frame->fields[yaoosl_knowntypes_propertyindex_stackframe_Method]->additional.ptr = context->scopes[i]->related_method;
		// ToDo: Set Debug informations like Line, Column & File
		((yaooslinstancehandle*)array->additional.ptr)[i] = frame;
	}
	if (i != context->scopes_size)
	{
		for (i++; i > 0; i--)
		{
			frame = ((yaooslinstancehandle*)array->additional.ptr)[i];
			yaoosl_instance_dec_ref(frame);
		}
		yaoosl_instance_destroy(array);
		return NULL;
	}
	return array;
}

yaooslcontexthandle yaoosl_util_load_code(yaoosl* yaoosl, struct yaoosl_code* codehandle)
{
	yaooslcontexthandle context;
	yaooslscopehandle scope = yaoosl_scope_create();
	if (!scope)
	{
		return NULL;
	}
	scope->codehandle = codehandle;
	context = yaoosl_context_create();
	if (!context)
	{
		yaoosl_scope_destroy(scope);
		return NULL;
	}
	if (!yaoosl_context_push_scope(context, scope))
	{
		yaoosl_scope_destroy(scope);
		yaoosl_context_destroy(context);
		return NULL;
	}
	return context;
}
bool yaoosl_util_execute_code(yaoosl* yaoosl, struct yaoosl_code* codehandle)
{
	yaooslcontexthandle context = yaoosl_util_load_code(yaoosl, codehandle);
	if (context)
	{
		yaoosl_execute(yaoosl, context);
		yaoosl_context_destroy(context);
		return true;
	}
	return false;
}

bool yaoosl_util_push_null(yaoosl_context* context)
{
	yaooslinstancehandle handle = yaoosl_instance_create(NULL);
	if (handle)
	{
		yaoosl_instance_inc_ref(handle);
		if (!yaoosl_context_push_value(context, handle))
		{
			yaoosl_instance_dec_ref(handle);
			return false;
		}
		return true;
	}
	return false;
}

bool yaoosl_util_push_string(yaoosl* yaoosl, yaoosl_context* context, const char* value)
{
	size_t len = strlen(value);
	return yaoosl_util_push_stringn(yaoosl, context, len, value);
}
bool yaoosl_util_push_stringn(yaoosl* yaoosl, yaoosl_context* context, size_t len, const char* value)
{
	yaooslinstancehandle handle = yaoosl_util_get_stringn(yaoosl, len, value);
	if (!handle)
	{
		return false;
	}
	yaoosl_instance_inc_ref(handle);
	if (!yaoosl_context_push_value(context, handle))
	{
		yaoosl_instance_dec_ref(handle);
		return false;
	}
	return true;
}
struct yaoosl_instance* yaoosl_util_get_string(struct yaoosl* yaoosl, const char* value)
{
	size_t len = strlen(value);
	return yaoosl_util_get_stringn(yaoosl, len, value);
}
struct yaoosl_instance* yaoosl_util_get_stringn(struct yaoosl* yaoosl, size_t len, const char* value)
{
	yaooslinstancehandle handle = yaoosl_instance_create(yaoosl->classes[STRING]);
	if (handle)
	{
		handle->additional.str = malloc(sizeof(char) * (len + 1));
		if (!handle->additional.str)
		{
			yaoosl_instance_destroy(handle);
			return NULL;
		}
		strncpy(handle->additional.str, value, len);
		handle->additional.str[len] = '\0';
	}
	return handle;
}
bool yaoosl_util_throw_generic(struct yaoosl* yaoosl, struct yaoosl_context* context, const char* message)
{
	return yaoosl_util_throw(yaoosl, context, yaoosl->classes[EXCEPTION_CLASS], message);
}
bool yaoosl_util_throw(struct yaoosl* yaoosl, struct yaoosl_context* context, struct yaoosl_class* type, const char* message)
{
	yaooslinstancehandle exception;
	yaooslinstancehandle string;
	size_t i;
	if (!(exception = yaoosl_instance_create(type)))
	{
		return false;
	}
	if (!(string = yaoosl_util_get_string(yaoosl, message)))
	{
		yaoosl_instance_destroy(exception);
		return false;
	}
	if (type == yaoosl->classes[EXCEPTION_CLASS])
	{
		yaoosl_instance_dec_ref(exception->fields[yaoosl_knowntypes_propertyindex_exception_Message]);
		exception->fields[yaoosl_knowntypes_propertyindex_exception_Message] = string;
	}
	else
	{ // Lookup the fields
		for (i = 0; i < type->properties_size; i++)
		{
			if (str_cmp(type->properties[i]->title, -1, yaoosl_knowntypes_propertyindex_exception_Message_str, -1) == 0)
			{
				break;
			}
		}
		yaoosl_instance_dec_ref(exception->fields[i]);
		exception->fields[i] = string;
	}
	return yaoosl_util_throw2(yaoosl, context, exception);
}
bool yaoosl_util_throw2(yaoosl* yaoosl, yaoosl_context* context, yaoosl_instance* exception)
{
	yaooslstacktracehandle stacktracehandle;
	yaooslinstancehandle stackframearray;
	yaooslscopehandle scopehandle;
	yaoosl_catch_handle catch_handle;
	size_t i;
	if (!exception || !yaoosl_class_is_type(exception->type, yaoosl->classes[EXCEPTION_CLASS]))
	{
		return false;
	}

	if (!yaoosl_context_handle_exception(context, exception->type, &stacktracehandle, &catch_handle))
	{
		return false;
	}

	// Update Exception to contain stack frames
	if (!(stackframearray = yaoosl_util_create_stackframe_array(yaoosl, context)))
	{
		return false;
	}
	yaoosl_instance_inc_ref(stackframearray);

	if (exception->type == yaoosl->classes[EXCEPTION_CLASS])
	{
		yaoosl_instance_dec_ref(exception->fields[yaoosl_knowntypes_propertyindex_exception_Frames]);
		exception->fields[yaoosl_knowntypes_propertyindex_exception_Frames] = stackframearray;
	}
	else
	{ // Lookup the fields
		for (i = 0; i < exception->type->properties_size; i++)
		{
			if (str_cmp(exception->type->properties[i]->title, -1, yaoosl_knowntypes_propertyindex_exception_Frames_str, -1) == 0)
			{
				break;
			}
		}
		yaoosl_instance_dec_ref(exception->fields[i]);
		exception->fields[i] = stackframearray;
	}

	// Push exception back onto the value stack
	yaoosl_instance_inc_ref(exception);
	if (!yaoosl_context_push_value(context, exception))
	{
		yaoosl_instance_dec_ref(exception);
		return false;
	}

	// Pop scopes until we reach the target
	for (i = 0; i < stacktracehandle->scopes_size - 1; i++)
	{
		scopehandle = yaoosl_context_pop_scope(context);
		yaoosl_scope_destroy(scopehandle);
	}
	if (!(scopehandle = yaoosl_context_top_scope(context)))
	{
		return false;
	}
	scopehandle->offset = catch_handle.start;
	context->handles_exception = true;
	return true;
}
PRINT__yaoosl_PUSH_EXTENSIONS(uint8_t, uint8, UINT8)
PRINT__yaoosl_PUSH_EXTENSIONS(int8_t, int8, INT8)
PRINT__yaoosl_PUSH_EXTENSIONS(uint16_t, uint16, UINT16)
PRINT__yaoosl_PUSH_EXTENSIONS(int16_t, int16, INT16)
PRINT__yaoosl_PUSH_EXTENSIONS(uint32_t, uint32, UINT32)
PRINT__yaoosl_PUSH_EXTENSIONS(int32_t, int32, INT32)
PRINT__yaoosl_PUSH_EXTENSIONS(uint64_t, uint64, UINT64)
PRINT__yaoosl_PUSH_EXTENSIONS(int64_t, int64, INT64)
PRINT__yaoosl_PUSH_EXTENSIONS2(float, float, f, FLOAT)
PRINT__yaoosl_PUSH_EXTENSIONS2(double, double, d, DOUBLE)
PRINT__yaoosl_PUSH_EXTENSIONS2(struct yaoosl_class*, type, ptr, TYPE)