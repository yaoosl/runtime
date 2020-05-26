#include "yaoosl.h"
#include "string_map.h"
#include "string_op.h"
#include "yaoosl_code.h"
#include "yaoosl_instance.h"
#include "yaoosl_method.h"
#include "yaoosl_util.h"
#include "yaoosl_class.h"
#include "yaoosl_opcodes.h"
#include "yaoosl_operators.h"
#include "yaoosl_context.h"
#include "yaoosl_util_macros.h"
#include "yaoosl_std.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


#define ERR_MSG_NO_VALUE_PRESENT "Stack Corruption. No Value Present."
#define ERR_MSG_SCOPE_HAS_NO_BLOCKS "VM Corruption. Scope Has No Blocks."
#define ERR_MSG_CONTEXT_HAS_NO_SCOPE "VM Corruption. Context Has No Scope."
#define ERR_MSG_TYPE_MISSMATCH_TYPE "Stack Corruption. Value Provided Is No Type."
#define ERR_MSG_TYPE_MISSMATCH_BOOLEAN "Stack Corruption. Value Provided Is No Boolean."
#define ERR_MSG_TYPE_MISSMATCH_STRING "Stack Corruption. Value Provided Is No String."
#define ERR_MSG_TYPE_MISSMATCH_EXCEPTION "Stack Corruption. Value Provided Is No Exception."
#define ERR_MSG_LOCAL_OUT_OF_RANGE "Stack Corruption. Local Out Of Range."
#define ERR_MSG_STRING_EMPTY "VM Corruption. String Provided Materializes To NULL Pointer."
#define ERR_MSG_OUT_OF_MEMORY "Out Of Memory."
#define ERR_MSG_CLASS_CONSTRUCTION_IN_PROGRES "Stack Corruption. Class Creation Already In Progress."
#define ERR_MSG_CLASS_CONSTRUCTION_NOT_STARTED "Stack Corruption. No Class Creation In Progress."
#define ERR_MSG_CLASS_CONSTRUCTION_END_BLOCKED "Stack Corruption. Cannot End Class Creation As Property Or Method Creation In Progress."
#define ERR_MSG_METHOD_CONSTRUCTION_IN_PROGRES "Stack Corruption. Method Creation Already In Progress."
#define ERR_MSG_METHOD_CONSTRUCTION_NOT_STARTED "Stack Corruption. No Method Creation In Progress."
#define ERR_MSG_PROPERTY_CONSTRUCTION_IN_PROGRES "Stack Corruption. Property Creation Already In Progress."
#define ERR_MSG_PROPERTY_CONSTRUCTION_NOT_STARTED "Stack Corruption. No Property Creation In Progress."
#define ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE "Stack Corruption. Code Construction Incomplete."
#define ERR_MSG_NULL_VALUE "Stack Corruption. Null Value Provided."
#define ERR_MSG_PROPERTY_NOT_FOUND "Stack Corruption. Property Not Found."
#define ERR_MSG_METHOD_NOT_FOUND "Stack Corruption. Method Not Found."
#define ERR_MSG_OPERATOR_NOT_FOUND "Stack Corruption. Operator Not Found."
#define ERR_MSG_CLASS_NOT_FOUND "Stack Corruption. Class Not Found."
#define ERR_MSG_VALUE_STACK_COUNT_MISSMATCH "Stack Corruption. Value Stack Count Missmatch."

void yaoosl_mthd_object_to_string(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    size_t len;
    char* str;
    if (self)
    {
        // Build types full name
        len = 2;
        len += strlen(self->type->fullname);
        str = alloca(sizeof(char) * (len + 1));
        str[0] = '{';
        str[len - 1] = '}';
        str[len] = '\0';
        len = 1;
        strncpy(str + 1, self->type->fullname, strlen(self->type->fullname));
        if (!yaoosl_util_push_string(vm, context, self->type->fullname))
        {
            // ToDo: Throw OutOfMemoryException
            return;
        }
    }
    else
    {
        // ToDo: Throw NullPointerException
    }
}
void yaoosl_mthd_object_get_type(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    yaooslinstancehandle type;
    if (self)
    {
        if (!(type = yaoosl_instance_create(vm->classes[TYPE])))
        {
            // ToDo: Throw OutOfMemoryException
            return;
        }
        yaoosl_instance_inc_ref(type);
        if (!yaoosl_context_push_value(context, type))
        {
            yaoosl_instance_dec_ref(type);
            // ToDo: Throw OutOfMemoryException
            return;
        }
    }
    else
    {
        // ToDo: Throw NullPointerException
    }
}


void yaoosl_mthd_string_destroy(void* data, struct yaoosl_instance* self)
{
    if (self->additional.ptr)
    {
        free(self->additional.ptr);
    }
}
void yaoosl_mthd_array_destroy(void* data, struct yaoosl_instance* self)
{
    size_t i;
    for (i = 0; i < self->fields[yaoosl_knowntypes_propertyindex_array_Length]->additional.int32; i++)
    {
        yaoosl_instance_dec_ref(((yaooslinstancehandle*)self->additional.ptr)[i]);
    }
    if (self->additional.ptr)
    {
        free(self->additional.ptr);
    }
}
void yaoosl_mthd_console_write(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    yaooslinstancehandle instance;
    if (!(instance = yaoosl_context_pop_value(context)))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_NO_VALUE_PRESENT);
        return;
    }
    if (!(instance->type == vm->classes[STRING]))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_TYPE_MISSMATCH_STRING);
        return;
    }
    printf("%s", instance->additional.str);
    if (!yaoosl_util_push_null(context))
    {
        // ToDo: Throw OutOfMemoryException
        return;
    }
}
void yaoosl_mthd_console_writeline(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    yaooslinstancehandle instance;
    if (!(instance = yaoosl_context_pop_value(context)))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_NO_VALUE_PRESENT);
        return;
    }
    if (!(instance->type == vm->classes[STRING]))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_TYPE_MISSMATCH_STRING);
        return;
    }
    printf("%s\n", instance->additional.str);
    if (!yaoosl_util_push_null(context))
    {
        // ToDo: Throw OutOfMemoryException
        return;
    }
}

bool yaoosl_register_known_classes(yaooslhandle vm)
{
    // ToDo: Check all return values to prevent out-of-memory exception.
    yaooslclasshandle classhandle_object, classhandle_array, classhandle_boolean, classhandle_char, classhandle_string, classhandle_type, classhandle_method;


    // Object - MethodGroup - ToString
    yaooslmethodgrouphandle mg_tostring;
    yaooslcodehandle code_tostring;
    yaooslmethodhandle m_tostring;
    // Object - Methodgroup - GetType
    yaooslmethodgrouphandle mg_gettype;
    yaooslcodehandle code_gettype;
    yaooslmethodhandle m_gettype;


    classhandle_object = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "Object");
    classhandle_array = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "Array");
    classhandle_boolean = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "Boolean");
    classhandle_char = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "Char");
    classhandle_string = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "String");
    classhandle_type = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "Type");
    classhandle_method = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "Method");


    // Object - MethodGroup - ToString
    mg_tostring = yaoosl_method_group_create("ToString");
    code_tostring = yaoosl_code_create();
    m_tostring = yaoosl_method_create("ToString", classhandle_string, code_tostring);
    // Object - Methodgroup - GetType
    mg_gettype = yaoosl_method_group_create("GetType");
    code_gettype = yaoosl_code_create();
    m_gettype = yaoosl_method_create("GetType", classhandle_type, code_gettype);



    code_tostring->function = yaoosl_mthd_object_to_string;
    code_tostring->bytes_size = 0;
    yaoosl_method_group_push_back(mg_tostring, m_tostring);
    yaoosl_class_push_method_group(classhandle_object, mg_tostring);

    code_gettype->function = yaoosl_mthd_object_get_type;
    code_gettype->bytes_size = 0;
    yaoosl_method_group_push_back(mg_gettype, m_gettype);
    yaoosl_class_push_method_group(classhandle_object, mg_gettype);


    yaoosl_class_push_property(classhandle_array, yaoosl_property_create("Type", vm->classes[TYPE]));
    yaoosl_class_push_property(classhandle_array, yaoosl_property_create("Length", vm->classes[INT32]));

    classhandle_string->callback_destroy = yaoosl_mthd_string_destroy;
    classhandle_array->callback_destroy = yaoosl_mthd_array_destroy;

    yaoosl_class_push_base(classhandle_array, classhandle_object);
    yaoosl_class_push_base(classhandle_boolean, classhandle_object);
    yaoosl_class_push_base(classhandle_char, classhandle_object);
    yaoosl_class_push_base(classhandle_string, classhandle_object);
    yaoosl_class_push_base(classhandle_type, classhandle_object);
    yaoosl_class_push_base(classhandle_method, classhandle_object);

    classhandle_array->sealed = true;
    classhandle_boolean->sealed = true;
    classhandle_char->sealed = true;
    classhandle_string->sealed = true;
    classhandle_type->sealed = true;
    classhandle_method->sealed = true;
    yaoosl_class_finalize(classhandle_array);
    yaoosl_class_finalize(classhandle_boolean);
    yaoosl_class_finalize(classhandle_char);
    yaoosl_class_finalize(classhandle_string);
    yaoosl_class_finalize(classhandle_type);
    yaoosl_class_finalize(classhandle_method);


    return yaoosl_std_register_integral_classes(vm);
}

void yaoosl_register_console_class(yaooslhandle vm)
{
    yaooslclasshandle classhandle = yaoosl_class_create(yaoosl_STD_NAMESPACE_STR_PREFIX "Console");
    yaooslmethodgrouphandle mg_Write = yaoosl_method_group_create("Write");
    yaooslmethodgrouphandle mg_WriteLine = yaoosl_method_group_create("WriteLine");
    yaooslcodehandle c_Write = yaoosl_code_create2(yaoosl_mthd_console_write);
    yaooslcodehandle c_WriteLine = yaoosl_code_create2(yaoosl_mthd_console_writeline);
    yaooslarghandle a_Write_String = yaoosl_arg_create("value", vm->classes[STRING]);
    yaooslarghandle a_WriteLine_String = yaoosl_arg_create("value", vm->classes[STRING]);
    yaooslmethodhandle m_Write = yaoosl_method_create("Write", NULL, c_Write);
    yaooslmethodhandle m_WriteLine = yaoosl_method_create("WriteLine", NULL, c_WriteLine);

    yaoosl_method_push_arg(m_Write, a_Write_String);
    yaoosl_method_group_push_back(mg_Write, m_Write);
    yaoosl_class_push_method_group(classhandle, mg_Write);

    yaoosl_method_push_arg(m_WriteLine, a_WriteLine_String);
    yaoosl_method_group_push_back(mg_WriteLine, m_WriteLine);
    yaoosl_class_push_method_group(classhandle, mg_WriteLine);


    yaoosl_push_class(vm, classhandle);
}

static void yaoosl_mthd_exception_construct_empty(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    // Return this pointer
    yaoosl_context_push_value(context, self);
}
static void yaoosl_mthd_exception_construct_string(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    yaooslinstancehandle message;
    // Receive values R->L

    if (!(message = yaoosl_context_pop_value(context)))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_NO_VALUE_PRESENT);
        return;
    }
    if (!(message->type == vm->classes[STRING]))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_TYPE_MISSMATCH_STRING);
        return;
    }

    // Assign exception fields
    yaoosl_instance_dec_ref(self->fields[yaoosl_knowntypes_propertyindex_exception_Message]);
    yaoosl_instance_inc_ref(message);
    self->fields[yaoosl_knowntypes_propertyindex_exception_Message] = message;

    // Return this pointer
    yaoosl_context_push_value(context, self);
}
static void yaoosl_mthd_exception_construct_string_inner(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    yaooslinstancehandle message, innerException;
    // Receive values R->L
    if (!(innerException = yaoosl_context_pop_value(context)))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_NO_VALUE_PRESENT);
        return;
    }
    if (!(innerException->type == vm->classes[EXCEPTION_CLASS]))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_TYPE_MISSMATCH_EXCEPTION);
        return;
    }

    if (!(message = yaoosl_context_pop_value(context)))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_NO_VALUE_PRESENT);
        return;
    }
    if (!(message->type == vm->classes[STRING]))
    {
        yaoosl_util_throw_generic(vm, context, ERR_MSG_TYPE_MISSMATCH_STRING);
        return;
    }

    // Assign exception fields
    yaoosl_instance_dec_ref(self->fields[yaoosl_knowntypes_propertyindex_exception_Message]);
    yaoosl_instance_dec_ref(self->fields[yaoosl_knowntypes_propertyindex_exception_InnerException]);
    yaoosl_instance_inc_ref(message);
    yaoosl_instance_inc_ref(innerException);
    self->fields[yaoosl_knowntypes_propertyindex_exception_Message] = message;
    self->fields[yaoosl_knowntypes_propertyindex_exception_InnerException] = innerException;

    // Return this pointer
    yaoosl_context_push_value(context, self);
}

void yaoosl_register_exception_class(yaooslhandle vm)
{
    yaooslclasshandle classhandle_exception = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "Exception");
    yaooslclasshandle classhandle_stackframe = yaoosl_declare_class(vm, yaoosl_STD_NAMESPACE_STR_PREFIX "StackFrame");
    yaooslmethodgrouphandle mgc_exception = yaoosl_method_group_create("Exception");

    yaooslcodehandle c_exception_empty = yaoosl_code_create2(yaoosl_mthd_exception_construct_empty);
    yaooslmethodhandle mc_exception_empty = yaoosl_method_create("Exception", classhandle_exception, c_exception_empty);

    yaooslcodehandle c_exception_string = yaoosl_code_create2(yaoosl_mthd_exception_construct_string);
    yaooslarghandle a_exception_string_1 = yaoosl_arg_create("message", vm->classes[STRING]);
    yaooslmethodhandle mc_exception_string = yaoosl_method_create("Exception", classhandle_exception, c_exception_string);

    yaooslcodehandle c_exception_string_inner = yaoosl_code_create2(yaoosl_mthd_exception_construct_string_inner);
    yaooslarghandle a_exception_string_inner_1 = yaoosl_arg_create("message", vm->classes[STRING]);
    yaooslarghandle a_exception_string_inner_2 = yaoosl_arg_create("innerException", classhandle_exception);
    yaooslmethodhandle mc_exception_string_inner = yaoosl_method_create("Exception", classhandle_exception, c_exception_string_inner);


    yaoosl_method_group_push_back(mgc_exception, mc_exception_empty);

    yaoosl_method_push_arg(mc_exception_string, a_exception_string_1);
    yaoosl_method_group_push_back(mgc_exception, mc_exception_string);

    yaoosl_method_push_arg(mc_exception_string_inner, a_exception_string_inner_1);
    yaoosl_method_push_arg(mc_exception_string_inner, a_exception_string_inner_2);
    yaoosl_method_group_push_back(mgc_exception, mc_exception_string_inner);

    yaoosl_class_push_property(classhandle_exception, yaoosl_property_create("Message", vm->classes[STRING]));
    yaoosl_class_push_property(classhandle_exception, yaoosl_property_create("InnerException", classhandle_exception));
    yaoosl_class_push_property(classhandle_exception, yaoosl_property_create("Frames", vm->classes[ARRAY]));

    yaoosl_class_push_property(classhandle_stackframe, yaoosl_property_create("Method", vm->classes[METHOD]));
    yaoosl_class_push_property(classhandle_stackframe, yaoosl_property_create("Line", vm->classes[INT32]));
    yaoosl_class_push_property(classhandle_stackframe, yaoosl_property_create("Column", vm->classes[INT32]));
    yaoosl_class_push_property(classhandle_stackframe, yaoosl_property_create("File", vm->classes[STRING]));

    classhandle_stackframe->sealed = true;
    classhandle_exception->constructor_method_group = mgc_exception;


    yaoosl_class_push_base(classhandle_exception, vm->classes[OBJECT]);
    yaoosl_class_push_base(classhandle_stackframe, vm->classes[OBJECT]);


    yaoosl_class_finalize(classhandle_exception);
    yaoosl_class_finalize(classhandle_stackframe);
}

bool yaoosl_default_error_handle(struct yaoosl* vm, struct yaoosl_context* context, const char* errmsg)
{
    printf("!!! FATAL ERROR !!!\n%s\n", errmsg);
    return false;
}

#define YS_CREATE_VM_EX_CLEANUP(test) if (!(test)) {\
    for (i = 0; i < handle->classes_size; i++)\
    {\
        yaoosl_class_destroy(handle->classes[i]);\
    }\
    yaoosl_map_destroy_list(handle->classes_map, yaoosl_map_no_destroy);\
    free(handle->classes);\
    return NULL;\
}
yaooslhandle yaoosl_create_virtualmachine()
{
    yaooslhandle handle;
    size_t i;
    handle = malloc(sizeof(yaoosl));
    if (handle)
    {
        memset(handle, 0, sizeof(yaoosl));
        if (!(handle->classes_map = yaoosl_map_create_list(32)))
        {
            free(handle);
            return NULL;
        }

        handle->error_handle = yaoosl_default_error_handle;
        handle->classes = 0;
        handle->classes_capacity = 0;
        handle->classes_size = 0;
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Object"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Array"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Uint8"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Int8"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Uint16"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Int16"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Uint32"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Int32"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Uint64"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Int64"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Float"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Double"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Boolean"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Char"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "String"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Type"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Method"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "Exception"));
        YS_CREATE_VM_EX_CLEANUP(yaoosl_declare_class(handle, yaoosl_STD_NAMESPACE_STR_PREFIX "StackFrame"));

        yaoosl_register_known_classes(handle);
        yaoosl_register_exception_class(handle);
        yaoosl_register_console_class(handle);
    }
    return handle;
}


bool yaoosl_destroy_virtualmachine(yaooslhandle handle)
{
    unsigned int i;
    if (handle)
    {
        yaoosl_map_destroy_list(handle->classes_map, yaoosl_map_no_destroy);
        for (i = 0; i < handle->classes_size; i++)
        {
            yaoosl_class_destroy(handle->classes[i]);
        }
        free(handle->classes);
    }
    free(handle);
    return true;
}
bool yaoosl_push_class(yaooslhandle yaoosl, struct yaoosl_class* classhandle)
{
    yaooslclasshandle* class_handles;
    if (!yaoosl || !classhandle || !yaoosl_class_finalize(classhandle))
    {
        return false;
    }
    yaoosl_map_set_value(yaoosl->classes_map, classhandle->fullname, classhandle);
    if (yaoosl->classes_size == yaoosl->classes_capacity)
    {
        class_handles = realloc(yaoosl->classes, sizeof(yaooslclasshandle) * (yaoosl->classes_capacity * yaoosl->classes_capacity + 1));
        if (!class_handles)
        {
            return false;
        }
        yaoosl->classes = class_handles;
        yaoosl->classes_capacity = yaoosl->classes_capacity * yaoosl->classes_capacity + 1;
    }
    yaoosl->classes[yaoosl->classes_size++] = classhandle;
    return true;
}
struct yaoosl_class* yaoosl_declare_class(yaooslhandle yaoosl, const char* classname)
{
    yaooslclasshandle classhandle = 0;
    yaooslclasshandle* class_handles;
    if (yaoosl && classname)
    {
        classhandle = yaoosl_map_get_value(yaoosl->classes_map, classname);
        if (!classhandle)
        {
            if (yaoosl->classes_size == yaoosl->classes_capacity)
            {
                class_handles = realloc(yaoosl->classes, sizeof(yaooslclasshandle) * (yaoosl->classes_capacity * yaoosl->classes_capacity + 1));
                if (!class_handles)
                {
                    return NULL;
                }
                yaoosl->classes = class_handles;
                yaoosl->classes_capacity = yaoosl->classes_capacity * yaoosl->classes_capacity + 1;
            }
            classhandle = yaoosl_class_create(classname);
            if (!classhandle)
            {
                return NULL;
            }
            yaoosl_map_set_value(yaoosl->classes_map, classhandle->fullname, classhandle);
            yaoosl->classes[yaoosl->classes_size++] = classhandle;
        }
    }
    return classhandle;
}

#define EXEC_ASSERT(CODE, ERRMSG)\
if (!(CODE))\
{\
    YAOOSL_FORCE_BREAK();\
    vm->error_handle(vm, context, ERRMSG);\
    error_ok = false;\
    break;\
}
#define EXEC_ASSERT2(CODE, ERRMSG, HANDLE)\
if (!(CODE))\
{\
    YAOOSL_FORCE_BREAK();\
    vm->error_handle(vm, context, ERRMSG);\
    error_ok = false;\
    HANDLE;\
    break;\
}

#define EXEC_STR_COPY_FROM_VALUE(TARGET)\
EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);\
EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[STRING]), ERR_MSG_TYPE_MISSMATCH_STRING, yaoosl_instance_dec_ref(valuehandle));\
EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_STRING_EMPTY, yaoosl_instance_dec_ref(valuehandle));\
i = strlen(((char*)valuehandle->additional.ptr));\
EXEC_ASSERT2(ptr = realloc(TARGET, sizeof(char) * (i + 1)), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));\
TARGET = ptr;\
strncpy(TARGET, valuehandle->additional.ptr, i);\
TARGET[i] = '\0';\
yaoosl_instance_dec_ref(valuehandle);

#define EXEC_STR_ALLOC_FROM_VALUE()\
EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);\
EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[STRING]), ERR_MSG_TYPE_MISSMATCH_STRING, yaoosl_instance_dec_ref(valuehandle));\
EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_STRING_EMPTY, yaoosl_instance_dec_ref(valuehandle));\
i = strlen(((char*)valuehandle->additional.ptr));\
EXEC_ASSERT2(str = malloc(sizeof(char) * (i + 1)), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));\
strncpy(str, valuehandle->additional.ptr, i);\
str[i] = '\0';\
yaoosl_instance_dec_ref(valuehandle);

#define EXEC_READ_X64(VAR, TYPE)\
VAR =\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 7)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 6)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 5)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 4)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 3)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 2)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 1)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 0))
#define EXEC_READ_X32(VAR, TYPE)\
VAR =\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 3)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 2)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 1)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 0))
#define EXEC_READ_X16(VAR, TYPE)\
VAR =\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 1)) |\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 0))
#define EXEC_READ_X8(VAR, TYPE)\
VAR =\
    ((TYPE)yaoosl_context_next(context, &error_ok) << (8 * 0))

#define EXEC_READ_UINT64 EXEC_READ_X64(uint64, uint64_t)
#define EXEC_READ_INT64 EXEC_READ_X64(int64, int64_t)
#define EXEC_READ_UINT32 EXEC_READ_X32(uint32, uint32_t)
#define EXEC_READ_INT32 EXEC_READ_X32(int32, int32_t)
#define EXEC_READ_UINT16 EXEC_READ_X16(uint16, uint16_t)
#define EXEC_READ_INT16 EXEC_READ_X16(int16, int16_t)
#define EXEC_READ_UINT8 EXEC_READ_X8(uint8, uint8_t)
#define EXEC_READ_INT8 EXEC_READ_X8(int8, int8_t)


bool yaoosl_execute_operator(yaooslhandle vm, yaooslcontexthandle context, enum yaoosl_operator op, yaooslclasshandle returntype, size_t argc)
{
    yaooslclasshandle* arg_types = alloca(sizeof(yaooslclasshandle) * argc);
    yaooslmethodgrouphandle methodgroup;
    yaooslmethodhandle method;
    yaooslinstancehandle instance;
    size_t i;
    if (argc == 0)
    { // We need at least one argument to determine the operator
        return false;
    }
    if (argc > context->value_stack_size)
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_VALUE_STACK_COUNT_MISSMATCH);
        return false;
    }
    for (i = 0; i < argc; i++)
    {
        instance = context->value_stack[context->value_stack_size - 1 - i];
        arg_types[argc - 1 - i] = instance->type;
    }
    if (!arg_types[0])
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_NULL_VALUE);
        return false;
    }
    if (!(methodgroup = arg_types[0]->operator_method_groups[op]) || methodgroup->methods_size == 0)
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_OPERATOR_NOT_FOUND);
        return false;
    }
    if (!(method = yaoosl_method_group_get_method2(methodgroup, returntype, argc, arg_types)))
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_OPERATOR_NOT_FOUND);
        return false;
    }
    if (!yaoosl_call_method(vm, context, method, NULL))
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_OUT_OF_MEMORY);
        return false;
    }
    return true;
}
bool yaoosl_execute_operator_self(yaooslhandle vm, yaooslcontexthandle context, enum yaoosl_operator op, yaooslclasshandle returntype, size_t argc)
{
    yaooslclasshandle* arg_types = alloca(sizeof(yaooslclasshandle) * argc);
    yaooslmethodgrouphandle methodgroup;
    yaooslmethodhandle method;
    yaooslinstancehandle instance;
    size_t i;
    if (argc + 1 == 0)
    { // We need at least one argument to determine the operator
        return false;
    }
    if (argc > context->value_stack_size)
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_VALUE_STACK_COUNT_MISSMATCH);
        return false;
    }
    for (i = 1; i < argc; i++)
    {
        instance = context->value_stack[context->value_stack_size - 1 - i];
        arg_types[argc - 1 - i] = instance->type;
    }
    if (!context->value_stack[context->value_stack_size - 1]->type)
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_NULL_VALUE);
        return false;
    }
    if (!(methodgroup = context->value_stack[context->value_stack_size - 1]->type->operator_method_groups[op]) || methodgroup->methods_size == 0)
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_OPERATOR_NOT_FOUND);
        return false;
    }
    if (!(method = yaoosl_method_group_get_method2(methodgroup, returntype, argc, arg_types)))
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_OPERATOR_NOT_FOUND);
        return false;
    }
    if (!yaoosl_call_method(vm, context, method, yaoosl_context_pop_value(context)))
    {
        YAOOSL_FORCE_BREAK();
        vm->error_handle(vm, context, ERR_MSG_OUT_OF_MEMORY);
        return false;
    }
    return true;
}

#define EXEC_VALUE_PUSH2(GET, VAR, TYPE, CAST, TARGET)\
GET;\
EXEC_ASSERT(valuehandle = yaoosl_instance_create(vm->classes[TYPE]), ERR_MSG_OUT_OF_MEMORY);\
yaoosl_instance_inc_ref(valuehandle);\
valuehandle->additional.TARGET = *(CAST*)(void*)&VAR;\
EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));

#define EXEC_VALUE_PUSH(GET, VAR, TYPE)\
GET;\
EXEC_ASSERT(valuehandle = yaoosl_instance_create(vm->classes[TYPE]), ERR_MSG_OUT_OF_MEMORY);\
yaoosl_instance_inc_ref(valuehandle);\
valuehandle->additional.VAR = VAR;\
EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));


//#define EXEC_CASE(ENUM) case ENUM: printf("%03d| " #ENUM "\n", (int)count++);
#define EXEC_CASE(ENUM) case ENUM:
static bool yaoosl_execute_get_opcode(struct yaoosl_context* context, enum yaoosl_opcode * opout)
{
    uint8_t uint8;
    switch (sizeof(enum yaoosl_opcode))
    {
    case 1:
        if (yaoosl_context_try_next(context, &uint8))
        {
            *opout = uint8;
            return true;
        }
        return false;
    case 2:
        *opout = 0;
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint16_t)uint8) << (8 * 1);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint16_t)uint8) << (8 * 0);
        return true;
    case 4:
        *opout = 0;
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint32_t)uint8) << (8 * 3);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint32_t)uint8) << (8 * 2);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint32_t)uint8) << (8 * 1);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint32_t)uint8) << (8 * 0);
        return true;
    default:
        *opout = 0;
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 7);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 6);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 5);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 4);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 3);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 2);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 1);
        if (!yaoosl_context_try_next(context, &uint8)) { return false; }
        *opout |= ((uint64_t)uint8) << (8 * 0);
        return true;
    }
}
#define SPACE10 "          "
#define SPACE50 SPACE10 SPACE10 SPACE10 SPACE10 SPACE10 
#define SPACE100 SPACE50 SPACE50
#define SPACE500 SPACE100 SPACE100 SPACE100 SPACE100 SPACE100 
#define SPACE1000 SPACE500 SPACE500 
void yaoosl_execute(yaooslhandle vm, struct yaoosl_context* context)
{
    enum OpCodes opcode = OPC_NOP;
    size_t i = 0, j, k;
    bool error_ok = true;
    bool flag;
    uint8_t uint8 = 0;
    uint16_t uint16 = 0;
    uint32_t uint32 = 0;
    uint64_t uint64 = 0;
    int8_t int8 = 0;
    int16_t int16 = 0;
    int32_t int32 = 0;
    int64_t int64 = 0;
    char* str = 0;
    size_t buffer_size = 512;
    char buffer[512];
    yaooslinstancehandle valuehandle = 0;
    yaooslinstancehandle valuehandle2 = 0;
    yaooslmethodgrouphandle methodgrouphandle = 0;
    yaooslmethodhandle methodhandle = 0;
    yaooslclasshandle create_classhandle = 0;
    yaooslpropertyhandle create_propertyhandle = 0;
    yaooslmethodhandle create_methodhandle = 0;
    yaooslclasshandle classhandle = 0;
    yaooslpropertyhandle propertyhandle = 0;
    yaooslcodehandle codehandle = 0;
    yaooslscopehandle scopehandle = 0;
    yaooslblockhandle blockhandle = 0;
    yaooslarghandle arghandle = 0;
    yaooslstacktracehandle stacktracehandle = 0;
    yaoosl_exception_handler exception_handler = { 0 };
    yaoosl_catch_handle catch_handler = { 0 };
    enum yaoosl_operator operator = __INVALID;
    void* ptr;
    size_t count = 0;
    if (!context) { return; }
    while ((!vm->diagnostics.can_continue || vm->diagnostics.can_continue(vm->diagnostics.user_data, vm, context)) && error_ok && yaoosl_execute_get_opcode(context, &opcode))
    {
//#define _DEBUG  1
#if _DEBUG 
        scopehandle = yaoosl_context_top_scope(context);
        if (scopehandle && opcode != OPC_DIAG_a16)
        {
            yaoosl_opcode_to_string(scopehandle->codehandle->bytes + scopehandle->offset - sizeof(enum yaoosl_operator), buffer, buffer_size);
            printf(
                "I:%04llu O:%05lluS:%02hu |%.*s%s\n",
                (long long)count++,
                (long long)(scopehandle->offset - sizeof(enum yaoosl_operator)),
                (uint16_t)context->scopes_size,
                (unsigned int)context->scopes_size,
                SPACE1000,
                buffer);
        }
#endif
        switch (opcode)
        {
        EXEC_CASE(OPC_NOP)
            break;
        EXEC_CASE(OPC_JUMP_OFF_a32)
            EXEC_READ_INT32;
            error_ok = yaoosl_context_move(context, int32 < 0 ? int32 - sizeof(enum yaoosl_opcode) - 4 : int32);
                break;
        EXEC_CASE(OPC_JUMP_OFF_a16)
            EXEC_READ_INT16;
            error_ok = yaoosl_context_move(context, int16 < 0 ? int16 - sizeof(enum yaoosl_opcode) - 2 : int16);
            break;
        EXEC_CASE(OPC_JUMP_OFF_a8)
            EXEC_READ_INT8;
            error_ok = yaoosl_context_move(context, int8 < 0 ? int8 - sizeof(enum yaoosl_opcode) - 1 : int8);
            break;
        EXEC_CASE(OPC_DIAG_a16)
            EXEC_READ_UINT16;
            for (i = uint16; i > 0; i--)
            {
                yaoosl_context_next(context, &error_ok);
            }
            break;
        EXEC_CASE(OPC_SKIP_IF_TRUE)
            EXEC_ASSERT(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[BOOLEAN]), ERR_MSG_TYPE_MISSMATCH_BOOLEAN, yaoosl_instance_dec_ref(valuehandle));
            if (valuehandle->additional.flag)
            {
                for (i = yaoosl_opcode_length(scopehandle->codehandle->bytes + scopehandle->offset); i > 0; i--)
                {
                    yaoosl_context_next(context, &error_ok);
                }
            }
            yaoosl_instance_dec_ref(valuehandle);
            break;
        EXEC_CASE(OPC_SKIP_IF_FALSE)
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[BOOLEAN]), ERR_MSG_TYPE_MISSMATCH_BOOLEAN, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE, yaoosl_instance_dec_ref(valuehandle));
            if (!valuehandle->additional.flag)
            {
                for (i = yaoosl_opcode_length(scopehandle->codehandle->bytes + scopehandle->offset); i > 0; i--)
                {
                    yaoosl_context_next(context, &error_ok);
                }
            }
            yaoosl_instance_dec_ref(valuehandle);
            break;
        EXEC_CASE(OPC_SKIP_IF_IN_EXCEPTION)
            EXEC_ASSERT(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);
            if (context->handles_exception)
            {
                for (i = yaoosl_opcode_length(scopehandle->codehandle->bytes + scopehandle->offset); i > 0; i--)
                {
                    yaoosl_context_next(context, &error_ok);
                }
            }
            break;
        EXEC_CASE(OPC_BLOCK_PUSH)
        {
            EXEC_ASSERT(blockhandle = yaoosl_block_create(), ERR_MSG_OUT_OF_MEMORY);
            EXEC_ASSERT2(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE, yaoosl_block_destroy(blockhandle));
            blockhandle->start = scopehandle->offset;
            EXEC_ASSERT2(yaoosl_scope_push_block(scopehandle, blockhandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_block_destroy(blockhandle));
        }
        break;
        EXEC_CASE(OPC_BLOCK_PREFIX)
        {
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[STRING]), ERR_MSG_TYPE_MISSMATCH_STRING, yaoosl_instance_dec_ref(valuehandle));

            EXEC_ASSERT2(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(scopehandle->blocks_size > 0, ERR_MSG_SCOPE_HAS_NO_BLOCKS, yaoosl_instance_dec_ref(valuehandle));
            blockhandle = scopehandle->blocks[scopehandle->blocks_size - 1];
            EXEC_ASSERT2(str = strdup(valuehandle->additional.str), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(yaoosl_block_push_prefix(blockhandle, str), ERR_MSG_OUT_OF_MEMORY, free(str); yaoosl_instance_dec_ref(valuehandle));
            yaoosl_instance_dec_ref(valuehandle);
        }
        break;
        EXEC_CASE(OPC_BLOCK_POP)
        {
            EXEC_ASSERT(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);
            EXEC_ASSERT(blockhandle = yaoosl_scope_pop_block(scopehandle), ERR_MSG_SCOPE_HAS_NO_BLOCKS);
            if (blockhandle->catchhandles_capacity > 0)
            {
                yaoosl_context_pop_exception_handler(context);
            }
            yaoosl_block_destroy(blockhandle);
            context->handles_exception = false;
        }
        break;
        EXEC_CASE(OPC_BLOCK_CATCH)
        {
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_TYPE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(yaoosl_class_is_type(valuehandle->additional.ptr, vm->classes[EXCEPTION_CLASS]), ERR_MSG_TYPE_MISSMATCH_EXCEPTION, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(blockhandle = yaoosl_scope_pop_block(scopehandle), ERR_MSG_SCOPE_HAS_NO_BLOCKS, yaoosl_instance_dec_ref(valuehandle));
            // Readd to top
            yaoosl_scope_push_block(scopehandle, blockhandle);

            // create catch_handler
            catch_handler.start = scopehandle->offset;
            catch_handler.type = valuehandle->additional.ptr;
            EXEC_ASSERT2(yaoosl_block_push_catch_handle(blockhandle, catch_handler), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            
            // create exception handler
            exception_handler.block = blockhandle;
            exception_handler.scope = scopehandle;
            EXEC_ASSERT2(yaoosl_context_push_exception_handler(context, exception_handler), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));

            // Decrease ref count of popped value
            yaoosl_instance_dec_ref(valuehandle);
        }
        break;
        EXEC_CASE(OPC_BLOCK_THROW)
        {
            // Get Exception to throw
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[EXCEPTION_CLASS]), ERR_MSG_TYPE_MISSMATCH_EXCEPTION, yaoosl_instance_dec_ref(valuehandle));

            EXEC_ASSERT2(yaoosl_util_throw2(vm, context, valuehandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            yaoosl_instance_dec_ref(valuehandle);
        }
        break;
        EXEC_CASE(OPC_SCOPE_ALLOCATE_a8) {
            EXEC_READ_UINT8;
            uint16 = uint8;
        } goto OPC_SCOPE_ALLOCATE_a;
        EXEC_CASE(OPC_SCOPE_ALLOCATE_a16) {
            EXEC_READ_UINT16;
            OPC_SCOPE_ALLOCATE_a:
            EXEC_ASSERT(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);

            EXEC_ASSERT2(ptr = realloc(scopehandle->locals, sizeof(yaooslinstancehandle) * ((size_t)scopehandle->locals_size + uint16)), ERR_MSG_OUT_OF_MEMORY, yaoosl_scope_destroy(scopehandle));
            scopehandle->locals = ptr;
            for (i = scopehandle->locals_size; i < ((size_t)scopehandle->locals_size + uint16); i++)
            {
                scopehandle->locals[i] = 0;
            }
            scopehandle->locals_size += uint16;
        }
        break;
        EXEC_CASE(OPC_SCOPE_POP)
        {
            EXEC_ASSERT(scopehandle = yaoosl_context_pop_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);
            yaoosl_scope_destroy(scopehandle);
        }
        break;
        EXEC_CASE(OPC_GET_VALUE_a8) {
            EXEC_READ_UINT8;
            uint16 = uint8;
        } goto OPC_GET_VALUE_a;
        EXEC_CASE(OPC_GET_VALUE_a16) {
            EXEC_READ_UINT16;
            OPC_GET_VALUE_a:
            EXEC_ASSERT(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);
            EXEC_ASSERT(scopehandle->locals_size > uint16, ERR_MSG_LOCAL_OUT_OF_RANGE);
            valuehandle = scopehandle->locals[uint16];
            if (valuehandle)
            {
                yaoosl_instance_inc_ref(valuehandle);
                EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_LOCAL_OUT_OF_RANGE, yaoosl_instance_dec_ref(valuehandle));
            }
            else
            {
                EXEC_ASSERT(valuehandle = yaoosl_instance_create(NULL), ERR_MSG_OUT_OF_MEMORY);
                yaoosl_instance_inc_ref(valuehandle);
                scopehandle->locals[uint16] = valuehandle;

                yaoosl_instance_inc_ref(valuehandle);
                EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            }
        } break;
        EXEC_CASE(OPC_SET_VALUE_a8) {
            EXEC_READ_UINT8;
            uint16 = uint8;
        } goto OPC_SET_VALUE_a;
        EXEC_CASE(OPC_SET_VALUE_a16) {
            EXEC_READ_UINT16;
        OPC_SET_VALUE_a:
            EXEC_ASSERT(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);
            EXEC_ASSERT(scopehandle->locals_size > uint16, ERR_MSG_LOCAL_OUT_OF_RANGE);
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            valuehandle2 = scopehandle->locals[uint16];
            if (valuehandle2)
            {
                yaoosl_instance_dec_ref(valuehandle2);
            }
            scopehandle->locals[uint16] = valuehandle;
        } break;
        EXEC_CASE(OPC_POP_VALUE) {
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            yaoosl_instance_dec_ref(valuehandle);
        } break;
        EXEC_CASE(OPC_CLEAR_VALUES) {
            while (valuehandle = yaoosl_context_pop_value(context))
            {
                yaoosl_instance_dec_ref(valuehandle);
            }
        } break;
        EXEC_CASE(OPC_DUPLICATE_VALUE) {
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_NO_VALUE_PRESENT, yaoosl_instance_dec_ref(valuehandle));
            yaoosl_instance_inc_ref(valuehandle);
            EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_NO_VALUE_PRESENT, yaoosl_instance_dec_ref(valuehandle));
        }
        break;

#pragma region Code Construction
#pragma region Class Construction
        EXEC_CASE(OPC_DECLARE_CLASS_a16)
        {
            EXEC_READ_UINT16;
            EXEC_ASSERT(str = malloc(sizeof(char) * ((size_t)uint16 + 1)), ERR_MSG_OUT_OF_MEMORY);
            str[uint16] = '\0';
            for (i = 0; i < uint16 && error_ok; i++)
            {
                str[i] = yaoosl_context_next(context, &error_ok);
            }
            EXEC_ASSERT2(yaoosl_declare_class(vm, str), ERR_MSG_OUT_OF_MEMORY, free(str));
            free(str);
        } break;
        EXEC_CASE(OPC_CREATE_CLASS_BEGIN_a16)
        {
            EXEC_READ_UINT16;
            EXEC_ASSERT(str = malloc(sizeof(char) * ((size_t)uint16 + 1)), ERR_MSG_OUT_OF_MEMORY);
            str[uint16] = '\0';
            for (i = 0; i < uint16 && error_ok; i++)
            {
                str[i] = yaoosl_context_next(context, &error_ok);
            }
            EXEC_ASSERT2(!create_classhandle, ERR_MSG_CLASS_CONSTRUCTION_IN_PROGRES, free(str));
            EXEC_ASSERT2(create_classhandle = yaoosl_declare_class(vm, str), ERR_MSG_OUT_OF_MEMORY, free(str));
            free(str);
            EXEC_ASSERT2(yaoosl_class_push_base(create_classhandle, vm->classes[OBJECT]), ERR_MSG_OUT_OF_MEMORY, yaoosl_class_destroy(create_classhandle));
        } break;
        EXEC_CASE(OPC_CREATE_CLASS_BASECLASS)
        {
            EXEC_ASSERT(create_classhandle, ERR_MSG_CLASS_CONSTRUCTION_NOT_STARTED);
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_TYPE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_NULL_VALUE, yaoosl_instance_dec_ref(valuehandle));

            EXEC_ASSERT2(yaoosl_class_push_base(create_classhandle, valuehandle->additional.ptr), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));

            yaoosl_instance_dec_ref(valuehandle);
        } break;
        EXEC_CASE(OPC_CREATE_CLASS_END)
        {
            EXEC_ASSERT(create_classhandle, ERR_MSG_CLASS_CONSTRUCTION_NOT_STARTED);
            EXEC_ASSERT(!create_methodhandle, ERR_MSG_CLASS_CONSTRUCTION_END_BLOCKED);
            EXEC_ASSERT(!create_propertyhandle, ERR_MSG_CLASS_CONSTRUCTION_END_BLOCKED);
            EXEC_ASSERT(create_classhandle->fullname[0] != '\0', ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
            yaoosl_class_finalize(create_classhandle);
            create_classhandle = 0;
        } break;
#pragma endregion
#pragma region Method Construction
        EXEC_CASE(OPC_CREATE_METHOD_BEGIN)
        {
            EXEC_ASSERT(create_classhandle, ERR_MSG_CLASS_CONSTRUCTION_NOT_STARTED);
            EXEC_ASSERT(!create_methodhandle, ERR_MSG_METHOD_CONSTRUCTION_IN_PROGRES);
            EXEC_ASSERT(create_methodhandle = yaoosl_method_create("", NULL, NULL), ERR_MSG_OUT_OF_MEMORY);
        } break;
        EXEC_CASE(OPC_CREATE_METHOD_RETURN)
        {
            EXEC_ASSERT(create_methodhandle, ERR_MSG_METHOD_CONSTRUCTION_NOT_STARTED);
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_TYPE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_NULL_VALUE, yaoosl_instance_dec_ref(valuehandle));
            create_methodhandle->returntype = valuehandle->additional.ptr;
            yaoosl_instance_dec_ref(valuehandle);
        } break;
        EXEC_CASE(OPC_CREATE_METHOD_NAME) { EXEC_ASSERT(create_methodhandle, ERR_MSG_METHOD_CONSTRUCTION_NOT_STARTED); EXEC_STR_COPY_FROM_VALUE(create_methodhandle->title); } break;
        EXEC_CASE(OPC_CREATE_METHOD_OPERATOR)
        {
            EXEC_ASSERT(create_methodhandle, ERR_MSG_METHOD_CONSTRUCTION_NOT_STARTED);
            EXEC_STR_ALLOC_FROM_VALUE();
            operator = yaoosl_operator_from_string(str);
        } break;
        EXEC_CASE(OPC_CREATE_METHOD_ARG) 
        {
            EXEC_ASSERT(create_methodhandle, ERR_MSG_METHOD_CONSTRUCTION_NOT_STARTED);
            EXEC_STR_ALLOC_FROM_VALUE();
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_TYPE, free(str); yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_NULL_VALUE, free(str); yaoosl_instance_dec_ref(valuehandle));

            EXEC_ASSERT2(arghandle = yaoosl_arg_create(str, valuehandle->additional.ptr), ERR_MSG_OUT_OF_MEMORY, free(str); yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(yaoosl_method_push_arg(create_methodhandle, arghandle), ERR_MSG_OUT_OF_MEMORY, free(str); yaoosl_instance_dec_ref(valuehandle); yaoosl_arg_destroy(arghandle));
            free(str);
            yaoosl_instance_dec_ref(valuehandle);
        } break;
        EXEC_CASE(OPC_CREATE_METHOD_CODEBLOCK_a64)
        {
            EXEC_ASSERT(create_methodhandle, ERR_MSG_METHOD_CONSTRUCTION_NOT_STARTED);
            EXEC_READ_UINT64;
            EXEC_ASSERT(ptr = malloc(sizeof(uint8_t) * uint64), ERR_MSG_OUT_OF_MEMORY);
            EXEC_ASSERT2(codehandle = yaoosl_code_create(), ERR_MSG_OUT_OF_MEMORY, free(ptr));
            codehandle->bytes = ptr;
            codehandle->bytes_size = uint64;
            create_methodhandle->contents = codehandle;
            for (uint64 = 0; uint64 < codehandle->bytes_size; uint64++)
            {
                codehandle->bytes[uint64] = yaoosl_context_next(context, &error_ok);
            }
        } break;
        EXEC_CASE(OPC_CREATE_METHOD_END)
        {
            EXEC_ASSERT(create_methodhandle, ERR_MSG_METHOD_CONSTRUCTION_NOT_STARTED);
            EXEC_ASSERT(create_methodhandle->title[0] != '\0', ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
            if (create_propertyhandle != 0)
            {
                if (!str_cmp(create_methodhandle->title, -1, "get", 3))
                {
                    EXEC_ASSERT(create_methodhandle->args_size == 0 && create_methodhandle->returntype == create_propertyhandle->type, ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
                    create_propertyhandle->get = create_methodhandle;
                }
                else if (!str_cmp(create_methodhandle->title, -1, "set", 3))
                {
                    EXEC_ASSERT(create_methodhandle->args_size == 1 && !create_methodhandle->returntype, ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
                    create_propertyhandle->set = create_methodhandle;
                }
            }
            else if (operator != __INVALID)
            {
                EXEC_ASSERT(create_methodhandle->args_size == yaoosl_operator_arg_count(operator) && create_methodhandle->returntype, ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
                EXEC_ASSERT(yaoosl_method_group_push_back(create_classhandle->operator_method_groups[operator], create_methodhandle), ERR_MSG_OUT_OF_MEMORY);
                operator = __INVALID;
            }
            else if (!str_cmp(create_methodhandle->title, -1, create_classhandle->name, -1))
            {
                EXEC_ASSERT(!create_methodhandle->returntype || create_methodhandle->returntype == create_classhandle, ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
                // create_methodhandle->returntype = create_classhandle;
                if (!create_classhandle->constructor_method_group)
                {
                    EXEC_ASSERT(create_classhandle->constructor_method_group = yaoosl_method_group_create(create_classhandle->name), ERR_MSG_OUT_OF_MEMORY);
                }
                EXEC_ASSERT(yaoosl_method_group_push_back(create_classhandle->constructor_method_group, create_methodhandle), ERR_MSG_OUT_OF_MEMORY);
            }
            else if (create_methodhandle->title[0] == '~' && !str_cmp(create_methodhandle->title + 1, -1, create_classhandle->name, -1))
            {
                EXEC_ASSERT(!create_methodhandle->returntype, ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
                create_classhandle->destructor_method = create_methodhandle;
            }
            else
            {
                EXEC_ASSERT(yaoosl_class_push_method(create_classhandle, create_methodhandle), ERR_MSG_OUT_OF_MEMORY);
            }
            if (scopehandle = yaoosl_context_top_scope(context))
            {
                for (i = 0; i < scopehandle->blocks_size; i++)
                {
                    blockhandle = scopehandle->blocks[i];
                    for (j = blockhandle->prefixes_size - 1; j != ~(size_t)0; j--)
                    {
                        EXEC_ASSERT(str = strdup(blockhandle->prefixes[j]), ERR_MSG_OUT_OF_MEMORY);
                        EXEC_ASSERT2(yaoosl_method_push_prefix(create_methodhandle, str), ERR_MSG_OUT_OF_MEMORY, str);
                    }
                }
            }
            create_methodhandle = 0;
        } break;
#pragma endregion
#pragma region Property Construction
        EXEC_CASE(OPC_CREATE_PROPERTY_BEGIN) {
            EXEC_ASSERT(create_classhandle, ERR_MSG_CLASS_CONSTRUCTION_NOT_STARTED);
            EXEC_ASSERT(!create_propertyhandle, ERR_MSG_PROPERTY_CONSTRUCTION_IN_PROGRES);
            EXEC_ASSERT(create_propertyhandle = yaoosl_property_create2("", NULL, NULL, NULL), ERR_MSG_OUT_OF_MEMORY);
        } break;
        EXEC_CASE(OPC_CREATE_PROPERTY_NAME) { EXEC_STR_COPY_FROM_VALUE(create_propertyhandle->title); } break;
        EXEC_CASE(OPC_CREATE_PROPERTY_RETURN) 
        {
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_STRING, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_NULL_VALUE, yaoosl_instance_dec_ref(valuehandle));
            create_propertyhandle->type = valuehandle->additional.ptr;
            yaoosl_instance_dec_ref(valuehandle);
        } break;
        EXEC_CASE(OPC_CREATE_PROPERTY_END)
        {
            EXEC_ASSERT(create_propertyhandle, ERR_MSG_PROPERTY_CONSTRUCTION_NOT_STARTED);
            EXEC_ASSERT(create_propertyhandle->type, ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
            EXEC_ASSERT(create_propertyhandle->title[0] != '\0', ERR_MSG_CODE_CONSTRUCTION_INCOMPLETE);
            if (!create_propertyhandle->get && !create_propertyhandle->set)
            {
                EXEC_ASSERT(codehandle = yaoosl_code_create(), ERR_MSG_OUT_OF_MEMORY);
                codehandle->function = yaoosl_property_default_get;
                EXEC_ASSERT2(methodhandle = yaoosl_method_create("get", create_propertyhandle->type, codehandle), ERR_MSG_OUT_OF_MEMORY, free(codehandle));
                create_propertyhandle->get = methodhandle;





                EXEC_ASSERT2(codehandle = yaoosl_code_create(), ERR_MSG_OUT_OF_MEMORY,
                    yaoosl_method_destroy(create_propertyhandle->get);
                create_propertyhandle->get = 0);
                codehandle->function = yaoosl_property_default_set;

                EXEC_ASSERT2(methodhandle = yaoosl_method_create("set", NULL, codehandle), ERR_MSG_OUT_OF_MEMORY,
                    free(codehandle);
                yaoosl_method_destroy(create_propertyhandle->get);
                create_propertyhandle->get = 0);

                EXEC_ASSERT2(arghandle = yaoosl_arg_create("value", create_propertyhandle->type), ERR_MSG_OUT_OF_MEMORY,
                    free(codehandle);
                yaoosl_method_destroy(methodhandle);
                yaoosl_method_destroy(create_propertyhandle->get);
                create_propertyhandle->get = 0);

                EXEC_ASSERT2(yaoosl_method_push_arg(methodhandle, arghandle), ERR_MSG_OUT_OF_MEMORY,
                    free(codehandle);
                yaoosl_arg_destroy(arghandle);
                yaoosl_method_destroy(methodhandle);
                yaoosl_method_destroy(create_propertyhandle->get);
                create_propertyhandle->get = 0);

                create_propertyhandle->set = methodhandle;
            }
            EXEC_ASSERT2(yaoosl_class_push_property(create_classhandle, create_propertyhandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_property_destroy(create_propertyhandle));
            create_propertyhandle = 0;
        } break;
#pragma endregion
#pragma endregion

        EXEC_CASE(OPC_NAVIGATE_PROPERTY_a32)
            EXEC_READ_UINT32;
            goto OPC_NAVIGATE_PROPERTY_a;
        EXEC_CASE(OPC_NAVIGATE_PROPERTY_a16)
            EXEC_READ_UINT16;
            uint32 = uint16;
            goto OPC_NAVIGATE_PROPERTY_a;
        EXEC_CASE(OPC_NAVIGATE_PROPERTY_a8)
            EXEC_READ_UINT8;
            uint32 = uint8;
            goto OPC_NAVIGATE_PROPERTY_a;
        OPC_NAVIGATE_PROPERTY_a:
            {
                EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
                EXEC_ASSERT2(str = malloc(sizeof(char) * ((size_t)uint32 + 1)), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
                str[uint32] = '\0';
                for (i = 0; i < uint32 && error_ok; i++)
                {
                    str[i] = yaoosl_context_next(context, &error_ok);
                }
                for (i = 0; i < valuehandle->type->properties_size; i++)
                {
                    if (!str_cmp((char*)str, uint32, valuehandle->type->properties[i]->title, -1))
                    {
                        break;
                    }
                }
                EXEC_ASSERT2(valuehandle->type->properties_size != i, ERR_MSG_PROPERTY_NOT_FOUND, yaoosl_instance_dec_ref(valuehandle); free(str));
                free(str);
                yaoosl_call_method(vm, context, valuehandle->type->properties[i]->get, valuehandle);
                yaoosl_instance_dec_ref(valuehandle);
            } break;
        EXEC_CASE(OPC_SET_PROPERTY_a32)
            EXEC_READ_UINT32;
            goto OPC_SET_PROPERTY_a;
        EXEC_CASE(OPC_SET_PROPERTY_a16)
            EXEC_READ_UINT16;
            uint32 = uint16;
            goto OPC_SET_PROPERTY_a;
        EXEC_CASE(OPC_SET_PROPERTY_a8)
            EXEC_READ_UINT8;
            uint32 = uint8;
            goto OPC_SET_PROPERTY_a;
        OPC_SET_PROPERTY_a:
            {
                EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
                EXEC_ASSERT2(str = malloc(sizeof(char) * ((size_t)uint32 + 1)), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
                str[uint32] = '\0';
                for (i = 0; i < uint32 && error_ok; i++)
                {
                    str[i] = yaoosl_context_next(context, &error_ok);
                }
                for (i = 0; i < valuehandle->type->properties_size; i++)
                {
                    if (!str_cmp((char*)str, uint32, valuehandle->type->properties[i]->title, -1))
                    {
                        break;
                    }
                }
                EXEC_ASSERT2(valuehandle->type->properties_size != i, ERR_MSG_PROPERTY_NOT_FOUND, yaoosl_instance_dec_ref(valuehandle); free(str));
                free(str);
                yaoosl_call_method(vm, context, valuehandle->type->properties[i]->set, valuehandle);
                yaoosl_instance_dec_ref(valuehandle);
            } break;
#pragma region Operators
        EXEC_CASE(OPC_INCREMENT) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_INCREASE, ((void*)~0LL), 0); break;
        EXEC_CASE(OPC_DECREMENT) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_DECREASE, ((void*)~0LL), 0); break;

        EXEC_CASE(OPC_A_ADD) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_ADD, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_SUBTRACT) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_SUBTRACT, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_MULTIPLICATE) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_MULTIPLICATE, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_DIVIDE) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_DIVIDE, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_AND) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_AND, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_XOR) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_XOR, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_OR) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_OR, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_BITSHIFT_LEFT) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_BITSHIFT_LEFT, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_BITSHIFT_RIGHT) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_BITSHIFT_RIGHT, ((void*)~0LL), 2); break;
        EXEC_CASE(OPC_A_MODULO) error_ok = yaoosl_execute_operator(vm, context, OP_ARITHMETICAL_MODULO, ((void*)~0LL), 2); break;

        EXEC_CASE(OPC_A_SELF_ADD) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_ADD, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_SUBTRACT) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_SUBTRACT, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_MULTIPLICATE) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_MULTIPLICATE, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_DIVIDE) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_DIVIDE, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_AND) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_AND, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_XOR) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_XOR, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_OR) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_OR, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_BITSHIFT_LEFT) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_BITSHIFT_LEFT, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_BITSHIFT_RIGHT) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_BITSHIFT_RIGHT, NULL, 1); break;
        EXEC_CASE(OPC_A_SELF_MODULO) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_MODULO, NULL, 1); break;
        EXEC_CASE(OPC_LOGICAL_NOT) error_ok = yaoosl_execute_operator_self(vm, context, OP_ARITHMETICAL_SELF_INVERT, NULL, 0); break;

        EXEC_CASE(OPC_LOGICAL_AND) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_AND, vm->classes[BOOLEAN], 2); break;
        EXEC_CASE(OPC_LOGICAL_OR) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_OR, vm->classes[BOOLEAN], 2); break;
        EXEC_CASE(OPC_LOGICAL_EQUALS) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_EQUALS, vm->classes[BOOLEAN], 2); break;
        EXEC_CASE(OPC_LOGICAL_EQUALS_NOT) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_EQUALS_NOT, vm->classes[BOOLEAN], 2); break;
        EXEC_CASE(OPC_LOGICAL_GREATER_THEN) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_LARGER_THEN, vm->classes[BOOLEAN], 2); break;
        EXEC_CASE(OPC_LOGICAL_GREATER_THEN_OR_EQUAL) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_LARGER_THEN_OR_EQUAL, vm->classes[BOOLEAN], 2); break;
        EXEC_CASE(OPC_LOGICAL_LESS_THEN) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_LESS_THEN, vm->classes[BOOLEAN], 2); break;
        EXEC_CASE(OPC_LOGICAL_LESS_THEN_OR_EQUAL) error_ok = yaoosl_execute_operator(vm, context, OP_LOGICAL_LESS_THEN_OR_EQUAL, vm->classes[BOOLEAN], 2); break;

        EXEC_CASE(OPC_CALL_a32_b8)
            EXEC_READ_UINT32;
            EXEC_READ_UINT8;
            goto OPC_CALL_a;
        EXEC_CASE(OPC_CALL_a16_b8)
            EXEC_READ_UINT16;
            uint32 = uint16;
            EXEC_READ_UINT8;
            goto OPC_CALL_a;
        EXEC_CASE(OPC_CALL_a8_b8)
            EXEC_READ_UINT8;
            uint32 = uint8;
            EXEC_READ_UINT8;
        OPC_CALL_a:
            {
                EXEC_ASSERT(str = malloc(sizeof(char) * ((size_t)uint32 + 1)), ERR_MSG_OUT_OF_MEMORY);
                str[uint32] = '\0';
                for (i = 0, j = 0, k = 0; i < uint32 && error_ok; i++)
                {
                    if ((str[i] = yaoosl_context_next(context, &error_ok)) == '.')
                    {
                        j = k;
                        k = i;
                    }
                }
                str[k] = '\0';
                EXEC_ASSERT2(classhandle = yaoosl_context_resolve_type(context, vm, str), ERR_MSG_CLASS_NOT_FOUND, free(str));
                EXEC_ASSERT2(methodgrouphandle = yaoosl_class_get_method(classhandle, str + k + 1, (int)(uint32 - k - 1)), ERR_MSG_METHOD_NOT_FOUND, free(str));
                EXEC_ASSERT2(context->value_stack_size >= uint8, ERR_MSG_VALUE_STACK_COUNT_MISSMATCH, free(str));
                EXEC_ASSERT2(ptr = malloc(sizeof(yaooslclasshandle) * uint8), ERR_MSG_OUT_OF_MEMORY, free(str));
                for (i = context->value_stack_size - 1, j = 0; i != ~(size_t)0 && i >= context->value_stack_size - uint8; i--, j++)
                {
                    ((yaooslclasshandle*)ptr)[j] = context->value_stack[i]->type;
                }
                EXEC_ASSERT2(methodhandle = yaoosl_method_group_get_method2(methodgrouphandle, ((void*)~0LL), uint8, ptr), ERR_MSG_METHOD_NOT_FOUND, free(str); free(ptr));
                free(str);
                free(ptr);
                yaoosl_call_method(vm, context, methodhandle, NULL);
            } break;

        EXEC_CASE(OPC_CALL_SELF_a32_b8)
            EXEC_READ_UINT32;
            EXEC_READ_UINT8;
            goto OPC_CALL_SELF_a;
        EXEC_CASE(OPC_CALL_SELF_a16_b8)
            EXEC_READ_UINT16;
            uint32 = uint16;
            EXEC_READ_UINT8;
            goto OPC_CALL_SELF_a;
        EXEC_CASE(OPC_CALL_SELF_a8_b8)
            EXEC_READ_UINT8;
            uint32 = uint8;
            EXEC_READ_UINT8;
        OPC_CALL_SELF_a:
            EXEC_ASSERT(str = malloc(sizeof(char) * ((size_t)uint32 + 1)), ERR_MSG_OUT_OF_MEMORY);
            str[uint32] = '\0';
            for (i = 0; i < uint32 && error_ok; i++)
            {
                str[i] = yaoosl_context_next(context, &error_ok);
            }
            EXEC_ASSERT2(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT, free(str));
            EXEC_ASSERT2(classhandle = valuehandle->type, ERR_MSG_NULL_VALUE, free(str); yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(methodgrouphandle = yaoosl_class_get_method(classhandle, str, (int)(uint32)), ERR_MSG_METHOD_NOT_FOUND, free(str); yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(context->value_stack_size >= uint8, ERR_MSG_VALUE_STACK_COUNT_MISSMATCH, free(str); yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(ptr = malloc(sizeof(yaooslclasshandle) * uint8), ERR_MSG_OUT_OF_MEMORY, free(str); yaoosl_instance_dec_ref(valuehandle));
            for (i = context->value_stack_size - 1, j = 0; i != ~(size_t)0 && i >= context->value_stack_size - uint8; i--, j++)
            {
                ((yaooslclasshandle*)ptr)[j] = context->value_stack[i]->type;
            }
            EXEC_ASSERT2(methodhandle = yaoosl_method_group_get_method2(methodgrouphandle, ((void*)~0LL), uint8, ptr), ERR_MSG_METHOD_NOT_FOUND, free(str); free(ptr); yaoosl_instance_dec_ref(valuehandle));
            free(str);
            free(ptr);
            yaoosl_call_method(vm, context, methodhandle, valuehandle);
            yaoosl_instance_dec_ref(valuehandle);
            break;
#pragma endregion
#pragma region value manipulation
        EXEC_CASE(OPC_PUSH_UINT8_a8) EXEC_VALUE_PUSH(EXEC_READ_UINT8, uint8, UINT8); break;
        EXEC_CASE(OPC_PUSH_INT8_a8) EXEC_VALUE_PUSH(EXEC_READ_INT8, int8, INT8); break;
        EXEC_CASE(OPC_PUSH_UINT16_a16) EXEC_VALUE_PUSH(EXEC_READ_UINT16, uint16, UINT16); break;
        EXEC_CASE(OPC_PUSH_INT16_a16) EXEC_VALUE_PUSH(EXEC_READ_INT16, int16, INT16); break;
        EXEC_CASE(OPC_PUSH_UINT32_a32) EXEC_VALUE_PUSH(EXEC_READ_UINT32, uint32, UINT32); break;
        EXEC_CASE(OPC_PUSH_INT32_a32) EXEC_VALUE_PUSH(EXEC_READ_INT32, int32, INT32); break;
        EXEC_CASE(OPC_PUSH_UINT64_a64) EXEC_VALUE_PUSH(EXEC_READ_UINT64, uint64, UINT64); break;
        EXEC_CASE(OPC_PUSH_INT64_a64) EXEC_VALUE_PUSH(EXEC_READ_INT64, int64, INT64); break;

        EXEC_CASE(OPC_PUSH_FLOAT_a32) EXEC_VALUE_PUSH2(EXEC_READ_UINT32, uint32, FLOAT, float, f); break;
        EXEC_CASE(OPC_PUSH_DOUBLE_a64) EXEC_VALUE_PUSH2(EXEC_READ_UINT64, uint64, DOUBLE, double, d); break;

        EXEC_CASE(OPC_PUSH_TRUE) EXEC_VALUE_PUSH(flag = true, flag, BOOLEAN); break;
        EXEC_CASE(OPC_PUSH_FALSE) EXEC_VALUE_PUSH(flag = false, flag, BOOLEAN); break;
        EXEC_CASE(OPC_PUSH_THIS) 
        {
            EXEC_ASSERT(scopehandle = yaoosl_context_top_scope(context), ERR_MSG_CONTEXT_HAS_NO_SCOPE);
            EXEC_ASSERT(scopehandle->self, ERR_MSG_NULL_VALUE);
            EXEC_ASSERT(yaoosl_context_push_value(context, scopehandle->self), ERR_MSG_OUT_OF_MEMORY);
            yaoosl_instance_inc_ref(scopehandle->self);
        } break;

        EXEC_CASE(OPC_PUSH_CHAR_a8) EXEC_VALUE_PUSH2(EXEC_READ_UINT8, uint8, CHAR, char, c); break;
        EXEC_CASE(OPC_PUSH_STRING_a32)
            EXEC_READ_UINT32;
            goto OPC_PUSH_STRING_a;
        EXEC_CASE(OPC_PUSH_STRING_a16)
            EXEC_READ_UINT16;
            uint32 = uint16;
            goto OPC_PUSH_STRING_a;
        EXEC_CASE(OPC_PUSH_STRING_a8)
            EXEC_READ_UINT8;
            uint32 = uint8;
        OPC_PUSH_STRING_a:
            EXEC_ASSERT(valuehandle = yaoosl_instance_create(vm->classes[STRING]), ERR_MSG_OUT_OF_MEMORY);
            yaoosl_instance_inc_ref(valuehandle);
            EXEC_ASSERT2(valuehandle->additional.str = malloc(sizeof(char) * ((size_t)uint32 + 1)), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            for (i = 0; i < uint32; i++)
            {
                valuehandle->additional.str[i] = (char)yaoosl_context_next(context, &error_ok);
            }
            valuehandle->additional.str[uint32] = '\0';
            EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle); free(valuehandle->additional.str));
            break;
        EXEC_CASE(OPC_PUSH_NEW_a8) {
            EXEC_READ_UINT8;


            // Create instance
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_TYPE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_NULL_VALUE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle2 = yaoosl_instance_create(valuehandle->additional.ptr), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            yaoosl_instance_dec_ref(valuehandle);

            yaoosl_instance_inc_ref(valuehandle2);

            // Analyze stack and find the types for constructor
            methodgrouphandle = classhandle->constructor_method_group;
            if (methodgrouphandle)
            {
                EXEC_ASSERT2(context->value_stack_size >= uint8, ERR_MSG_VALUE_STACK_COUNT_MISSMATCH, yaoosl_instance_dec_ref(valuehandle2));
                EXEC_ASSERT2(ptr = malloc(sizeof(yaooslclasshandle) * uint8), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle2));
                for (i = context->value_stack_size - 1, j = 0; i != ~(size_t)0 && i >= context->value_stack_size - uint8; i--, j++)
                {
                    ((yaooslclasshandle*)ptr)[j] = context->value_stack[i]->type;
                }
                EXEC_ASSERT2(methodhandle = yaoosl_method_group_get_method2(methodgrouphandle, ((void*)~0LL), uint8, ptr), ERR_MSG_METHOD_NOT_FOUND, free(ptr));
                free(ptr);
            }

            if (methodgrouphandle)
            {
                // Call constructor
                yaoosl_call_method(vm, context, methodhandle, valuehandle2);
            }
            else
            {
                // Push Value
                yaoosl_instance_inc_ref(valuehandle2);
                EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle2), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle2));
            }
        } break;
        EXEC_CASE(OPC_PUSH_NULL)
            EXEC_ASSERT(valuehandle = yaoosl_instance_create(NULL), ERR_MSG_OUT_OF_MEMORY);
            yaoosl_instance_inc_ref(valuehandle);
            EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            break;
        EXEC_CASE(OPC_PUSH_ARRAY)
            EXEC_ASSERT(valuehandle2 = yaoosl_util_create_array(vm, 0, vm->classes[OBJECT]), ERR_MSG_OUT_OF_MEMORY);
            yaoosl_instance_inc_ref(valuehandle2);
            EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle2), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle2));
            break;
        EXEC_CASE(OPC_PUSH_ARRAY_TYPED)
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_TYPE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_NULL_VALUE, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle2 = yaoosl_util_create_array(vm, 0, valuehandle->additional.ptr), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle));
            yaoosl_instance_dec_ref(valuehandle);
            yaoosl_instance_inc_ref(valuehandle2);
            EXEC_ASSERT2(yaoosl_context_push_value(context, valuehandle2), ERR_MSG_OUT_OF_MEMORY, yaoosl_instance_dec_ref(valuehandle2));
            break;
#pragma endregion

        EXEC_CASE(OPC_RESOLVE_TYPE)
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[STRING]), ERR_MSG_TYPE_MISSMATCH_STRING, yaoosl_instance_dec_ref(valuehandle));
            EXEC_ASSERT2(valuehandle->additional.ptr != 0, ERR_MSG_NULL_VALUE, yaoosl_instance_dec_ref(valuehandle));
            
            EXEC_ASSERT2(classhandle = yaoosl_context_resolve_type(context, vm, valuehandle->additional.str), ERR_MSG_CLASS_NOT_FOUND, yaoosl_instance_dec_ref(valuehandle));
            yaoosl_instance_dec_ref(valuehandle);
            EXEC_ASSERT(yaoosl_util_push_type(vm, context, classhandle), ERR_MSG_OUT_OF_MEMORY);
            break;
        EXEC_CASE(OPC_IS_TYPE)
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            EXEC_ASSERT2(valuehandle->type && yaoosl_class_is_type(valuehandle->type, vm->classes[TYPE]), ERR_MSG_TYPE_MISSMATCH_TYPE, yaoosl_instance_dec_ref(valuehandle));
            classhandle = valuehandle->additional.ptr;
            yaoosl_instance_dec_ref(valuehandle);
            EXEC_ASSERT(valuehandle = yaoosl_context_pop_value(context), ERR_MSG_NO_VALUE_PRESENT);
            if (yaoosl_class_is_type(valuehandle->type, classhandle))
            {
                yaoosl_instance_dec_ref(valuehandle);
                EXEC_VALUE_PUSH(flag = true, flag, BOOLEAN);
            }
            else
            {
                yaoosl_instance_dec_ref(valuehandle);
                EXEC_VALUE_PUSH(flag = false, flag, BOOLEAN);
            }
            break;

        EXEC_CASE(OPC_INDEX_GET) break;
        EXEC_CASE(OPC_INDEX_SET) break;

        EXEC_CASE(OPC_EXTEND)
            vm->error_handle(vm, context, "Unexpected Instruction");
            error_ok = false;
            break;
        }
    }
}

bool yaoosl_call_method(yaooslhandle vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self)
{
    yaooslscopehandle scopehandle;
    yaooslinstancehandle instance;
    yaooslblockhandle block;
    size_t i;
    char* str;
    // 0. Check if method is ByteCode or C
    if (method->contents->function)
    { // C Method
        method->contents->function(vm, context, method, self);
        return true;
    }
    else
    { // Byte Code
        // 1. Create
        if (!(scopehandle = yaoosl_scope_create())) { return false; }
        // 2. Reserve space for arguments
        if (method->args_size > 0)
        {
            if (!(scopehandle->locals = malloc(sizeof(yaooslinstancehandle) * method->args_size))) { yaoosl_scope_destroy(scopehandle); return false; }
            memset(scopehandle->locals, 0, sizeof(yaooslinstancehandle) * method->args_size);
            scopehandle->locals_size = method->args_size;
        }
        // 3. Set Arguments
        for (i = 0; i < method->args_size; i++)
        {
            if (!(instance = yaoosl_context_pop_value(context))) { yaoosl_scope_destroy(scopehandle); return false; }
            yaoosl_instance_inc_ref(instance);
            scopehandle->locals[method->args_size - 1 - i] = instance;
        }
        // 4. Set Code
        scopehandle->codehandle = method->contents;
        // 5. Set this
        if (self)
        {
            yaoosl_instance_inc_ref(self);
            scopehandle->self = self;
        }
        // 6. Push Scope
        if (!yaoosl_context_push_scope(context, scopehandle)) { yaoosl_scope_destroy(scopehandle); yaoosl_instance_dec_ref(self); return false; }
        // 7. If true, push prefixes
        if (method->prefixes_size > 0)
        {
            if (!(block = yaoosl_block_create())) { yaoosl_context_pop_scope(context); yaoosl_scope_destroy(scopehandle); yaoosl_instance_dec_ref(self); return false; }
            if (!yaoosl_scope_push_block(scopehandle, block)) { yaoosl_block_destroy(block); yaoosl_context_pop_scope(context); yaoosl_scope_destroy(scopehandle); yaoosl_instance_dec_ref(self); return false; }

            for (i = 0; i < method->prefixes_size; i++)
            {
                if (!(str = strdup(method->prefixes[i]))) {
                    yaoosl_block_destroy(block);
                    yaoosl_context_pop_scope(context);
                    yaoosl_scope_destroy(scopehandle);
                    yaoosl_instance_dec_ref(self);
                    return false;
                }
                if (!(yaoosl_block_push_prefix(block, str)))
                {
                    yaoosl_block_destroy(block);
                    yaoosl_context_pop_scope(context);
                    yaoosl_scope_destroy(scopehandle);
                    yaoosl_instance_dec_ref(self);
                    return false;
                }
            }
        }
        return true;
    }
}