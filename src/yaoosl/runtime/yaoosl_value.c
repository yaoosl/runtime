#include "yaoosl_value.h"
#include <malloc.h>
#include <string.h>

yaoosl_classtemplate* create_yaoosl_classtemplate(enum yaoosl_encapsulation encapsulation, const char* ns, const char* name)
{
    yaoosl_classtemplate* type;
    size_t ns_len = strlen(ns);
    size_t name_len = strlen(name);
    type = malloc(sizeof(yaoosl_classtemplate) + (sizeof(char) * (ns_len + 1)) + (sizeof(char) * (name_len + 1)));
    if (type)
    {
        type->full_namespace = ((uint8_t*)type) + sizeof(yaoosl_classtemplate);
        type->name = ((uint8_t*)type) + sizeof(yaoosl_classtemplate) + (sizeof(char) * (ns_len + 1));
        strncpy(type->full_namespace, ns, ns_len);
        strncpy(type->name, name, name_len);
        type->encapsulation = encapsulation;
    }
    return type;
}