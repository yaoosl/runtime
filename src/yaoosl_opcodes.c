#include "yaoosl_opcodes.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define READ_IN8 value.uint8 = bytes[0]
#define READ_IN16 value.uint16 = (((uint16_t)bytes[0]) << (8 * 1)) | (((uint16_t)bytes[1]) << (8 * 0))
#define READ_IN32 value.uint32 = (((uint32_t)bytes[0]) << (8 * 3)) | (((uint32_t)bytes[1]) << (8 * 2)) | (((uint32_t)bytes[2]) << (8 * 1)) | (((uint32_t)bytes[3]) << (8 * 0))
#define READ_IN64 value.uint64 = (((uint64_t)bytes[0]) << (8 * 7)) | (((uint64_t)bytes[1]) << (8 * 6)) | (((uint64_t)bytes[2]) << (8 * 5)) | (((uint64_t)bytes[3]) << (8 * 4)) | (((uint64_t)bytes[4]) << (8 * 3)) | (((uint64_t)bytes[5]) << (8 * 2)) | (((uint64_t)bytes[6]) << (8 * 1)) | (((uint64_t)bytes[7]) << (8 * 0))


int yaoosl_opcode_length(uint8_t* bytes)
{
    enum yaoosl_opcode opcode;
    union val {
        uint8_t  uint8;
         int8_t   int8;
        uint16_t uint16;
         int16_t  int16;
        uint32_t uint32;
         int32_t  int32;
        uint64_t uint64;
         int64_t  int64;
    } value;
    size_t tmp;
    switch (sizeof(enum yaoosl_opcode))
    {
    case 1: opcode = bytes[0]; bytes += 1; break;
    case 2: opcode = (((uint16_t)bytes[0]) << (8 * 1)) | (((uint16_t)bytes[1]) << (8 * 0)); bytes += 2; break;
    case 4: opcode = (((uint32_t)bytes[0]) << (8 * 3)) | (((uint32_t)bytes[1]) << (8 * 2)) | (((uint32_t)bytes[2]) << (8 * 1)) | (((uint32_t)bytes[3]) << (8 * 0)); bytes += 4; break;
    default: opcode = (((uint64_t)bytes[0]) << (8 * 7)) | (((uint64_t)bytes[1]) << (8 * 6)) | (((uint64_t)bytes[2]) << (8 * 5)) | (((uint64_t)bytes[3]) << (8 * 4)) | (((uint64_t)bytes[4]) << (8 * 3)) | (((uint64_t)bytes[5]) << (8 * 2)) | (((uint64_t)bytes[6]) << (8 * 1)) | (((uint64_t)bytes[7]) << (8 * 0)); bytes += 8; break;
    }
    switch (opcode)
    {
    case OPC_NOP:
    case OPC_BLOCK_THROW:
    case OPC_SCOPE_POP:
    case OPC_SKIP_IF_TRUE:
    case OPC_SKIP_IF_FALSE:
    case OPC_SKIP_IF_IN_EXCEPTION:
    case OPC_BLOCK_PUSH:
    case OPC_BLOCK_PREFIX:
    case OPC_BLOCK_POP:
    case OPC_BLOCK_CATCH:
    case OPC_POP_VALUE:
    case OPC_CLEAR_VALUES:
    case OPC_DUPLICATE_VALUE:
    case OPC_CREATE_CLASS_BASECLASS:
    case OPC_CREATE_CLASS_END:
    case OPC_CREATE_METHOD_BEGIN:
    case OPC_CREATE_METHOD_RETURN:
    case OPC_CREATE_METHOD_NAME:
    case OPC_CREATE_METHOD_OPERATOR:
    case OPC_CREATE_METHOD_ARG:
    case OPC_CREATE_METHOD_END:
    case OPC_CREATE_PROPERTY_BEGIN:
    case OPC_CREATE_PROPERTY_NAME:
    case OPC_CREATE_PROPERTY_RETURN:
    case OPC_CREATE_PROPERTY_END:
    case OPC_INCREMENT:
    case OPC_DECREMENT:
    case OPC_A_ADD:
    case OPC_A_SUBTRACT:
    case OPC_A_MULTIPLICATE:
    case OPC_A_DIVIDE:
    case OPC_A_AND:
    case OPC_A_OR:
    case OPC_A_XOR:
    case OPC_A_BITSHIFT_LEFT:
    case OPC_A_BITSHIFT_RIGHT:
    case OPC_A_MODULO:
    case OPC_A_INVERT:
    case OPC_A_SELF_ADD:
    case OPC_A_SELF_SUBTRACT:
    case OPC_A_SELF_MULTIPLICATE:
    case OPC_A_SELF_DIVIDE:
    case OPC_A_SELF_AND:
    case OPC_A_SELF_OR:
    case OPC_A_SELF_XOR:
    case OPC_A_SELF_BITSHIFT_LEFT:
    case OPC_A_SELF_BITSHIFT_RIGHT:
    case OPC_A_SELF_MODULO:
    case OPC_A_SELF_INVERT:
    case OPC_LOGICAL_NOT:
    case OPC_LOGICAL_AND:
    case OPC_LOGICAL_OR:
    case OPC_LOGICAL_EQUALS:
    case OPC_LOGICAL_EQUALS_NOT:
    case OPC_LOGICAL_GREATER_THEN:
    case OPC_LOGICAL_GREATER_THEN_OR_EQUAL:
    case OPC_LOGICAL_LESS_THEN:
    case OPC_LOGICAL_LESS_THEN_OR_EQUAL:
    case OPC_PUSH_TRUE:
    case OPC_PUSH_FALSE:
    case OPC_PUSH_THIS:
    case OPC_PUSH_NULL:
    case OPC_PUSH_ARRAY:
    case OPC_PUSH_ARRAY_TYPED:
    case OPC_RESOLVE_TYPE:
    case OPC_INDEX_GET:
    case OPC_INDEX_SET:
        return sizeof(enum yaoosl_opcode) + 0;
    case OPC_JUMP_OFF_a8:
    case OPC_SCOPE_ALLOCATE_a8:
    case OPC_SET_VALUE_a8:
    case OPC_GET_VALUE_a8:
    case OPC_PUSH_INT8_a8:
    case OPC_PUSH_UINT8_a8:
    case OPC_PUSH_CHAR_a8:
    case OPC_PUSH_NEW_a8:
        return sizeof(enum yaoosl_opcode) + 1;
    case OPC_PUSH_INT16_a16:
    case OPC_PUSH_UINT16_a16:
    case OPC_JUMP_OFF_a16:
    case OPC_SCOPE_ALLOCATE_a16:
    case OPC_SET_VALUE_a16:
    case OPC_GET_VALUE_a16:
        return sizeof(enum yaoosl_opcode) + 2;
    case OPC_JUMP_OFF_a32:
    case OPC_PUSH_INT32_a32:
    case OPC_PUSH_UINT32_a32:
    case OPC_PUSH_FLOAT_a32:
        return sizeof(enum yaoosl_opcode) + 4;
    case OPC_CREATE_METHOD_CODEBLOCK_a64:
    case OPC_PUSH_INT64_a64:
    case OPC_PUSH_DOUBLE_a64:
    case OPC_PUSH_UINT64_a64:
        return sizeof(enum yaoosl_opcode) + 8;
    case OPC_DIAG_a16:
        READ_IN16;
        return sizeof(enum yaoosl_opcode) + 1 + value.uint16;
    case OPC_EXTEND:
        return sizeof(enum yaoosl_opcode);


    case OPC_SET_PROPERTY_a8:
    case OPC_NAVIGATE_PROPERTY_a8:
    case OPC_PUSH_STRING_a8:
        READ_IN8;
        return sizeof(enum yaoosl_opcode) + 1 + value.uint8;
    case OPC_PUSH_STRING_a16:
    case OPC_NAVIGATE_PROPERTY_a16:
    case OPC_SET_PROPERTY_a16:
    case OPC_DECLARE_CLASS_a16:
    case OPC_CREATE_CLASS_BEGIN_a16:
        READ_IN16;
        return sizeof(enum yaoosl_opcode) + 2 + value.uint16;
    case OPC_PUSH_STRING_a32:
    case OPC_SET_PROPERTY_a32:
    case OPC_NAVIGATE_PROPERTY_a32:
        READ_IN32;
        return sizeof(enum yaoosl_opcode) + 4 + value.uint32;


    case OPC_CALL_SELF_a8_b8:
    case OPC_CALL_a8_b8:
        READ_IN8;
        tmp = value.uint8;
        READ_IN8;
        return sizeof(enum yaoosl_opcode) + 2 + tmp + value.uint8;
    case OPC_CALL_SELF_a16_b8:
    case OPC_CALL_a16_b8:
        READ_IN16;
        tmp = value.uint16;
        READ_IN8;
        return sizeof(enum yaoosl_opcode) + 3 + tmp + value.uint8;
    case OPC_CALL_SELF_a32_b8:
    case OPC_CALL_a32_b8:
        READ_IN32;
        tmp = value.uint32;
        READ_IN8;
        return sizeof(enum yaoosl_opcode) + 5 + tmp + value.uint8;
    default:
        return -1;
    }
}


#define COPY_STRING(STR) i = strlen(STR); strncpy(buffer, STR, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; 
#define COPY_CHAR_TO_STRING str[0] = bytes[0]; str[2] = '\0'; i = 1; strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 1;
#define COPY_HEX_TO_STRING snprintf(str, 256, " %02X", uint8 = bytes[0]); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 1;
#define COPY_UINT8_TO_STRING snprintf(str, 256, " %hhu", uint8 = bytes[0]); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 1;
#define COPY_UINT16_TO_STRING snprintf(str, 256, " %hu", uint16 = (((uint16_t)bytes[0]) << (8 * 1)) | (((uint16_t)bytes[1]) << (8 * 0))); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 2;
#define COPY_UINT32_TO_STRING snprintf(str, 256, " %u", uint32 = (((uint32_t)bytes[0]) << (8 * 3)) | (((uint32_t)bytes[1]) << (8 * 2)) | (((uint32_t)bytes[2]) << (8 * 1)) | (((uint32_t)bytes[3]) << (8 * 0))); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 4;
#define COPY_UINT64_TO_STRING snprintf(str, 256, " %llu", uint64 = (((uint64_t)bytes[0]) << (8 * 7)) | (((uint64_t)bytes[1]) << (8 * 6)) | (((uint64_t)bytes[2]) << (8 * 5)) | (((uint64_t)bytes[3]) << (8 * 4)) | (((uint64_t)bytes[4]) << (8 * 3)) | (((uint64_t)bytes[5]) << (8 * 2)) | (((uint64_t)bytes[6]) << (8 * 1)) | (((uint64_t)bytes[7]) << (8 * 0))); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 8;
#define COPY_INT8_TO_STRING snprintf(str, 256, " %hhd", int8 = bytes[0]); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 1;
#define COPY_INT16_TO_STRING snprintf(str, 256, " %hd", int16 = (((int16_t)bytes[0]) << (8 * 1)) | (((int16_t)bytes[1]) << (8 * 0))); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 2;
#define COPY_INT32_TO_STRING snprintf(str, 256, " %d", int32 = (((int32_t)bytes[0]) << (8 * 3)) | (((int32_t)bytes[1]) << (8 * 2)) | (((int32_t)bytes[2]) << (8 * 1)) | (((int32_t)bytes[3]) << (8 * 0))); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 4;
#define COPY_INT64_TO_STRING snprintf(str, 256, " %lld", int64 = (((int64_t)bytes[0]) << (8 * 7)) | (((int64_t)bytes[1]) << (8 * 6)) | (((int64_t)bytes[2]) << (8 * 5)) | (((int64_t)bytes[3]) << (8 * 4)) | (((int64_t)bytes[4]) << (8 * 3)) | (((int64_t)bytes[5]) << (8 * 2)) | (((int64_t)bytes[6]) << (8 * 1)) | (((int64_t)bytes[7]) << (8 * 0))); i = strlen(str); strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i); buffer += i; buffer_len -= (unsigned int)i; buffer[0] = '\0'; bytes += 8;

#define COPY_FLOAT_TO_STRING conversion.uint32 = ((((uint32_t)bytes[0]) << (8 * 3)) | (((uint32_t)bytes[1]) << (8 * 2)) | (((uint32_t)bytes[2]) << (8 * 1)) | (((uint32_t)bytes[3]) << (8 * 0)));\
snprintf(str, 256, " %f", (float)conversion.f);\
i = strlen(str);\
strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i);\
buffer += i;\
buffer_len -= (unsigned int)i;\
buffer[0] = '\0';\
bytes += 4;
#define COPY_DOUBLE_TO_STRING conversion.uint64 = ((((uint64_t)bytes[0]) << (8 * 7)) | (((uint64_t)bytes[1]) << (8 * 6)) | (((uint64_t)bytes[2]) << (8 * 5)) | (((uint64_t)bytes[3]) << (8 * 4)) | (((uint64_t)bytes[4]) << (8 * 3)) | (((uint64_t)bytes[5]) << (8 * 2)) | (((uint64_t)bytes[6]) << (8 * 1)) | (((uint64_t)bytes[7]) << (8 * 0)));\
snprintf(str, 256, " %lf", conversion.d);\
i = strlen(str);\
strncpy(buffer, str, i > ((size_t)buffer_len) ? ((size_t)buffer_len) : i);\
buffer += i;\
buffer_len -= (unsigned int)i;\
buffer[0] = '\0';\
bytes += 8;

unsigned int yaoosl_opcode_to_string(uint8_t* bytes, char* buffer, unsigned int buffer_len)
{
    size_t i, j, k;
    char str[256];
    uint8_t uint8;
    uint16_t uint16;
    uint32_t uint32;
    uint64_t uint64;
    int8_t int8;
    int16_t int16;
    int32_t int32;
    int64_t int64;
    union conv
    {
        uint32_t uint32;
        uint64_t uint64;
        float f;
        double d;
    } conversion;
    buffer_len--;
    enum yaoosl_opcode opcode;
    switch (sizeof(enum yaoosl_opcode))
    {
    case 1: opcode = bytes[0]; bytes += 1; break;
    case 2: opcode = (((uint16_t)bytes[0]) << (8 * 1)) | (((uint16_t)bytes[1]) << (8 * 0)); bytes += 2; break;
    case 4: opcode = (((uint32_t)bytes[0]) << (8 * 3)) | (((uint32_t)bytes[1]) << (8 * 2)) | (((uint32_t)bytes[2]) << (8 * 1)) | (((uint32_t)bytes[3]) << (8 * 0)); bytes += 4; break;
    default: opcode = (((uint64_t)bytes[0]) << (8 * 7)) | (((uint64_t)bytes[1]) << (8 * 6)) | (((uint64_t)bytes[2]) << (8 * 5)) | (((uint64_t)bytes[3]) << (8 * 4)) | (((uint64_t)bytes[4]) << (8 * 3)) | (((uint64_t)bytes[5]) << (8 * 2)) | (((uint64_t)bytes[6]) << (8 * 1)) | (((uint64_t)bytes[7]) << (8 * 0)); bytes += 8; break;
    }
    switch (opcode)
    {
    case OPC_NOP: COPY_STRING("OPC_NOP"); return sizeof(enum yaoosl_opcode);
    case OPC_SCOPE_POP: COPY_STRING("OPC_SCOPE_POP"); return sizeof(enum yaoosl_opcode);
    case OPC_SKIP_IF_TRUE: COPY_STRING("OPC_SKIP_IF_TRUE"); return sizeof(enum yaoosl_opcode);
    case OPC_SKIP_IF_FALSE: COPY_STRING("OPC_SKIP_IF_FALSE"); return sizeof(enum yaoosl_opcode);
    case OPC_SKIP_IF_IN_EXCEPTION: COPY_STRING("OPC_SKIP_IF_IN_EXCEPTION"); return sizeof(enum yaoosl_opcode);
    case OPC_BLOCK_PUSH: COPY_STRING("OPC_BLOCK_PUSH"); return sizeof(enum yaoosl_opcode);
    case OPC_BLOCK_PREFIX: COPY_STRING("OPC_BLOCK_PREFIX"); return sizeof(enum yaoosl_opcode);
    case OPC_BLOCK_THROW: COPY_STRING("OPC_BLOCK_THROW"); return sizeof(enum yaoosl_opcode);
    case OPC_BLOCK_POP: COPY_STRING("OPC_BLOCK_POP"); return sizeof(enum yaoosl_opcode);
    case OPC_BLOCK_CATCH: COPY_STRING("OPC_BLOCK_CATCH"); return sizeof(enum yaoosl_opcode);
    case OPC_POP_VALUE: COPY_STRING("OPC_POP_VALUE"); return sizeof(enum yaoosl_opcode);
    case OPC_CLEAR_VALUES: COPY_STRING("OPC_CLEAR_VALUES"); return sizeof(enum yaoosl_opcode);
    case OPC_DUPLICATE_VALUE: COPY_STRING("OPC_DUPLICATE_VALUE"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_CLASS_BASECLASS: COPY_STRING("OPC_CREATE_CLASS_BASECLASS"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_CLASS_END: COPY_STRING("OPC_CREATE_CLASS_END"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_METHOD_BEGIN: COPY_STRING("OPC_CREATE_METHOD_BEGIN"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_METHOD_RETURN: COPY_STRING("OPC_CREATE_METHOD_RETURN"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_METHOD_NAME: COPY_STRING("OPC_CREATE_METHOD_NAME"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_METHOD_OPERATOR: COPY_STRING("OPC_CREATE_METHOD_OPERATOR"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_METHOD_ARG: COPY_STRING("OPC_CREATE_METHOD_ARG"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_METHOD_END: COPY_STRING("OPC_CREATE_METHOD_END"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_PROPERTY_BEGIN: COPY_STRING("OPC_CREATE_PROPERTY_BEGIN"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_PROPERTY_NAME: COPY_STRING("OPC_CREATE_PROPERTY_NAME"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_PROPERTY_RETURN: COPY_STRING("OPC_CREATE_PROPERTY_RETURN"); return sizeof(enum yaoosl_opcode);
    case OPC_CREATE_PROPERTY_END: COPY_STRING("OPC_CREATE_PROPERTY_END"); return sizeof(enum yaoosl_opcode);
    case OPC_INCREMENT: COPY_STRING("OPC_INCREMENT"); return sizeof(enum yaoosl_opcode);
    case OPC_DECREMENT: COPY_STRING("OPC_DECREMENT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_ADD: COPY_STRING("OPC_A_ADD"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SUBTRACT: COPY_STRING("OPC_A_SUBTRACT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_MULTIPLICATE: COPY_STRING("OPC_A_MULTIPLICATE"); return sizeof(enum yaoosl_opcode);
    case OPC_A_DIVIDE: COPY_STRING("OPC_A_DIVIDE"); return sizeof(enum yaoosl_opcode);
    case OPC_A_AND: COPY_STRING("OPC_A_AND"); return sizeof(enum yaoosl_opcode);
    case OPC_A_OR: COPY_STRING("OPC_A_OR"); return sizeof(enum yaoosl_opcode);
    case OPC_A_XOR: COPY_STRING("OPC_A_XOR"); return sizeof(enum yaoosl_opcode);
    case OPC_A_BITSHIFT_LEFT: COPY_STRING("OPC_A_BITSHIFT_LEFT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_BITSHIFT_RIGHT: COPY_STRING("OPC_A_BITSHIFT_RIGHT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_MODULO: COPY_STRING("OPC_A_MODULO"); return sizeof(enum yaoosl_opcode);
    case OPC_A_INVERT: COPY_STRING("OPC_A_INVERT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_ADD: COPY_STRING("OPC_A_SELF_ADD"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_SUBTRACT: COPY_STRING("OPC_A_SELF_SUBTRACT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_MULTIPLICATE: COPY_STRING("OPC_A_SELF_MULTIPLICATE"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_DIVIDE: COPY_STRING("OPC_A_SELF_DIVIDE"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_AND: COPY_STRING("OPC_A_SELF_AND"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_OR: COPY_STRING("OPC_A_SELF_OR"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_XOR: COPY_STRING("OPC_A_SELF_XOR"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_BITSHIFT_LEFT: COPY_STRING("OPC_A_SELF_BITSHIFT_LEFT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_BITSHIFT_RIGHT: COPY_STRING("OPC_A_SELF_BITSHIFT_RIGHT"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_MODULO: COPY_STRING("OPC_A_SELF_MODULO"); return sizeof(enum yaoosl_opcode);
    case OPC_A_SELF_INVERT: COPY_STRING("OPC_A_SELF_INVERT"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_NOT: COPY_STRING("OPC_LOGICAL_NOT"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_AND: COPY_STRING("OPC_LOGICAL_AND"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_OR: COPY_STRING("OPC_LOGICAL_OR"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_EQUALS: COPY_STRING("OPC_LOGICAL_EQUALS"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_EQUALS_NOT: COPY_STRING("OPC_LOGICAL_EQUALS_NOT"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_GREATER_THEN: COPY_STRING("OPC_LOGICAL_GREATER_THEN"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_GREATER_THEN_OR_EQUAL: COPY_STRING("OPC_LOGICAL_GREATER_THEN_OR_EQUAL"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_LESS_THEN: COPY_STRING("OPC_LOGICAL_LESS_THEN"); return sizeof(enum yaoosl_opcode);
    case OPC_LOGICAL_LESS_THEN_OR_EQUAL: COPY_STRING("OPC_LOGICAL_LESS_THEN_OR_EQUAL"); return sizeof(enum yaoosl_opcode);
    case OPC_PUSH_TRUE: COPY_STRING("OPC_PUSH_TRUE"); return sizeof(enum yaoosl_opcode);
    case OPC_PUSH_FALSE: COPY_STRING("OPC_PUSH_FALSE"); return sizeof(enum yaoosl_opcode);
    case OPC_PUSH_THIS: COPY_STRING("OPC_PUSH_THIS"); return sizeof(enum yaoosl_opcode);
    case OPC_PUSH_NULL: COPY_STRING("OPC_PUSH_NULL"); return sizeof(enum yaoosl_opcode);
    case OPC_PUSH_ARRAY: COPY_STRING("OPC_PUSH_ARRAY"); return sizeof(enum yaoosl_opcode);
    case OPC_PUSH_ARRAY_TYPED: COPY_STRING("OPC_PUSH_ARRAY_TYPED"); return sizeof(enum yaoosl_opcode);
    case OPC_RESOLVE_TYPE: COPY_STRING("OPC_RESOLVE_TYPE"); return sizeof(enum yaoosl_opcode);
    case OPC_INDEX_GET: COPY_STRING("OPC_INDEX_GET"); return sizeof(enum yaoosl_opcode);
    case OPC_INDEX_SET: COPY_STRING("OPC_INDEX_SET"); return sizeof(enum yaoosl_opcode);
    case OPC_JUMP_OFF_a8: COPY_STRING("OPC_JUMP_OFF_a8"); COPY_INT8_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_SCOPE_ALLOCATE_a8: COPY_STRING("OPC_SCOPE_ALLOCATE_a8"); COPY_UINT8_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_SET_VALUE_a8: COPY_STRING("OPC_SET_VALUE_a8"); COPY_UINT8_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_GET_VALUE_a8: COPY_STRING("OPC_GET_VALUE_a8"); COPY_UINT8_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_PUSH_INT8_a8: COPY_STRING("OPC_PUSH_INT8_a8"); COPY_INT8_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_PUSH_UINT8_a8: COPY_STRING("OPC_PUSH_UINT8_a8"); COPY_INT8_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_PUSH_CHAR_a8: COPY_STRING("OPC_PUSH_CHAR_a8"); COPY_CHAR_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_PUSH_NEW_a8: COPY_STRING("OPC_PUSH_NEW_a8"); COPY_UINT8_TO_STRING; return sizeof(enum yaoosl_opcode) + 1;
    case OPC_PUSH_INT16_a16: COPY_STRING("OPC_PUSH_INT16_a16"); COPY_INT16_TO_STRING; return sizeof(enum yaoosl_opcode) + 2;
    case OPC_PUSH_UINT16_a16: COPY_STRING("OPC_PUSH_UINT16_a16"); COPY_UINT16_TO_STRING; return sizeof(enum yaoosl_opcode) + 2;
    case OPC_JUMP_OFF_a16: COPY_STRING("OPC_JUMP_OFF_a16"); COPY_INT16_TO_STRING; return sizeof(enum yaoosl_opcode) + 2;
    case OPC_SCOPE_ALLOCATE_a16: COPY_STRING("OPC_SCOPE_ALLOCATE_a16"); COPY_UINT16_TO_STRING; return sizeof(enum yaoosl_opcode) + 2;
    case OPC_SET_VALUE_a16: COPY_STRING("OPC_SET_VALUE_a16"); COPY_UINT16_TO_STRING; return sizeof(enum yaoosl_opcode) + 2;
    case OPC_GET_VALUE_a16: COPY_STRING("OPC_GET_VALUE_a16"); COPY_UINT16_TO_STRING; return sizeof(enum yaoosl_opcode) + 2;
    case OPC_JUMP_OFF_a32: COPY_STRING("OPC_JUMP_OFF_a32"); COPY_INT32_TO_STRING; return sizeof(enum yaoosl_opcode) + 4;
    case OPC_PUSH_INT32_a32: COPY_STRING("OPC_PUSH_INT32_a32"); COPY_INT32_TO_STRING; return sizeof(enum yaoosl_opcode) + 4;
    case OPC_PUSH_UINT32_a32: COPY_STRING("OPC_PUSH_UINT32_a32"); COPY_UINT32_TO_STRING; return sizeof(enum yaoosl_opcode) + 4;
    case OPC_PUSH_FLOAT_a32: COPY_STRING("OPC_PUSH_FLOAT_a32"); COPY_FLOAT_TO_STRING; return sizeof(enum yaoosl_opcode) + 4;
    case OPC_CREATE_METHOD_CODEBLOCK_a64: COPY_STRING("OPC_CREATE_METHOD_CODEBLOCK_a64"); COPY_UINT64_TO_STRING; return sizeof(enum yaoosl_opcode) + 8;
    case OPC_PUSH_INT64_a64: COPY_STRING("OPC_PUSH_INT64_a64"); COPY_INT64_TO_STRING; return sizeof(enum yaoosl_opcode) + 8;
    case OPC_PUSH_DOUBLE_a64: COPY_STRING("OPC_PUSH_DOUBLE_a64"); COPY_DOUBLE_TO_STRING; return sizeof(enum yaoosl_opcode) + 8;
    case OPC_PUSH_UINT64_a64: COPY_STRING("OPC_PUSH_UINT64_a64"); COPY_UINT64_TO_STRING; return sizeof(enum yaoosl_opcode) + 8;


    case OPC_PUSH_STRING_a8:
        COPY_STRING("OPC_PUSH_STRING_a8");
        COPY_UINT8_TO_STRING;
        j = uint8;
        goto OPC_PUSH_STRING;
    case OPC_PUSH_STRING_a16:
        COPY_STRING("OPC_PUSH_STRING_a16");
        COPY_UINT16_TO_STRING;
        j = uint16;
        goto OPC_PUSH_STRING;
    case OPC_PUSH_STRING_a32:
        COPY_STRING("OPC_PUSH_STRING_a32");
        COPY_UINT32_TO_STRING;
        j = uint32;
        goto OPC_PUSH_STRING;

    OPC_PUSH_STRING:
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        buffer[0] = '"';
        buffer++;
        buffer_len--;
        for (i = 0, k = 0; i < j && k < buffer_len - 1; i++, k++)
        {
            uint8 = bytes[i];
            switch (uint8)
            {
            case '\n':
                buffer[k] = '\\';
                k++;
                if (k > buffer_len) { break; }
                buffer[k] = 'n';
                break;
            case '\r':
                buffer[k] = '\\';
                k++;
                if (k > buffer_len) { break; }
                buffer[k] = 'r';
                break;
            case '\t':
                buffer[k] = '\\';
                k++;
                if (k > buffer_len) { break; }
                buffer[k] = 't';
                break;
            case '\0':
                buffer[k] = '\\';
                k++;
                if (k > buffer_len) { break; }
                buffer[k] = '0';
                break;
            default: buffer[k] = uint8; break;
            }
        }
        buffer[k] = '"';
        buffer++;
        buffer_len--;
        buffer[k] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 1 + j);

    case OPC_NAVIGATE_PROPERTY_a8:
        COPY_STRING("OPC_NAVIGATE_PROPERTY_a8");
        COPY_UINT8_TO_STRING;
        j = uint8;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 1 + j);
    case OPC_SET_PROPERTY_a8:
        COPY_STRING("OPC_SET_PROPERTY_a8");
        COPY_UINT8_TO_STRING;
        j = uint8;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 1 + j);

    case OPC_DECLARE_CLASS_a16:
        COPY_STRING("OPC_DECLARE_CLASS_a16");
        COPY_UINT16_TO_STRING;
        j = uint16;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 2 + j);
    case OPC_CREATE_CLASS_BEGIN_a16:
        COPY_STRING("OPC_CREATE_CLASS_BEGIN_a16");
        COPY_UINT16_TO_STRING;
        j = uint16;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 2 + j);
    case OPC_NAVIGATE_PROPERTY_a16:
        COPY_STRING("OPC_NAVIGATE_PROPERTY_a16");
        COPY_UINT16_TO_STRING;
        j = uint16;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 2 + j);
    case OPC_SET_PROPERTY_a16:
        COPY_STRING("OPC_SET_PROPERTY_a16");
        COPY_UINT16_TO_STRING;
        j = uint16;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 2 + j);
    case OPC_NAVIGATE_PROPERTY_a32:
        COPY_STRING("OPC_NAVIGATE_PROPERTY_a32");
        COPY_UINT32_TO_STRING;
        j = uint32;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 4 + j);
    case OPC_SET_PROPERTY_a32:
        COPY_STRING("OPC_SET_PROPERTY_a32");
        COPY_UINT32_TO_STRING;
        j = uint32;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 4 + j);

    case OPC_CALL_a8_b8:
        COPY_STRING("OPC_CALL_a8_b8");
        COPY_UINT8_TO_STRING;
        j = uint8;
        COPY_UINT8_TO_STRING;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 2 + j);
    case OPC_CALL_SELF_a8_b8:
        COPY_STRING("OPC_CALL_SELF_a8_b8");
        COPY_UINT8_TO_STRING;
        j = uint8;
        COPY_UINT8_TO_STRING;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 2 + j);
    case OPC_CALL_SELF_a16_b8:
        COPY_STRING("OPC_CALL_SELF_a16_b8");
        COPY_UINT16_TO_STRING;
        j = uint16;
        COPY_UINT8_TO_STRING;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 3 + j);
    case OPC_CALL_a16_b8:
        COPY_STRING("OPC_CALL_a16_b8");
        COPY_UINT16_TO_STRING;
        j = uint16;
        COPY_UINT8_TO_STRING;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 3 + j);
    case OPC_CALL_a32_b8:
        COPY_STRING("OPC_CALL_a32_b8");
        COPY_UINT32_TO_STRING;
        j = i;
        COPY_UINT8_TO_STRING;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 5 + j);
    case OPC_CALL_SELF_a32_b8:
        COPY_STRING("OPC_CALL_SELF_a32_b8");
        COPY_UINT32_TO_STRING;
        j = uint32;
        COPY_UINT8_TO_STRING;
        buffer[0] = ' ';
        buffer++;
        buffer_len--;
        for (i = 0; i < j && i < buffer_len; i++)
        {
            buffer[i] = bytes[i];
        }
        buffer[i] = '\0';
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 5 + j);
    case OPC_DIAG_a16:
        COPY_STRING("OPC_DIAG_START_a16");
        COPY_UINT16_TO_STRING;
        for (j = uint16; j > 0; j--)
        {
            if (isprint(bytes[0]))
            {
                COPY_CHAR_TO_STRING;
            }
            else
            {
                bytes++;
            }
        }
        return (unsigned int)(sizeof(enum yaoosl_opcode) + 2 + uint16);
    case OPC_EXTEND: COPY_STRING("OPC_EXTEND"); return 1;
    default:
        return -1;
    }
}