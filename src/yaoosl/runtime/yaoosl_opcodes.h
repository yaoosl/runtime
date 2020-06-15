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

        // Takes the top-most value from the value-stack and pushes it again onto the value-stack
        YOPC_DUPLICATE_VALUE,

        // Exit current scope.
        YOPC_POP_SCOPE,
        // Exits current scope and keeps the top-most value on the stack.
        YOPC_POP_SCOPE_WITH_VALUE,

        // Pops a value from the stack
        // and calls it if it is indeed a delegate type
        YOPC_CALL,

        // Pops a value from the stack,
        // checks if it is a reference type
        // and pushes a reference to its property X/<value>
        YOPC_LOAD_PROPERTY0,
        YOPC_LOAD_PROPERTY1,
        YOPC_LOAD_PROPERTY2,
        YOPC_LOAD_PROPERTY3,
        YOPC_LOAD_PROPERTY4,
        YOPC_LOAD_PROPERTY_uint8,
        YOPC_LOAD_PROPERTY_uint16,

        // Pops a value from the stack,
        // checks if it is a reference type
        // and pushes a reference to its method X/<value>
        YOPC_LOAD_METHOD0,
        YOPC_LOAD_METHOD1,
        YOPC_LOAD_METHOD2,
        YOPC_LOAD_METHOD3,
        YOPC_LOAD_METHOD4,
        YOPC_LOAD_METHOD_uint8,
        YOPC_LOAD_METHOD_uint16,

        // Load Argument from slot X/<value> to value stack
        YOPC_LOAD_ARGUMENT0,
        YOPC_LOAD_ARGUMENT1,
        YOPC_LOAD_ARGUMENT2,
        YOPC_LOAD_ARGUMENT3,
        YOPC_LOAD_ARGUMENT4,
        YOPC_LOAD_ARGUMENT_uint8,
        YOPC_LOAD_ARGUMENT_uint16,

        // Stores Argument from value stack to slot X/<value>
        YOPC_STORE_ARGUMENT0,
        YOPC_STORE_ARGUMENT1,
        YOPC_STORE_ARGUMENT2,
        YOPC_STORE_ARGUMENT3,
        YOPC_STORE_ARGUMENT4,
        YOPC_STORE_ARGUMENT_uint8,
        YOPC_STORE_ARGUMENT_uint16,

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
        YOPC_LOAD_IMMEDIATE_true,
        YOPC_LOAD_IMMEDIATE_false,

        // Creates a new array on the value stack with a size of X/<value>
        YOPC_ARRAY_CREATE0,
        YOPC_ARRAY_CREATE1,
        YOPC_ARRAY_CREATE2,
        YOPC_ARRAY_CREATE3,
        YOPC_ARRAY_CREATE4,
        YOPC_ARRAY_CREATE_uint8,
        YOPC_ARRAY_CREATE_uint16,
        YOPC_ARRAY_CREATE_uint32,
        YOPC_ARRAY_CREATE_uint64,

        // Resizes an array on the value stack to the size of X/<value>
        // DYN will take the targeted value, attempt to read it as 
        // a valid integral type and use it for the array.
        // DYN VAL STACK N-0: Target Size as Integral
        //     VAL STACK N-1: Array to resize
        YOPC_ARRAY_RESIZE_uint8,
        YOPC_ARRAY_RESIZE_uint16,
        YOPC_ARRAY_RESIZE_uint32,
        YOPC_ARRAY_RESIZE_uint64,
        YOPC_ARRAY_RESIZE_DYN,

        // Updates a slot of an array on the value stack with another value.
        // Slot is provided by X/<value>
        // DYN will take the targeted value, attempt to read it as 
        // a valid integral type and use it for the array.
        // DYN VAL STACK N-0: Target Size as Integral
        //     VAL STACK N-1: Value to set
        //     VAL STACK N-2: Array to update
        YOPC_ARRAY_SET0,
        YOPC_ARRAY_SET1,
        YOPC_ARRAY_SET2,
        YOPC_ARRAY_SET3,
        YOPC_ARRAY_SET4,
        YOPC_ARRAY_SET_uint8,
        YOPC_ARRAY_SET_uint16,
        YOPC_ARRAY_SET_uint32,
        YOPC_ARRAY_SET_uint64,
        YOPC_ARRAY_SET_DYN,

        // Reads a slot of an array onto the value stack.
        // Slot is provided by X/<value>
        // DYN will take the targeted value, attempt to read it as 
        // a valid integral type and use it for the array.
        // DYN VAL STACK N-0: Target Size as Integral
        //     VAL STACK N-1: Array to update
        YOPC_ARRAY_GET0,
        YOPC_ARRAY_GET1,
        YOPC_ARRAY_GET2,
        YOPC_ARRAY_GET3,
        YOPC_ARRAY_GET4,
        YOPC_ARRAY_GET_uint8,
        YOPC_ARRAY_GET_uint16,
        YOPC_ARRAY_GET_uint32,
        YOPC_ARRAY_GET_uint64,
        YOPC_ARRAY_GET_DYN,

        // Load delegate
        YOPC_LOAD_DELEGATE_uint8,
        YOPC_LOAD_DELEGATE_uint16,
        YOPC_LOAD_DELEGATE_uint32,
        YOPC_LOAD_DELEGATE_uint64,

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
        YOPC_BIT_INV_v1,
        YOPC_BIT_INV_r0,
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
        YOPC_LOG_LESS_THEN_OR_EQUAL_v2,
        YOPC_LOG_GREATER_THEN_v2,
        YOPC_LOG_GREATER_THEN_OR_EQUAL_v2,
        YOPC_MOD_v2,
        YOPC_MOD_r1,
        YOPC_LSHIFT_v2,
        YOPC_LSHIFT_r1,
        YOPC_RSHIFT_v2,
        YOPC_RSHIFT_r1,
    };

#ifdef __cplusplus
}
#endif // __cplusplus