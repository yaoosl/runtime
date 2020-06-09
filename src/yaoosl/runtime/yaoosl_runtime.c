#include "yaoosl_runtime.h"
#include "yaoosl_value.h"
#include "yaoosl_code_page.h"
#include "yaoosl_opcodes.h"

#include <malloc.h>
#include <string.h>

static bool yaoosl_runtime_increase_scope_stack(yaoosl_runtime* yvm)
{
    yaoosl_scope* tmp;
    size_t new_capacity = yvm->scopes_capacity + yvm->scopes_capacity + 1;
    if (yvm->values_size == yvm->values_capacity)
    {
        tmp = realloc(yvm->scopes, sizeof(yaoosl_scope) * new_capacity);
        if (!tmp)
        { // Allocation failed
            return false;
        }
        yvm->scopes = tmp;
        yvm->scopes_capacity = new_capacity;
    }
    return true;
}
static bool yaoosl_runtime_ensure_scope_stack(yaoosl_runtime* yvm, size_t size)
{
    while (yvm->scopes_capacity <= size)
    {
        if (!yaoosl_runtime_increase_scope_stack(yvm)) { return false; }
    }
    return true;
}

#pragma region Code Generating Macros
#define OPEXEC1_PRE(LEFT, OP)\
case YVT_FLOAT:   LEFT ## as.f      = OP ( LEFT ## as.f      ); break;\
case YVT_DOUBLE:  LEFT ## as.d      = OP ( LEFT ## as.d      ); break;\
case YVT_BOOLEAN: LEFT ## as.flag   = OP ( LEFT ## as.flag   ); break;\
case YVT_INT8:    LEFT ## as.int8   = OP ( LEFT ## as.int8   ); break;\
case YVT_INT16:   LEFT ## as.int16  = OP ( LEFT ## as.int16  ); break;\
case YVT_INT32:   LEFT ## as.int32  = OP ( LEFT ## as.int32  ); break;\
case YVT_INT64:   LEFT ## as.int64  = OP ( LEFT ## as.int64  ); break;\
case YVT_UINT8:   LEFT ## as.uint8  = OP ( LEFT ## as.uint8  ); break;\
case YVT_UINT16:  LEFT ## as.uint16 = OP ( LEFT ## as.uint16 ); break;\
case YVT_UINT32:  LEFT ## as.uint32 = OP ( LEFT ## as.uint32 ); break;\
case YVT_UINT64:  LEFT ## as.uint64 = OP ( LEFT ## as.uint64 ); break;
#define OPEXEC1_PRE_INT(LEFT, OP)\
case YVT_BOOLEAN: LEFT ## as.flag   = OP ( LEFT ## as.flag   ); break;\
case YVT_INT8:    LEFT ## as.int8   = OP ( LEFT ## as.int8   ); break;\
case YVT_INT16:   LEFT ## as.int16  = OP ( LEFT ## as.int16  ); break;\
case YVT_INT32:   LEFT ## as.int32  = OP ( LEFT ## as.int32  ); break;\
case YVT_INT64:   LEFT ## as.int64  = OP ( LEFT ## as.int64  ); break;\
case YVT_UINT8:   LEFT ## as.uint8  = OP ( LEFT ## as.uint8  ); break;\
case YVT_UINT16:  LEFT ## as.uint16 = OP ( LEFT ## as.uint16 ); break;\
case YVT_UINT32:  LEFT ## as.uint32 = OP ( LEFT ## as.uint32 ); break;\
case YVT_FLOAT:\
case YVT_DOUBLE:\
case YVT_UINT64:  LEFT ## as.uint64 = OP ( LEFT ## as.uint64 ); break;

#define OPEXEC2_(LEFT, OP, RIGHT)\
switch (LEFT ## type)\
{\
case YVT_DOUBLE:   LEFT ## as.d      = ( LEFT ## as.d      ) OP ( RIGHT ## as.d      ); break;\
case YVT_BOOLEAN:  LEFT ## as.flag   = ( LEFT ## as.flag   ) OP ( RIGHT ## as.flag   ); break;\
case YVT_FLOAT:    LEFT ## as.f      = ( LEFT ## as.f      ) OP ( RIGHT ## as.f      ); break;\
case YVT_INT8:     LEFT ## as.int8   = ( LEFT ## as.int8   ) OP ( RIGHT ## as.int8   ); break;\
case YVT_INT16:    LEFT ## as.int16  = ( LEFT ## as.int16  ) OP ( RIGHT ## as.int16  ); break;\
case YVT_INT32:    LEFT ## as.int32  = ( LEFT ## as.int32  ) OP ( RIGHT ## as.int32  ); break;\
case YVT_INT64:    LEFT ## as.int64  = ( LEFT ## as.int64  ) OP ( RIGHT ## as.int64  ); break;\
case YVT_UINT8:    LEFT ## as.uint8  = ( LEFT ## as.uint8  ) OP ( RIGHT ## as.uint8  ); break;\
case YVT_UINT16:   LEFT ## as.uint16 = ( LEFT ## as.uint16 ) OP ( RIGHT ## as.uint16 ); break;\
case YVT_UINT32:   LEFT ## as.uint32 = ( LEFT ## as.uint32 ) OP ( RIGHT ## as.uint32 ); break;\
case YVT_UINT64:   LEFT ## as.uint64 = ( LEFT ## as.uint64 ) OP ( RIGHT ## as.uint64 ); break;\
} break;
#define OPEXEC2(LEFT, OP, RIGHT)\
switch (RIGHT ## type)\
{\
case YVT_DOUBLE:   OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_BOOLEAN:  OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_FLOAT:    OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_INT8:     OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_INT16:    OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_INT32:    OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_INT64:    OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_UINT8:    OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_UINT16:   OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_UINT32:   OPEXEC2_(LEFT, OP, RIGHT)\
case YVT_UINT64:   OPEXEC2_(LEFT, OP, RIGHT)\
}
#define OPEXEC2_INT_(LEFT, OP, RIGHT)\
switch (LEFT ## type)\
{\
case YVT_BOOLEAN:  LEFT ## as.flag   = ( LEFT ## as.flag   ) OP ( RIGHT ## as.flag   ); break;\
case YVT_INT8:     LEFT ## as.int8   = ( LEFT ## as.int8   ) OP ( RIGHT ## as.int8   ); break;\
case YVT_INT16:    LEFT ## as.int16  = ( LEFT ## as.int16  ) OP ( RIGHT ## as.int16  ); break;\
case YVT_INT32:    LEFT ## as.int32  = ( LEFT ## as.int32  ) OP ( RIGHT ## as.int32  ); break;\
case YVT_INT64:    LEFT ## as.int64  = ( LEFT ## as.int64  ) OP ( RIGHT ## as.int64  ); break;\
case YVT_UINT8:    LEFT ## as.uint8  = ( LEFT ## as.uint8  ) OP ( RIGHT ## as.uint8  ); break;\
case YVT_UINT16:   LEFT ## as.uint16 = ( LEFT ## as.uint16 ) OP ( RIGHT ## as.uint16 ); break;\
case YVT_UINT32:   LEFT ## as.uint32 = ( LEFT ## as.uint32 ) OP ( RIGHT ## as.uint32 ); break;\
case YVT_FLOAT:\
case YVT_DOUBLE:\
case YVT_UINT64:   LEFT ## as.uint64 = ( LEFT ## as.uint64 ) OP ( RIGHT ## as.uint64 ); break;\
} break;
#define OPEXEC2_INT(LEFT, OP, RIGHT)\
switch (RIGHT ## type)\
{\
case YVT_BOOLEAN:  OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_INT8:     OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_INT16:    OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_INT32:    OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_INT64:    OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_UINT8:    OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_UINT16:   OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_UINT32:   OPEXEC2_INT_(LEFT, OP, RIGHT)\
case YVT_FLOAT:\
case YVT_DOUBLE:\
case YVT_UINT64:   OPEXEC2_INT_(LEFT, OP, RIGHT)\
}
#pragma endregion
#pragma region Error Messages
#define ERR_MSG_UNKNOWN_INSTRUCTION "Unknown Instruction."
#define ERR_MSG_JUMP_MOVED_PRE_SCOPE_START "Jump Instruction caused scope position to leave by start."
#define ERR_MSG_JUMP_MOVED_POST_SCOPE_START "Jump Instruction caused scope position to leave by end."
#define ERR_MSG_SCOPE_SLOT_NOT_AVAILABLE "Scope slot requested was not preallocated and thus cannot be accessed."
#define ERR_MSG_VALUE_STACK_EMPTY "Pop Failed. Value stack is empty."
#define ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH "Call requires more arguments on the value stack to be present."
#define ERR_MSG_OPERATOR_NOT_IMPLEMENTED "Operator not implemented."
#define ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE "Stack Corruption. Operator ops are not possible on callables."
#define ERR_MSG_STACK_CORRUPTION_OPERATOR_PROPERTY "Stack Corruption. Operator ops cannot execute on nested properties."
#define ERR_MSG_STACK_CORRUPTION_OPERATOR_REFERENCE_RIGHT "Stack Corruption. Primitive left mixed with reference on right."
#define ERR_MSG_STACK_CORRUPTION_EXPECTED_REFERENCE "Stack Corruption. Expected reference or field value."
#define ERR_MSG_STACK_CORRUPTION_EXPECTED_DELEGATE "Stack Corruption. Expected delegate."
#pragma endregion




#pragma region Exception Helpers
// False if NullPointerException (NPE) could not be catched by any means
static bool yaoosl_runtime_throw_NPE(yaoosl_runtime * yvm) { return false; }
// False if NotImplementedException (NIE) could not be catched by any means
static bool yaoosl_runtime_throw_NIE(yaoosl_runtime * yvm) { return false; }
#pragma endregion
#pragma region Bytecode Read Helpers
static uint8_t  r_uint8(yaoosl_scope* scope) { return scope->position <= scope->position_end ? *(scope->position++) : 0; }
static uint16_t r_uint16(yaoosl_scope* scope) { return ((uint16_t)r_uint8(scope) << (8 * 1)) | ((uint16_t)r_uint8(scope) << (8 * 0)); }
static uint32_t r_uint32(yaoosl_scope* scope) { return ((uint32_t)r_uint16(scope) << (8 * 2)) | ((uint32_t)r_uint16(scope) << (8 * 0)); }
static uint64_t r_uint64(yaoosl_scope* scope) { return ((uint64_t)r_uint32(scope) << (8 * 4)) | ((uint64_t)r_uint32(scope) << (8 * 0)); }
static int8_t   r_int8(yaoosl_scope* scope) { return r_uint8(scope); }
static int16_t  r_int16(yaoosl_scope* scope) { return r_uint16(scope); }
static int32_t  r_int32(yaoosl_scope* scope) { return r_uint32(scope); }
static int64_t  r_int64(yaoosl_scope* scope) { return r_uint64(scope); }
static float    r_float(yaoosl_scope* scope) { union as { uint32_t uint32; float f; } as; as.uint32 = r_uint32(scope); return as.f; }
static double   r_double(yaoosl_scope* scope) { union as { uint64_t uint64; double d; } as; as.uint64 = r_uint64(scope); return as.d; }
#pragma endregion
#pragma region Value Stack Manipulation
// Pops a value from the stack and puts it into out_value.
// Returns:
// - true:  pop was successfull
// - false: pop failed as stack size is empty
static bool pop_value_stack(yaoosl_runtime* yvm, yaoosl_value * out_value)
{
    if (yvm->values_size == 0)
    {
        return false;
    }
    else
    {
        *out_value = yvm->values[--yvm->values_size];
        return true;
    }
}
// Pushes a value to the stack.
// Returns:
// - true:  push was successfull
// - false: push required resizing the values stack and realloc returned NULL (OUT_OF_MEMORY)
static bool push_value_stack(yaoosl_runtime* yvm, yaoosl_value value)
{
    yaoosl_value* tmp;
    size_t new_capacity = yvm->values_capacity + yvm->values_capacity + 1;
    if (yvm->values_size == yvm->values_capacity)
    {
        tmp = realloc(yvm->values, sizeof(yaoosl_value) * new_capacity);
        if (!tmp)
        { // Allocation failed
            return false;
        }
        yvm->values = tmp;
        yvm->values_capacity = new_capacity;
    }
    yvm->values[yvm->values_size++] = value;
    return true;
}
#pragma endregion


static bool lookup_method_no_args(yaoosl_method* out_method, yaoosl_method_group method_group, yaoosl_classtemplate* method_owner, yaoosl_scope* scope0)
{
    yaoosl_method method;
    size_t i, j;
    for (i = 0; i < method_group.method_size; i++)
    {
        method = method_group.method[i];

        // Ensure Argcount
        if (method.args_size != 0) { continue; }

        // Ensure Accessrights
        switch (method.encapsulation)
        {
        case YENCPS_INTERNAL: if (strncmp(method_owner->full_namespace, scope0->local_class->full_namespace, strlen(scope0->local_class->full_namespace))) { continue; }  break;
        case YENCPS_DERIVED:
            for (j = 0; j < method_owner->implements_size; j++)
            {
                if (method_owner->implements[i] == scope0->local_class)
                {
                    break;
                }
            }
            if (method_owner->implements_size == j) { continue; }
            break;
        case YENCPS_PRIVATE: if (method_owner != scope0->local_class) { continue; } break;
        }

        *out_method = method;
        return true;
    }
    return false;
}

/*
    summary:
        Looks up a method matching the arguments residing on the value stack currently
        and the return-type.
    remarks:
        Analyzes the value-stack of the runtime.
    returns:
        true: Method found.
        false: Method not found.
*/
static bool lookup_method_analyzing_value_stack(
    yaoosl_runtime* yvm,
    yaoosl_method* out_method,
    yaoosl_method_group method_group,
    yaoosl_classtemplate* method_owner,
    yaoosl_scope* scope0,
    yaoosl_classtemplate* return_type)
{
    yaoosl_method method;
    size_t i, j;
    yaoosl_value value0;
    bool match;
    for (i = 0; i < method_group.method_size; i++)
    {
        method = method_group.method[i];

        // Ensure Argcount
        if (method.args_size > yvm->values_size) { continue; }

        // Ensure Argtypes
        match = false;
        for (j = 0; j < method.args_size; j++)
        {
            value0 = yvm->values[yvm->values_size - j];
            if (value0.type == YVT_REFERENCE)
            {
                if (method.args[j].type != YVT_REFERENCE || method.args[j].as.reference->type != value0.as.reference->type)
                {
                    match = false;
                    break;
                }
            }
            else if (value0.type != method.args[j].type)
            {
                match = false;
                break;
            }
        }
        if (!match) { continue; }

        // Ensure Returntype
        if (method.return_type != return_type) { continue; }

        // Ensure Accessrights
        switch (method.encapsulation)
        {
        case YENCPS_INTERNAL: if (strncmp(method_owner->full_namespace, scope0->local_class->full_namespace, strlen(scope0->local_class))) { continue; }  break;
        case YENCPS_DERIVED:
            for (j = 0; j < method_owner->implements_size; j++)
            {
                if (method_owner->implements[i] == scope0->local_class)
                {
                    break;
                }
            }
            if (method_owner->implements_size == j) { continue; }
            break;
        case YENCPS_PRIVATE: if (method_owner != scope0->local_class) { continue; } break;
        }

        *out_method = method;
        return true;
    }
    return false;
}

/*
    returns:
        true: method group found
        false: method group not found
*/
static bool lookup_op_method_group(yaoosl_classtemplate* type, enum yaoosl_operator op, yaoosl_method_group* out_method_group)
{
    yaoosl_method_group method_group;
    size_t i;
    for (i = 0; i < type->methods_size; i++)
    {
        method_group = type->methods[i];
        if (method_group.operator_implementation == op)
        {
            *out_method_group = method_group;
            return true;
        }
    }
    return false;
}
/*
    returns:
        0: success
        1: out-of-memory
        2: ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH
*/
static int call_method(yaoosl_runtime* yvm, yaoosl_method method, yaoosl_classtemplate* local_type, yaoosl_code_page* local_page)
{
    const int RET_OK = 0;
    const int RET_OUT_OF_MEM = 1;
    const int RET_VALUE_STACK_SIZE_ARG_MISSMATCH = 2;
    yaoosl_scope* scope;
    yaoosl_value value = { 0 };

    // Perform checks
    if (yvm->values_size < method.args_size) { return RET_VALUE_STACK_SIZE_ARG_MISSMATCH; }
    if (!yaoosl_runtime_ensure_scope_stack(yvm, yvm->scopes_size)) { return RET_OUT_OF_MEM; }

    // Ensure values are available
    if (!local_type) { local_type = method.owning_group->owning_type; }
    if (!local_page) { local_page = local_type->declaring_code_page; }

    // Prepare scope
    scope = yvm->scopes + yvm->scopes_size++;
    scope->values = yvm->values - method.args_size;
    scope->local_class = local_type;
    scope->associated_page = local_page;
    scope->position = scope->position_start = local_page->code + method.method_start;
    scope->position_end = local_page->code + method.method_end;

    // Reserve space variable slots if needed
    while (yvm->values_size < method.args_size + method.varslots)
    {
        push_value_stack(yvm, value);
    }

    // Return a happy success
    return RET_OK;
}

/*
    valuestack-in:
        0: The value to enact the op_r0 on
    valuestack-out:
        0: The value that was enacted
    returns:
        0: success
        1: out-of-memory
        2: Null Pointer Exception
        3: Not Implemented Exception
        4: ERR_MSG_VALUE_STACK_EMPTY
        5: ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE
        6: ERR_MSG_STACK_CORRUPTION_EXPECTED_REFERENCE
        7: ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH
*/
static int handle_op_r0(yaoosl_runtime* yvm, yaoosl_scope* scope0, enum yaoosl_operator op)
{
    const int RET_OK = 0;
    const int RET_OUT_OF_MEMORY = 1;
    const int RET_NULL_EXCEPTION = 2;
    const int RET_NOT_IMPLEMENTED_EXCEPTION = 3;
    const int RET_VAL_STACK_EMPTY = 4;
    const int RET_STKCRPT_CALLABLE = 5;
    const int RET_STKCRPT_REFERENCE = 6;
    const int RET_CALL_COUNT_MSSMTCH = 7;

    yaoosl_value value0;
    yaoosl_method_group method_group;
    yaoosl_method method;
    if (!pop_value_stack(yvm, &value0)) { return RET_VAL_STACK_EMPTY; }
    switch (value0.type)
    {
    case YVT_REFERENCE: {
        if (!value0.as.reference) // Check if reference is null
        {
            return RET_NULL_EXCEPTION;
        }
        if (lookup_op_method_group(value0.as.reference->type, op, &method_group))
        {
            if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
            // Lookup matching method in method-group
            if (lookup_method_no_args(&method, method_group, value0.as.reference->type, scope0))
            {
                switch (call_method(yvm, method, value0.as.reference->type, 0))
                {
                case 1: return RET_CALL_COUNT_MSSMTCH;
                case 2: return RET_OUT_OF_MEMORY;
                }
            }
            else
            {
                return RET_NOT_IMPLEMENTED_EXCEPTION;
            }
        }
        else
        {
            return RET_NOT_IMPLEMENTED_EXCEPTION;
        }
    } break;
    case YVT_DELEGATE: return RET_STKCRPT_CALLABLE;
    case YVT_FIELD:
        value0 = *value0.as.field;
        switch (op)
        {
        case YOP_INC_r0: switch (value0.type) { OPEXEC1_PRE(value0.as.field->, 1 + ) } break;
        case YOP_DEC_r0: switch (value0.type) { OPEXEC1_PRE(value0.as.field->, 1 - ) } break;
        case YOP_BIT_INV_r0: switch (value0.type) { OPEXEC1_PRE_INT(value0.as.field->, ~) } break;
        }
        if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
        break;
    default: return RET_STKCRPT_REFERENCE;
    }
    return RET_OK;
}
/*
    valuestack-in:
        0: The value to enact the op_r1 on
        1: The first argument
    valuestack-out:
        0: The value that was enacted
    returns:
        0: success
        1: out-of-memory
        2: Null Pointer Exception
        3: Not Implemented Exception
        4: ERR_MSG_VALUE_STACK_EMPTY
        5: ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE
        6: ERR_MSG_STACK_CORRUPTION_OPERATOR_REFERENCE_RIGHT
        7: ERR_MSG_STACK_CORRUPTION_EXPECTED_REFERENCE
        8: ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH
*/
static int handle_op_r1(yaoosl_runtime* yvm, yaoosl_scope* scope0, enum yaoosl_operator op)
{
    const int RET_OK = 0;
    const int RET_OUT_OF_MEMORY = 1;
    const int RET_NULL_EXCEPTION = 2;
    const int RET_NOT_IMPLEMENTED_EXCEPTION = 3;
    const int RET_VAL_STACK_EMPTY = 4;
    const int RET_STKCRPT_CALLABLE = 5;
    const int RET_STKCRPT_REFERENCE_RIGHT = 6;
    const int RET_STKCRPT_REFERENCE = 7;
    const int RET_CALL_COUNT_MSSMTCH = 8;

    yaoosl_value value0, value1;
    yaoosl_method_group method_group;
    yaoosl_method method;
    yaoosl_scope* scope1;
    if (!pop_value_stack(yvm, &value0)) { return RET_VAL_STACK_EMPTY; }
    switch (value0.type)
    {
    case YVT_REFERENCE: {
        if (!value0.as.reference) // Check if reference is null
        {
            return RET_NULL_EXCEPTION;
        }
        if (lookup_op_method_group(value0.as.reference->type, op, &method_group))
        {
            if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
            // Lookup matching method in method-group
            if (lookup_method_no_args(&method, method_group, value0.as.reference->type, scope0))
            {
                switch (call_method(yvm, method, value0.as.reference->type, 0))
                {
                case 1: return RET_OUT_OF_MEMORY;
                case 2: return RET_CALL_COUNT_MSSMTCH;
                }
            }
            else
            {
                return RET_NOT_IMPLEMENTED_EXCEPTION;
            }
        }
        else
        {
            return RET_NOT_IMPLEMENTED_EXCEPTION;
        }
    } break;
    case YVT_DELEGATE: return RET_STKCRPT_CALLABLE;
    case YVT_FIELD:
        if (!pop_value_stack(yvm, &value1)) { return RET_VAL_STACK_EMPTY; }
        switch (value1.type)
        {
        case YVT_REFERENCE: return RET_STKCRPT_REFERENCE_RIGHT;
        case YVT_DELEGATE: return RET_STKCRPT_CALLABLE;
        case YVT_FIELD: break;
        default: return RET_STKCRPT_REFERENCE;
        }
        switch (op)
        {
        case YOP_ADD_r1:                switch (value0.type) { OPEXEC2(    value0.as.field->, +,  value1.as.field->) } break;
        case YOP_SUB_r1:                switch (value0.type) { OPEXEC2(    value0.as.field->, -,  value1.as.field->) } break;
        case YOP_MUL_r1:                switch (value0.type) { OPEXEC2(    value0.as.field->, *,  value1.as.field->) } break;
        case YOP_DIV_r1:                switch (value0.type) { OPEXEC2(    value0.as.field->, /,  value1.as.field->) } break;
        case YOP_BIT_OR_r1:             switch (value0.type) { OPEXEC2_INT(value0.as.field->, |,  value1.as.field->) } break;
        case YOP_BIT_XOR_r1:            switch (value0.type) { OPEXEC2_INT(value0.as.field->, ^,  value1.as.field->) } break;
        case YOP_BIT_AND_r1:            switch (value0.type) { OPEXEC2_INT(value0.as.field->, &,  value1.as.field->) } break;
        case YOP_MOD_r1:                switch (value0.type) { OPEXEC2_INT(value0.as.field->, %,  value1.as.field->) } break;
        case YOP_LSHIFT_r1:             switch (value0.type) { OPEXEC2_INT(value0.as.field->, <<, value1.as.field->) } break;
        case YOP_RSHIFT_r1:             switch (value0.type) { OPEXEC2_INT(value0.as.field->, >>, value1.as.field->) } break;
        }
        if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
        break;
    default: return RET_STKCRPT_REFERENCE;
    }
    return RET_OK;
}
/*
    valuestack-in:
        0: The value to enact the op_b1 on
        1: The first argument
    valuestack-out:
        0: The value that was enacted
    returns:
        0: success
        1: out-of-memory
        2: Null Pointer Exception
        3: Not Implemented Exception
        4: ERR_MSG_VALUE_STACK_EMPTY
        5: ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE
        6: ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH
*/
static int handle_op_v1(yaoosl_runtime* yvm, yaoosl_scope* scope0, enum yaoosl_operator op)
{
    const int RET_OK = 0;
    const int RET_OUT_OF_MEMORY = 1;
    const int RET_NULL_EXCEPTION = 2;
    const int RET_NOT_IMPLEMENTED_EXCEPTION = 3;
    const int RET_VAL_STACK_EMPTY = 4;
    const int RET_STKCRPT_CALLABLE = 5;
    const int RET_CALL_COUNT_MSSMTCH = 6;

    yaoosl_value value0;
    yaoosl_method_group method_group;
    yaoosl_method method;
    yaoosl_scope* scope1;
    if (!pop_value_stack(yvm, &value0)) { return RET_VAL_STACK_EMPTY; }
    switch (value0.type)
    {
    case YVT_REFERENCE: {
        if (!value0.as.reference) // Check if reference is null
        {
            return RET_NULL_EXCEPTION;
        }
        if (lookup_op_method_group(value0.as.reference->type, op, &method_group))
        {
            if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
            // Lookup matching method in method-group
            if (lookup_method_no_args(&method, method_group, value0.as.reference->type, scope0))
            {
                switch (call_method(yvm, method, value0.as.reference->type, 0))
                {
                case 1: return RET_OUT_OF_MEMORY;
                case 2: return RET_CALL_COUNT_MSSMTCH;
                }
            }
            else
            {
                return RET_NOT_IMPLEMENTED_EXCEPTION;
            }
        }
        else
        {
            return RET_NOT_IMPLEMENTED_EXCEPTION;
        }
    } break;
    case YVT_DELEGATE: return RET_STKCRPT_CALLABLE;
    case YVT_FIELD:
        value0 = *value0.as.field;
        /* FALL THROUGH */
    default:
        switch (op)
        {
        case YOP_NOT_v1: switch (value0.type) { OPEXEC1_PRE(value0., !) } break;
        case YOP_BIT_INV_v1: switch (value0.type) { OPEXEC1_PRE_INT(value0., ~) } break;
        }
        if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
    }
    return RET_OK;
}
/*
    valuestack-in:
        0: The value to enact the op_r2 on
        1: The left argument
        1: The right argument
    valuestack-out:
        0: The value that was produced
    returns:
        0: success
        1: out-of-memory
        2: Null Pointer Exception
        3: Not Implemented Exception
        4: ERR_MSG_VALUE_STACK_EMPTY
        5: ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE
        6: ERR_MSG_STACK_CORRUPTION_OPERATOR_REFERENCE_RIGHT
        7: ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH
*/
static int handle_op_v2(yaoosl_runtime* yvm, yaoosl_scope* scope0, enum yaoosl_operator op)
{
    const int RET_OK = 0;
    const int RET_OUT_OF_MEMORY = 1;
    const int RET_NULL_EXCEPTION = 2;
    const int RET_NOT_IMPLEMENTED_EXCEPTION = 3;
    const int RET_VAL_STACK_EMPTY = 4;
    const int RET_STKCRPT_CALLABLE = 5;
    const int RET_STKCRPT_REFERENCE_RIGHT = 6;
    const int RET_CALL_COUNT_MSSMTCH = 7;

    yaoosl_value value0, value1;
    yaoosl_method_group method_group;
    yaoosl_method method;
    if (!pop_value_stack(yvm, &value0)) { return RET_VAL_STACK_EMPTY; }
    switch (value0.type)
    {
    case YVT_REFERENCE: {
        if (!value0.as.reference) // Check if reference is null
        {
            return RET_NULL_EXCEPTION;
        }
        if (lookup_op_method_group(value0.as.reference->type, op, &method_group))
        {
            if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
            // Lookup matching method in method-group
            if (lookup_method_no_args(&method, method_group, value0.as.reference->type, scope0))
            {
                switch (call_method(yvm, method, value0.as.reference->type, 0))
                {
                case 1: return RET_OUT_OF_MEMORY;
                case 2: return RET_CALL_COUNT_MSSMTCH;
                }
            }
            else
            {
                return RET_NOT_IMPLEMENTED_EXCEPTION;
            }
        }
        else
        {
            return RET_NOT_IMPLEMENTED_EXCEPTION;
        }
    } break;
    case YVT_DELEGATE: return RET_STKCRPT_CALLABLE;
    case YVT_FIELD:
        value0 = *value0.as.field;
        /* FALL THROUGH */
    default:
        if (!pop_value_stack(yvm, &value1)) { return RET_VAL_STACK_EMPTY; }
        switch (value1.type)
        {
        case YVT_REFERENCE: return RET_STKCRPT_REFERENCE_RIGHT;
        case YVT_DELEGATE: return RET_STKCRPT_CALLABLE;
        case YVT_FIELD:
            value1 = *value1.as.field;
        }
        switch (op)
        {
        case YOP_ADD_v2:                switch (value0.type) { OPEXEC2(value0., + , value1.) } break;
        case YOP_SUB_v2:                switch (value0.type) { OPEXEC2(value0., - , value1.) } break;
        case YOP_MUL_v2:                switch (value0.type) { OPEXEC2(value0., * , value1.) } break;
        case YOP_DIV_v2:                switch (value0.type) { OPEXEC2(value0., / , value1.) } break;
        case YOP_BIT_OR_v2:             switch (value0.type) { OPEXEC2_INT(value0., | , value1.) } break;
        case YOP_BIT_XOR_v2:            switch (value0.type) { OPEXEC2_INT(value0., ^ , value1.) } break;
        case YOP_BIT_AND_v2:            switch (value0.type) { OPEXEC2_INT(value0., & , value1.) } break;
        case YOP_LOG_OR_v2:             switch (value0.type) { OPEXEC2(value0., ||, value1.) } break;
        case YOP_LOG_AND_v2:            switch (value0.type) { OPEXEC2(value0., &&, value1.) } break;
        case YOP_LOG_EQUAL_v2:          switch (value0.type) { OPEXEC2(value0., ==, value1.) } break;
        case YOP_LOG_NOTEQUAL_v2:       switch (value0.type) { OPEXEC2(value0., !=, value1.) } break;
        case YOP_LOG_LESS_THEN_v2:      switch (value0.type) { OPEXEC2(value0., < , value1.) } break;
        case YOP_LOG_GREATER_THEN_v2:   switch (value0.type) { OPEXEC2(value0., > , value1.) } break;
        case YOP_MOD_v2:                switch (value0.type) { OPEXEC2_INT(value0., % , value1.) } break;
        case YOP_LSHIFT_v2:             switch (value0.type) { OPEXEC2_INT(value0., <<, value1.) } break;
        case YOP_RSHIFT_v2:             switch (value0.type) { OPEXEC2_INT(value0., >>, value1.) } break;
        }
        if (!push_value_stack(yvm, value0)) { return RET_OUT_OF_MEMORY; }
    }
    return RET_OK;
}

#define YVMSCPVAL (yvm->values_size - (scope_active->values - yvm->values))
enum yaoosl_retcde yaoosl_runtime_execute(yaoosl_runtime* yvm, yaoosl_code_page* page, size_t offset, yaoosl_classtemplate* local_class)
{
	size_t cur_scope = yvm->scopes_size;
    size_t i = 0;
    size_t j = 0;
	yaoosl_scope* scope_active;
	enum yaoosl_opcodes opcode;
    yaoosl_as as0;
    yaoosl_value value0;
    yaoosl_value value1;
    enum yaoosl_operator op;

    // Prepare top-scope
    if (!yaoosl_runtime_ensure_scope_stack(yvm, 1)) { return YSRC_OUT_OF_MEMORY; }
    scope_active = yvm->scopes + (yvm->scopes_size - 1);
    scope_active->associated_page = page;
    scope_active->position_start = page->code;
    scope_active->position = page->code + offset;
    scope_active->position_end = page->code + page->code_size;
    scope_active->values = yvm->values + yvm->values_size;
    scope_active->local_class = local_class;

    // Start execution loop
	while (cur_scope < yvm->scopes_size)
	{
        if (scope_active->position >= scope_active->position_end)
        {
            yvm->scopes_size--;
            if (yvm->scopes_size > 0)
            {
                scope_active = yvm->scopes + (yvm->scopes_size - 1);
            }
            continue;
        }
		opcode = *(scope_active->position++);
		switch (opcode)
		{
        default: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_UNKNOWN_INSTRUCTION)) { return YSRC_FATAL; } break;
        case YOPC_NOP: /* DO NOTHING */ break;
        case YOPC_BREAK: /* DEBUG HALT REACHED */ return YSRC_BREAK;
        case YOPC_DUPLICATE_VALUE: {
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }
        } break;
        case YOPC_POP_SCOPE: {
            // Get delta from start of this scope
            j = YVMSCPVAL;

            // Pop delta values to reset to lower scope
            for (i = 0; i < j; i++)
            {
                if (!pop_value_stack(yvm, &value0))
                { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            }

            // Remove scope from runtime
            yvm->scopes_size--;
            if (yvm->scopes_size > 0)
            {
                scope_active = yvm->scopes + (yvm->scopes_size - 1);
            }
            else
            {
                return YSRC_OKAY;
            }
        } break;
        case YOPC_POP_SCOPE_WITH_VALUE: {
            // Get delta from start of this scope, excluding the return value
            j = YVMSCPVAL - 1;

            // Pop the return value
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }

            // Pop delta values to reset to lower scope
            for (i = 0; i < j; i++)
            {
                if (!pop_value_stack(yvm, &value1))
                { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            }

            // Push the return value 
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }

            // Remove scope from runtime
            yvm->scopes_size--;
            if (yvm->scopes_size > 0)
            {
                scope_active = yvm->scopes + (yvm->scopes_size - 1);
            }
            else
            {
                return YSRC_OKAY;
            }
        } break;
        case YOPC_CALL: {
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (value0.type != YVT_DELEGATE)
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_EXPECTED_DELEGATE)) { return YSRC_FATAL; } break; }

            switch (call_method(yvm, value0.as.delegate, value0.as.reference->type, 0))
            {
            case 1: return YSRC_OUT_OF_MEMORY;
            case 2: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH)) { return YSRC_FATAL; } break;
            }
        } break;
#pragma region YOPC_LOAD_PROPERTY
        case YOPC_LOAD_PROPERTY0:       as0.uint16 = 0;                      goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY1:       as0.uint16 = 1;                      goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY2:       as0.uint16 = 2;                      goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY3:       as0.uint16 = 3;                      goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY4:       as0.uint16 = 4;                      goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY_uint8:  as0.uint16 = r_uint8(scope_active);  goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY_uint16: as0.uint16 = r_uint16(scope_active); goto YOPC_LOAD_PROPERTY;
        YOPC_LOAD_PROPERTY:
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value0.as.reference) // Check if reference is null
            { if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } break; }

            value0 = yaoosl_value_from_field(value0.as.reference->fields_start + as0.uint16);
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_METHOD
        case YOPC_LOAD_METHOD0:       as0.uint16 = 0;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD1:       as0.uint16 = 1;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD2:       as0.uint16 = 2;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD3:       as0.uint16 = 3;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD4:       as0.uint16 = 4;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD_uint8:  as0.uint16 = r_uint8(scope_active);  goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD_uint16: as0.uint16 = r_uint16(scope_active); goto YOPC_LOAD_METHOD;
        YOPC_LOAD_METHOD:
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value0.as.reference) // Check if reference is null
            { if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } break; }

            value0 = yaoosl_value_from_method(value0.as.reference->methods_start[as0.uint16]);
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_ARGUMENT
        case YOPC_LOAD_ARGUMENT0:       as0.uint16 = 0;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT1:       as0.uint16 = 1;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT2:       as0.uint16 = 2;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT3:       as0.uint16 = 3;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT4:       as0.uint16 = 4;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT_uint8:  as0.uint16 = r_uint8(scope_active);  goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT_uint16: as0.uint16 = r_uint16(scope_active); goto YOPC_LOAD_ARGUMENT;
        YOPC_LOAD_ARGUMENT:
            if (YVMSCPVAL < as0.uint16)
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_SCOPE_SLOT_NOT_AVAILABLE)) { return YSRC_FATAL; } break; }
            if (!push_value_stack(yvm, scope_active->values[as0.uint16])) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_STORE_ARGUMENT
        case YOPC_STORE_ARGUMENT0:       as0.uint16 = 0;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT1:       as0.uint16 = 1;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT2:       as0.uint16 = 2;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT3:       as0.uint16 = 3;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT4:       as0.uint16 = 4;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT_uint8:  as0.uint16 = r_uint8(scope_active);  goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT_uint16: as0.uint16 = r_uint16(scope_active); goto YOPC_STORE_ARGUMENT;
        YOPC_STORE_ARGUMENT:
            if (YVMSCPVAL < as0.uint16)
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_SCOPE_SLOT_NOT_AVAILABLE)) { return YSRC_FATAL; } break; }
            if (!pop_value_stack(yvm, &scope_active->values[as0.uint16]))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_IMMEDIATE
        case YOPC_LOAD_IMMEDIATE_int8:   value0 = yaoosl_value_from_int8(r_int8(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int16:  value0 = yaoosl_value_from_int16(r_int16(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int32:  value0 = yaoosl_value_from_int32(r_int32(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int64:  value0 = yaoosl_value_from_int64(r_int64(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint8:  value0 = yaoosl_value_from_uint8(r_uint8(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint16: value0 = yaoosl_value_from_uint16(r_uint16(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint32: value0 = yaoosl_value_from_uint32(r_uint32(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint64: value0 = yaoosl_value_from_uint64(r_uint64(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_float:  value0 = yaoosl_value_from_float(r_float(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_double: value0 = yaoosl_value_from_double(r_double(scope_active)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_true:   value0 = yaoosl_value_from_bool(true); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_false:  value0 = yaoosl_value_from_bool(false); goto YOPC_LOAD_IMMEDIATE;
        YOPC_LOAD_IMMEDIATE:
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_DELEGATE
        case YOPC_LOAD_DELEGATE_uint8:  as0.uint64 = r_uint8(scope_active);   goto YOPC_LOAD_DELEGATE;
        case YOPC_LOAD_DELEGATE_uint16: as0.uint64 = r_uint16(scope_active);  goto YOPC_LOAD_DELEGATE;
        case YOPC_LOAD_DELEGATE_uint32: as0.uint64 = r_uint32(scope_active);  goto YOPC_LOAD_DELEGATE;
        case YOPC_LOAD_DELEGATE_uint64: as0.uint64 = r_uint64(scope_active);  goto YOPC_LOAD_DELEGATE;
        YOPC_LOAD_DELEGATE:
            value0 = yaoosl_value_from_method(*scope_active->associated_page->methods[as0.uint16]);
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_JUMP
        case YOPC_JUMP5B:     as0.int64 = -5; goto YOPC_JUMP;
        case YOPC_JUMP4B:     as0.int64 = -4; goto YOPC_JUMP;
        case YOPC_JUMP3B:     as0.int64 = -3; goto YOPC_JUMP;
        case YOPC_JUMP2B:     as0.int64 = -2; goto YOPC_JUMP;
        case YOPC_JUMP1B:     as0.int64 = -1; goto YOPC_JUMP;
        case YOPC_JUMP1F:     as0.int64 = +1; goto YOPC_JUMP;
        case YOPC_JUMP2F:     as0.int64 = +2; goto YOPC_JUMP;
        case YOPC_JUMP3F:     as0.int64 = +3; goto YOPC_JUMP;
        case YOPC_JUMP4F:     as0.int64 = +4; goto YOPC_JUMP;
        case YOPC_JUMP5F:     as0.int64 = +5; goto YOPC_JUMP;
        case YOPC_JUMP_int8:  as0.int64 = r_int8(scope_active);   goto YOPC_JUMP;
        case YOPC_JUMP_int16: as0.int64 = r_int16(scope_active);  goto YOPC_JUMP;
        case YOPC_JUMP_int32: as0.int64 = r_int32(scope_active);  goto YOPC_JUMP;
        case YOPC_JUMP_int64: as0.int64 = r_int64(scope_active);  goto YOPC_JUMP;
        YOPC_JUMP:
            scope_active->position += as0.int64;
            if (scope_active->position < scope_active->position_start)
            {
                if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_JUMP_MOVED_PRE_SCOPE_START)) { return YSRC_FATAL; } break;
            }
            else if (scope_active->position > scope_active->position_end)
            {
                if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_JUMP_MOVED_POST_SCOPE_START)) { return YSRC_FATAL; } break;
            }
            break;
#pragma endregion
#pragma region YOPC_BRANCH_FALSE
        case YOPC_BRANCH_FALSE1F:     as0.int64 = +1;              goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE2F:     as0.int64 = +2;              goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE3F:     as0.int64 = +3;              goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE4F:     as0.int64 = +4;              goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE5F:     as0.int64 = +5;              goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int8:  as0.int64 = r_int8(scope_active);   goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int16: as0.int64 = r_int16(scope_active);  goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int32: as0.int64 = r_int32(scope_active);  goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int64: as0.int64 = r_int64(scope_active);  goto YOPC_BRANCH_FALSE;
        YOPC_BRANCH_FALSE:
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (value0.as.flag)
            {
                break;
            }
            // On success, treat as if this was a normal jump instruction
            goto YOPC_JUMP;
#pragma endregion
#pragma region YOPC_BRANCH_TRUE
        case YOPC_BRANCH_TRUE1F:     as0.int64 = +1;              goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE2F:     as0.int64 = +2;              goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE3F:     as0.int64 = +3;              goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE4F:     as0.int64 = +4;              goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE5F:     as0.int64 = +5;              goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int8:  as0.int64 = r_int8(scope_active);   goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int16: as0.int64 = r_int16(scope_active);  goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int32: as0.int64 = r_int32(scope_active);  goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int64: as0.int64 = r_int64(scope_active);  goto YOPC_BRANCH_TRUE;
        YOPC_BRANCH_TRUE:
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value0.as.flag)
            {
                break;
            }
            // On success, treat as if this was a normal jump instruction
            goto YOPC_JUMP;
#pragma endregion
#pragma region YOPC_OP_r0
        case YOPC_INC_r0:
            op = YOP_INC_r0;
            goto YOPC_OP_r0;
        case YOPC_DEC_r0:
            op = YOP_DEC_r0;
            goto YOPC_OP_r0;
        case YOPC_BIT_INV_r0:
            op = YOP_BIT_INV_r0;
            goto YOPC_OP_r0;

        YOPC_OP_r0:
            switch (handle_op_r0(yvm, scope_active, op))
            {
            case 1: return YSRC_OUT_OF_MEMORY;
            case 2: if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } continue;
            case 3: if (!yaoosl_runtime_throw_NIE(yvm)) { return YSRC_ERROR; } continue;
            case 4: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } continue;
            case 5: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE)) { return YSRC_FATAL; } continue;
            case 6: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_EXPECTED_REFERENCE)) { return YSRC_FATAL; } continue;
            case 7: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH)) { return YSRC_FATAL; } continue;
            }
            break;
#pragma endregion
#pragma region YOPC_OP_r1
        case YOPC_ADD_r1:
            op = YOP_ADD_r1;
            goto YOPC_OP_r1;
        case YOPC_SUB_r1:
            op = YOP_SUB_r1;
            goto YOPC_OP_r1;
        case YOPC_MUL_r1:
            op = YOP_MUL_r1;
            goto YOPC_OP_r1;
        case YOPC_DIV_r1:
            op = YOP_DIV_r1;
            goto YOPC_OP_r1;
        case YOPC_RSHIFT_r1:
            op = YOP_RSHIFT_r1;
            goto YOPC_OP_r1;
        case YOPC_LSHIFT_r1:
            op = YOP_LSHIFT_r1;
            goto YOPC_OP_r1;
        case YOPC_MOD_r1:
            op = YOP_MOD_r1;
            goto YOPC_OP_r1;
        case YOPC_BIT_AND_r1:
            op = YOP_BIT_AND_r1;
            goto YOPC_OP_r1;
        case YOPC_BIT_OR_r1:
            op = YOP_BIT_OR_r1;
            goto YOPC_OP_r1;
        case YOPC_BIT_XOR_r1:
            op = YOP_BIT_XOR_r1;
            goto YOPC_OP_r1;
        YOPC_OP_r1:
            switch (handle_op_r1(yvm, scope_active, op))
            {
            case 1: return YSRC_OUT_OF_MEMORY;
            case 2: if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } continue;
            case 3: if (!yaoosl_runtime_throw_NIE(yvm)) { return YSRC_ERROR; } continue;
            case 4: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } continue;
            case 5: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE)) { return YSRC_FATAL; } continue;
            case 6: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_REFERENCE_RIGHT)) { return YSRC_FATAL; } continue;
            case 7: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_EXPECTED_REFERENCE)) { return YSRC_FATAL; } continue;
            case 8: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH)) { return YSRC_FATAL; } continue;
            }
            break;
#pragma endregion
#pragma region YOPC_OP_v1
        case YOPC_NOT_v1:
            op = YOP_ADD_r1;
            goto YOPC_OP_v1;
        case YOPC_BIT_INV_v1:
            op = YOP_BIT_INV_v1;
            goto YOPC_OP_v1;
        YOPC_OP_v1:
            switch (handle_op_v1(yvm, scope_active, op))
            {
            case 1: return YSRC_OUT_OF_MEMORY;
            case 2: if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } continue;
            case 3: if (!yaoosl_runtime_throw_NIE(yvm)) { return YSRC_ERROR; } continue;
            case 4: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } continue;
            case 5: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE)) { return YSRC_FATAL; } continue;
            case 6: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH)) { return YSRC_FATAL; } continue;
            }
            break;
#pragma endregion
#pragma region YOPC_OP_v2
        case YOPC_ADD_v2:
            op = YOP_ADD_v2;
            goto YOPC_OP_v2;
        case YOPC_SUB_v2:
            op = YOP_SUB_v2;
            goto YOPC_OP_v2;
        case YOPC_MUL_v2:
            op = YOP_MUL_v2;
            goto YOPC_OP_v2;
        case YOPC_DIV_v2:
            op = YOP_DIV_v2;
            goto YOPC_OP_v2;
        case YOPC_BIT_OR_v2:
            op = YOP_BIT_OR_v2;
            goto YOPC_OP_v2;
        case YOPC_BIT_XOR_v2:
            op = YOP_BIT_XOR_v2;
            goto YOPC_OP_v2;
        case YOPC_BIT_AND_v2:
            op = YOP_BIT_AND_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_OR_v2:
            op = YOP_LOG_OR_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_AND_v2:
            op = YOP_LOG_AND_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_EQUAL_v2:
            op = YOP_LOG_EQUAL_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_NOTEQUAL_v2:
            op = YOP_LOG_NOTEQUAL_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_LESS_THEN_v2:
            op = YOP_LOG_LESS_THEN_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_LESS_THEN_OR_EQUAL_v2:
            op = YOP_LOG_LESS_THEN_OR_EQUAL_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_GREATER_THEN_v2:
            op = YOP_LOG_GREATER_THEN_v2;
            goto YOPC_OP_v2;
        case YOPC_LOG_GREATER_THEN_OR_EQUAL_v2:
            op = YOP_LOG_GREATER_THEN_OR_EQUAL_v2;
            goto YOPC_OP_v2;
        case YOPC_MOD_v2:
            op = YOP_MOD_v2;
            goto YOPC_OP_v2;
        case YOPC_LSHIFT_v2:
            op = YOP_LSHIFT_v2;
            goto YOPC_OP_v2;
        case YOPC_RSHIFT_v2:
            op = YOP_RSHIFT_v2;
            goto YOPC_OP_v2;
        YOPC_OP_v2:
            switch (handle_op_v2(yvm, scope_active, op))
            {
            case 1: return YSRC_OUT_OF_MEMORY;
            case 2: if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } continue;
            case 3: if (!yaoosl_runtime_throw_NIE(yvm)) { return YSRC_ERROR; } continue;
            case 4: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } continue;
            case 5: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE)) { return YSRC_FATAL; } continue;
            case 6: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_REFERENCE_RIGHT)) { return YSRC_FATAL; } continue;
            case 7: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_CALL_COUNT_MISSMATCH)) { return YSRC_FATAL; } continue;
            }
            break;
#pragma endregion
		}
	}
    return YSRC_OKAY;
}


yaoosl_runtime* yaoosl_runtime_create()
{
    yaoosl_runtime* yvm = malloc(sizeof(yaoosl_runtime));
    if (yvm)
    {
        // Init runtime to defaults
        memset(yvm, 0, sizeof(yaoosl_runtime));
    }
    return yvm;
}

void yaoosl_runtime_destroy(yaoosl_runtime* runtime)
{
    size_t i;

    free(runtime->values);
    runtime->values_capacity = runtime->values_size = 0;

    free(runtime->scopes);
    runtime->scopes_capacity = runtime->scopes_size = 0;

    for (i = 0; i < runtime->references_size; i++)
    {
        free(runtime->references[i]);
    }

    // ToDo: Free code-pages

    free(runtime);
}