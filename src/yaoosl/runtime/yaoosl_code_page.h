#pragma once
#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	struct yaoosl_code_page;
	struct yaoosl_class;

	// Special struct containing a range of code.
	// May be passed into a method or similar as its body.
	typedef struct yaoosl_code_fragment
	{
		struct yaoosl_code_page* owner;
		uint8_t* start;
		uint8_t* end;
	} yaoosl_code_fragment;


	// Helper structure for yaoosl_code_section
	// containing informations about the catch section
	typedef struct yaoosl_code_sector_catch
	{
		size_t start;
		size_t usedtype_index;
	} yaoosl_code_sector_catch;

	// Sector information for eg. Try-Catch-Finally blocks.
	typedef struct yaoosl_code_sector
	{
		size_t try_start;

		size_t                     catch_sectors_size;
		size_t                     catch_sectors_capacity;
		yaoosl_code_sector_catch * catch_sectors;

		size_t finally_start;
	} yaoosl_code_sector;

	// Contains debug informations for a full code-page
	// To find the correcto ne, look up the best-match for `start` compared
	// to current offset.
	typedef struct yaoosl_code_debug
	{
		size_t code_start;

		uint32_t file_line;
		uint32_t file_column;
		uint32_t file_offset;
		uint32_t file_length;
		size_t  file_path_length;
		char *  file_path;
	} yaoosl_code_debug;

	typedef struct yaoosl_code_page
	{
		// Typemap where the used types get put into.
		size_t	        usedtypes_capacity;
		size_t	        usedtypes_size;
		struct yaoosl_class** usedtypes;

		// Sector informations for this code-page
		size_t               sector_capacity;
		size_t               sector_size;
		yaoosl_code_sector * sector;

		// Debug informations for this code-page
		size_t              debug_capacity;
		size_t              debug_size;
		yaoosl_code_debug * debug;

		// The actual code of this codepage.
		size_t    code_capactiy;
		size_t    code_size;
		uint8_t * code;

		// The scope-slots required by this page if executed
		// from the very start
		size_t scope_slots;
	} yaoosl_code_page;

	yaoosl_code_page* yaoosl_code_page_deserialize(const char* fpath);
	void yaoosl_code_page_serialize(const char* fpath, const yaoosl_code_page* code_page);

#ifdef __cplusplus
}
#endif // __cplusplus