#include "yaoosl_runtime.h"
#include "yaoosl_value.h"
#include "yaoosl_code_page.h"
#include "yaoosl_opcodes.h"

#include <malloc.h>
#include <string.h>

bool yaoosl_runtime_push_scope(yaoosl_runtime* yvm, yaoosl_scope* scope)
{
    yaoosl_scope** tmp;
    size_t new_capacity = yvm->scopes_capacity + yvm->scopes_capacity + 1;
    if (yvm->values_size == yvm->values_capacity)
    {
        tmp = realloc(yvm->scopes, sizeof(yaoosl_scope*) * new_capacity);
        if (!tmp)
        { // Allocation failed
            return false;
        }
        yvm->scopes = tmp;
        yvm->scopes_capacity = new_capacity;
    }
    yvm->scopes[yvm->scopes_size++] = scope;
    return true;
}

yaoosl_ref yaoosl_reference_create(yaoosl_runtime* yvm, yaoosl_class* type)
{
    return 0;
}

yaoosl_scope* yaoosl_scope_create(size_t slots, yaoosl_code_page* page)
{
	yaoosl_scope* scope = malloc((sizeof(yaoosl_scope) - sizeof(yaoosl_value*)) + (sizeof(yaoosl_value) * slots));
	if (scope)
	{
		scope->associated_page = page;
		scope->position_start = page->code;
		scope->position = page->code;
		scope->position_end = page->code + page->code_size;
		scope->values_size = slots;
		scope->values = &scope->values;
	}
	return scope;
}

#pragma region Code Generating Macros
#define OPEXEC0_PRE(PRE, OP)\
case YVT_DOUBLE:  OP PRE ## as.d      ; break;\
case YVT_BOOLEAN: OP PRE ## as.flag   ; break;\
case YVT_FLOAT:   OP PRE ## as.f      ; break;\
case YVT_INT8:    OP PRE ## as.int8   ; break;\
case YVT_INT16:   OP PRE ## as.int16  ; break;\
case YVT_INT32:   OP PRE ## as.int32  ; break;\
case YVT_INT64:   OP PRE ## as.int64  ; break;\
case YVT_UINT8:   OP PRE ## as.uint8  ; break;\
case YVT_UINT16:  OP PRE ## as.uint16 ; break;\
case YVT_UINT32:  OP PRE ## as.uint32 ; break;\
case YVT_UINT64:  OP PRE ## as.uint64 ; break;
#define OPEXEC0_POST(PRE, OP)\
case YVT_DOUBLE:  PRE ## as.d      OP ; break;\
case YVT_BOOLEAN: PRE ## as.flag   OP ; break;\
case YVT_FLOAT:   PRE ## as.f      OP ; break;\
case YVT_INT8:    PRE ## as.int8   OP ; break;\
case YVT_INT16:   PRE ## as.int16  OP ; break;\
case YVT_INT32:   PRE ## as.int32  OP ; break;\
case YVT_INT64:   PRE ## as.int64  OP ; break;\
case YVT_UINT8:   PRE ## as.uint8  OP ; break;\
case YVT_UINT16:  PRE ## as.uint16 OP ; break;\
case YVT_UINT32:  PRE ## as.uint32 OP ; break;\
case YVT_UINT64:  PRE ## as.uint64 OP ; break;
#pragma endregion



#define ERR_MSG_UNKNOWN_INSTRUCTION "Unknown Instruction."
#define ERR_MSG_JUMP_MOVED_PRE_SCOPE_START "Jump Instruction caused scope position to leave by start."
#define ERR_MSG_JUMP_MOVED_POST_SCOPE_START "Jump Instruction caused scope position to leave by end."
#define ERR_MSG_SCOPE_SLOT_NOT_AVAILABLE "Scope slot requested was not preallocated and thus cannot be accessed."
#define ERR_MSG_VALUE_STACK_EMPTY "Pop Failed. Value stack is empty."
#define ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE "Stack Corruption. Operator ops are not possible on callables."
#define ERR_MSG_STACK_CORRUPTION_OPERATOR_PROPERTY "Stack Corruption. Operator ops cannot execute on nested properties."
#define ERR_MSG_OPERATOR_NOT_IMPLEMENTED "Operator not implemented."


// False if NullPointerException (NPE) could not be catched by any means
static bool yaoosl_runtime_throw_NPE(yaoosl_runtime* yvm) {}
// False if NotImplementedException (NIE) could not be catched by any means
static bool yaoosl_runtime_throw_NIE(yaoosl_runtime* yvm) {}

static uint8_t  r_uint8(yaoosl_scope* scope) { return scope->position <= scope->position_end ? scope->position++ : 0; }
static uint16_t r_uint16(yaoosl_scope* scope) { return ((uint16_t)r_uint8(scope) << (8 * 1)) | ((uint16_t)r_uint8(scope) << (8 * 0)); }
static uint32_t r_uint32(yaoosl_scope* scope) { return ((uint32_t)r_uint16(scope) << (8 * 2)) | ((uint32_t)r_uint16(scope) << (8 * 0)); }
static uint64_t r_uint64(yaoosl_scope* scope) { return ((uint64_t)r_uint32(scope) << (8 * 4)) | ((uint64_t)r_uint32(scope) << (8 * 0)); }
static int8_t   r_int8(yaoosl_scope* scope) { return r_uint8(scope); }
static int16_t  r_int16(yaoosl_scope* scope) { return r_uint16(scope); }
static int32_t  r_int32(yaoosl_scope* scope) { return r_uint32(scope); }
static int64_t  r_int64(yaoosl_scope* scope) { return r_uint64(scope); }
static float    r_float(yaoosl_scope* scope) { union as { uint32_t uint32; float f; } as; as.uint32 = r_uint32(scope); return as.f; }
static double   r_double(yaoosl_scope* scope) { union as { uint64_t uint64; double d; } as; as.uint64 = r_uint64(scope); return as.d; }


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

static yaoosl_scope* create_method_scope(yaoosl_runtime* yvm, yaoosl_class* owning_type, yaoosl_method method)
{
    // Create Scope
    yaoosl_scope* scope = yaoosl_scope_create(method.args_size + method.scope_slots, owning_type->declaring_code_page);
    scope->position_end = scope->position_start + method.method_end;
    scope->position_start = method.method_start;
    scope->position = scope->position_start;
    scope->local_class = owning_type;
    return scope;
}
static bool lookup_method_no_args(yaoosl_method* out_method, yaoosl_method_group method_group, yaoosl_class* method_owner, yaoosl_scope* scope0)
{
    yaoosl_method method;
    size_t i, j;
    yaoosl_value value0;
    for (i = 0; i < method_group.method_size; i++)
    {
        method = method_group.method[i];

        // Ensure Argcount
        if (method.args_size != 0) { continue; }

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
static bool lookup_op_method_group(yaoosl_class* type, enum yaoosl_operator op, yaoosl_method_group* out_method_group)
{
    yaoosl_method_group method_group;
    size_t i;
    for (i = 0; i < type->operators_size; i++)
    {
        method_group = type->operators[i];
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
        1: ERR_MSG_VALUE_STACK_EMPTY
        2: out-of-memory
*/
static int call_method(yaoosl_runtime* yvm, yaoosl_class* owning_type, yaoosl_method method, yaoosl_scope** out_scope)
{
    yaoosl_scope* scope = create_method_scope(yvm, owning_type, method);
    size_t i;
    yaoosl_value value;
    *out_scope = scope;
    // Set the argument slots accordingly
    for (i = 0; i < method.args_size; i++)
    {
        if (!pop_value_stack(yvm, &value))
        {
            free(scope);
            return 1;
        }
        scope->values[i] = value;
    }
    if (!yaoosl_runtime_push_scope(yvm, scope)) { return 2; }
    return 0;
}

/*
    returns:
        0: success
        1: ERR_MSG_VALUE_STACK_EMPTY
        2: Null Pointer Exception
        3: out-of-memory
        4: Not Implemented Exception
        5: ERR_MSG_STACK_CORRUPTION_OPERATOR_PROPERTY
        6: ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE
*/
static int handle_op_r0(yaoosl_runtime* yvm, yaoosl_scope* scope0, enum yaoosl_operator operator)
{
    yaoosl_value value0;
    yaoosl_method_group method_group;
    yaoosl_method method;
    yaoosl_scope* scope1;
    if (!pop_value_stack(yvm, &value0)) { return 1; }
    switch (value0.type)
    {
    case YVT_REFERENCE: {
        if (!value0.as.reference) // Check if reference is null
        {
            return 2;
        }
        if (lookup_op_method_group(value0.as.reference->type, operator, &method_group))
        {
            // Lookup matching method in method-group
            if (lookup_method_no_args(&method, method_group, value0.as.reference->type, scope0))
            {
                switch (call_method(yvm, value0.as.reference->type, method, &scope1))
                {
                case 1: return 1;
                case 2: return 3;
                }
            }
            else
            {
                return 4;
            }
        }
        else
        {
            return 4;
        }
    } break;
    case YVT_PROPERTY: {
        switch (value0.as.prop.value->type)
        {
            OPEXEC0_POST(value0.as.prop.value->, ++)
        default:
            return 5;
        }
    } break;
    case YVT_CALLABLE: return 6;
        OPEXEC0_POST(value0., ++)
    }
}


enum yaoosl_retcde yaoosl_runtime_execute(yaoosl_runtime* yvm, yaoosl_code_page* page, size_t offset)
{
	size_t cur_scope = yvm->scopes_size;
    size_t i = 0;
    size_t j = 0;
	yaoosl_scope* scope0 = yaoosl_scope_create(page->scope_slots, page);
    yaoosl_scope* scope1 = 0;
	enum yaoosl_opcodes opcode;
    yaoosl_as as0;
    yaoosl_as as1;
    yaoosl_value value0;
    yaoosl_value value1;
    yaoosl_method_group method_group;
    yaoosl_method method;
    yaoosl_class* typeptr;
    bool flag = false;
    yaoosl_runtime_push_scope(yvm, scope0);
	while (cur_scope < yvm->scopes_size)
	{
        if (scope0->position >= scope0->position_end)
        {
            free(scope0);
            yvm->scopes_size--;
            if (yvm->scopes_size > 0)
            {
                scope0 = yvm->scopes[yvm->scopes_size - 1];
            }
            continue;
        }
		opcode = *(scope0->position++);
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
            free(scope0);
            yvm->scopes_size--;
            if (yvm->scopes_size > 0)
            {
                scope0 = yvm->scopes[yvm->scopes_size];
            }
            else
            {
                return YSRC_OKAY;
            }
        } break;
#pragma region YOPC_LOAD_PROPERTY
        case YOPC_LOAD_PROPERTY0:       as0.uint16 = 0;               goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY1:       as0.uint16 = 1;               goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY2:       as0.uint16 = 2;               goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY3:       as0.uint16 = 3;               goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY4:       as0.uint16 = 4;               goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY_uint8:  as0.uint16 = r_uint8(scope0);  goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY_uint16: as0.uint16 = r_uint16(scope0); goto YOPC_LOAD_PROPERTY;
        YOPC_LOAD_PROPERTY:
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value0.as.reference) // Check if reference is null
            { if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } break; }

            value0 = yaoosl_value_from_prop(as1.reference->type, value0.as.reference->fields_start + as0.uint16);
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_METHOD
        case YOPC_LOAD_METHOD0:       as0.uint16 = 0;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD1:       as0.uint16 = 1;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD2:       as0.uint16 = 2;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD3:       as0.uint16 = 3;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD4:       as0.uint16 = 4;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD_uint8:  as0.uint16 = r_uint8(scope0);  goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD_uint16: as0.uint16 = r_uint16(scope0); goto YOPC_LOAD_METHOD;
        YOPC_LOAD_METHOD:
            if (!pop_value_stack(yvm, &value0))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value0.as.reference) // Check if reference is null
            { if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } break; }

            value0 = yaoosl_value_from_method(as1.reference->type, value0.as.reference->methods_start + as0.uint16);
            if (!push_value_stack(yvm, value0)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_ARGUMENT
        case YOPC_LOAD_ARGUMENT0:       as0.uint16 = 0;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT1:       as0.uint16 = 1;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT2:       as0.uint16 = 2;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT3:       as0.uint16 = 3;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT4:       as0.uint16 = 4;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT_uint8:  as0.uint16 = r_uint8(scope0);  goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT_uint16: as0.uint16 = r_uint16(scope0); goto YOPC_LOAD_ARGUMENT;
        YOPC_LOAD_ARGUMENT:
            if (scope0->values_size < as0.uint16)
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_SCOPE_SLOT_NOT_AVAILABLE)) { return YSRC_FATAL; } break; }
            if (!push_value_stack(yvm, scope0->values[as0.uint16])) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_STORE_ARGUMENT
        case YOPC_STORE_ARGUMENT0:       as0.uint16 = 0;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT1:       as0.uint16 = 1;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT2:       as0.uint16 = 2;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT3:       as0.uint16 = 3;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT4:       as0.uint16 = 4;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT_uint8:  as0.uint16 = r_uint8(scope0);  goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT_uint16: as0.uint16 = r_uint16(scope0); goto YOPC_STORE_ARGUMENT;
        YOPC_STORE_ARGUMENT:
            if (!pop_value_stack(yvm, &scope0->values[as0.uint16]))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_IMMEDIATE
        case YOPC_LOAD_IMMEDIATE_int8:   value0 = yaoosl_value_from_int8(r_int8(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int16:  value0 = yaoosl_value_from_int16(r_int16(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int32:  value0 = yaoosl_value_from_int32(r_int32(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int64:  value0 = yaoosl_value_from_int64(r_int64(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint8:  value0 = yaoosl_value_from_uint8(r_uint8(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint16: value0 = yaoosl_value_from_uint16(r_uint16(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint32: value0 = yaoosl_value_from_uint32(r_uint32(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint64: value0 = yaoosl_value_from_uint64(r_uint64(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_float:  value0 = yaoosl_value_from_float(r_float(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_double: value0 = yaoosl_value_from_double(r_double(scope0)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_true:   value0 = yaoosl_value_from_bool(true); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_false:  value0 = yaoosl_value_from_bool(false); goto YOPC_LOAD_IMMEDIATE;
        YOPC_LOAD_IMMEDIATE:
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
        case YOPC_JUMP_int8:  as0.int64 = r_int8(scope0);   goto YOPC_JUMP;
        case YOPC_JUMP_int16: as0.int64 = r_int16(scope0);  goto YOPC_JUMP;
        case YOPC_JUMP_int32: as0.int64 = r_int32(scope0);  goto YOPC_JUMP;
        case YOPC_JUMP_int64: as0.int64 = r_int64(scope0);  goto YOPC_JUMP;
        YOPC_JUMP:
            scope0->position += as0.int64;
            if (scope0->position < scope0->position_start)
            {
                if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_JUMP_MOVED_PRE_SCOPE_START)) { return YSRC_FATAL; } break;
            }
            else if (scope0->position > scope0->position_end)
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
        case YOPC_BRANCH_FALSE_int8:  as0.int64 = r_int8(scope0);   goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int16: as0.int64 = r_int16(scope0);  goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int32: as0.int64 = r_int32(scope0);  goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int64: as0.int64 = r_int64(scope0);  goto YOPC_BRANCH_FALSE;
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
        case YOPC_BRANCH_TRUE_int8:  as0.int64 = r_int8(scope0);   goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int16: as0.int64 = r_int16(scope0);  goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int32: as0.int64 = r_int32(scope0);  goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int64: as0.int64 = r_int64(scope0);  goto YOPC_BRANCH_TRUE;
        YOPC_BRANCH_TRUE:
            if (!pop_value_stack(yvm, &as0.reference))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value0.as.flag)
            {
                break;
            }
            // On success, treat as if this was a normal jump instruction
            goto YOPC_JUMP;
#pragma endregion
#pragma region Operators
        case YOPC_INC_r0: {
            switch (handle_op_r0(yvm, scope0, YOP_INC_r0))
            {
            case 1: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } continue;
            case 2: if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } continue;
            case 3: return YSRC_OUT_OF_MEMORY;
            case 4: if (!yaoosl_runtime_throw_NIE(yvm)) { return YSRC_ERROR; } continue;
            case 5: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_PROPERTY)) { return YSRC_FATAL; } continue;
            case 6: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_STACK_CORRUPTION_OPERATOR_CALLABLE)) { return YSRC_FATAL; } continue;
            }
        } break;
        case YOPC_DEC_r0: {
        } break;
        case YOPC_NOT_v1: {
        } break;
        case YOPC_ADD_v2: {
        } break;
        case YOPC_ADD_r1: {
        } break;
        case YOPC_SUB_v2: {
        } break;
        case YOPC_SUB_r1: {
        } break;
        case YOPC_MUL_v2: {
        } break;
        case YOPC_MUL_r1: {
        } break;
        case YOPC_DIV_v2: {
        } break;
        case YOPC_DIV_r1: {
        } break;
        case YOPC_BIT_INV_v2: {
        } break;
        case YOPC_BIT_INV_r1: {
        } break;
        case YOPC_BIT_OR_v2: {
        } break;
        case YOPC_BIT_OR_r1: {
        } break;
        case YOPC_BIT_XOR_v2: {
        } break;
        case YOPC_BIT_XOR_r1: {
        } break;
        case YOPC_BIT_AND_v2: {
        } break;
        case YOPC_BIT_AND_r1: {
        } break;
        case YOPC_LOG_OR_v2: {
        } break;
        case YOPC_LOG_AND_v2: {
        } break;
        case YOPC_LOG_EQUAL_v2: {
        } break;
        case YOPC_LOG_NOTEQUAL_v2: {
        } break;
        case YOPC_LOG_LESS_THEN_v2: {
        } break;
        case YOPC_LOG_GREATER_THEN_v2: {
        } break;
        case YOPC_MOD_v2: {
        } break;
        case YOPC_LSHIFT_v2: {
        } break;
        case YOPC_LSHIFT_r1: {
        } break;
        case YOPC_RSHIFT_v2: {
        } break;
        case YOPC_RSHIFT_r1: {
        } break;
#pragma endregion
		}
	}
}
