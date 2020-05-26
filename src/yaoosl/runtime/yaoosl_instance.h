#pragma once
#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	struct yaoosl;
	struct yaoosl_class;
	typedef struct yaoosl_instance {
		struct yaoosl_class* type;
		unsigned int ref_count;
		bool gc_mark;
		union data
		{
			uint8_t  uint8;
			uint16_t uint16;
			uint32_t uint32;
			uint64_t uint64;
			int8_t   int8;
			int16_t  int16;
			int32_t  int32;
			int64_t  int64;
			float    f;
			double   d;
			char     c;
			bool	 flag;
			char*    str;
			void*    ptr;
		} additional;
		struct yaoosl_instance** fields;
		uint16_t fields_size;
	} yaoosl_instance;
	typedef yaoosl_instance* yaooslinstancehandle;


	// Creates a new valuehandle and returns the value.
	// The value handle will be equal to NULL.
	// To give it a type, you have to initialize it via a valid yaoosl
	//
	// Param 0: The classhandle that this value is supposed to represent or NULL for a null value.
	// Return:  The newly created handle or NULL if something failed (eg. out of memory).
	yaooslinstancehandle yaoosl_instance_create(struct yaoosl_class* type);

	// Helper method to change the type of an uninitialized instance
	bool yaoosl_change_type(yaooslinstancehandle handle, struct yaoosl_class* type);

	void yaoosl_instance_inc_ref(yaooslinstancehandle handle);
	void yaoosl_instance_dec_ref(yaooslinstancehandle handle);

	// !Not intended to be called by user code!
	// Destroys an existing class handle.
	void yaoosl_instance_destroy(yaooslinstancehandle handle);

#ifdef __cplusplus
}
#endif // __cplusplus