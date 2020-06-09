#pragma once
#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	
	struct yaoosl_code_page;
	struct yaoosl_reference;
	struct yaoosl_value;
	struct yaoosl_runtime;
	struct yaoosl_class;

	enum yaoosl_opcodes;

	enum yaoosl_retcde
	{
		// All fine, execution finished
		YSRC_OKAY,
		// Reached Debugger Break. Should be treated
		// as error if no debugger is attached!
		YSRC_BREAK,
		// Some code-error caused a termination (eg. uncatched exception)
		YSRC_ERROR,
		// Fatal error that yaoosl_runtime.fatal_callback could not recover from.
		YSRC_FATAL,
		// Execution was aborted because something failed to allocate something.
		YSRC_OUT_OF_MEMORY,
	};

	typedef struct yaoosl_scope
	{
		struct yaoosl_code_page * associated_page;
		uint8_t * position;
		uint8_t * position_start;
		uint8_t * position_end;
		struct yaoosl_class * local_class;

		size_t                values_size;
		struct yaoosl_value * values;
	} yaoosl_scope;

	// Callback to report fatal errors to.
	// Should return true if executed may be aborted.
	// If false is returned, yaoosl will continue executing
	// wherever it is, allowing the enduser to recover from fatal issues.
	typedef bool (*yaoosl_runtime_fatal_callback)(struct yaoosl_runtime * yvm, enum yaoosl_opcodes opcode, const char* reason);

	typedef struct yaoosl_runtime
	{
		struct yaoosl_reference* references;
		size_t                   references_capacity;
		size_t                   references_size;

		yaoosl_scope** scopes;
		size_t         scopes_capacity;
		size_t         scopes_size;

		struct yaoosl_value * values;
		size_t                values_capacity;
		size_t                values_size;

		struct yaoosl_code_page * code_pages;
		size_t                    code_pages_capacity;
		size_t                    code_pages_size;

		yaoosl_runtime_fatal_callback fatal_callback;
	} yaoosl_runtime;
	
	yaoosl_runtime* yaoosl_runtime_create();
	void yaoosl_runtime_destroy(yaoosl_runtime* runtime);

	bool yaoosl_runtime_push_scope(yaoosl_runtime* yvm, yaoosl_scope* scope);
	struct yaoosl_reference* yaoosl_reference_create(yaoosl_runtime* yvm, struct yaoosl_class* type);
    yaoosl_scope* yaoosl_scope_create(size_t slots, struct yaoosl_code_page* page);
	enum yaoosl_retcde yaoosl_runtime_execute(yaoosl_runtime* yvm, struct yaoosl_code_page* page, size_t offset);

#ifdef __cplusplus
}
#endif // __cplusplus