/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YAOOSL_YAOOSL_TAB_H_INCLUDED
# define YY_YAOOSL_YAOOSL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YAOOSL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define YAOOSL_DEBUG 1
#  else
#   define YAOOSL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define YAOOSL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined YAOOSL_DEBUG */
#if YAOOSL_DEBUG
extern int yaoosl_debug;
#endif
/* "%code requires" blocks.  */
#line 42 "yaoosl.y" /* yacc.c:1909  */

        #ifndef YY_TYPEDEF_YY_SCANNER_T
        #define YY_TYPEDEF_YY_SCANNER_T
        typedef void* yyscan_t;
        #endif
        #ifndef YY_EXTRA_TYPE
        #define YY_EXTRA_TYPE void *
        #endif
        
        YY_EXTRA_TYPE yyget_extra(yyscan_t yyscanner);
        void yaoosl_set_extra(YY_EXTRA_TYPE user_defined, yyscan_t yyscanner);
        
        int yaoosl_lex_init (yyscan_t* scanner);
        void yaoosl_yyscan_string(const char* str, yyscan_t yyscanner);
        int yaoosl_lex_destroy(yyscan_t yyscanner);
        #include "yaoosl_code.h"
        #include <stdbool.h>
        struct yaoosl_yystring {
            char* string;
            size_t length;
            size_t capacity;
        };
        struct yaoosl_string_stack {
            struct yaoosl_yystring* strings;
            size_t size;
            size_t capacity;
        };
        struct yaoosl_yyvar {
            const char* str;
            size_t str_len;
        };
        struct yaoosl_yyhelper {
            yaooslcodehandle handle;
            struct yaoosl_string_stack* sstack;
            bool errored;
            bool debug_symbols;
            
            char* current_class;
            
            const char* code;
            size_t code_index;
            size_t code_line;
            size_t code_column;
            const char* code_file;
            uint16_t code_file_len;
            
            bool is_constructor;
            bool is_void;
            size_t tmp_size;
            bool is_static;
            
            
            

            struct yaoosl_yyvar* vars;
            size_t vars_size;
            size_t vars_capacity;

            uint64_t* break_offsets;
            size_t  break_offsets_size;
            size_t  break_offsets_capacity;

            uint64_t* continue_offsets;
            size_t  continue_offsets_size;
            size_t  continue_offsets_capacity;

            int64_t* jump_offsets;
            size_t  jump_offsets_size;
            size_t  jump_offsets_capacity;
        };
        struct yaoosl_string_stack* yystring_create_stack();
        void yystring_destroy_stack(struct yaoosl_string_stack* sstack);
        int yaoosl_yylex_get_next_char(struct yaoosl_yyhelper* helper, char* buffer, int max_buffer);
    

#line 128 "yaoosl.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YAOOSL_TOKENTYPE
# define YAOOSL_TOKENTYPE
  enum yaoosl_tokentype
  {
    YST_NAME = 258,
    YST_COLON = 259,
    YST_CLASS = 260,
    YST_WITH = 261,
    YST_OPERATOR = 262,
    YST_CURLYO = 263,
    YST_CURLYC = 264,
    YST_ROUNDO = 265,
    YST_ROUNDC = 266,
    YST_SQUAREO = 267,
    YST_SQUAREC = 268,
    YST_SC = 269,
    YST_COMMA = 270,
    YST_PREFIX = 271,
    YST_GET = 272,
    YST_EXTERN = 273,
    YST_SET = 274,
    YST_THIS = 275,
    YST_PLUSPLUS = 276,
    YST_PLUS = 277,
    YST_MINUSMINUS = 278,
    YST_MINUS = 279,
    YST_STAR = 280,
    YST_SLASH = 281,
    YST_LTLT = 282,
    YST_LTEQ = 283,
    YST_LT = 284,
    YST_GTGT = 285,
    YST_GTEQ = 286,
    YST_GT = 287,
    YST_EQEQ = 288,
    YST_NOTEQ = 289,
    YST_NOT = 290,
    YST_INVERT = 291,
    YST_MODULO = 292,
    YST_TYPEOF = 293,
    YST_VAR = 294,
    YST_EQ = 295,
    YST_EQXOR = 296,
    YST_EQOR = 297,
    YST_EQAND = 298,
    YST_EQSLAH = 299,
    YST_EQSTAR = 300,
    YST_EQMINUS = 301,
    YST_EQPLUS = 302,
    YST_EQMODULO = 303,
    YST_QUESTIONMARK = 304,
    YST_LOGICAL_OR = 305,
    YST_LOGICAL_AND = 306,
    YST_ARITHMETICAL_OR = 307,
    YST_ARITHMETICAL_AND = 308,
    YST_AS = 309,
    YST_IS = 310,
    YST_IS_NOT = 311,
    YST_TRUE = 312,
    YST_FALSE = 313,
    YST_DOT = 314,
    YST_NUMBER = 315,
    YST_HEXNUMBER = 316,
    YST_BINARYNUMBER = 317,
    YST_STRING = 318,
    YST_CHAR = 319,
    YST_NEW = 320,
    YST_PRIVATE = 321,
    YST_PROTECTED = 322,
    YST_INTERNAL = 323,
    YST_PUBLIC = 324,
    YST_STATIC = 325,
    YST_IF = 326,
    YST_ELSE = 327,
    YST_FOR = 328,
    YST_WHILE = 329,
    YST_DO = 330,
    YST_TRY = 331,
    YST_CATCH = 332,
    YST_THROW = 333,
    YST_VOID = 334,
    YST_NULL = 335,
    YST_BREAK = 336,
    YST_CONTINUE = 337,
    YST_RETURN = 338
  };
#endif

/* Value type.  */
#if ! defined YAOOSL_STYPE && ! defined YAOOSL_STYPE_IS_DECLARED

union YAOOSL_STYPE
{
#line 139 "yaoosl.y" /* yacc.c:1909  */

      short s;
      int i;
      long l;
      long long ll;
      float f;
      double d;
      bool (*emit)(yaooslcodehandle code);
      
      char* str;
    

#line 237 "yaoosl.tab.h" /* yacc.c:1909  */
};

typedef union YAOOSL_STYPE YAOOSL_STYPE;
# define YAOOSL_STYPE_IS_TRIVIAL 1
# define YAOOSL_STYPE_IS_DECLARED 1
#endif


extern YAOOSL_STYPE yaoosl_lval;

int yaoosl_parse (yyscan_t scanner, struct yaoosl_yyhelper* helper);

#endif /* !YY_YAOOSL_YAOOSL_TAB_H_INCLUDED  */
