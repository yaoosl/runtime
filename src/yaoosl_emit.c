#include "yaoosl_emit.h"

#include <malloc.h>
#include <string.h>

bool yaoosl_emit_uint8(yaooslcodehandle code, uint8_t value)
{
	uint8_t* bytes;
	if (code->bytes_size == code->bytes_capacity)
	{
		bytes = realloc(code->bytes, sizeof(uint8_t) * (code->bytes_capacity + code->bytes_capacity + 1));
		if (!bytes)
		{
			return false;
		}
		code->bytes = bytes;
		code->bytes_capacity = code->bytes_capacity + code->bytes_capacity + 1;
	}
	code->bytes[code->bytes_size++] = value;
	return true;
}
bool yaoosl_emit_uint16(yaooslcodehandle code, uint16_t value)
{
	return yaoosl_emit_uint8(code, (uint8_t)(value >> (8 * 1))) && yaoosl_emit_uint8(code, (uint8_t)(value >> (8 * 0)));
}
bool yaoosl_emit_uint32(yaooslcodehandle code, uint32_t value)
{
	return yaoosl_emit_uint16(code, (uint16_t)(value >> (8 * 2))) && yaoosl_emit_uint16(code, (uint16_t)(value >> (8 * 0)));
}
bool yaoosl_emit_uint64(yaooslcodehandle code, uint64_t value)
{
	return yaoosl_emit_uint32(code, (uint32_t)(value >> (8 * 4))) && yaoosl_emit_uint32(code, (uint32_t)(value >> (8 * 0)));
}
bool yaoosl_emit_uint(yaooslcodehandle code, uint64_t value)
{
	if (value <= UINT8_MAX)
	{
		return yaoosl_emit_uint8(code, value);
	} 
	else if (value <= UINT16_MAX)
	{
		return yaoosl_emit_uint16(code, value);
	}
	else if (value <= UINT32_MAX)
	{
		return yaoosl_emit_uint32(code, value);
	}
	else
	{
		return yaoosl_emit_uint64(code, value);
	}
}
bool yaoosl_emit_int8(yaooslcodehandle code, int8_t value)
{
	return yaoosl_emit_uint8(code, (uint8_t)value);
}
bool yaoosl_emit_int16(yaooslcodehandle code, int16_t value)
{
	return yaoosl_emit_uint16(code, (int16_t)value);
}
bool yaoosl_emit_int32(yaooslcodehandle code, int32_t value)
{
	return yaoosl_emit_uint32(code, (int32_t)value);
}
bool yaoosl_emit_int64(yaooslcodehandle code, int64_t value)
{
	return yaoosl_emit_uint64(code, (int64_t)value);
}

bool yaoosl_emit_opcode(yaooslcodehandle code, enum yaoosl_opcode opcode)
{
	switch (sizeof(enum yaoosl_opcode))
	{
	case 1:
		return yaoosl_emit_uint8(code, (uint8_t)opcode);
	case 2:
		return yaoosl_emit_uint16(code, (uint16_t)opcode);
	case 4:
		return yaoosl_emit_uint32(code, (uint32_t)opcode);
	default:
		return yaoosl_emit_uint64(code, (uint64_t)opcode);
	}
}

bool yaoosl_emit_trim_excess_from_codehandle(yaooslcodehandle code)
{
	uint8_t* bytes;
	if (code->bytes_size != code->bytes_capacity)
	{
		bytes = realloc(code->bytes, sizeof(uint8_t) * (code->bytes_size));
		if (!bytes)
		{
			return false;
		}
		code->bytes = bytes;
		code->bytes_capacity = code->bytes_size;
	}
	return true;
}

bool yaoosl_emit_prepend_class_declaration(yaooslcodehandle code, const char* classname)
{
	size_t len = strlen(classname);
	size_t size = len * sizeof(char) + sizeof(enum yaoosl_opcode) + sizeof(uint16_t);
	uint8_t* bytes;
	size_t i;
	uint64_t tmp;

	if (code->bytes_size + size >= code->bytes_capacity)
	{
		bytes = realloc(code->bytes, sizeof(uint8_t) * (code->bytes_size + size));
		if (!bytes)
		{
			return false;
		}
		code->bytes = bytes;
		code->bytes_capacity = code->bytes_size + size;
	}

	for (i = code->bytes_size - 1; i != ~(size_t)0; i--)
	{
		code->bytes[i + size] = code->bytes[i];
	}
	tmp = code->bytes_size + size;
	code->bytes_size = 0;

	// Following methods CANNOT FAIL to allocate memory as we allocated the required memory above
	yaoosl_emit_opcode(code, OPC_DECLARE_CLASS_a16);
	yaoosl_emit_uint16(code, (uint16_t)len);
	for (len = 0; classname[len] != '\0'; len++)
	{
		yaoosl_emit_int8(code, classname[len]);
	}
	code->bytes_size = tmp;

	return true;
}

bool yaoosl_emit_nop(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_NOP);
}
bool yaoosl_emit_jump_off_a8(yaooslcodehandle code, int8_t value)
{
	return yaoosl_emit_opcode(code, OPC_JUMP_OFF_a8) && yaoosl_emit_int8(code, value);
}
bool yaoosl_emit_jump_off_a16(yaooslcodehandle code, int16_t value)
{
	return yaoosl_emit_opcode(code, OPC_JUMP_OFF_a16) && yaoosl_emit_int16(code, value);
}
bool yaoosl_emit_jump_off_a32(yaooslcodehandle code, int32_t value)
{
	return yaoosl_emit_opcode(code, OPC_JUMP_OFF_a32) && yaoosl_emit_int32(code, value);
}
bool yaoosl_emit_jump_off_a(yaooslcodehandle code, int32_t value)
{
	if (value < INT8_MAX && value > INT8_MIN)
	{
		return yaoosl_emit_jump_off_a8(code, value);
	}
	else if (value < INT16_MAX && value > INT16_MIN)
	{
		return yaoosl_emit_jump_off_a16(code, value);
	}
	else
	{
		return yaoosl_emit_jump_off_a32(code, value);
	}
}
bool yaoosl_emit_skip_if_true(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_SKIP_IF_TRUE);
}
bool yaoosl_emit_skip_if_false(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_SKIP_IF_FALSE);
}
bool yaoosl_emit_skip_if_in_exception(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_SKIP_IF_IN_EXCEPTION);
}
bool yaoosl_emit_block_push(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_BLOCK_PUSH);
}
bool yaoosl_emit_block_prefix(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_BLOCK_PREFIX);
}
bool yaoosl_emit_block_pop(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_BLOCK_POP);
}
bool yaoosl_emit_block_catch(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_BLOCK_CATCH);
}
bool yaoosl_emit_block_throw(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_BLOCK_THROW);
}
bool yaoosl_emit_prepend_scope_allocate_a(yaooslcodehandle code, uint16_t value)
{
	size_t size = sizeof(enum yaoosl_opcode) + (value <= UINT8_MAX ? sizeof(uint8_t) : sizeof(uint16_t));
	uint8_t* bytes;
	size_t i;
	uint64_t tmp;

	if (code->bytes_size + size >= code->bytes_capacity)
	{
		bytes = realloc(code->bytes, sizeof(uint8_t) * (code->bytes_size + size));
		if (!bytes)
		{
			return false;
		}
		code->bytes = bytes;
		code->bytes_capacity = code->bytes_size + size;
	}

	for (i = code->bytes_size; i != ~(size_t)0; i--)
	{
		code->bytes[i + size] = code->bytes[i];
	}
	tmp = code->bytes_size + size;
	code->bytes_size = 0;

	// Following methods CANNOT FAIL to allocate memory as we allocated the required memory above
	yaoosl_emit_scope_allocate_a(code, value);
	code->bytes_size = tmp;
	return true;
}
bool yaoosl_emit_scope_allocate_a(yaooslcodehandle code, uint16_t value)
{
	if (value <= UINT8_MAX)
	{
		return yaoosl_emit_scope_allocate_a8(code, value);
	}
	return yaoosl_emit_scope_allocate_a16(code, value);
}
bool yaoosl_emit_scope_allocate_a8(yaooslcodehandle code, uint8_t value)
{
	return yaoosl_emit_opcode(code, OPC_SCOPE_ALLOCATE_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_scope_allocate_a16(yaooslcodehandle code, uint16_t value)
{
	return yaoosl_emit_opcode(code, OPC_SCOPE_ALLOCATE_a16) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_scope_pop(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_SCOPE_POP);
}
bool yaoosl_emit_set_value_a8(yaooslcodehandle code, uint8_t value)
{
	return yaoosl_emit_opcode(code, OPC_SET_VALUE_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_set_value_a16(yaooslcodehandle code, uint16_t value)
{
	return yaoosl_emit_opcode(code, OPC_SET_VALUE_a8) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_set_value_a(yaooslcodehandle code, uint16_t value)
{
	if (value < INT8_MAX)
	{
		return yaoosl_emit_set_value_a8(code, value);
	}
	else 
	{
		return yaoosl_emit_set_value_a16(code, value);
	}
}
bool yaoosl_emit_get_value_a8(yaooslcodehandle code, uint8_t value)
{
	return yaoosl_emit_opcode(code, OPC_GET_VALUE_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_get_value_a16(yaooslcodehandle code, uint16_t value)
{
	return yaoosl_emit_opcode(code, OPC_GET_VALUE_a8) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_get_value_a(yaooslcodehandle code, uint16_t value)
{
	if (value < INT8_MAX)
	{
		return yaoosl_emit_get_value_a8(code, value);
	}
	else
	{
		return yaoosl_emit_get_value_a16(code, value);
	}
}
bool yaoosl_emit_pop_value(yaooslcodehandle code) 
{
	return yaoosl_emit_opcode(code, OPC_POP_VALUE);
}
bool yaoosl_emit_clear_values(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CLEAR_VALUES);
}
bool yaoosl_emit_duplicate_value(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_DUPLICATE_VALUE);
}
bool yaoosl_emit_create_class_begin_a16(yaooslcodehandle code, uint16_t value)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_CLASS_BEGIN_a16) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_create_class_begin_a(yaooslcodehandle code, const char* name)
{
	size_t len = strlen(name);
	if (!yaoosl_emit_create_class_begin_a16(code, (uint16_t)len)) { return false; }
	for (len = 0; name[len] != '\0'; len++)
	{
		if (!yaoosl_emit_int8(code, name[len])) { return false; }
	}
	return true;
}
bool yaoosl_emit_create_class_baseclass(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_CLASS_BASECLASS);
}
bool yaoosl_emit_create_class_baseclass2(yaooslcodehandle code, const char* base)
{
	return yaoosl_emit_push_string(code, base) && yaoosl_emit_resolve_type(code) && yaoosl_emit_create_class_baseclass(code);
}
bool yaoosl_emit_create_class_end(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_CLASS_END);
}
bool yaoosl_emit_create_method_begin(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_METHOD_BEGIN);
}
bool yaoosl_emit_create_method_return(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_METHOD_RETURN);
}
bool yaoosl_emit_create_method_return2(yaooslcodehandle code, const char* fqtype)
{
	return yaoosl_emit_push_string(code, fqtype) && yaoosl_emit_resolve_type(code) && yaoosl_emit_create_method_return(code);
}
bool yaoosl_emit_create_method_name(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_METHOD_NAME);
}
bool yaoosl_emit_create_method_name2(yaooslcodehandle code, const char* name)
{
	return yaoosl_emit_push_string(code, name) && yaoosl_emit_create_method_name(code);
}
bool yaoosl_emit_create_method_operator(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_METHOD_OPERATOR);
}
bool yaoosl_emit_create_method_operator2(yaooslcodehandle code, const char* operator)
{
	return yaoosl_emit_push_string(code, operator) && yaoosl_emit_create_method_operator(code);
}
bool yaoosl_emit_create_method_arg(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_METHOD_ARG);
}
bool yaoosl_emit_create_method_arg2(yaooslcodehandle code, const char* fqtype, const char* name)
{
	return yaoosl_emit_push_string(code, fqtype) && yaoosl_emit_resolve_type(code) && yaoosl_emit_push_string(code, name) && yaoosl_emit_opcode(code, OPC_CREATE_METHOD_ARG);
}
bool yaoosl_emit_create_method_codeblock_a64(yaooslcodehandle code, uint64_t value)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_METHOD_CODEBLOCK_a64) && yaoosl_emit_uint64(code, value);
}
bool yaoosl_emit_create_method_end(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_METHOD_END);
}
bool yaoosl_emit_create_property_begin(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_PROPERTY_BEGIN);
}
bool yaoosl_emit_create_property_name(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_PROPERTY_NAME);
}
bool yaoosl_emit_create_property_name2(yaooslcodehandle code, const char* name)
{
	return yaoosl_emit_push_string(code, name) && yaoosl_emit_create_property_name(code);
}
bool yaoosl_emit_create_property_return(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_PROPERTY_RETURN);
}
bool yaoosl_emit_create_property_return2(yaooslcodehandle code, const char* fqtype)
{
	return yaoosl_emit_push_string(code, fqtype) && yaoosl_emit_resolve_type(code) && yaoosl_emit_create_property_return(code);
}
bool yaoosl_emit_create_property_end(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_CREATE_PROPERTY_END);
}
bool yaoosl_emit_navigate_property_a(yaooslcodehandle code, const char* property)
{
	size_t len;
	len = strlen(property);

	if (len <= UINT8_MAX)
	{
		if (!yaoosl_emit_navigate_property_a8(code, (uint8_t)len)) { return false; }
	}
	else if (len <= UINT16_MAX)
	{
		if (!yaoosl_emit_navigate_property_a16(code, (uint16_t)len)) { return false; }
	}
	else
	{
		if (!yaoosl_emit_navigate_property_a32(code, (uint32_t)len)) { return false; }
	}
	for (len = 0; property[len] != '\0'; len++)
	{
		if (!yaoosl_emit_int8(code, property[len])) { return false; }
	}
	return true;
}
bool yaoosl_emit_navigate_property_a8(yaooslcodehandle code, int8_t value)
{
	return yaoosl_emit_opcode(code, OPC_NAVIGATE_PROPERTY_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_navigate_property_a16(yaooslcodehandle code, int16_t value)
{
	return yaoosl_emit_opcode(code, OPC_NAVIGATE_PROPERTY_a16) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_navigate_property_a32(yaooslcodehandle code, int32_t value)
{
	return yaoosl_emit_opcode(code, OPC_NAVIGATE_PROPERTY_a32) && yaoosl_emit_uint32(code, value);
}
bool yaoosl_emit_set_property_a(yaooslcodehandle code, const char* property)
{
	size_t len;
	len = strlen(property);

	if (len <= UINT8_MAX)
	{
		if (!yaoosl_emit_set_property_a8(code, (uint8_t)len)) { return false; }
	}
	else if (len <= UINT16_MAX)
	{
		if (!yaoosl_emit_set_property_a16(code, (uint16_t)len)) { return false; }
	}
	else
	{
		if (!yaoosl_emit_set_property_a32(code, (uint32_t)len)) { return false; }
	}
	for (len = 0; property[len] != '\0'; len++)
	{
		if (!yaoosl_emit_int8(code, property[len])) { return false; }
	}
	return true;
}
bool yaoosl_emit_set_property_a8(yaooslcodehandle code, int8_t value)
{
	return yaoosl_emit_opcode(code, OPC_SET_PROPERTY_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_set_property_a16(yaooslcodehandle code, int16_t value)
{
	return yaoosl_emit_opcode(code, OPC_SET_PROPERTY_a16) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_set_property_a32(yaooslcodehandle code, int32_t value)
{
	return yaoosl_emit_opcode(code, OPC_SET_PROPERTY_a32) && yaoosl_emit_uint32(code, value);
}
bool yaoosl_emit_call_a_b8(yaooslcodehandle code, const char* str, uint8_t argc)
{
	size_t len;
	len = strlen(str);

	if (len <= UINT8_MAX)
	{
		if (!yaoosl_emit_call_a8_b8(code, (uint8_t)len, argc)) { return false; }
	}
	else if (len <= UINT16_MAX)
	{
		if (!yaoosl_emit_call_a16_b8(code, (uint16_t)len, argc)) { return false; }
	}
	else
	{
		if (!yaoosl_emit_call_a32_b8(code, (uint32_t)len, argc)) { return false; }
	}
	for (len = 0; str[len] != '\0'; len++)
	{
		if (!yaoosl_emit_int8(code, str[len])) { return false; }
	}
	return true;
}
bool yaoosl_emit_call_a8_b8(yaooslcodehandle code, uint8_t strlen, uint8_t argc)
{
	return yaoosl_emit_opcode(code, OPC_CALL_a8_b8) && yaoosl_emit_uint8(code, strlen) && yaoosl_emit_uint8(code, argc);
}
bool yaoosl_emit_call_a16_b8(yaooslcodehandle code, uint16_t strlen, uint8_t argc)
{
	return yaoosl_emit_opcode(code, OPC_CALL_a16_b8) && yaoosl_emit_uint16(code, strlen) && yaoosl_emit_uint8(code, argc);
}
bool yaoosl_emit_call_a32_b8(yaooslcodehandle code, uint32_t strlen, uint8_t argc)
{
	return yaoosl_emit_opcode(code, OPC_CALL_a32_b8) && yaoosl_emit_uint32(code, strlen) && yaoosl_emit_uint8(code, argc);
}
bool yaoosl_emit_call_self_a_b8(yaooslcodehandle code, const char* str, uint8_t argc)
{
	size_t len;
	len = strlen(str);

	if (len <= UINT8_MAX)
	{
		if (!yaoosl_emit_call_self_a8_b8(code, (uint8_t)len, argc)) { return false; }
	}
	else if (len <= UINT16_MAX)
	{
		if (!yaoosl_emit_call_self_a16_b8(code, (uint16_t)len, argc)) { return false; }
	}
	else
	{
		if (!yaoosl_emit_call_self_a32_b8(code, (uint32_t)len, argc)) { return false; }
	}
	for (len = 0; str[len] != '\0'; len++)
	{
		if (!yaoosl_emit_int8(code, str[len])) { return false; }
	}
	return true;
}
bool yaoosl_emit_call_self_a8_b8(yaooslcodehandle code, uint8_t strlen, uint8_t argc)
{
	return yaoosl_emit_opcode(code, OPC_CALL_SELF_a8_b8) && yaoosl_emit_uint8(code, strlen) && yaoosl_emit_uint8(code, argc);
}
bool yaoosl_emit_call_self_a16_b8(yaooslcodehandle code, uint16_t strlen, uint8_t argc)
{
	return yaoosl_emit_opcode(code, OPC_CALL_SELF_a16_b8) && yaoosl_emit_uint16(code, strlen) && yaoosl_emit_uint8(code, argc);
}
bool yaoosl_emit_call_self_a32_b8(yaooslcodehandle code, uint32_t strlen, uint8_t argc)
{
	return yaoosl_emit_opcode(code, OPC_CALL_SELF_a32_b8) && yaoosl_emit_uint32(code, strlen) && yaoosl_emit_uint8(code, argc);
}
bool yaoosl_emit_increment(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_INCREMENT);
}
bool yaoosl_emit_decrement(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_DECREMENT);
}
bool yaoosl_emit_a_add(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_ADD);
}
bool yaoosl_emit_a_subtract(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SUBTRACT);
}
bool yaoosl_emit_a_multiplicate(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_MULTIPLICATE);
}
bool yaoosl_emit_a_divide(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_DIVIDE);
}
bool yaoosl_emit_a_and(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_AND);
}
bool yaoosl_emit_a_or(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_OR);
}
bool yaoosl_emit_a_xor(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_XOR);
}
bool yaoosl_emit_a_bitshift_left(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_BITSHIFT_LEFT);
}
bool yaoosl_emit_a_bitshift_right(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_BITSHIFT_RIGHT);
}
bool yaoosl_emit_a_modulo(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_MODULO);
}
bool yaoosl_emit_a_invert(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_INVERT);
}
bool yaoosl_emit_a_self_add(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_ADD);
}
bool yaoosl_emit_a_self_subtract(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_SUBTRACT);
}
bool yaoosl_emit_a_self_multiplicate(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_MULTIPLICATE);
}
bool yaoosl_emit_a_self_divide(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_DIVIDE);
}
bool yaoosl_emit_a_self_and(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_AND);
}
bool yaoosl_emit_a_self_or(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_OR);
}
bool yaoosl_emit_a_self_xor(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_XOR);
}
bool yaoosl_emit_a_self_bitshift_left(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_BITSHIFT_LEFT);
}
bool yaoosl_emit_a_self_bitshift_right(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_BITSHIFT_RIGHT);
}
bool yaoosl_emit_a_self_modulo(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_MODULO);
}
bool yaoosl_emit_a_self_invert(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_A_SELF_INVERT);
}
bool yaoosl_emit_logical_not(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_NOT);
}
bool yaoosl_emit_logical_and(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_AND);
}
bool yaoosl_emit_logical_or(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_OR);
}
bool yaoosl_emit_logical_equals(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_EQUALS);
}
bool yaoosl_emit_logical_equals_not(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_EQUALS_NOT);
}
bool yaoosl_emit_logical_greater_then(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_GREATER_THEN);
}
bool yaoosl_emit_logical_greater_then_or_equal(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_GREATER_THEN_OR_EQUAL);
}
bool yaoosl_emit_logical_less_then(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_LESS_THEN);
}
bool yaoosl_emit_logical_less_then_or_equal(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_LOGICAL_LESS_THEN_OR_EQUAL);
}
bool yaoosl_emit_push_int8_a8(yaooslcodehandle code, int8_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_INT8_a8) && yaoosl_emit_int8(code, value);
}
bool yaoosl_emit_push_int16_a16(yaooslcodehandle code, int16_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_INT16_a16) && yaoosl_emit_int16(code, value);
}
bool yaoosl_emit_push_int32_a32(yaooslcodehandle code, int32_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_INT32_a32) && yaoosl_emit_int32(code, value);
}
bool yaoosl_emit_push_int64_a64(yaooslcodehandle code, int64_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_INT64_a64) && yaoosl_emit_int64(code, value);
}
bool yaoosl_emit_push_uint8_a8(yaooslcodehandle code, uint8_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_UINT8_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_push_uint16_a16(yaooslcodehandle code, uint16_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_UINT16_a16) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_push_uint32_a32(yaooslcodehandle code, uint32_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_UINT32_a32) && yaoosl_emit_uint32(code, value);
}
bool yaoosl_emit_push_uint64_a64(yaooslcodehandle code, uint64_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_UINT64_a64) && yaoosl_emit_uint64(code, value);
}
bool yaoosl_emit_push_float_a32(yaooslcodehandle code, float value)
{
	union conv {
		uint32_t uint32;
		float f;
	} conversion;
	conversion.f = value;
	return yaoosl_emit_opcode(code, OPC_PUSH_FLOAT_a32) && yaoosl_emit_uint32(code, conversion.uint32);
}
bool yaoosl_emit_push_double_a64(yaooslcodehandle code, double value)
{
	union conv {
		uint64_t uint64;
		double d;
	} conversion;
	conversion.d = value;
	return yaoosl_emit_opcode(code, OPC_PUSH_DOUBLE_a64) && yaoosl_emit_uint64(code, conversion.uint64);
}
bool yaoosl_emit_push_true(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_TRUE);
}
bool yaoosl_emit_push_false(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_FALSE);
}
bool yaoosl_emit_push_char_a8(yaooslcodehandle code, char value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_CHAR_a8) && yaoosl_emit_int8(code, (int8_t)value);
}
bool yaoosl_emit_push_string_a8(yaooslcodehandle code, uint8_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_STRING_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_push_string_a16(yaooslcodehandle code, uint16_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_STRING_a16) && yaoosl_emit_uint16(code, value);
}
bool yaoosl_emit_push_string_a32(yaooslcodehandle code, uint32_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_STRING_a32) && yaoosl_emit_uint32(code, value);
}
bool yaoosl_emit_push_string(yaooslcodehandle code, const char* str)
{
	size_t len;
	len = strlen(str);

	if (len <= UINT8_MAX)
	{
		if (!yaoosl_emit_push_string_a8(code, (uint8_t)len)) { return false; }
	}
	else if (len <= UINT16_MAX)
	{
		if (!yaoosl_emit_push_string_a16(code, (uint16_t)len)) { return false; }
	}
	else
	{
		if (!yaoosl_emit_push_string_a32(code, (uint32_t)len)) { return false; }
	}
	for (len = 0; str[len] != '\0'; len++)
	{
		if (!yaoosl_emit_int8(code, str[len])) { return false; }
	}
	return true;
}
bool yaoosl_emit_push_this(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_THIS);
}
bool yaoosl_emit_push_null(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_NULL);
}
bool yaoosl_emit_push_new_a8(yaooslcodehandle code, uint8_t value)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_NEW_a8) && yaoosl_emit_uint8(code, value);
}
bool yaoosl_emit_push_array(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_ARRAY);
}
bool yaoosl_emit_push_array_typed(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_PUSH_ARRAY_TYPED);
}
bool yaoosl_emit_resolve_type(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_RESOLVE_TYPE);
}

bool yaoosl_emit_is_type(yaooslcodehandle code)
{
	return yaoosl_emit_opcode(code, OPC_IS_TYPE);
}
