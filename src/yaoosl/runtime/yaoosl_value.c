#include "yaoosl_value.h"
#include <malloc.h>
#include <string.h>

yaoosl_class* create_yaoosl_class(enum yaoosl_encapsulation encapsulation, const char* ns, const char* name)
{
    yaoosl_class* type;
    size_t ns_len = strlen(ns);
    size_t name_len = strlen(name);
    type = malloc(sizeof(yaoosl_class) + (sizeof(char) * (ns_len + 1)) + (sizeof(char) * (name_len + 1)));
    if (type)
    {
        type->full_namespace = ((void*)type) + sizeof(yaoosl_class);
        type->name = ((void*)type) + sizeof(yaoosl_class) + (sizeof(char) * (ns_len + 1));
        strncpy(type->full_namespace, ns, ns_len);
        strncpy(type->name, name, name_len);
        type->encapsulation = encapsulation;
    }
    return type;
}