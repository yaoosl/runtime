#pragma once
#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    /********************************************************************
     * Bytes are expected to be in BIG-EDIAN!                           *
     * number 0x0D0C0B0A -> code 0x0D0C0B0A                             *
     * ---------------------------------------------------------------- *
     * Value Stack:                                                     *
     *    A simple array containing the values currently in use.        *
     *    It may look like this (example):                              *
     *     0| integer:5	                                                *
     *     1| integer:3	                                                *
     *    The ADD operator now would take theese two values,            *
     *    add them together and put the result back onto the stack.     *
     *    The resulting value stack then would look like the following: *
     *     0| integer:8                                                 *
     * ---------------------------------------------------------------- *
     * Constructors                                                     *
     *    Constructors HAVE TO return the type they are constructing.   *
     *    To be more precise, Constructors need to return the this      *
     *    value in the end. The Compiler/Transpiler has to take care    *
     *    that in the end of every constructor, the following           *
     *    instruction (or a simmilar variant) is present:               *
     *     0|OPC_PUSH_THIS                                              *
     * ---------------------------------------------------------------- *
     * Exception Handling                                               *
     *    Exceptions in yaoosl are handled by so called blocks.         *
     *    If an exception is thrown, yaoosl will look into the          *
     *    exception map, and transfer control to the block that appears *
     *    at the top with a matching exception type.                    *
     *    Execution then starts after the OPC_BLOCK_CATCH instruction.  *
     *    This means, to make a proper catch block, you have to do      *
     *    the following:                                                *
     *      | # Prepare Block                                           *
     *     0| OPC_BLOCK_PUSH                                            *
     *      | # Load type onto value stack and anounce catch.           *
     *     1| OPC_PUSH_STRING_a8 (9|Exception)                          *
     *     2| OPC_RESOLVE_TYPE_STR_a32 (0)                              *
     *     3| OPC_BLOCK_CATCH                                           *
     *      | # Skip whole catchblock until                             *
     *      | # we are inside a catch block                             *
     *     4| OPC_SKIP_IF_IN_EXCEPTION                                  *
     *     5| OPC_JUMP_OFF_a8 (2)                                       *
     *     6| # catchblock instructions                                 *
     *      | # Skip Try part as we just handled an exception           *
     *     7| OPC_JUMP_OFF_a8 (1)                                       *
     *     8| # tryblock instructions                                   *
     *      | # Destroy block                                           *
     *     9| OPC_BLOCK_POP                                             *
     *    Actual execution order is obviously up to you and serves      *
     *    just as an example.                                           *
     *    The exception itself will reside on top of                    *
     *    the valuestack once it happened.                              *
     ********************************************************************/
    enum yaoosl_opcode
    {
        // Causes the VM to do nothing for a cycle.
        OPC_NOP,
        // Moves the head by the intX provided.
        OPC_JUMP_OFF_a8,
        OPC_JUMP_OFF_a16,
        OPC_JUMP_OFF_a32,

        // Receives the top-most value from the stack,
        // casts it to a bool and skips the next instruction
        // if the bool is true
        // Cannot be followed by an dynamic sized OPCODE!
        OPC_SKIP_IF_TRUE,
        // Receives the top-most value from the stack,
        // casts it to a bool and skips the next instruction
        // if the bool is false
        // Cannot be followed by an dynamic sized OPCODE!
        OPC_SKIP_IF_FALSE,
        // Skips the next instruction if current block is
        // handling an exception.
        // Cannot be followed by an dynamic sized OPCODE!
        OPC_SKIP_IF_IN_EXCEPTION,

        // Pushes a new block onto the current scope
        OPC_BLOCK_PUSH,
        // Adds the string currently on top of the value-stack to the blocks using prefixes,
        // allowing any class resolutions following to omit this.
        OPC_BLOCK_PREFIX,
        // Pops the top-most block from the current scope
        OPC_BLOCK_POP,
        // Marks the current block for exception management and
        // adds a handler. Exception will reside on value stack.
        OPC_BLOCK_CATCH,
        // Starts exception handling with the exception currently ontop of the value-stack.
        OPC_BLOCK_THROW,

        // Allocates additional space to the local-variables-stack according to the provided uintX size.
        OPC_SCOPE_ALLOCATE_a8,
        OPC_SCOPE_ALLOCATE_a16,
        // Destroys the top-most scope.
        // value-stack will be left untouched!
        // Required to implement return
        OPC_SCOPE_POP,

        // Stores the top-most value in the provided uint8 slot.
        OPC_SET_VALUE_a8,
        OPC_SET_VALUE_a16,
        // Receives a value from the provided uint8 slot and pushes it to the value stack.
        OPC_GET_VALUE_a8,
        OPC_GET_VALUE_a16,
        // Removes a value from the valuestack and decreases its reference counter.
        OPC_POP_VALUE,
        // Removes all values from the valuestack and decreases their reference counter.
        OPC_CLEAR_VALUES,
        // Duplicates the top-value on the value-stack
        OPC_DUPLICATE_VALUE,


        // Declares a new class with the name, provided by the following uint16 chars.
        OPC_DECLARE_CLASS_a16,
        // Starts creating a new class with the name, provided by the following uint16 chars.
        // Must be terminated using OPC_CREATE_CLASS_END before new class
        // may be constructed.
        OPC_CREATE_CLASS_BEGIN_a16,
        // Takes a type from the valuestack and appends it
        // as a base-class
        OPC_CREATE_CLASS_BASECLASS,
        // Ends the construction of a class on the stack,
        // finallizing the class and putting it onto the VM.
        // Must have all method/property creations being closed already.
        OPC_CREATE_CLASS_END,

        // Starts creation of a new method
        // Must only occur during class or property creation.
        // Must be terminated using OPC_CREATE_METHOD_END before new method
        // may be constructed.
        OPC_CREATE_METHOD_BEGIN,
        // Takes a type from the valuestack and sets the returntype to it.
        // Not providing implies void.
        // Must not occur for property setters.
        // Must not occur for constructors.
        // Must not occur for destructors.
        OPC_CREATE_METHOD_RETURN,
        // Takes a string from the valuestack and changes the
        // name of the method acording to it.
        // For properties, this may only be get or set!
        // For class constructor, name needs to be the same as class.
        // For class destructor, name needs to be the same as class prefixed with '~'.
        // Must not occur for operator overloads.
        OPC_CREATE_METHOD_NAME,
        // Takes a string from the valuestack and compares against the available operators.
        OPC_CREATE_METHOD_OPERATOR,
        // Takes a string and then a type from the valuestack and
        // appends an arg to the method currently being built.
        OPC_CREATE_METHOD_ARG,
        // Sets the following bytes up to the provided uint64 length as the
        // contents of this method.
        OPC_CREATE_METHOD_CODEBLOCK_a64,
        // Ends method creation, setting it to the corresponding method-group
        // if inside a class or to the corresponding property getter/setter.
        OPC_CREATE_METHOD_END,

        // Starts property creation.
        // Must only occur during class creation.
        // Must be terminated using OPC_CREATE_PROPERTY_END before new property
        // may be constructed.
        OPC_CREATE_PROPERTY_BEGIN,
        // Takes a string from the valuestack and changes the
        // name of the property acording to it.
        OPC_CREATE_PROPERTY_NAME,
        // Takes a type from the valuestack and sets the property type
        // to it
        OPC_CREATE_PROPERTY_RETURN,
        // Finishes the property creation and adds it to the class.
        OPC_CREATE_PROPERTY_END,

        // Takes the top most value and looks for a matching property inside of it.
        // Propertyname is designated by the following X bytes provided by the uint8/uint16/uint32 argument.
        OPC_NAVIGATE_PROPERTY_a8,
        OPC_NAVIGATE_PROPERTY_a16,
        OPC_NAVIGATE_PROPERTY_a32,

        OPC_SET_PROPERTY_a8,
        OPC_SET_PROPERTY_a16,
        OPC_SET_PROPERTY_a32,

        // Calls the method named by the following X bytes provided by the uint8/uint16/uint32 argument.
        // Fully Qualified Type name is expected (Package + Name) including the method to call, separated by a dot ('.').
        // Operators need to be ordered like so, that the first operator is sitting on top.
        // Second (b) uint8 argument gives how many arguments are present
        OPC_CALL_a8_b8,
        OPC_CALL_a16_b8,
        OPC_CALL_a32_b8,
        // Calls the method named by the following X bytes provided by the uint8/uint16/uint32 argument.
        // Methodname is expected.
        // Operators need to be ordered like so, that the first operator is sitting on top of the others.
        // Self reference is expected to be on top of the value stack
        // Second (b) uint8 argument gives how many arguments are present
        OPC_CALL_SELF_a8_b8,
        OPC_CALL_SELF_a16_b8,
        OPC_CALL_SELF_a32_b8,
       

        // Increases the top value in the value-stack and pushes the result on the value stack
        OPC_INCREMENT,
        // Decreases the top value in the value-stack and pushes the result on the value stack
        OPC_DECREMENT,

        // Arithmetical operations.
        // Require two values on the value stack.
        // First (0) being left value from which the operator is deduced,
        // second (1) being the right value passed.
        OPC_A_ADD,
        OPC_A_SUBTRACT,
        OPC_A_MULTIPLICATE,
        OPC_A_DIVIDE,
        OPC_A_AND,
        OPC_A_OR,
        OPC_A_XOR,
        OPC_A_BITSHIFT_LEFT,
        OPC_A_BITSHIFT_RIGHT,
        OPC_A_MODULO,
        OPC_A_INVERT,
        // Arithmetical operations.
        // Require two values on the value stack.
        // First (0) being this value, second (1) being the value to add.
        OPC_A_SELF_ADD,
        OPC_A_SELF_SUBTRACT,
        OPC_A_SELF_MULTIPLICATE,
        OPC_A_SELF_DIVIDE,
        OPC_A_SELF_AND,
        OPC_A_SELF_OR,
        OPC_A_SELF_XOR,
        OPC_A_SELF_BITSHIFT_LEFT,
        OPC_A_SELF_BITSHIFT_RIGHT,
        OPC_A_SELF_MODULO,
        OPC_A_SELF_INVERT,
        // Logical operations requiring only one value on the stack.
        OPC_LOGICAL_NOT,
        // Logical operations requiring two values on the stack.
        OPC_LOGICAL_AND,
        OPC_LOGICAL_OR,
        OPC_LOGICAL_EQUALS,
        OPC_LOGICAL_EQUALS_NOT,
        OPC_LOGICAL_GREATER_THEN,
        OPC_LOGICAL_GREATER_THEN_OR_EQUAL,
        OPC_LOGICAL_LESS_THEN,
        OPC_LOGICAL_LESS_THEN_OR_EQUAL,

        // Opcodes to push a value onto the value stack
        OPC_PUSH_INT8_a8,
        OPC_PUSH_INT16_a16,
        OPC_PUSH_INT32_a32,
        OPC_PUSH_INT64_a64,

        OPC_PUSH_UINT8_a8,
        OPC_PUSH_UINT16_a16,
        OPC_PUSH_UINT32_a32,
        OPC_PUSH_UINT64_a64,

        OPC_PUSH_FLOAT_a32,
        OPC_PUSH_DOUBLE_a64,

        OPC_PUSH_TRUE,
        OPC_PUSH_FALSE,

        OPC_PUSH_CHAR_a8,

        // Creates a string out of the following X bytes provided by the uint16/uint32 argument
        OPC_PUSH_STRING_a8,
        OPC_PUSH_STRING_a16,
        OPC_PUSH_STRING_a32,
        // Pushes the self pointer onto the value stack
        OPC_PUSH_THIS,

        // Takes the type from the value stack and creates
        // an instance of it. The provided uint8 saying how many args the constructor call has.
        OPC_PUSH_NEW_a8,
        // Pushes a null value to the stack
        OPC_PUSH_NULL,

        // Creates an empty array with the target type
        // OBJECT.
        OPC_PUSH_ARRAY,

        // Creates an empty array with the target type
        // provided by the value stack.
        OPC_PUSH_ARRAY_TYPED,

        // Resolves the type, designated by the top-most string on the value stack. 
        OPC_RESOLVE_TYPE,
        // Takes the top value on the valuestack and expects it to be a type.
        // Takes the top-1 value on the valuestack and takes the type of the value. 
        // Pushes true if the top-1 type is a descendant or exactly the same as the top type.
        // False otherwise.
        OPC_IS_TYPE,

        ////////////////////////////////
        // ABOVE -> Done              //
        // BELOW -> Subject to change //
        ////////////////////////////////

        // Index Operator.
        // Requires two values on the value stack.
        // First (0) being this value.
        // Second (1) being the index key.
        // Third (2) being the value to set. Only required for OPC_INDEX_SET
        OPC_INDEX_GET,
        OPC_INDEX_SET,


        // Starts a diagnostics section. The uint16 will designate how much of the following code is debug instruction.
        // Diagnostics sections are taken into account in jump instructions!
        OPC_DIAG_a16,
        // Reserved for future use. Plan is that this will allow access to additional opcode pages
        OPC_EXTEND = 255
    };

    typedef enum yaoosl_opcode yaoosl_opcode;

    int yaoosl_opcode_length(uint8_t* bytes);
    unsigned int yaoosl_opcode_to_string(uint8_t* bytes, char* buffer, unsigned int buffer_len);

#ifdef __cplusplus
}
#endif // __cplusplus