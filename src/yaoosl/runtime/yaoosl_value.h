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
    struct yaoosl_class;
    struct yaoosl_reference;
    struct yaoosl_value_reference;
    struct yaoosl_value;
    typedef struct yaoosl_reference* yaoosl_ref;
    typedef void (*yaoosl_class_callback)(struct yaoosl_runtime* yvm, yaoosl_ref reference, void* userdata);


    enum yaoosl_encapsulation
    {
        YENCPS_PUBLIC,
        YENCPS_INTERNAL,
        YENCPS_DERIVED,
        YENCPS_PRIVATE
    };
    enum yaoosl_value_type
    {
        YVT_NA,
        YVT_REFERENCE,
        YVT_CALLABLE,
        YVT_PROPERTY,
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
        YOP_BIT_INV_v2,
        YOP_BIT_INV_r1,
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
        YOP_LOG_GREATER_THEN_v2,
        YOP_MOD_v2,
        YOP_LSHIFT_v2,
        YOP_LSHIFT_r1,
        YOP_RSHIFT_v2,
        YOP_RSHIFT_r1,
    };



    typedef struct yaoosl_arg
    {
        char * name;
        size_t name_length;
        struct yaoosl_class * type;
        enum yaoosl_value_type valtype;
    } yaoosl_arg;
    typedef struct yaoosl_method
    {
        struct yaoosl_method_group* owning_group;
        yaoosl_arg * args;
        size_t       args_capacity;
        size_t       args_size;

        struct yaoosl_class* return_type;

        enum yaoosl_encapsulation encapsulation;

        // Start offset of this method in code-page
        size_t method_start;
        // End offset of this method in code-page
        size_t method_end;

        // The scope-slots required by this method
        size_t scope_slots;
    } yaoosl_method;
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
        yaoosl_arg * args;
        size_t       args_capacity;
        size_t       args_size;

        struct yaoosl_class* return_type;
        size_t setter_start;
        size_t getter_start;

        enum yaoosl_encapsulation encapsulation;
        bool has_data_field;
    } yaoosl_property;
    typedef struct yaoosl_class
    {
        struct yaoosl_class ** implements;
        size_t                 implements_capacity;
        size_t                 implements_size;

        struct yaoosl_method_group * methods;
        size_t                       methods_capacity;
        size_t                       methods_size;

        struct yaoosl_method_group * operators;
        size_t                       operators_capacity;
        size_t                       operators_size;

        struct yaoosl_property * properties;
        size_t                   properties_capacity;
        size_t                   properties_size;

        struct yaoosl_code_page* declaring_code_page;

        // Unless YVT_NA, this type belongs to a primitive
        enum yaoosl_value_type value_type;


        enum yaoosl_encapsulation encapsulation;
        char* full_namespace;
        char* name;

        yaoosl_class_callback user_construct;
        void* user_data;
        yaoosl_class_callback user_destruct;
    } yaoosl_class;
    typedef struct yaoosl_reference
    {
        yaoosl_class* type;
        bool marked; // GC Marker

        /*
            Struct size undefined!
            There will be further data
            depending on the yaoosl_class
            defining this reference following this!
        */
        struct yaoosl_value* fields_start;
        yaoosl_method* methods_start;
    } yaoosl_reference;
    typedef struct yaoosl_callable_reference
    {
        struct yaoosl_code_page* code_page;
        yaoosl_method* method;
    } yaoosl_callable_reference;
    typedef struct yaoosl_property_reference
    {
        yaoosl_class* type;
        struct yaoosl_value* value;
    } yaoosl_property_reference;
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
        yaoosl_callable_reference callable;
        yaoosl_property_reference prop;
    } yaoosl_as;
    typedef struct yaoosl_value
    {
        yaoosl_as as;
        enum yaoosl_value_type type;
    } yaoosl_value;


    static yaoosl_value yaoosl_value_from_float(float f)		  { yaoosl_value ret; ret.type = YVT_FLOAT;           ret.as.f         = f;            return ret; }
    static yaoosl_value yaoosl_value_from_double(double d)		  { yaoosl_value ret; ret.type = YVT_DOUBLE;          ret.as.d         = d;            return ret; }
    static yaoosl_value yaoosl_value_from_int8(int8_t int8)		  { yaoosl_value ret; ret.type = YVT_INT8;            ret.as.int8      = int8;         return ret; }
    static yaoosl_value yaoosl_value_from_int16(int16_t int16)	  { yaoosl_value ret; ret.type = YVT_INT16;           ret.as.int16     = int16;        return ret; }
    static yaoosl_value yaoosl_value_from_int32(int32_t int32)	  { yaoosl_value ret; ret.type = YVT_INT32;           ret.as.int32     = int32;        return ret; }
    static yaoosl_value yaoosl_value_from_int64(int64_t int64)	  { yaoosl_value ret; ret.type = YVT_INT64;           ret.as.int64     = int64;        return ret; }
    static yaoosl_value yaoosl_value_from_uint8(uint8_t uint8)	  { yaoosl_value ret; ret.type = YVT_UINT8;           ret.as.uint8     = uint8;        return ret; }
    static yaoosl_value yaoosl_value_from_uint16(uint16_t uint16) { yaoosl_value ret; ret.type = YVT_UINT16;          ret.as.uint16    = uint16;       return ret; }
    static yaoosl_value yaoosl_value_from_uint32(uint32_t uint32) { yaoosl_value ret; ret.type = YVT_UINT32;          ret.as.uint32    = uint32;       return ret; }
    static yaoosl_value yaoosl_value_from_uint64(uint64_t uint64) { yaoosl_value ret; ret.type = YVT_UINT64;          ret.as.uint64    = uint64;       return ret; }
    static yaoosl_value yaoosl_value_from_bool(bool flag)         { yaoosl_value ret; ret.type = YVT_BOOLEAN;         ret.as.flag      = flag;         return ret; }
    static yaoosl_value yaoosl_value_from_ref(yaoosl_ref ref)     { yaoosl_value ret; ret.type = YVT_REFERENCE;       ret.as.reference = ref;          return ret; }

    static yaoosl_value yaoosl_value_from_prop(yaoosl_class* type, yaoosl_value* ref)
    {
        yaoosl_value ret;
        ret.type = YVT_PROPERTY;
        ret.as.prop.type = type;
        ret.as.prop.value = ref;
        return ret;
    }
    static yaoosl_value yaoosl_value_from_method(yaoosl_class* type, yaoosl_method* mthd)
    {
        yaoosl_value ret;
        ret.type = YVT_CALLABLE;
        ret.as.callable.code_page = type->declaring_code_page;
        ret.as.prop.value = mthd;
        return ret;
    }


    static yaoosl_class* create_yaoosl_class(enum yaoosl_encapsulation encapsulation, const char* ns, const char* name)
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

#ifdef __cplusplus
}
#endif // __cplusplus