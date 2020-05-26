#pragma once
#include <stdbool.h>
#include "yaoosl_operators.h"
#include "yaoosl_knowntypes.h"
#include "yaoosl_method.h"
#include "yaoosl_util_macros.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	struct yaoosl_instance;
	struct yaoosl_code;
	struct yaoosl_class;

	typedef struct yaoosl_property {
		char* title;
		yaooslmethodhandle get;
		yaooslmethodhandle set;
		struct yaoosl_class* type;
		unsigned int value_index;
	} yaoosl_property;
	typedef yaoosl_property* yaooslpropertyhandle;

	typedef struct yaoosl_class {
		char* fullname;
		char* name;
		bool requires_free;
		bool fin;

		bool sealed;
		void* callback_data;
		bool (*callback_create)(void* data, struct yaoosl_instance* instance);
		void (*callback_destroy)(void* data, struct yaoosl_instance* instance);

		struct yaoosl_class** implements;
		unsigned int implements_capacity;
		unsigned int implements_size;
		
		yaooslmethodgrouphandle operator_method_groups[__OPERATOR_MAX];
		yaooslmethodgrouphandle constructor_method_group;
		yaooslmethodhandle destructor_method;

		yaooslmethodgrouphandle* method_groups;
		unsigned int method_groups_capacity;
		unsigned int method_groups_size;

		yaooslpropertyhandle* properties;
		unsigned int properties_capacity;
		// Total properties size.
		unsigned int properties_size;
		// Properties, declared by this class
		// nstead of inherited by parents.
		unsigned int properties_size_self;
	} yaoosl_class;
	typedef yaoosl_class* yaooslclasshandle;


	// Creates a new classhandle and returns the value.
	// Note that this will not yet be added to any virtual machine yet.
	//
	// Param 0: The actual class name.
	// Return:  The newly created handle or NULL if something failed (eg. out of memory).
	yaooslclasshandle yaoosl_class_create(const char* name);


	yaooslmethodgrouphandle yaoosl_class_get_method(yaooslclasshandle handle, const char* name, int strlen);

	// Sets the name of a classhandle
	// Return:  true on success or false if something failed (eg. out of memory).
	bool yaoosl_class_set_name(yaooslclasshandle handle, const char* name);

	// !Not intended to be called by user code!
	// Destroys an existing class handle.
	void yaoosl_class_destroy(yaooslclasshandle handle);

	// Finalizes the provided classhandle and sets the required value size.
	// Note that after this method was called, the classhandle should NEVER ever be modified again.
	// If yaoosl_class_ methods are being used, they will fail after this.
	//
	// Param 0: The handle that should be finalized.
	bool yaoosl_class_finalize(yaooslclasshandle handle);

	// Checks if the left type is either the right type or inherits from it.
	// 
	// Param 0: The class that may be derived
	// Param 1: The class that is suspected to be the base
	// Return: 0 if no type relation exists, 1..* if origin is a relative of against.
	//         The number indicates how equal they are, with 1 meaning that they are the same type,
	//         2 that origin has against as base, 3 that origin has a base that has against as base,
	//         ...
	int yaoosl_class_is_type(yaooslclasshandle handle_origin, yaooslclasshandle handle_against);


	void yaoosl_property_default_get(struct yaoosl*, struct yaoosl_context*, struct yaoosl_method*, struct yaoosl_instance*);
	void yaoosl_property_default_set(struct yaoosl*, struct yaoosl_context*, struct yaoosl_method*, struct yaoosl_instance*);
	
	yaooslpropertyhandle yaoosl_property_copy(yaooslpropertyhandle handle);
	yaooslpropertyhandle yaoosl_property_create(const char* name, yaooslclasshandle type);
	yaooslpropertyhandle yaoosl_property_create2(const char* name, yaooslclasshandle type, yaooslmethodhandle get, yaooslmethodhandle set);
	void yaoosl_property_destroy(yaooslpropertyhandle handle);

	bool yaoosl_class_push_method(yaooslclasshandle handle, yaooslmethodhandle method);
	bool yaoosl_class_push_operator_method(yaooslclasshandle handle, enum yaoosl_operator op, yaooslmethodhandle method);


	// Appends the provided base class to the provided handle.
	//
	// Param 0: The handle that a base should be added onto.
	// Param 1: The base that should be added to Param 0.
	// Return:  True if all worked, False if something failed (eg. out of memory)
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(class, yaooslclasshandle, class_handle, yaooslclasshandle, base);

	// Appends the provided method group to the provided handle.
	//
	// Param 0: The handle that a method group should be added onto.
	// Param 1: The method group that should be added to Param 0.
	// Return:  True if all worked, False if something failed (eg. out of memory)
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(class, yaooslclasshandle, class_handle, yaooslmethodgrouphandle, method_group);

	// Appends the provided property to the provided handle.
	//
	// Param 0: The handle that a method group should be added onto.
	// Param 1: The property that should be added to Param 0.
	// Return:  True if all worked, False if something failed (eg. out of memory)
	PRINT__YAOOSL_MTHD_PUSH_VALUE_PROTO(class, yaooslclasshandle, class_handle, yaooslpropertyhandle, property);

#ifdef __cplusplus
}
#endif // __cplusplus