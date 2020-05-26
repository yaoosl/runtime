#pragma once
#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define yaoosl_STD_NAMESPACE_STR_PREFIX "Yaoosl."

	struct yaoosl_method;
	struct yaoosl_class;
	struct yaoosl_map_list;
	struct yaoosl_instance;
	struct yaoosl_context;
	
	typedef struct yaoosl {
		bool (*error_handle)(struct yaoosl* vm, struct yaoosl_context* context, const char* errmsg);

		struct yaoosl_map_list* classes_map;
		struct yaoosl_class** classes;
		size_t classes_capacity;
		size_t classes_size;

		struct diagnostics {
			// Called for each context individual before the actual opcode is received.
			// Allows to intercept execution BEFORE next instruction executes
			bool (*can_continue)(void* user_data, struct yaoosl* vm, struct yaoosl_context* cntxt);
			void* user_data;
		} diagnostics;
	} yaoosl;
	typedef yaoosl* yaooslhandle;

	bool yaoosl_default_error_handle(struct yaoosl* vm, struct yaoosl_context* context, const char* errmsg);

	// Creates a new yaoosl and returns the value.
	// Note that this method may return NULL if something failed.
	yaooslhandle yaoosl_create_virtualmachine(void);

	// Destroys an existing vm handle.
	// Returns true on success.
	bool yaoosl_destroy_virtualmachine(yaooslhandle yaoosl);

	// Adds the provided classhandle to the provided yaoosl instance.
	// Ownership moves to yaoosl afterwards.
	// Destroying the yaoosl will destroy the class!
	bool yaoosl_push_class(yaooslhandle yaoosl, struct yaoosl_class* classhandle);
	// Creates a class and pushes it to the vm classes list.
	// Class will not be finalized and may be edited.
	// Note that this method may return NULL if something failed (eg. OutOfMemory).
	struct yaoosl_class* yaoosl_declare_class(yaooslhandle yaoosl, const char* classname);


	void yaoosl_execute(yaooslhandle vm, struct yaoosl_context* context);
	bool yaoosl_call_method(yaooslhandle vm, struct yaoosl_context* context, struct yaoosl_method* method, struct yaoosl_instance* self);
#ifdef __cplusplus
}
#endif // __cplusplus