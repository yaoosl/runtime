#include "yaoosl_class.h"
#include "yaoosl_instance.h"
#include "string_op.h"
#include "yaoosl_code.h"
#include "yaoosl_context.h"

#include <stddef.h>
#include <malloc.h>
#include <string.h>

yaooslclasshandle yaoosl_class_create(const char* name)
{
	size_t len;
	yaooslclasshandle handle = malloc(sizeof(yaoosl_class));
	const char* str1;
	const char* str2 = name;
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_class));

		if (!yaoosl_class_set_name(handle, name))
		{
			free(handle);
			return NULL;
		}

		// Initialize implements list
		handle->implements = NULL;
		handle->implements_capacity = 0;
		handle->implements_size = 0;

		// Initialize the method groups
		handle->method_groups = NULL;
		handle->method_groups_capacity = 0;
		handle->method_groups_size = 0;

		// Prepare constructor & destructor
		handle->constructor_method_group = NULL;
		handle->destructor_method = NULL;

		// Set handle->operator_method_groups to NULL
		memset(&handle->operator_method_groups, 0, sizeof(handle->operator_method_groups));



		handle->fin = false;
	}
	return handle;
}

yaooslmethodgrouphandle yaoosl_class_get_method(yaooslclasshandle handle, const char* name, int name_len)
{
	size_t i;
	yaooslmethodgrouphandle mg;
	for (i = 0; i < handle->method_groups_size; i++)
	{
		if (!str_cmp(handle->method_groups[i]->title, -1, name, name_len))
		{
			return handle->method_groups[i];
		}
	}
	for (i = (size_t)handle->implements_size - 1; i != ~(size_t)0; i--)
	{
		mg = yaoosl_class_get_method(handle->implements[i], name, name_len);
		if (mg)
		{
			return mg;
		}
	}
	i = strlen(handle->name);
	if (i + i + 1 == ((size_t)name_len) && str_sw(name, handle->name) == 0 && name[i] == '.')
	{
		return handle->constructor_method_group;
	}
	// if (handle->name == name)
	// {
	// 
	// }
	return NULL;
}

bool yaoosl_class_set_name(yaooslclasshandle handle, const char* name)
{
	size_t len;
	const char* str1;
	const char* str2 = name;
	if (!handle || !name)
	{
		return false;
	}
	if (handle->fullname)
	{
		free(handle->fullname);
		handle->fullname = 0;
	}
	if (handle->name)
	{
		free(handle->name);
		handle->name = 0;
	}
	// Set full name
	len = strlen(name);
	handle->fullname = malloc(sizeof(char) * (len + 1));
	if (!handle->fullname)
	{
		handle->fullname = 0;
		return false;
	}
	strncpy(handle->fullname, name, len);
	handle->fullname[len] = '\0';

	// Set direct-name (name without namespace)
	while ((str1 = strchr(str2, '.')))
	{
		str2 = str1 + 1;
	}

	len = strlen(str2);
	handle->name = malloc(sizeof(char) * (len + 1));
	if (!handle->name)
	{
		free(handle->fullname);
		handle->fullname = 0;
		handle->name = 0;
		return false;
	}
	strncpy(handle->name, str2, len);
	handle->name[len] = '\0';
	return true;
}
void yaoosl_class_destroy(yaooslclasshandle handle)
{
	unsigned int i;
	if (handle)
	{
		for (i = 0; i < handle->properties_size_self; i++)
		{
			yaoosl_property_destroy(handle->properties[i]);
		}
		free(handle->properties);

		for (i = 0; i < handle->method_groups_size; i++)
		{
			yaoosl_method_group_destroy(handle->method_groups[i]);
		}
		free(handle->method_groups);

		for (i = 0; i < __OPERATOR_MAX; i++)
		{
			yaoosl_method_group_destroy(handle->operator_method_groups[i]);
		}

		yaoosl_method_group_destroy(handle->constructor_method_group);
		yaoosl_method_destroy(handle->destructor_method);
		free(handle->fullname);
		free(handle->name);
		free(handle->implements);
		free(handle);
	}
}

bool yaoosl_class_finalize(yaooslclasshandle handle)
{
	unsigned int i, j, k;
	if (!handle)
	{
		return false;
	}
	if (handle->fin)
	{
		return true;
	}
	k = handle->properties_size_self = handle->properties_size;
	yaooslpropertyhandle propertyhandle;
	for (i = 0; i < handle->implements_size; i++)
	{
		if (!handle->implements[i]->fin)
		{
			yaoosl_class_finalize(handle->implements[i]);
		}
		for (j = 0; j < handle->implements[i]->properties_size; j++)
		{
			if (!(propertyhandle = yaoosl_property_copy(handle->implements[i]->properties[j])))
			{
				return false;
			}
			if (!yaoosl_class_push_property(handle, propertyhandle))
			{
				return false;
			}
		}
	}
	for (i = 0; i < handle->properties_size; i++)
	{
		handle->properties[i]->value_index = i;
		if (handle->properties[i]->get->contents->function != 0)
		{
			handle->properties[i]->get->contents->bytes_size = i;
		}
		if (handle->properties[i]->set->contents->function != 0)
		{
			handle->properties[i]->set->contents->bytes_size = i;
		}
	}
	handle->fin = true;
	return true;
}

int yaoosl_class_is_type(yaooslclasshandle handle_origin, yaooslclasshandle handle_against)
{
	size_t i, j = 1, k;
	if (handle_origin == handle_against)
	{
		return (int)j;
	}
	for (i = 0; i < handle_origin->implements_size; i++, j++)
	{
		k = yaoosl_class_is_type(handle_origin->implements[i], handle_against);
		if (k > 0)
		{
			return (int)(j + k);
		}
	}
	return 0;
}

void yaoosl_property_default_get(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
	struct yaoosl_instance* valuehandle;
	if (self)
	{
		valuehandle = self->fields[method->contents->bytes_size];
		yaoosl_instance_inc_ref(valuehandle);
		yaoosl_context_push_value(context, valuehandle);
	}
	else
	{
		// ToDo: Throw NullPointerException
	}
}
void yaoosl_property_default_set(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
	struct yaoosl_instance* valuehandle;
	struct yaoosl_instance* new_valuehandle;

	if (self)
	{
		new_valuehandle = yaoosl_context_pop_value(context);
		if (!new_valuehandle)
		{
			// ToDo: Throw StackCorruption
			return;
		}
		valuehandle = self->fields[method->contents->bytes_size];
		yaoosl_instance_dec_ref(valuehandle);
		self->fields[method->contents->bytes_size] = new_valuehandle;
	}
	else
	{
		// ToDo: Throw NullPointerException
	}
}
yaooslpropertyhandle yaoosl_property_copy(yaooslpropertyhandle handle)
{
	return yaoosl_property_create2(handle->title, handle->type, handle->get, handle->set);
}
yaooslpropertyhandle yaoosl_property_create(const char* name, yaooslclasshandle type)
{
	yaooslpropertyhandle handle;
	yaooslarghandle arghandle_value;
	yaooslmethodhandle methodhandle_get, methodhandle_set;
	yaooslcodehandle codehandle_get, codehandle_set;

	codehandle_get = yaoosl_code_create();
	if (!codehandle_get)
	{
		return NULL;
	}
	codehandle_set = yaoosl_code_create();
	if (!codehandle_set)
	{
		free(codehandle_get);
		return NULL;
	}
	methodhandle_get = yaoosl_method_create("get", type, codehandle_get);
	if (!methodhandle_get)
	{
		free(codehandle_set);
		free(codehandle_get);
		return NULL;
	}
	methodhandle_set = yaoosl_method_create("set", type, codehandle_set);
	if (!methodhandle_set)
	{
		yaoosl_method_destroy(methodhandle_get);
		free(codehandle_set);
		free(codehandle_get);
		return NULL;
	}
	arghandle_value = yaoosl_arg_create("value", type);
	if (!arghandle_value)
	{
		yaoosl_method_destroy(methodhandle_set);
		yaoosl_method_destroy(methodhandle_get);
		free(codehandle_set);
		free(codehandle_get);
		return NULL;
	}
	if (!yaoosl_method_push_arg(methodhandle_set, arghandle_value))
	{
		yaoosl_arg_destroy(arghandle_value);
		yaoosl_method_destroy(methodhandle_set);
		yaoosl_method_destroy(methodhandle_get);
		free(codehandle_set);
		free(codehandle_get);
		return NULL;
	}

	handle = yaoosl_property_create2(name, type, methodhandle_get, methodhandle_set);
	if (!handle)
	{
		yaoosl_arg_destroy(arghandle_value);
		yaoosl_method_destroy(methodhandle_set);
		yaoosl_method_destroy(methodhandle_get);
		free(codehandle_set);
		free(codehandle_get);
		return NULL;
	}
	codehandle_get->bytes_size = 0;
	codehandle_get->function = yaoosl_property_default_get;
	codehandle_set->bytes_size = 0;
	codehandle_set->function = yaoosl_property_default_set;
	return handle;
}

yaooslpropertyhandle yaoosl_property_create2(const char* name, yaooslclasshandle type, yaooslmethodhandle get, yaooslmethodhandle set)
{
	size_t len;
	yaooslpropertyhandle handle = malloc(sizeof(yaoosl_property));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_property));
		handle->set = set;
		handle->get = get;
		handle->type = type;
		handle->value_index = 0;

		// Set name
		len = strlen(name);
		handle->title = malloc(sizeof(char) * (len + 1));
		if (!handle->title)
		{
			free(handle);
			return NULL;
		}
		strncpy(handle->title, name, len);
		handle->title[len] = '\0';
	}
	return handle;
}
void yaoosl_property_destroy(yaooslpropertyhandle handle)
{
	if (!handle) { return; }
	yaoosl_method_destroy(handle->get);
	yaoosl_method_destroy(handle->set);
	free(handle->title);
	free(handle);
}

bool yaoosl_class_push_method(yaooslclasshandle handle, yaooslmethodhandle method)
{
	size_t i;
	yaooslmethodgrouphandle methodgroup = 0;
	for (i = 0; i < handle->method_groups_size; i++)
	{
		if (!str_cmp(handle->method_groups[i]->title, -1, method->title, -1))
		{
			methodgroup = handle->method_groups[i];
			break;
		}
	}
	if (!methodgroup)
	{
		if (!(methodgroup = yaoosl_method_group_create(method->title)))
		{
			return false;
		}
		if (!yaoosl_class_push_method_group(handle, methodgroup))
		{
			yaoosl_method_group_destroy(methodgroup);
			return false;
		}
	}

	return yaoosl_method_group_push_back(methodgroup, method);
}

bool yaoosl_class_push_operator_method(yaooslclasshandle handle, enum yaoosl_operator op, yaooslmethodhandle method)
{
	yaooslmethodgrouphandle methodgroup = handle->operator_method_groups[op];
	if (!methodgroup)
	{
		methodgroup = handle->operator_method_groups[op] = yaoosl_method_group_create(method->title);
		if (!methodgroup)
		{
			return false;
		}
	}
	return yaoosl_method_group_push_back(methodgroup, method);
}


// Appends the provided base class to the provided handle.
//
// Param 0: The handle that a base should be added onto.
// Param 1: The base that should be added to Param 0.
// Return:  True if all worked, False if something failed (eg. out of memory)
PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(class, yaooslclasshandle, class_handle, yaooslclasshandle, base)
{
	PRINT__YAOOSL_MTHD_PUSH_VALUE_BODY_HEAD(class, yaooslclasshandle, class_handle, yaooslclasshandle, base, implements)
	if (class_handle->sealed)
	{
		return false;
	}
	if ((base->callback_create || base->callback_destroy) && (class_handle->callback_create || class_handle->callback_destroy))
	{
		return false;
	}
	PRINT__YAOOSL_MTHD_PUSH_VALUE_BODY(class, yaooslclasshandle, class_handle, yaooslclasshandle, base, implements)

	if (base->callback_create || base->callback_destroy)
	{
		class_handle->callback_data = base->callback_data;
		class_handle->callback_create = base->callback_create;
		class_handle->callback_destroy = base->callback_destroy;
	}
	return true;
}

// Appends the provided method group to the provided handle.
//
// Param 0: The handle that a method group should be added onto.
// Param 1: The method group that should be added to Param 0.
// Return:  True if all worked, False if something failed (eg. out of memory)
PRINT__YAOOSL_MTHD_PUSH_VALUE(class, yaooslclasshandle, class_handle, yaooslmethodgrouphandle, method_group, method_groups);

// Appends the provided property to the provided handle.
//
// Param 0: The handle that a method group should be added onto.
// Param 1: The property that should be added to Param 0.
// Return:  True if all worked, False if something failed (eg. out of memory)
PRINT__YAOOSL_MTHD_PUSH_VALUE(class, yaooslclasshandle, class_handle, yaooslpropertyhandle, property, properties);