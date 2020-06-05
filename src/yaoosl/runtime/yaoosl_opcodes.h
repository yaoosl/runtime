#pragma once
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    enum yaoosl_opcodes
    {
        // Do Nothing
        YOPC_NOP,
        // Breakpoint Reached
        YOPC_BREAK,
        // Exit current method. If value should be returned, it needs to reside on value-stack already
        YOPC_RETURN,

        // Load Argument from slot X/<value> to value stack
        YOPC_LOAD_ARGUMENT_0,
        YOPC_LOAD_ARGUMENT_1,
        YOPC_LOAD_ARGUMENT_2,
        YOPC_LOAD_ARGUMENT_3,
        YOPC_LOAD_ARGUMENT_4,
        YOPC_LOAD_ARGUMENT_int8,
        YOPC_LOAD_ARGUMENT_int16,

        // Stores Argument from value stack to slot X/<value>
        YOPC_STORE_ARGUMENT_0,
        YOPC_STORE_ARGUMENT_1,
        YOPC_STORE_ARGUMENT_2,
        YOPC_STORE_ARGUMENT_3,
        YOPC_STORE_ARGUMENT_4,
        YOPC_STORE_ARGUMENT_int8,
        YOPC_STORE_ARGUMENT_int16,

		// Load Immediate <value> to value stack
		YOPC_LOAD_IMMEDIATE_int8,
		YOPC_LOAD_IMMEDIATE_int16,
		YOPC_LOAD_IMMEDIATE_int32,
		YOPC_LOAD_IMMEDIATE_int64,
		YOPC_LOAD_IMMEDIATE_uint8,
		YOPC_LOAD_IMMEDIATE_uint16,
		YOPC_LOAD_IMMEDIATE_uint32,
		YOPC_LOAD_IMMEDIATE_uint64,
		YOPC_LOAD_IMMEDIATE_float,
		YOPC_LOAD_IMMEDIATE_double,

		// Operators. r => Reference (eg. +=). v => Value (eg. +).
        YOPC_INC_r0,
        YOPC_DEC_r0,
        YOPC_NOT_v1,
        YOPC_ADD_v2,
        YOPC_ADD_r1,
        YOPC_SUB_v2,
        YOPC_SUB_r1,
        YOPC_MUL_v2,
        YOPC_MUL_r1,
        YOPC_DIV_v2,
        YOPC_DIV_r1,
        YOPC_BIT_INV_v2,
        YOPC_BIT_INV_r1,
        YOPC_BIT_OR_v2,
        YOPC_BIT_OR_r1,
        YOPC_BIT_XOR_v2,
        YOPC_BIT_XOR_r1,
        YOPC_BIT_AND_v2,
        YOPC_BIT_AND_r1,
        YOPC_LOG_OR_v2,
        YOPC_LOG_AND_v2,
        YOPC_LOG_EQUAL_v2,
        YOPC_LOG_NOTEQUAL_v2,
        YOPC_LOG_LESS_THEN_v2,
        YOPC_LOG_GREATER_THEN_v2,
        YOPC_MOD_v2,
        YOPC_LSHIFT_v2,
        YOPC_LSHIFT_r1,
        YOPC_RSHIFT_v2,
        YOPC_RSHIFT_r1,

        // JUMP X/<value> bytes in code. (F => Forward; B => Backward)
        YOPC_JUMP5B,
        YOPC_JUMP4B,
        YOPC_JUMP3B,
        YOPC_JUMP2B,
        YOPC_JUMP1B,
        YOPC_JUMP1F,
        YOPC_JUMP2F,
        YOPC_JUMP3F,
        YOPC_JUMP4F,
        YOPC_JUMP5F,
        YOPC_JUMP_int8,
        YOPC_JUMP_int16,
        YOPC_JUMP_int32,
        YOPC_JUMP_int64,

        // BRANCH X/<value> bytes in code if value on stack is FALSE. (F => Forward; B => Backward)
        YOPC_BRANCH_FALSE1F,
        YOPC_BRANCH_FALSE2F,
        YOPC_BRANCH_FALSE3F,
        YOPC_BRANCH_FALSE4F,
        YOPC_BRANCH_FALSE5F,
        YOPC_BRANCH_FALSE_int8,
        YOPC_BRANCH_FALSE_int16,
        YOPC_BRANCH_FALSE_int32,
        YOPC_BRANCH_FALSE_int64,

        // BRANCH X/<value> bytes in code if value on stack is TRUE. (F => Forward; B => Backward)
        YOPC_BRANCH_TRUE1F,
        YOPC_BRANCH_TRUE2F,
        YOPC_BRANCH_TRUE3F,
        YOPC_BRANCH_TRUE4F,
        YOPC_BRANCH_TRUE5F,
        YOPC_BRANCH_TRUE_int8,
        YOPC_BRANCH_TRUE_int16,
        YOPC_BRANCH_TRUE_int32,
        YOPC_BRANCH_TRUE_int64,
	};

#ifdef __cplusplus
}
#endif // __cplusplus