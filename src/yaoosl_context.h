#pragma once
#include <stdbool.h>
#include <inttypes.h>
#include "yaoosl_util_macros.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define YAOOSL_DEFAULT_VALUE_STACK_SIZE 16
#define YAOOSL_DEFAULT_SCOPES_SIZE 32
#define YAOOSL_DEFAULT_EXCEPTION_HANDLERS_SIZE 32

	struct yaoosl_instance;
	struct yaoosl_method;
	struct yaoosl_class;
	struct yaoosl_map_list;
	struct yaoosl_code;

	typedef struct yaoosl_catch_handle
	{
		struct yaoosl_class* type;
		uint64_t start;
	} yaoosl_catch_handle;
	typedef struct yaoosl_block {
		uint64_t start;

		yaoosl_catch_handle* catchhandles;
		uint16_t catchhandles_capacity;
		uint16_t catchhandles_size;

		char** prefixes;
		uint16_t prefixes_capacity;
		uint16_t prefixes_size;
	} yaoosl_block;
	typedef yaoosl_block* yaooslblockhandle;

	typedef struct yaoosl_scope {
		struct yaoosl_method* related_method;

		struct yaoosl_instance** locals;
		uint16_t locals_size;

		yaooslblockhandle* blocks;
		uint16_t blocks_capacity;
		uint16_t blocks_size;

		uint64_t offset;
		struct yaoosl_code* codehandle;
		bool destroy_code;
		struct yaoosl_instance* self;
	} yaoosl_scope;
	typedef yaoosl_scope* yaooslscopehandle;

	typedef struct yaoosl_exception_handler
	{
		yaooslscopehandle scope;
		yaooslblockhandle block;
	} yaoosl_exception_handler;

	typedef struct yaoosl_context {
		bool handles_exception;

		yaooslscopehandle* scopes;
		uint16_t scopes_capacity;
		uint16_t scopes_size;

		struct yaoosl_instance** value_stack;
		uint16_t value_stack_capacity;
		uint16_t value_stack_size;

		yaoosl_exception_handler* exception_handlers;
		uint16_t exception_handlers_capacity;
		uint16_t exception_handlers_size;
	} yaoosl_context;
	typedef yaoosl_context* yaooslcontexthandle;

	typedef struct yaoosl_stacktrace {
		yaooslscopehandle* scopes;
		uint16_t scopes_size;
	} yaoosl_stacktrace;
	typedef yaoosl_stacktrace* yaooslstacktracehandle;

	// Creates a new context and returns the value.
	// Note that this method may return NULL if something failed.
	yaooslcontexthandle yaoosl_context_create(void);
	// Destroys an existing context handle and everything related.
	void yaoosl_context_destroy(yaooslcontexthandle handle);

	// Creates a new scope and returns the value.
	// Note that this method may return NULL if something failed.
	yaooslscopehandle yaoosl_scope_create(void);
	// Destroys an existing scope handle and everything related.
	void yaoosl_scope_destroy(yaooslscopehandle handle);

	// Creates a new block and returns the value.
	// Note that this method may return NULL if something failed.
	yaooslblockhandle yaoosl_block_create(void);
	// Destroys an existing block handle and everything related.
	void yaoosl_block_destroy(yaooslblockhandle handle);

	yaooslscopehandle yaoosl_context_top_scope(yaooslcontexthandle context);
	bool yaoosl_context_peek(yaooslcontexthandle context, uint8_t offset, uint8_t* out_value);
	bool yaoosl_context_try_next(yaooslcontexthandle context, uint8_t* out_value);
	uint8_t yaoosl_context_next(yaooslcontexthandle context, bool* out_success_optional);
	struct yaoosl_code* yaoosl_context_current_code(yaooslcontexthandle context);
	struct yaoosl_class* yaoosl_context_resolve_type(yaooslcontexthandle context, struct yaoosl* yaoosl, const char* classname);

	// Moves the head relative from the current position.
	// Cannot be used to move out of a scope.
	//
	// Returns true if the move was successfull, false in any other case.
	bool yaoosl_context_move(yaooslcontexthandle context, int32_t offset);

	// Starts the exception handling and returns true if it was successful
	// (the exception got catched) or false, if it was not (exception bubbled to the top)
	//
	// Param 0: The context to handle the exception
	// Param 1: The exception type
	// Param 2: OUT - The resulting stacktrace. If result is false and this is NULL, OutOfMemory happened.
	// Return:  True if the exception got handled, false if not.
	bool yaoosl_context_handle_exception(yaooslcontexthandle context, struct yaoosl_class* type, yaooslstacktracehandle* out_stacktrace, yaoosl_catch_handle* out_catch_handle);

	// Pushes a scope onto the scope-stack, transfering ownership to the context.
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(context, yaooslcontexthandle, context_handle, yaooslscopehandle, scope);
	// Pops the topmost scope
	PRINT__YAOOSL_MTHD_POP_VALUE_PROTO(context, yaooslcontexthandle, context_handle, yaooslscopehandle, scope);

	// Pushes a value onto the value-stack, transfering ownership to the context.
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(context, yaooslcontexthandle, context_handle, struct yaoosl_instance*, value);
	// Pops the topmost value
	PRINT__YAOOSL_MTHD_POP_VALUE_PROTO(context, yaooslcontexthandle, context_handle, struct yaoosl_instance*, value);

	// Pushes a exception_handler onto the exception_handler-stack, transfering ownership to the context.
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(context, yaooslcontexthandle, context_handle, yaoosl_exception_handler, exception_handler);
	// Pops the topmost exception_handler
	PRINT__YAOOSL_MTHD_POP_VALUE_PROTO(context, yaooslcontexthandle, context_handle, yaoosl_exception_handler, exception_handler);

	// Pushes a block onto the block-stack, transfering ownership to the scope.
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(scope, yaooslscopehandle, scope_handle, yaooslblockhandle, block);
	// Pops the topmost block
	PRINT__YAOOSL_MTHD_POP_VALUE_PROTO(scope, yaooslscopehandle, scope_handle, yaooslblockhandle, block);

	// Pushes a block onto the block-stack, transfering ownership to the scope.
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(block, yaooslblockhandle, block_handle, yaoosl_catch_handle, catch_handle);
	// Pops the topmost block
	PRINT__YAOOSL_MTHD_POP_VALUE_PROTO(block, yaooslblockhandle, block_handle, yaoosl_catch_handle, catch_handle);

	// Pushes a string prefix onto the block-stack, transfering ownership to the scope.
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(block, yaooslblockhandle, block_handle, char*, prefix);
	// Pops the topmost string
	PRINT__YAOOSL_MTHD_POP_VALUE_PROTO(block, yaooslblockhandle, block_handle, char*, prefix);

#ifdef __cplusplus
}
#endif // __cplusplus