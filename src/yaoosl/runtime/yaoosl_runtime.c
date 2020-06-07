#include "yaoosl_runtime.h"
#include "yaoosl_value.h"
#include "yaoosl_code_page.h"
#include "yaoosl_opcodes.h"

#include <malloc.h>

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

#define ERR_MSG_UNKNOWN_INSTRUCTION "Unknown Instruction."
#define ERR_MSG_JUMP_MOVED_PRE_SCOPE_START "Jump Instruction caused scope position to leave by start."
#define ERR_MSG_JUMP_MOVED_POST_SCOPE_START "Jump Instruction caused scope position to leave by end."
#define ERR_MSG_SCOPE_SLOT_NOT_AVAILABLE "Scope slot requested was not preallocated and thus cannot be accessed."
#define ERR_MSG_VALUE_STACK_EMPTY "Pop Failed. Value stack is empty."

// False if NPE could not be catched by any means
static bool yaoosl_runtime_throw_NPE(yaoosl_runtime* yvm) {}

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
enum yaoosl_retcde yaoosl_runtime_execute(yaoosl_runtime* yvm, yaoosl_code_page* page, size_t offset)
{
	size_t cur_scope = yvm->scopes_size;
	yaoosl_scope* scope = yaoosl_scope_create(page->scope_slots, page);
	enum yaoosl_opcodes opcode;
    yaoosl_as as0;
    yaoosl_as as1;
    yaoosl_value value;
	while (cur_scope < yvm->scopes_size)
	{
		opcode = *(scope->position++);
		switch (opcode)
		{
        default: if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_UNKNOWN_INSTRUCTION)) { return YSRC_FATAL; } break;
        case YOPC_NOP: /* DO NOTHING */ break;
        case YOPC_BREAK: /* DEBUG HALT REACHED */ return YSRC_BREAK;
        case YOPC_DUPLICATE_VALUE: {
            if (!pop_value_stack(yvm, &value))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!push_value_stack(yvm, value)) { return YSRC_OUT_OF_MEMORY; }
        } break;
        case YOPC_POP_SCOPE: {
            free(scope);
            yvm->scopes_size--;
            if (yvm->scopes_size > 0)
            {
                scope = yvm->scopes[yvm->scopes_size];
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
        case YOPC_LOAD_PROPERTY_uint8:  as0.uint16 = r_uint8(scope);  goto YOPC_LOAD_PROPERTY;
        case YOPC_LOAD_PROPERTY_uint16: as0.uint16 = r_uint16(scope); goto YOPC_LOAD_PROPERTY;
        YOPC_LOAD_PROPERTY:
            if (!pop_value_stack(yvm, &value))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value.as.reference) // Check if reference is null
            { if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } break; }

            value = yaoosl_value_from_prop(as1.reference->type, value.as.reference->fields_start + as0.uint16);
            if (!push_value_stack(yvm, value)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_METHOD
        case YOPC_LOAD_METHOD0:       as0.uint16 = 0;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD1:       as0.uint16 = 1;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD2:       as0.uint16 = 2;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD3:       as0.uint16 = 3;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD4:       as0.uint16 = 4;               goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD_uint8:  as0.uint16 = r_uint8(scope);  goto YOPC_LOAD_METHOD;
        case YOPC_LOAD_METHOD_uint16: as0.uint16 = r_uint16(scope); goto YOPC_LOAD_METHOD;
        YOPC_LOAD_METHOD:
            if (!pop_value_stack(yvm, &value))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value.as.reference) // Check if reference is null
            { if (!yaoosl_runtime_throw_NPE(yvm)) { return YSRC_ERROR; } break; }

            value = yaoosl_value_from_method(as1.reference->type, value.as.reference->methods_start + as0.uint16);
            if (!push_value_stack(yvm, value)) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_ARGUMENT
        case YOPC_LOAD_ARGUMENT0:       as0.uint16 = 0;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT1:       as0.uint16 = 1;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT2:       as0.uint16 = 2;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT3:       as0.uint16 = 3;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT4:       as0.uint16 = 4;               goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT_uint8:  as0.uint16 = r_uint8(scope);  goto YOPC_LOAD_ARGUMENT;
        case YOPC_LOAD_ARGUMENT_uint16: as0.uint16 = r_uint16(scope); goto YOPC_LOAD_ARGUMENT;
        YOPC_LOAD_ARGUMENT:
            if (scope->values_size < as0.uint16)
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_SCOPE_SLOT_NOT_AVAILABLE)) { return YSRC_FATAL; } break; }
            if (!push_value_stack(yvm, scope->values[as0.uint16])) { return YSRC_OUT_OF_MEMORY; }
            break;
#pragma endregion
#pragma region YOPC_STORE_ARGUMENT
        case YOPC_STORE_ARGUMENT0:       as0.uint16 = 0;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT1:       as0.uint16 = 1;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT2:       as0.uint16 = 2;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT3:       as0.uint16 = 3;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT4:       as0.uint16 = 4;               goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT_uint8:  as0.uint16 = r_uint8(scope);  goto YOPC_STORE_ARGUMENT;
        case YOPC_STORE_ARGUMENT_uint16: as0.uint16 = r_uint16(scope); goto YOPC_STORE_ARGUMENT;
        YOPC_STORE_ARGUMENT:
            if (!pop_value_stack(yvm, &scope->values[as0.uint16]))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            break;
#pragma endregion
#pragma region YOPC_LOAD_IMMEDIATE
        case YOPC_LOAD_IMMEDIATE_int8:   value = yaoosl_value_from_int8(r_int8(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int16:  value = yaoosl_value_from_int16(r_int16(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int32:  value = yaoosl_value_from_int32(r_int32(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_int64:  value = yaoosl_value_from_int64(r_int64(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint8:  value = yaoosl_value_from_uint8(r_uint8(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint16: value = yaoosl_value_from_uint16(r_uint16(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint32: value = yaoosl_value_from_uint32(r_uint32(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_uint64: value = yaoosl_value_from_uint64(r_uint64(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_float:  value = yaoosl_value_from_float(r_float(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_double: value = yaoosl_value_from_double(r_double(scope)); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_true:   value = yaoosl_value_from_bool(true); goto YOPC_LOAD_IMMEDIATE;
        case YOPC_LOAD_IMMEDIATE_false:  value = yaoosl_value_from_bool(false); goto YOPC_LOAD_IMMEDIATE;
        YOPC_LOAD_IMMEDIATE:
            if (!push_value_stack(yvm, value)) { return YSRC_OUT_OF_MEMORY; }
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
        case YOPC_JUMP_int8:  as0.int64 = r_int8(scope);   goto YOPC_JUMP;
        case YOPC_JUMP_int16: as0.int64 = r_int16(scope);  goto YOPC_JUMP;
        case YOPC_JUMP_int32: as0.int64 = r_int32(scope);  goto YOPC_JUMP;
        case YOPC_JUMP_int64: as0.int64 = r_int64(scope);  goto YOPC_JUMP;
        YOPC_JUMP:
            scope->position += as0.int64;
            if (scope->position < scope->position_start)
            {
                if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_JUMP_MOVED_PRE_SCOPE_START)) { return YSRC_FATAL; } break;
            }
            else if (scope->position > scope->position_end)
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
        case YOPC_BRANCH_FALSE_int8:  as0.int64 = r_int8(scope);   goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int16: as0.int64 = r_int16(scope);  goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int32: as0.int64 = r_int32(scope);  goto YOPC_BRANCH_FALSE;
        case YOPC_BRANCH_FALSE_int64: as0.int64 = r_int64(scope);  goto YOPC_BRANCH_FALSE;
        YOPC_BRANCH_FALSE:
            if (!pop_value_stack(yvm, &value))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (value.as.flag)
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
        case YOPC_BRANCH_TRUE_int8:  as0.int64 = r_int8(scope);   goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int16: as0.int64 = r_int16(scope);  goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int32: as0.int64 = r_int32(scope);  goto YOPC_BRANCH_TRUE;
        case YOPC_BRANCH_TRUE_int64: as0.int64 = r_int64(scope);  goto YOPC_BRANCH_TRUE;
        YOPC_BRANCH_TRUE:
            if (!pop_value_stack(yvm, &as0.reference))
            { if (!yvm->fatal_callback || yvm->fatal_callback(yvm, opcode, ERR_MSG_VALUE_STACK_EMPTY)) { return YSRC_FATAL; } break; }
            if (!value.as.flag)
            {
                break;
            }
            // On success, treat as if this was a normal jump instruction
            goto YOPC_JUMP;
#pragma endregion
#pragma region Operators
        case YOPC_INC_r0:
            break;
        case YOPC_DEC_r0:
            break;
        case YOPC_NOT_v1:
            break;
        case YOPC_ADD_v2:
            break;
        case YOPC_ADD_r1:
            break;
        case YOPC_SUB_v2:
            break;
        case YOPC_SUB_r1:
            break;
        case YOPC_MUL_v2:
            break;
        case YOPC_MUL_r1:
            break;
        case YOPC_DIV_v2:
            break;
        case YOPC_DIV_r1:
            break;
        case YOPC_BIT_INV_v2:
            break;
        case YOPC_BIT_INV_r1:
            break;
        case YOPC_BIT_OR_v2:
            break;
        case YOPC_BIT_OR_r1:
            break;
        case YOPC_BIT_XOR_v2:
            break;
        case YOPC_BIT_XOR_r1:
            break;
        case YOPC_BIT_AND_v2:
            break;
        case YOPC_BIT_AND_r1:
            break;
        case YOPC_LOG_OR_v2:
            break;
        case YOPC_LOG_AND_v2:
            break;
        case YOPC_LOG_EQUAL_v2:
            break;
        case YOPC_LOG_NOTEQUAL_v2:
            break;
        case YOPC_LOG_LESS_THEN_v2:
            break;
        case YOPC_LOG_GREATER_THEN_v2:
            break;
        case YOPC_MOD_v2:
            break;
        case YOPC_LSHIFT_v2:
            break;
        case YOPC_LSHIFT_r1:
            break;
        case YOPC_RSHIFT_v2:
            break;
        case YOPC_RSHIFT_r1:
            break;
#pragma endregion
		}
	}
}
