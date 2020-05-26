#pragma once
#ifndef _STRING_MAP_H_
#define _STRING_MAP_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct yaoosl_map_bucket
{
	char** names;
	void** values;
	unsigned int size;
	unsigned int top;
} yaoosl_map_bucket;
typedef struct yaoosl_map_list
{
	yaoosl_map_bucket** buckets;
	unsigned int buckets_size;
} yaoosl_map_list;

void yaoosl_map_no_destroy(void*);

/*
Creates a new yaoosl_map_bucket on HEAP and returns a pointer to it.

param 1: initial size of the bucket
param 2: the ammount of slots the bucket should grow when yaoosl_map_grow_bucket is called
*/
yaoosl_map_bucket* yaoosl_map_create_bucket();
/*
Destroys provided bucket and frees all memory associated with it (pointer passed in param 1 will get invalid).

param 1: valid pointer to a bucket allocated by yaoosl_map_create_bucket
param 2: optional function to call when destroying values. If not required, pass NULL
*/
void yaoosl_map_destroy_bucket(yaoosl_map_bucket* bucket, void(*destroy_ptr)(void*));
/*
Increases amount of slots available in given bucket.

param 1: pointer to the bucket to increase
*/
bool yaoosl_map_grow_bucket(yaoosl_map_bucket* bucket);

/*
Creates a new list containing given amount of buckets where each bucket will have provided size and growth.

param 1: the total bucket count of this list.
param 2: the initial size of each bucket.
param 3: the growth of each bucket.
*/
yaoosl_map_list* yaoosl_map_create_list(unsigned int bucketcount);
/*
Destroys provided list and all buckets it contains.
All memory associated with it will be freed (pointer passed in param 1 will get invalid).

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: optional function to call when destroying values. If not required, pass NULL
*/
void yaoosl_map_destroy_list(yaoosl_map_list* list, void(*destroy_ptr)(void*));

/*
Received correct bucket for provided name.

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: \0 terminated string as identifier
*/
yaoosl_map_bucket* yaoosl_map_get_bucket_for(yaoosl_map_list* list, const char* name);

/*
Searches for the provided name in given bucket and returns the value.
If nothing is found, a NULL pointer will be returned.

param 1: valid pointer to a bucket allocated by yaoosl_map_create_bucket
param 2: \0 terminated string as identifier
*/
void* yaoosl_map_get_value_from_bucket(yaoosl_map_bucket* bucket, const char* name);

/*
Searches for the provided name in given bucket and drops it.
All indexes above it will be shifted by one down.
returns the value.
If nothing is found, a NULL pointer will be returned.

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: \0 terminated string as identifier
*/
void* yaoosl_map_drop_value_from_bucket(yaoosl_map_bucket* bucket, const char* name);
/*
Searches for the provided name in given bucket and sets the value slot for the name to given value.
If there was already a value at that spot, it will be returned.
In any other case, NULL is returned.

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: \0 terminated string as identifier
param 3: pointer to the value to set
*/
inline void* yaoosl_map_get_value(yaoosl_map_list* list, const char* name)
{
	return yaoosl_map_get_value_from_bucket(yaoosl_map_get_bucket_for(list, name), name);
}
/*
Searches for the provided name in given bucket and drops it.
All indexes above it will be shifted by one down.
returns the value.
If nothing is found, a NULL pointer will be returned.

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: \0 terminated string as identifier
*/
inline void* yaoosl_map_drop_value(yaoosl_map_list* list, const char* name)
{
	return yaoosl_map_drop_value_from_bucket(yaoosl_map_get_bucket_for(list, name), name);
}
/*
Searches for the provided name in given bucket and sets the value slot for the name to given value.
If there was already a value at that spot, it will be returned.
In any other case, NULL is returned.

param 1: valid pointer to a bucket allocated by yaoosl_map_create_bucket
param 2: \0 terminated string as identifier
param 3: pointer to the value to set
*/
void* yaoosl_map_set_value_in_bucket(yaoosl_map_bucket* bucket, const char* name, void* value);
/*
Searches for the provided name in given lists buckets and sets the value slot for the name to given value.
If there was already a value at that spot, it will be returned.
In any other case, NULL is returned.

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: \0 terminated string as identifier
param 3: pointer to the value to set
*/
inline void* yaoosl_map_set_value(yaoosl_map_list* list, const char* name, void* value)
{
	return yaoosl_map_set_value_in_bucket(yaoosl_map_get_bucket_for(list, name), name, value);
}

/*
Gets the total item count in provided list.

param 1: valid pointer to a list allocated by yaoosl_map_create_list
*/
unsigned int yaoosl_map_count(yaoosl_map_list* list);
/*
Receives an item via index from provided list.
Indexes might change when new items are added!
Only should be used for enumeration.
Returns 0 if index was too large;

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: Current index of enumeration
*/
void* yaoosl_map_get_value_index(yaoosl_map_list* list, unsigned int index);
/*
Receives an items name via index from provided list.
Indexes might change when new items are added!
Only should be used for enumeration.
Returns 0 if index was too large;

param 1: valid pointer to a list allocated by yaoosl_map_create_list
param 2: Current index of enumeration
*/
char* yaoosl_map_get_name_index(yaoosl_map_list* list, unsigned int index);


#endif // !_STRING_MAP_H_




#ifdef __cplusplus
}
#endif // __cplusplus