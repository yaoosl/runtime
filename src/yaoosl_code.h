#pragma once
#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	struct yaoosl;
	struct yaoosl_context;
	struct yaoosl_instance;


	typedef void (*yaoosl_code_callback)(struct yaoosl* vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self);

	typedef struct yaoosl_code {
		uint8_t* bytes;
		uint64_t bytes_size;
		uint64_t bytes_capacity;
		yaoosl_code_callback function;
	} yaoosl_code;
	typedef yaoosl_code* yaooslcodehandle;

	// Creates empty code block, initialized to null.
	// Returns NULL if something moved wrong (eg. OutOfMemory)
	yaooslcodehandle yaoosl_code_create(void);
	// Creates empty code block, initialized to null.
	// Returns NULL if something moved wrong (eg. OutOfMemory)
	yaooslcodehandle yaoosl_code_create2(yaoosl_code_callback callback);

	// Parses the provided file into a newly created code-handle
	//
	// path: The filepath to the ys source file.
	// debug_symbols: Emit debug symbols if true
	yaooslcodehandle yaoosl_code_parse_file(const char* path, bool debug_symbols);
	// Parses the provbided contents into a newly created code-handle
	//
	// contents: the file contents
	// debug_symbols: Emit debug symbols if true
	// filepath: The filepath to the ys source file. May be NULL.
	yaooslcodehandle yaoosl_code_parse_contents(const char* contents, bool debug_symbols, const char* filepath);

	// Parses the provided codehandle and returns a human-readable
	// string.
	char* yaoosl_code_to_string(yaooslcodehandle codehandle);
#ifdef __cplusplus
}
#endif // __cplusplus