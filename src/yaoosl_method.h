#pragma once
#include <stdbool.h>
#include <inttypes.h>
#include "yaoosl_util_macros.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	struct yaoosl_code;

	typedef struct yaoosl_arg {
		char* title;
		struct yaoosl_class* type;
	} yaoosl_arg;
	typedef yaoosl_arg* yaooslarghandle;

	typedef struct yaoosl_method {
		char* title;
		
		yaooslarghandle* args;
		unsigned int args_capacity;
		unsigned int args_size;

		char** prefixes;
		uint16_t prefixes_capacity;
		uint16_t prefixes_size;

		struct yaoosl_class* returntype;
		struct yaoosl_code* contents;
	} yaoosl_method;
	typedef yaoosl_method* yaooslmethodhandle;

	typedef struct yaoosl_method_group {
		char* title;
		yaooslmethodhandle* methods;
		unsigned int methods_capacity;
		unsigned int methods_size;
	} yaoosl_method_group;
	typedef yaoosl_method_group* yaooslmethodgrouphandle;


	// Creates a new methodgrouphandle and returns the value.
	// Note that this will not yet be added to any virtual machine yet.
	//
	// Param 0: The name of the package this resides in.
	// Param 1: The actual class name.
	// Return:  The newly created handle or NULL if something failed (eg. out of memory).
	yaooslmethodgrouphandle yaoosl_method_group_create(const char* name);

	// Adds the provided method to the provided method group
	bool yaoosl_method_group_push_back(yaooslmethodgrouphandle grouphandle, yaooslmethodhandle methodhandle);

	// !Not intended to be called by user code!
	// Destroys an existing method group handle.
	void yaoosl_method_group_destroy(yaooslmethodgrouphandle handle);

	// Creates a new methodhandle and returns the value.
	// Note that this will not yet be added to any virtual machine yet.
	//
	// Param 0: The method name.
	// Param 1: The return type. May be NULL if void is expected.
	// Param 2: The code.
	// Return:  The newly created handle or NULL if something failed (eg. out of memory).
	yaooslmethodhandle yaoosl_method_create(const char* name, struct yaoosl_class* returntype, struct yaoosl_code* codehandle);


	// Creates a new methodhandle and returns the value.
	// Note that this will not yet be added to any virtual machine yet.
	//
	// Param 0: The method group handle.
	// Param 1: The return type. May be `NULL` if void is expected. May be `((void*)~0LL)` if ANY type may be allowed, including void.
	// Param 2: The amount of args followed
	// Param N: The types of the arguments for the expected method.
	// Return:  The method or NULL if no match was found.
	yaooslmethodhandle yaoosl_method_group_get_method(yaooslmethodgrouphandle handle, struct yaoosl_class* returntype, unsigned int arg_count, ...);
	// Creates a new methodhandle and returns the value.
	// Note that this will not yet be added to any virtual machine yet.
	//
	// Param 0: The method group handle.
	// Param 1: The return type. May be NULL if void is expected.
	// Param 2: The amount of args followed
	// Param 3: The types of the arguments for the expected method.
	// Return:  The method or NULL if no match was found.
	yaooslmethodhandle yaoosl_method_group_get_method2(yaooslmethodgrouphandle handle, struct yaoosl_class* returntype, unsigned int arg_count, struct yaoosl_class** args);

	// Adds the provided arg to the provided method
	bool yaoosl_method_push_arg(yaooslmethodhandle methodhandle, yaooslarghandle arghandle);

	// !Not intended to be called by user code!
	// Destroys an existing mmethod group handle.
	void yaoosl_method_destroy(yaooslmethodhandle handle);



	// Creates a new classhandle and returns the value.
	// Note that this will not yet be added to any virtual machine yet.
	//
	// Param 0: The name of the package this resides in.
	// Param 1: The actual class name.
	// Return:  The newly created handle or NULL if something failed (eg. out of memory).
	yaooslarghandle yaoosl_arg_create(const char* name, struct yaoosl_class* type);

	// !Not intended to be called by user code!
	// Destroys an existing arg handle.
	void yaoosl_arg_destroy(yaooslarghandle handle);


	// Pushes a string prefix onto the method-stack, transfering ownership to the methodhandle.
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(method, yaooslmethodhandle, method_handle, char*, prefix);
	// Pops the topmost string
	PRINT__YAOOSL_MTHD_POP_VALUE_PROTO(method, yaooslmethodhandle, method_handle, char*, prefix);

#ifdef __cplusplus
}
#endif // __cplusplus