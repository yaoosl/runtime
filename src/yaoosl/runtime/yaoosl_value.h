#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	enum yaoosl_encapsulation
	{
		YENCPS_PUBLIC,
		YENCPS_INTERNAL,
		YENCPS_DERIVED,
		YENCPS_PRIVATE
	};
	enum yaoosl_value_type
	{
		YVT_REFERENCE,
		YVT_DOUBLE,
		YVT_FLOAT,
		YVT_INT8,
		YVT_INT16,
		YVT_INT32,
		YVT_INT64,
		YVT_UINT8,
		YVT_UINT16,
		YVT_UINT32,
		YVT_UINT64,
	};
	typedef struct yaoosl_class
	{
		struct yaoosl_class** implements;
		struct yaoosl_class** implements_capacity;
		struct yaoosl_class** implements_size;

		char* full_namespace;
		char* name;

		yaoosl_encapsulation encapsulation;
	} yaoosl_class;
	typedef struct yaoosl_reference
	{
		yaoosl_class type;
	} yaoosl_reference;

	typedef struct yaoosl_value
	{
		enum yaoosl_value_type type;
		union as
		{
			float f;
			double d;
			int8_t  int8;
			int16_t int16;
			int32_t int32;
			int64_t int64;
			uint8_t  uint8;
			uint16_t uint16;
			uint32_t uint32;
			uint64_t uint64;
			yaoosl_reference* reference;
		} as;
	} yaoosl_value;

#ifdef __cplusplus
}
#endif // __cplusplus