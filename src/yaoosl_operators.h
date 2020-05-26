#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	enum yaoosl_operator
	{
		__INVALID = -1,
		// Arithmetical operations requiring two values
		OP_ARITHMETICAL_ADD,
		OP_ARITHMETICAL_SUBTRACT,
		OP_ARITHMETICAL_MULTIPLICATE,
		OP_ARITHMETICAL_DIVIDE,
		OP_ARITHMETICAL_AND,
		OP_ARITHMETICAL_OR,
		OP_ARITHMETICAL_XOR,
		OP_ARITHMETICAL_BITSHIFT_LEFT,
		OP_ARITHMETICAL_BITSHIFT_RIGHT,
		OP_ARITHMETICAL_MODULO,
		OP_ARITHMETICAL_INVERT,
		// Arithmetical operations requiring one value
		OP_ARITHMETICAL_SELF_ADD,
		OP_ARITHMETICAL_SELF_SUBTRACT,
		OP_ARITHMETICAL_SELF_MULTIPLICATE,
		OP_ARITHMETICAL_SELF_DIVIDE,
		OP_ARITHMETICAL_SELF_AND,
		OP_ARITHMETICAL_SELF_OR,
		OP_ARITHMETICAL_SELF_XOR,
		OP_ARITHMETICAL_SELF_BITSHIFT_LEFT,
		OP_ARITHMETICAL_SELF_BITSHIFT_RIGHT,
		OP_ARITHMETICAL_SELF_MODULO,
		OP_ARITHMETICAL_SELF_INVERT,
		// Arithmetical operations requiring no value
		OP_ARITHMETICAL_SELF_INCREASE,
		OP_ARITHMETICAL_SELF_DECREASE,
		// Logical operations requiring one value
		OP_LOGICAL_NOT,
		// Logical operations requiring two values
		OP_LOGICAL_AND,
		OP_LOGICAL_OR,
		OP_LOGICAL_EQUALS,
		OP_LOGICAL_EQUALS_NOT,
		OP_LOGICAL_LARGER_THEN,
		OP_LOGICAL_LARGER_THEN_OR_EQUAL,
		OP_LOGICAL_LESS_THEN,
		OP_LOGICAL_LESS_THEN_OR_EQUAL,

		OP_INDEX_GET,
		OP_INDEX_SET,




		__OPERATOR_MAX
	};
	enum yaoosl_operator yaoosl_operator_from_string(const char* str);
	const char* yaoosl_operator_to_string(enum yaoosl_operator op);
	int yaoosl_operator_arg_count(enum yaoosl_operator op);

#ifdef __cplusplus
}
#endif // __cplusplus