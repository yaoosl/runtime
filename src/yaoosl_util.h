#pragma once
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define PRINT__yaoosl_PUSH_EXTENSIONS(TYPE, NAME)\
	bool yaoosl_util_push_ ## NAME(struct yaoosl* yaoosl, struct yaoosl_context* context, TYPE value)

	struct yaoosl_context;
	struct yaoosl_class;
	struct yaoosl_instance;
	struct yaoosl_code;

	struct yaoosl_instance* yaoosl_util_create_array(struct yaoosl* yaoosl, int32_t size, struct yaoosl_class* type);
	struct yaoosl_instance* yaoosl_util_create_stackframe_array(struct yaoosl* yaoosl, struct yaoosl_context* context);

	struct yaoosl_context* yaoosl_util_load_code(struct yaoosl* yaoosl, struct yaoosl_code* codehandle);
	bool yaoosl_util_execute_code(struct yaoosl* yaoosl, struct yaoosl_code* codehandle);

	bool yaoosl_util_push_null(struct yaoosl_context* context);
	bool yaoosl_util_push_string(struct yaoosl* yaoosl, struct yaoosl_context* context, const char* value);
	bool yaoosl_util_push_stringn(struct yaoosl* yaoosl, struct yaoosl_context* context, size_t len, const char* value);
	struct yaoosl_instance* yaoosl_util_get_string(struct yaoosl* yaoosl, const char* value);
	struct yaoosl_instance* yaoosl_util_get_stringn(struct yaoosl* yaoosl, size_t len, const char* value);
	bool yaoosl_util_throw_generic(struct yaoosl* yaoosl, struct yaoosl_context* context, const char* message);
	bool yaoosl_util_throw(struct yaoosl* yaoosl, struct yaoosl_context* context, struct yaoosl_class* type, const char* message);
	bool yaoosl_util_throw2(struct yaoosl* yaoosl, struct yaoosl_context* context, struct yaoosl_instance* exception);
	PRINT__yaoosl_PUSH_EXTENSIONS(uint8_t, uint8);
	PRINT__yaoosl_PUSH_EXTENSIONS(int8_t, int8);
	PRINT__yaoosl_PUSH_EXTENSIONS(uint16_t, uint16);
	PRINT__yaoosl_PUSH_EXTENSIONS(int16_t, int16);
	PRINT__yaoosl_PUSH_EXTENSIONS(uint32_t, uint32);
	PRINT__yaoosl_PUSH_EXTENSIONS(int32_t, int32);
	PRINT__yaoosl_PUSH_EXTENSIONS(uint64_t, uint64);
	PRINT__yaoosl_PUSH_EXTENSIONS(int64_t, int64);
	PRINT__yaoosl_PUSH_EXTENSIONS(float, float);
	PRINT__yaoosl_PUSH_EXTENSIONS(double, double);
	PRINT__yaoosl_PUSH_EXTENSIONS(struct yaoosl_class*, type);




#undef PRINT__yaoosl_PUSH_EXTENSIONS
#ifdef __cplusplus
}
#endif // __cplusplus