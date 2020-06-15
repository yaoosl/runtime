#include "yaoosl_value.h"
#include <malloc.h>
#include <string.h>

yaoosl_classtemplate* yaoosl_classtemplate_create(struct yaoosl_code_page* owner, enum yaoosl_encapsulation encapsulation, const char* ns, const char* name)
{
    yaoosl_classtemplate* type;
    size_t ns_len = strlen(ns);
    size_t name_len = strlen(name);
    type = malloc(sizeof(yaoosl_classtemplate) + (sizeof(char) * (ns_len + 1)) + (sizeof(char) * (name_len + 1)));
    if (type)
    {
        type->declaring_code_page = owner;
        type->full_namespace = ((uint8_t*)type) + sizeof(yaoosl_classtemplate);
        type->name = ((uint8_t*)type) + sizeof(yaoosl_classtemplate) + (sizeof(char) * (ns_len + 1));
        strncpy(type->full_namespace, ns, ns_len);
        strncpy(type->name, name, name_len);
        type->encapsulation = encapsulation;
    }
    return type;
}

void yaoosl_classtemplate_destroy(yaoosl_classtemplate* classtemplate)
{
    size_t i;
    if (classtemplate->encapsulation == YENCPS_DUMMY)
    {
        free(classtemplate->full_namespace);
        free(classtemplate->name);
    }
    for (i = 0; i < classtemplate->methods_size; i++)
    {
        yaoosl_method_group_destroy(classtemplate->methods[i]);
    }
    // Following is not needed right now. 
    // for (i = 0; i < classtemplate->properties_size; i++)
    // {
    //     yaoosl_property_destroy(classtemplate->properties[i]);
    // }
    free(classtemplate->implements);
    free(classtemplate->methods);
    free(classtemplate->properties);
    free(classtemplate);
}

void yaoosl_method_group_destroy(yaoosl_method_group method_group)
{
    size_t i;
    for (i = 0; i < method_group.method_size; i++)
    {
        yaoosl_method_destroy(method_group.method[i]);
    }
    free(method_group.name);
}

void yaoosl_method_destroy(yaoosl_method method)
{
    size_t i;
    for (i = 0; i < method.args_size; i++)
    {
        yaoosl_arg_destroy(method.args[i]);
    }
    free(method.args);
}

void yaoosl_arg_destroy(yaoosl_arg arg)
{
    free(arg.name);
}
