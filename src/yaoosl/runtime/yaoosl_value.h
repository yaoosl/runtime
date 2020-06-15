#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    struct yaoosl_code_page;
    struct yaoosl_runtime;

    struct yaoosl_arg;
    struct yaoosl_method;
    struct yaoosl_method_group;
    struct yaoosl_property;
    struct yaoosl_classtemplate;
    struct yaoosl_reference;
    struct yaoosl_value_reference;
    struct yaoosl_value;
    struct yaoosl_value_array;
    typedef struct yaoosl_reference* yaoosl_ref;
    typedef void (*yaoosl_class_callback)(struct yaoosl_runtime* yvm, yaoosl_ref reference, void* userdata);


    enum yaoosl_encapsulation
    {
        // Special Encapsulation.
        // Supposed to aid in compiler creation where temporary dummy
        // classtemplates/methods/... are needed.
        // Dummy checks may be made by checking if the encapsulation field is "false".
        YENCPS_DUMMY = 0,

        // Visible to everybody.
        YENCPS_PUBLIC,

        // Visible only to same-namespace and below (My.Namespace -> My.Namespace.Fancy).
        // Namespaces above (My.Namespace -> My) cannot see/use this.
        YENCPS_INTERNAL,

        // Only visible to derived entities.
        YENCPS_DERIVED,

        // Only visible in this very entity.
        YENCPS_PRIVATE
    };
    enum yaoosl_value_type
    {
        YVT_NA,
        YVT_REFERENCE,
        YVT_DELEGATE,
        YVT_FIELD,
        YVT_CLASSTEMPLATE,
        YVT_ARRAY,
        YVT_DOUBLE,
        YVT_BOOLEAN,
        YVT_FLOAT,
        YVT_INT8,
        YVT_INT16,
        YVT_INT32,
        YVT_INT64,
        YVT_UINT8,
        YVT_UINT16,
        YVT_UINT32,
        YVT_UINT64,
    };
    enum yaoosl_operator
    {
        YOP_NA,
        YOP_INC_r0,
        YOP_DEC_r0,
        YOP_NOT_v1,
        YOP_ADD_v2,
        YOP_ADD_r1,
        YOP_SUB_v2,
        YOP_SUB_r1,
        YOP_MUL_v2,
        YOP_MUL_r1,
        YOP_DIV_v2,
        YOP_DIV_r1,
        YOP_BIT_INV_v1,
        YOP_BIT_INV_r0,
        YOP_BIT_OR_v2,
        YOP_BIT_OR_r1,
        YOP_BIT_XOR_v2,
        YOP_BIT_XOR_r1,
        YOP_BIT_AND_v2,
        YOP_BIT_AND_r1,
        YOP_LOG_OR_v2,
        YOP_LOG_AND_v2,
        YOP_LOG_EQUAL_v2,
        YOP_LOG_NOTEQUAL_v2,
        YOP_LOG_LESS_THEN_v2,
        YOP_LOG_LESS_THEN_OR_EQUAL_v2,
        YOP_LOG_GREATER_THEN_v2,
        YOP_LOG_GREATER_THEN_OR_EQUAL_v2,
        YOP_MOD_r1,
        YOP_MOD_v2,
        YOP_LSHIFT_v2,
        YOP_LSHIFT_r1,
        YOP_RSHIFT_v2,
        YOP_RSHIFT_r1,
    };




    typedef struct yaoosl_method
    {
        struct yaoosl_method_group* owning_group;
        struct yaoosl_arg* args;
        size_t       args_capacity;
        size_t       args_size;

        size_t varslots;

        struct yaoosl_class* return_type;

        enum yaoosl_encapsulation encapsulation;

        // Start offset of this method in code-page
        size_t method_start;
        // End offset of this method in code-page
        size_t method_end;

        // The scope-slots required by this method
        size_t scope_slots;
    } yaoosl_method;
    typedef union yaoosl_as
    {
        bool flag;
        float f;
        double d;
        int8_t  int8;
        int16_t int16;
        int32_t int32;
        int64_t int64;
        uint8_t  uint8;
        uint16_t uint16;
        uint32_t uint32;
        uint64_t uint64;
        yaoosl_ref reference;
        struct yaoosl_method delegate;
        struct yaoosl_value* field;
        struct yaoosl_value_array* array;
        struct yaoosl_classtemplate* classtemplate;
    } yaoosl_as;
    typedef struct yaoosl_arg
    {
        char * name;
        size_t name_length;
        yaoosl_as as;
        enum yaoosl_value_type type;
    } yaoosl_arg;
    typedef struct yaoosl_method_group
    {
        struct yaoosl_class* owning_type;
        char * name;
        size_t name_length;
        enum yaoosl_operator operator_implementation;

        yaoosl_method * method;
        size_t          method_capacity;
        size_t          method_size;
    } yaoosl_method_group;
    typedef struct yaoosl_property
    {
        struct yaoosl_class* owning_type;

        struct yaoosl_class* return_type;
        size_t setter_start;
        size_t getter_start;

        enum yaoosl_encapsulation encapsulation;
        bool has_data_field;
    } yaoosl_property;

    typedef struct yaoosl_value_array
    {
        size_t capacity;
        size_t size;
        struct yaoosl_value* values;
    } yaoosl_value_array;

    /*
        To create a class-dummy, check the encapsulation.
        if it is set to
    */
    typedef struct yaoosl_classtemplate
    {
        struct yaoosl_classtemplate** implements;
        size_t                        implements_capacity;
        size_t                        implements_size;

        struct yaoosl_method_group * methods;
        size_t                       methods_capacity;
        size_t                       methods_size;

        struct yaoosl_property * properties;
        size_t                   properties_capacity;
        size_t                   properties_size;

        struct yaoosl_code_page * declaring_code_page;

        // Unless YVT_NA, this type belongs to a primitive
        enum yaoosl_value_type value_type;


        enum yaoosl_encapsulation encapsulation;
        char* full_namespace;
        char* name;

        yaoosl_class_callback user_construct;
        void* user_data;
        yaoosl_class_callback user_destruct;
    } yaoosl_classtemplate;

    typedef struct yaoosl_reference
    {
        yaoosl_classtemplate* type;
        bool marked; // GC Marker

        struct yaoosl_value* fields_start;
        yaoosl_method* methods_start;
    } yaoosl_reference;

    typedef struct yaoosl_value
    {
        yaoosl_as as;
        enum yaoosl_value_type type;
    } yaoosl_value;


    static yaoosl_value yaoosl_value_from_float(float f)		     { yaoosl_value ret; ret.type = YVT_FLOAT;     ret.as.f         = f;            return ret; }
    static yaoosl_value yaoosl_value_from_double(double d)		     { yaoosl_value ret; ret.type = YVT_DOUBLE;    ret.as.d         = d;            return ret; }
    static yaoosl_value yaoosl_value_from_int8(int8_t int8)		     { yaoosl_value ret; ret.type = YVT_INT8;      ret.as.int8      = int8;         return ret; }
    static yaoosl_value yaoosl_value_from_int16(int16_t int16)	     { yaoosl_value ret; ret.type = YVT_INT16;     ret.as.int16     = int16;        return ret; }
    static yaoosl_value yaoosl_value_from_int32(int32_t int32)	     { yaoosl_value ret; ret.type = YVT_INT32;     ret.as.int32     = int32;        return ret; }
    static yaoosl_value yaoosl_value_from_int64(int64_t int64)	     { yaoosl_value ret; ret.type = YVT_INT64;     ret.as.int64     = int64;        return ret; }
    static yaoosl_value yaoosl_value_from_uint8(uint8_t uint8)	     { yaoosl_value ret; ret.type = YVT_UINT8;     ret.as.uint8     = uint8;        return ret; }
    static yaoosl_value yaoosl_value_from_uint16(uint16_t uint16)    { yaoosl_value ret; ret.type = YVT_UINT16;    ret.as.uint16    = uint16;       return ret; }
    static yaoosl_value yaoosl_value_from_uint32(uint32_t uint32)    { yaoosl_value ret; ret.type = YVT_UINT32;    ret.as.uint32    = uint32;       return ret; }
    static yaoosl_value yaoosl_value_from_uint64(uint64_t uint64)    { yaoosl_value ret; ret.type = YVT_UINT64;    ret.as.uint64    = uint64;       return ret; }
    static yaoosl_value yaoosl_value_from_bool(bool flag)            { yaoosl_value ret; ret.type = YVT_BOOLEAN;   ret.as.flag      = flag;         return ret; }
    static yaoosl_value yaoosl_value_from_ref(yaoosl_ref ref)        { yaoosl_value ret; ret.type = YVT_REFERENCE; ret.as.reference = ref;          return ret; }
    static yaoosl_value yaoosl_value_from_field(yaoosl_value* ref)   { yaoosl_value ret; ret.type = YVT_FIELD;     ret.as.field     = ref;          return ret; }
    static yaoosl_value yaoosl_value_from_method(yaoosl_method mthd) { yaoosl_value ret; ret.type = YVT_DELEGATE;  ret.as.delegate  = mthd;         return ret; }


    yaoosl_classtemplate* yaoosl_classtemplate_create(struct yaoosl_code_page* owner, enum yaoosl_encapsulation encapsulation, const char* ns, const char* name);
    void yaoosl_classtemplate_destroy(yaoosl_classtemplate* classtemplate);
    void yaoosl_method_group_destroy(yaoosl_method_group method_group);
    void yaoosl_method_destroy(yaoosl_method method);
    void yaoosl_arg_destroy(yaoosl_arg arg);

#ifdef __cplusplus
}
#endif // __cplusplus