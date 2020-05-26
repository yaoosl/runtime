#include "yaoosl_code.h"
#include "yaoosl.tab.h"
#include "yaoosl_opcodes.h"

#include <malloc.h>
#include <string.h>
#include <stdio.h>

yaooslcodehandle yaoosl_code_create(void)
{
	yaooslcodehandle handle = malloc(sizeof(yaoosl_code));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_code));
	}
	return handle;
}

yaooslcodehandle yaoosl_code_create2(yaoosl_code_callback callback)
{
	yaooslcodehandle handle = malloc(sizeof(yaoosl_code));
	if (handle)
	{
		memset(handle, 0, sizeof(yaoosl_code));
		handle->function = callback;
	}
	return handle;
}


static int get_bom_skip(const unsigned char* ubuff)
{
    if (!ubuff)
        return 0;
    // We are comparing against unsigned
    if (ubuff[0] == 0xEF && ubuff[1] == 0xBB && ubuff[2] == 0xBF)
    {
        //UTF-8
        return 3;
    }
    else if (ubuff[0] == 0xFE && ubuff[1] == 0xFF)
    {
        //UTF-16 (BE)
        return 2;
    }
    else if (ubuff[0] == 0xFE && ubuff[1] == 0xFE)
    {
        //UTF-16 (LE)
        return 2;
    }
    else if (ubuff[0] == 0x00 && ubuff[1] == 0x00 && ubuff[2] == 0xFF && ubuff[3] == 0xFF)
    {
        //UTF-32 (BE)
        return 2;
    }
    else if (ubuff[0] == 0xFF && ubuff[1] == 0xFF && ubuff[2] == 0x00 && ubuff[3] == 0x00)
    {
        //UTF-32 (LE)
        return 2;
    }
    else if (ubuff[0] == 0x2B && ubuff[1] == 0x2F && ubuff[2] == 0x76 &&
        (ubuff[3] == 0x38 || ubuff[3] == 0x39 || ubuff[3] == 0x2B || ubuff[3] == 0x2F))
    {
        //UTF-7
        return 4;
    }
    else if (ubuff[0] == 0xF7 && ubuff[1] == 0x64 && ubuff[2] == 0x4C)
    {
        //UTF-1
        return 3;
    }
    else if (ubuff[0] == 0xDD && ubuff[1] == 0x73 && ubuff[2] == 0x66 && ubuff[3] == 0x73)
    {
        //UTF-EBCDIC
        return 3;
    }
    else if (ubuff[0] == 0x0E && ubuff[1] == 0xFE && ubuff[2] == 0xFF)
    {
        //SCSU
        return 3;
    }
    else if (ubuff[0] == 0xFB && ubuff[1] == 0xEE && ubuff[2] == 0x28)
    {
        //BOCU-1
        if (ubuff[3] == 0xFF)
            return 4;
        return 3;
    }
    else if (ubuff[0] == 0x84 && ubuff[1] == 0x31 && ubuff[2] == 0x95 && ubuff[3] == 0x33)
    {
        //GB 18030
        return 3;
    }
    return 0;
}
static char* readFile(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    size_t file_size;
    char* out;
    int bom_skip, i;
    if (!file)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (!(out = malloc(sizeof(char) * (file_size + 1))))
    {
        fclose(file);
        return NULL;
    }
    if (file_size > 5)
    {
        fread(out, sizeof(char), 5, file);
        out[5] = '\0';
        bom_skip = get_bom_skip(out);
        for (i = bom_skip; i < 5; i++)
        {
            out[i - bom_skip] = out[i];
        }
        fread(out + 5 - bom_skip, sizeof(char), file_size - 5, file);
    }
    else
    {
        fread(out, sizeof(char), file_size, file);
    }
    out[file_size] = '\0';
    fclose(file);

    return out;
}

yaooslcodehandle yaoosl_code_parse_file(const char* path, bool debug_symbols)
{
    char* contents =  readFile(path);
    if (!contents)
    {
        return NULL;
    }
    yaooslcodehandle handle = yaoosl_code_parse_contents(contents, debug_symbols, path);
    free(contents);
    return handle;
}

yaooslcodehandle yaoosl_code_parse_contents(const char* contents, bool debug_symbols, const char* filepath)
{
    struct yaoosl_yyhelper helper = { 0 };
    yyscan_t scan;
    size_t filepath_len = strlen(filepath);
    if (filepath_len > UINT16_MAX)
    {
        return NULL;
    }
    helper.handle = yaoosl_code_create();
    helper.sstack = yystring_create_stack();
    helper.code = contents;
    helper.code_file = filepath;
    helper.code_file_len = (uint16_t)filepath_len;
    helper.debug_symbols = debug_symbols;
#if defined(_DEBUG) && defined(YAOOSL_DEBUG) && YAOOSL_DEBUG == 1
    yaoosl_debug = 1;
#endif
    yaoosl_lex_init(&scan);
    yaoosl_set_extra(&helper, scan);

    yaoosl_parse(scan, &helper);
    if (helper.errored)
    {
        if (helper.handle->bytes_size > 0) { free(helper.handle->bytes); }
        free(helper.handle);
        yaoosl_lex_destroy(scan);
        yystring_destroy_stack(helper.sstack);
        return NULL;
    }
    yaoosl_lex_destroy(scan);
    yystring_destroy_stack(helper.sstack);

    return helper.handle;
}

#define SPACE10 "          "
#define SPACE50 SPACE10 SPACE10 SPACE10 SPACE10 SPACE10 
#define SPACE100 SPACE50 SPACE50
#define SPACE500 SPACE100 SPACE100 SPACE100 SPACE100 SPACE100 
#define SPACE1000 SPACE500 SPACE500 


struct dstr
{
    char* str;
    size_t capacity;
    size_t length;
};
static bool append_string_n(struct dstr* str, const char* append, size_t append_len)
{
    char* tmp;
    while (str->length + append_len + 1 > str->capacity)
    {
        tmp = realloc(str->str, sizeof(char) * (str->capacity + str->capacity + 1));
        if (!tmp)
        {
            return false;
        }
        str->capacity = str->capacity + str->capacity + 1;
        str->str = tmp;
    }
    strncpy(str->str + str->length, append, append_len);
    str->str[str->length + append_len] = '\0';
    return true;
}
static bool append_string(struct dstr* str, const char* append)
{
    return append_string_n(str, append, strlen(append));
}
static bool append_size_t(struct dstr* str, size_t value, size_t padding)
{
    char buff[256];
    size_t len;
    len = snprintf(buff, 255, "%lld", (long long)value);
    for (; len < padding && len < 255; len++)
    {
        buff[len] = ' ';
    }
    buff[len] = '\0';
    return append_string_n(str, buff, len);
}


char* yaoosl_code_to_string(yaooslcodehandle handle)
{
    char buffer[512];
    size_t buffer_len = 512;
    size_t i, depth = 0, res;
    enum yaoosl_opcode current;
    enum yaoosl_opcode previous = 0;
    struct dstr str = { 0 };
    for (i = 0; i < handle->bytes_size;)
    {
        if (depth > 500)
        {
            depth = 0;
        }
        switch (sizeof(enum yaoosl_opcode))
        {
        case 1: current = handle->bytes[i + 0]; break;
        case 2: current = (((uint16_t)handle->bytes[i + 0]) << (8 * 1)) | (((uint16_t)handle->bytes[i + 1]) << (8 * 0)); break;
        case 4: current = (((uint32_t)handle->bytes[i + 0]) << (8 * 3)) | (((uint32_t)handle->bytes[i + 1]) << (8 * 2)) | (((uint32_t)handle->bytes[i + 2]) << (8 * 1)) | (((uint32_t)handle->bytes[i + 3]) << (8 * 0)); break;
        default: current = (((uint64_t)handle->bytes[i + 0]) << (8 * 7)) | (((uint64_t)handle->bytes[i + 1]) << (8 * 6)) | (((uint64_t)handle->bytes[i + 2]) << (8 * 5)) | (((uint64_t)handle->bytes[i + 3]) << (8 * 4)) | (((uint64_t)handle->bytes[i + 4]) << (8 * 3)) | (((uint64_t)handle->bytes[i + 5]) << (8 * 2)) | (((uint64_t)handle->bytes[i + 6]) << (8 * 1)) | (((uint64_t)handle->bytes[i + 7]) << (8 * 0));  break;
        }
        switch (current)
        {
        case OPC_CREATE_CLASS_BEGIN_a16:
        case OPC_CREATE_METHOD_BEGIN:
        case OPC_CREATE_PROPERTY_BEGIN:
            depth++;
            break;
        case OPC_CREATE_CLASS_END:
        case OPC_CREATE_METHOD_END:
        case OPC_CREATE_PROPERTY_END:
            depth--;
            break;
        }
        append_size_t(&str, i, 5);
        append_string(&str, "| ");
        append_string_n(&str, SPACE1000, depth * 2);

        res = yaoosl_opcode_to_string(handle->bytes + i, buffer, (unsigned int)buffer_len);
        if (res == (unsigned int)-1)
        {
            append_string(&str, "ERROR TOKEN");
            i++;
        }
        else
        {
            append_string(&str, buffer);
            i += res;
        }
        append_string(&str, "\n");

        switch (current)
        {
        case OPC_CREATE_CLASS_BEGIN_a16:
        case OPC_CREATE_METHOD_BEGIN:
        case OPC_CREATE_PROPERTY_BEGIN:
            depth++;
            break;
        case OPC_CREATE_CLASS_END:
        case OPC_CREATE_METHOD_END:
        case OPC_CREATE_PROPERTY_END:
            depth--;
            break;
        }
    }

    append_string(&str, "");
    return str.str;
}