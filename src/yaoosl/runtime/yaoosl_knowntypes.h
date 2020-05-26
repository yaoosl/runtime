#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	enum yaoosl_knowntypes
	{
		__KNOWN_MIN = 0,
		OBJECT = 0,
		ARRAY,

		UINT8,
		__NUMERIC_MIN = UINT8,
		INT8,
		UINT16,
		INT16,
		UINT32,
		INT32,
		UINT64,
		INT64,
		__INT_MAX = INT64,
		FLOAT,
		DOUBLE,
		__NUMERIC_MAX = DOUBLE,

		BOOLEAN,
		CHAR,
		STRING,
		TYPE,
		METHOD,
		EXCEPTION_CLASS,
		STACKFRAME_CLASS,

		__KNOWN_MAX
	};

#define yaoosl_knowntypes_propertyindex_array_Length 0
#define yaoosl_knowntypes_propertyindex_array_Type 1

#define yaoosl_knowntypes_propertyindex_exception_Message 0
#define yaoosl_knowntypes_propertyindex_exception_Message_str "Message"
#define yaoosl_knowntypes_propertyindex_exception_InnerException 1
#define yaoosl_knowntypes_propertyindex_exception_InnerException_str "InnerException"
#define yaoosl_knowntypes_propertyindex_exception_Frames 2
#define yaoosl_knowntypes_propertyindex_exception_Frames_str "Frames"

#define yaoosl_knowntypes_propertyindex_stackframe_Method 0
#define yaoosl_knowntypes_propertyindex_stackframe_Line 1
#define yaoosl_knowntypes_propertyindex_stackframe_Column 2
#define yaoosl_knowntypes_propertyindex_stackframe_File 3

#ifdef __cplusplus
}
#endif // __cplusplus