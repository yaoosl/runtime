#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "string_map.h"
#include "string_op.h"

extern inline void* yaoosl_map_get_value(yaoosl_map_list* list, const char* name);
extern inline void* yaoosl_map_set_value(yaoosl_map_list* list, const char* name, void* value);
extern inline void* yaoosl_map_drop_value(yaoosl_map_list* list, const char* name);



void yaoosl_map_no_destroy(void* ptr)
{
}

yaoosl_map_bucket* yaoosl_map_create_bucket()
{
	yaoosl_map_bucket* bucket = malloc(sizeof(yaoosl_map_bucket));
	if (bucket)
	{
		bucket->names = NULL;
		bucket->values = NULL;
		bucket->size = 0;
		bucket->top = 0;
	}
	return bucket;
}
void yaoosl_map_destroy_bucket(yaoosl_map_bucket* bucket, void(*destroy_ptr)(void*))
{
	int i;
	if (destroy_ptr == 0)
	{
		for (i = 0; i < (int)bucket->top; i++)
		{
			free(bucket->names[i]);
		}
	}
	else
	{
		for (i = 0; i < (int)bucket->top; i++)
		{
			destroy_ptr(bucket->values[i]);
			free(bucket->names[i]);
		}
	}
	free(bucket->names);
	free(bucket->values);
	free(bucket);
}
bool yaoosl_map_grow_bucket(yaoosl_map_bucket* bucket)
{
	char** names = realloc(bucket->names, sizeof(char*) * (bucket->size * bucket->size + 1));
	void** values = realloc(bucket->values, sizeof(void*) * (bucket->size * bucket->size + 1));

	if (names != 0)
	{
		bucket->names = names;
	}
	if (values != 0)
	{
		bucket->values = values;
	}
	if (names != 0 && values != 0)
	{
		bucket->size = bucket->size * bucket->size + 1;
		return true;
	}
	else
	{
		return false;
	}
}

yaoosl_map_list* yaoosl_map_create_list(unsigned int bucketcount)
{
	yaoosl_map_list* list = malloc(sizeof(yaoosl_map_list));
	int i;
	bool fail = false;
	if (list)
	{
		list->buckets = malloc(sizeof(yaoosl_map_bucket*) * bucketcount);
		if (!list->buckets)
		{
			free(list);
			return NULL;
		}
		list->buckets_size = bucketcount;

		for (i = 0; i < (int)bucketcount; i++)
		{
			if (!(list->buckets[i] = yaoosl_map_create_bucket()))
			{
				fail = true;
				break;
			}
		}
		if (fail)
		{
			for (i--;i >= 0; i--)
			{
				yaoosl_map_destroy_bucket(list->buckets[i], NULL);
			}
			free(list);
			return NULL;
		}
	}
	return list;
}
void yaoosl_map_destroy_list(yaoosl_map_list* list, void(*destroy_ptr)(void*))
{
	int i;
	for (i = 0; i < (int)list->buckets_size; i++)
	{
		yaoosl_map_destroy_bucket(list->buckets[i], destroy_ptr);
	}
	free(list->buckets);
	free(list);
}

yaoosl_map_bucket* yaoosl_map_get_bucket_for(yaoosl_map_list* list, const char* name)
{
	unsigned int hash = 1;
	int i;
	for (i = 0; name[i] != '\0'; i++)
	{
		hash += tolower(name[i]) * 2.0 * (double)hash;
		hash >>= 1;
	}
	hash %= list->buckets_size;
	return list->buckets[hash];
}
void* yaoosl_map_get_value_from_bucket(yaoosl_map_bucket* bucket, const char* name)
{
	int i;
	for (i = 0; i < (int)bucket->top; i++)
	{
		if (!str_cmpi(bucket->names[i], -1, name, -1))
		{
			return bucket->values[i];
		}
	}
	return 0;
}
void* yaoosl_map_set_value_in_bucket(yaoosl_map_bucket* bucket, const char* name, void* value)
{
	int i;
	void* val;
	char* str;
	for (i = 0; i < (int)bucket->top; i++)
	{
		if (!str_cmpi(bucket->names[i], -1, name, -1))
		{
			val = bucket->values[i];
			bucket->values[i] = value;
			return val;
		}
	}
	if (bucket->top == bucket->size)
	{
		yaoosl_map_grow_bucket(bucket);
	}
	i = strlen(name);
	str = malloc(sizeof(char) * (i + 1));
	if (str)
	{
		bucket->values[bucket->top] = value;
		strcpy(str, name);
		str[i] = '\0';
		bucket->names[bucket->top] = str;
		bucket->top++;
	}
	return 0;
}

void* yaoosl_map_drop_value_from_bucket(yaoosl_map_bucket* bucket, const char* name)
{
	int i;
	bool value_found = false;
	void* val = 0;
	for (i = 0; i < (int)bucket->top; i++)
	{
		if (value_found)
		{
			bucket->values[i - 1] = bucket->values[i];
			bucket->names[i - 1] = bucket->names[i];
		}
		else
		{
			if (!str_cmpi(bucket->names[i], -1, name, -1))
			{
				val = bucket->values[i];
				free(bucket->names[i]);
				value_found = true;
			}
		}
	}
	if (val != 0)
	{
		bucket->top--;
	}
	return val;
}

unsigned int yaoosl_map_count(yaoosl_map_list* list)
{
	unsigned int count = 0;
	int i;
	yaoosl_map_bucket* cur;
	for (i = 0; i < (int)list->buckets_size; i++)
	{
		cur = list->buckets[i];
		count += cur->top;
	}
	return count;
}
void* yaoosl_map_get_value_index(yaoosl_map_list* list, unsigned int index)
{
	unsigned int count = 0;
	int i;
	yaoosl_map_bucket* cur;
	for (i = 0; i < (int)list->buckets_size; i++)
	{
		cur = list->buckets[i];
		count += cur->top;
		if (count > index)
		{
			count -= cur->top;
			index -= count;
			return cur->values[index];
		}
	}
	return 0;
}
char* yaoosl_map_get_name_index(yaoosl_map_list* list, unsigned int index)
{
	unsigned int count = 0;
	int i;
	yaoosl_map_bucket* cur;
	for (i = 0; i < (int)list->buckets_size; i++)
	{
		cur = list->buckets[i];
		count += cur->top;
		if (count > index)
		{
			count -= cur->top;
			index -= count;
			return cur->names[index];
		}
	}
	return 0;
}