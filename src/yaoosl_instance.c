#include "yaoosl_instance.h"
#include "yaoosl_class.h"

#include <malloc.h>
#include <string.h>

yaooslinstancehandle yaoosl_instance_create(struct yaoosl_class* type)
{
	yaooslinstancehandle handle = malloc(sizeof(yaoosl_instance));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_instance));
		if (type)
		{
			if (!yaoosl_change_type(handle, type))
			{
				free(handle);
				return NULL;
			}
		}
	}
	return handle;
}

bool yaoosl_change_type(yaooslinstancehandle handle, yaoosl_class* type)
{
	unsigned int i;
	if (handle->type)
	{
		return false;
	}
	handle->type = type;
	// Allocate type property slots
	if ((handle->fields_size = handle->type->properties_size) > 0)
	{
		handle->fields = malloc(sizeof(yaoosl_instance*) * handle->fields_size);
		if (!handle->fields)
		{
			return false;
		}
		for (i = 0; i < handle->fields_size; i++)
		{
			if (!(handle->fields[i] = yaoosl_instance_create(NULL)))
			{
				break;
			}
			yaoosl_instance_inc_ref(handle->fields[i]);
		}
		if (i != handle->fields_size)
		{
			for (; i > 0; i--)
			{
				yaoosl_instance_dec_ref(handle->fields[i - 1]);
			}
			free(handle->fields);
			return false;
		}
	}

	// Handle callback
	if (type->callback_create && !type->callback_create(type->callback_data, handle))
	{
		for (i = 0; i < handle->fields_size; i++)
		{
			yaoosl_instance_dec_ref(handle->fields[i - 1]);
		}
		free(handle->fields);
		return false;
	}
	return true;
}

void yaoosl_instance_inc_ref(yaooslinstancehandle handle)
{
	if (!handle) { return; }
	// ToDo: Make this atomic
	handle->ref_count++;
}
void yaoosl_instance_dec_ref(yaooslinstancehandle handle)
{
	if (!handle) { return; }
	// ToDo: Make this atomic
	if (--handle->ref_count == 0)
	{
		yaoosl_instance_destroy(handle);
	}
}

void yaoosl_instance_destroy(yaooslinstancehandle handle)
{
	unsigned int i;
	if (!handle)
	{
		return;
	}

	if (handle->type && handle->type->callback_destroy)
	{
		handle->type->callback_destroy(handle->type->callback_data, handle);
	}
	for (i = 0; i < handle->fields_size; i++)
	{
		 yaoosl_instance_dec_ref(handle->fields[i]);
	}
	free(handle->fields);
	free(handle);
}