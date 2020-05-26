/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 13 "yaoosl.y" /* yacc.c:316  */

        #include <malloc.h>
        #include <string.h>
        #include <stdio.h>
        #include "yaoosl_emit.h"
        #include "yaoosl_operators.h"
        #include "string_op.h"
        #define YSSTR(IN) #IN
        #define YSEMIT(MTHD) yaoosl_emit_ ## MTHD
        #define YSEMITC(MTHD) YSEMIT(create_ ## MTHD)
        #define YSEMITCC(MTHD) YSEMITC(class_ ## MTHD)
        #define YSEMITCM(MTHD) YSEMITC(method_ ## MTHD)
        #define YSEMITCP(MTHD) YSEMITC(property_ ## MTHD)
        
        
        #define ERRMSG_EXPECTED_NO_VALUE "Expected no value."
        #define ERRMSG_EXPECTED_VALUE "Expected value."
        #define ERRMSG_EXPECTED_CONSTRUCTOR "Expected constructor."
        #define ERRMSG_UNEXPECTED_BREAK "Encountered unexpected break."
        #define ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED "Static variables are not (yet) supported."
        
        
        // FU bloody configuration hell!
        // Force the macros to be defined already to avoid
        // "inconsistent dll linkage" with malloc and free.
        #define YYMALLOC
        #define YYFREE
        #define DROP(VAL)
    

#line 94 "yaoosl.tab.c" /* yacc.c:316  */
/* Substitute the type names.  */
#define YYSTYPE         YAOOSL_STYPE
/* Substitute the variable and function names.  */
#define yyparse         yaoosl_parse
#define yylex           yaoosl_lex
#define yyerror         yaoosl_error
#define yydebug         yaoosl_debug
#define yynerrs         yaoosl_nerrs

#define yylval          yaoosl_lval
#define yychar          yaoosl_char

/* Copy the first part of user declarations.  */

#line 109 "yaoosl.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yaoosl.tab.h".  */
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
#line 42 "yaoosl.y" /* yacc.c:355  */

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
    

#line 223 "yaoosl.tab.c" /* yacc.c:355  */

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
#line 139 "yaoosl.y" /* yacc.c:355  */

      short s;
      int i;
      long l;
      long long ll;
      float f;
      double d;
      bool (*emit)(yaooslcodehandle code);
      
      char* str;
    

#line 332 "yaoosl.tab.c" /* yacc.c:355  */
};

typedef union YAOOSL_STYPE YAOOSL_STYPE;
# define YAOOSL_STYPE_IS_TRIVIAL 1
# define YAOOSL_STYPE_IS_DECLARED 1
#endif


extern YAOOSL_STYPE yaoosl_lval;

int yaoosl_parse (yyscan_t scanner, struct yaoosl_yyhelper* helper);

#endif /* !YY_YAOOSL_YAOOSL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 349 "yaoosl.tab.c" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 117 "yaoosl.y" /* yacc.c:359  */

        static bool yystring_push(struct yaoosl_string_stack* sstack, const char* begin, const char* end);
        static char* yystring_join_strings_3(const char* l, const char* d, const char* r);
        static void yystring_reverse_stack(struct yaoosl_string_stack* sstack, size_t offset);
        static char* yystring_join_stack(struct yaoosl_string_stack* sstack, const char* join, size_t offset);
        static short yaoosl_yyvar_index(struct yaoosl_yyhelper* helper, const char* varname);
        static bool yaoosl_yyvar_exists(struct yaoosl_yyhelper* helper, const char* varname);
        static bool yaoosl_yyhelper_push_break(struct yaoosl_yyhelper* helper, uint64_t offset);
        static bool yaoosl_yyhelper_push_continue(struct yaoosl_yyhelper* helper, uint64_t offset);
        static bool yaoosl_yyhelper_push_jump(struct yaoosl_yyhelper* helper, int64_t offset);
        static bool yaoosl_yyhelper_store_jump(struct yaoosl_yyhelper* helper);
        static void yaoosl_yytransform_string(char* str);
        static unsigned int yaoosl_yy_is_constructor(const char* classname, const char* methodname);
        int yaoosl_lex(yyscan_t scanner);
        int yaoosl_error(yyscan_t scanner, struct yaoosl_yyhelper* helper, const char* msg);
    

#line 369 "yaoosl.tab.c" /* yacc.c:359  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YAOOSL_STYPE_IS_TRIVIAL && YAOOSL_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  91
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   873

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  112
/* YYNRULES -- Number of rules.  */
#define YYNRULES  263
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  518

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YAOOSL_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   249,   249,   250,   251,   252,   254,   254,   256,   257,
     259,   260,   261,   263,   263,   264,   265,   267,   267,   268,
     268,   270,   271,   272,   273,   274,   275,   277,   278,   279,
     281,   282,   284,   284,   285,   285,   286,   286,   287,   287,
     288,   288,   289,   289,   290,   290,   291,   291,   292,   292,
     293,   293,   294,   294,   295,   295,   296,   296,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   307,   307,
     308,   308,   309,   309,   310,   310,   311,   311,   312,   312,
     313,   313,   314,   314,   315,   315,   316,   316,   318,   319,
     320,   322,   323,   324,   326,   336,   325,   351,   362,   350,
     377,   388,   376,   401,   413,   400,   427,   426,   439,   442,
     441,   451,   450,   460,   459,   468,   467,   475,   477,   478,
     479,   481,   482,   483,   485,   485,   518,   533,   534,   535,
     536,   538,   539,   540,   542,   543,   544,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   567,   580,
     581,   582,   583,   584,   586,   587,   589,   590,   592,   593,
     595,   596,   598,   599,   601,   602,   603,   605,   606,   607,
     608,   609,   611,   612,   613,   615,   616,   617,   619,   620,
     621,   622,   624,   625,   626,   627,   634,   641,   644,   645,
     648,   649,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,   667,   668,
     669,   671,   689,   701,   724,   735,   748,   768,   788,   801,
     816,   817,   818,   819,   820,   821,   822,   823,   826,   834,
     844,   844,   865,   868,   881,   865,   905,   906,   907,   909,
     909,   909,   926,   926,   935,   947,   935,   975,   976,   993,
     976,  1007,  1024,  1007
};
#endif

#if YAOOSL_DEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "YST_NAME", "YST_COLON", "YST_CLASS",
  "YST_WITH", "YST_OPERATOR", "YST_CURLYO", "YST_CURLYC", "YST_ROUNDO",
  "YST_ROUNDC", "YST_SQUAREO", "YST_SQUAREC", "YST_SC", "YST_COMMA",
  "YST_PREFIX", "YST_GET", "YST_EXTERN", "YST_SET", "YST_THIS",
  "YST_PLUSPLUS", "YST_PLUS", "YST_MINUSMINUS", "YST_MINUS", "YST_STAR",
  "YST_SLASH", "YST_LTLT", "YST_LTEQ", "YST_LT", "YST_GTGT", "YST_GTEQ",
  "YST_GT", "YST_EQEQ", "YST_NOTEQ", "YST_NOT", "YST_INVERT", "YST_MODULO",
  "YST_TYPEOF", "YST_VAR", "YST_EQ", "YST_EQXOR", "YST_EQOR", "YST_EQAND",
  "YST_EQSLAH", "YST_EQSTAR", "YST_EQMINUS", "YST_EQPLUS", "YST_EQMODULO",
  "YST_QUESTIONMARK", "YST_LOGICAL_OR", "YST_LOGICAL_AND",
  "YST_ARITHMETICAL_OR", "YST_ARITHMETICAL_AND", "YST_AS", "YST_IS",
  "YST_IS_NOT", "YST_TRUE", "YST_FALSE", "YST_DOT", "YST_NUMBER",
  "YST_HEXNUMBER", "YST_BINARYNUMBER", "YST_STRING", "YST_CHAR", "YST_NEW",
  "YST_PRIVATE", "YST_PROTECTED", "YST_INTERNAL", "YST_PUBLIC",
  "YST_STATIC", "YST_IF", "YST_ELSE", "YST_FOR", "YST_WHILE", "YST_DO",
  "YST_TRY", "YST_CATCH", "YST_THROW", "YST_VOID", "YST_NULL", "YST_BREAK",
  "YST_CONTINUE", "YST_RETURN", "$accept", "yaoosl", "yaoosl_prefix",
  "$@1", "yaoosl_prefix2", "yaoosl_body", "sc", "classes", "class", "$@2",
  "$@3", "classbody", "baseclasslist", "ident", "operator", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "$@16", "$@17", "$@18", "$@19", "$@20", "$@21", "$@22", "$@23",
  "$@24", "$@25", "$@26", "$@27", "$@28", "$@29", "$@30", "$@31", "$@32",
  "$@33", "$@34", "$@35", "$@36", "op_args", "property", "$@37", "$@38",
  "$@39", "$@40", "$@41", "$@42", "$@43", "$@44", "constructor", "$@45",
  "method", "$@46", "$@47", "$@48", "$@49", "methodargs", "methodargs_nc",
  "methodbody", "$@50", "encapsulation", "codebody", "multicode", "code",
  "expression", "bracedexpression", "expressionlist", "exp01", "exp02",
  "exp03", "exp04", "exp05", "exp06", "exp07", "exp08", "exp09", "exp10",
  "exp11", "exp12", "propertynav", "exp13", "assignment",
  "ifthen_midaction_helper", "ifthen", "$@51", "forloop", "$@52", "$@53",
  "$@54", "fl_arg", "whileloop", "$@55", "$@56", "dowhileloop", "$@57",
  "trycatch", "$@58", "$@59", "catchblocks", "$@60", "$@61", "$@62",
  "$@63", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338
};
# endif

#define YYPACT_NINF -320

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-320)))

#define YYTABLE_NINF -145

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     474,   220,    21,   317,  -320,    21,   325,   759,   759,    29,
      51,  -320,  -320,  -320,  -320,  -320,  -320,  -320,    21,    47,
      94,   122,  -320,  -320,   317,  -320,    -3,    58,   239,   141,
     548,  -320,   729,    82,   139,  -320,    20,   143,  -320,  -320,
     106,   108,   109,   110,   118,    13,    77,    -5,    88,    16,
       5,  -320,  -320,  -320,  -320,  -320,  -320,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   158,   165,  -320,   104,
     168,   163,   162,   174,   298,  -320,  -320,  -320,    21,   425,
     169,   317,   317,  -320,   624,   624,   164,  -320,  -320,  -320,
     166,  -320,  -320,  -320,  -320,   142,   729,  -320,  -320,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,  -320,  -320,    21,
      21,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
       6,  -320,   317,   317,  -320,    21,   173,   179,  -320,   162,
    -320,   126,   317,   317,  -320,   203,   317,  -320,   317,   205,
     202,   207,   317,   655,   150,  -320,  -320,  -320,  -320,   317,
    -320,   221,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,   211,   216,  -320,    98,    21,  -320,   212,   225,
    -320,  -320,  -320,   226,  -320,   317,  -320,  -320,  -320,   222,
     228,   155,  -320,   317,   317,   234,    98,    70,  -320,  -320,
    -320,  -320,   235,    98,    98,    98,    98,     9,   240,   232,
      21,  -320,  -320,  -320,   624,  -320,   317,   241,  -320,   317,
     233,  -320,  -320,  -320,   317,  -320,     4,  -320,  -320,  -320,
    -320,  -320,     3,     7,    66,    68,    98,    21,   162,   178,
     242,   624,   243,    21,   624,  -320,     8,   176,   254,   248,
     266,   127,  -320,   730,    35,    15,   261,  -320,   212,  -320,
    -320,  -320,   257,   269,  -320,    21,   277,   162,    21,  -320,
      36,   545,   271,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,   264,  -320,   274,  -320,  -320,
    -320,  -320,  -320,   624,   317,  -320,   275,   155,   282,   276,
     278,  -320,   286,   281,   283,   279,  -320,   284,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,    21,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   288,
     287,    21,   285,   285,   285,  -320,  -320,  -320,  -320,   292,
     295,    21,   296,   302,    21,   297,   293,    21,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   304,    24,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   306,   302,   302,   302,   307,   624,    21,  -320,
     311,    21,   314,  -320,   313,   302,   302,   318,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,  -320,   322,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,   302,  -320,  -320,  -320,   624,  -320,  -320,
     316,  -320,  -320,   729,   302,  -320,  -320,   302,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,   120,   309,   315,
    -320,  -320,   155,  -320,   324,  -320,   312,   319,  -320,  -320,
      21,   302,   302,  -320,  -320,   302,   302,   332,   338,   339,
     341,   342,   343,  -320,  -320,  -320,  -320,  -320
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,   214,     0,     0,   147,     0,   212,     0,     0,     0,
       0,   209,   210,   206,   207,   208,   204,   205,     0,     0,
       0,     0,   252,   254,     0,   211,     0,     0,     0,     0,
       3,     5,    10,    15,     0,    12,     0,     0,   213,   159,
     164,   166,   168,   170,   172,   174,   177,   182,   185,   188,
     192,   197,   149,   150,   151,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   221,   219,    30,
      17,     0,     0,     0,   222,   220,   198,   199,     0,     0,
       0,     0,   246,   249,     0,     0,     0,   157,   158,   154,
       0,     1,     4,    11,    16,     0,     0,   145,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   194,     0,
       0,   215,   230,   231,   232,   233,   234,   235,   236,   237,
     200,    31,   161,     0,   227,     0,     0,     0,   160,    13,
       6,   200,   161,     0,   229,     0,     0,   218,   161,     0,
     247,     0,     0,     0,     0,   141,   255,   156,   155,     0,
     146,     0,   167,   169,   171,   173,   175,   176,   178,   179,
     180,   181,   183,   184,   186,   187,   189,   190,   191,   196,
     195,   201,   162,     0,   226,     0,     0,    14,     8,     0,
     228,   203,   217,     0,   238,   246,   242,   250,   142,     0,
       0,   257,   216,     0,   161,   223,     0,     0,   140,   139,
     138,   137,     0,     0,     0,     0,     0,     0,     0,    27,
       0,     7,   225,   202,     0,   248,     0,     0,   143,     0,
     258,   256,   165,   163,     0,    26,     0,    18,    25,    24,
      22,    23,    30,     0,     0,     0,     0,    28,     0,   239,
       0,     0,     0,     0,     0,   224,    30,     0,     0,     0,
       0,     0,   123,     0,   119,     0,     0,    29,     8,   240,
     243,   251,     0,     0,   259,   131,     0,     0,   128,   125,
     121,     0,     0,    34,    38,    60,    62,    44,    46,    48,
      50,    52,    54,    56,    58,   104,   101,     0,    32,    36,
      40,    20,     9,     0,   246,   253,     0,   257,     0,     0,
       0,   103,     0,     0,     0,   107,   102,     0,    64,    66,
      68,    70,    72,    74,    76,    78,    80,    82,    84,    86,
      42,    88,    94,    90,    96,    92,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   128,     0,     0,     0,   241,   244,   261,   260,   132,
       0,   131,   129,     0,   128,     0,     0,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,   118,
       0,   128,   134,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    98,     0,    35,
      39,    61,    63,    45,    47,    49,    51,    53,    55,    57,
      59,   105,   111,     0,    33,    37,    41,     0,   262,   133,
       0,   130,   136,     0,     0,   108,   114,     0,    65,    67,
      69,    71,    73,    75,    77,    79,    81,    83,    85,    87,
      43,    89,    95,    91,    97,    93,   124,     0,     0,     0,
     120,   245,   257,   127,     0,   126,     0,     0,   122,    99,
       0,     0,     0,   263,   135,     0,     0,     0,     0,     0,
       0,     0,     0,   106,   112,   109,   115,   100
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -320,  -320,  -320,  -320,    89,   328,  -124,   327,  -320,  -320,
    -320,   -87,   116,    -2,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,   488,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -319,     0,    22,  -320,   157,
     -81,   -30,     1,    87,  -320,  -134,  -320,  -320,  -320,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -320,    62,   114,
      46,  -320,  -320,  -320,  -320,  -320,  -320,  -320,  -190,  -320,
    -320,  -320,  -320,  -320,  -320,  -320,  -320,  -288,  -320,  -320,
    -320,  -320
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    29,    30,   188,   221,    31,   140,    32,    33,   136,
     137,   212,   218,    34,   213,   352,   337,   353,   338,   354,
     380,   341,   342,   343,   344,   345,   346,   347,   348,   339,
     340,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   381,   383,   385,   382,   384,   388,   214,
     349,   488,   365,   496,   350,   489,   366,   497,   215,   259,
     216,   297,   317,   282,   314,   313,   309,   413,   463,   217,
     154,    35,   155,    37,    38,   183,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,   181,    51,
      68,   224,    52,   303,    53,   226,   304,   406,   151,    54,
     152,   227,    55,    84,    56,    85,   201,   231,   254,   307,
     407,   492
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    36,    93,    72,   156,   225,    97,   256,   189,   -30,
      69,    87,   242,  -116,   193,   187,    80,   386,   275,   358,
    -144,    96,   110,     1,    69,   111,   117,    69,   118,  -144,
       3,    36,   402,    36,     4,   437,   298,    36,   299,    78,
       6,   114,   115,   295,   315,   414,   104,   105,   417,   139,
     139,   300,    75,   116,    79,     7,     8,    81,     9,    10,
     119,   120,   135,    67,   131,    66,   160,   135,    74,   262,
     233,   264,    88,   263,   257,   265,   145,    11,    12,   243,
      13,    14,    15,    16,    17,    18,   260,     2,   244,   459,
      71,    19,   461,    20,    21,    22,    23,    36,    24,   206,
      25,    26,    27,    28,    82,   106,   107,   -21,   108,   109,
     112,    86,   113,   134,   356,    90,   207,   179,   180,   235,
     144,    76,    77,   199,   268,   147,   238,   239,   240,   241,
     280,   499,    83,   131,   281,   500,   208,   209,   210,   211,
     296,    91,    95,   249,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   311,    36,    99,   316,    98,   100,   266,
     101,   130,   102,   135,   208,   209,   210,   211,   149,   150,
     271,   103,   -19,   274,   138,   132,   139,   141,   157,   148,
     158,   185,   159,   186,   219,    73,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   503,   133,    58,    59,    60,    61,
      62,    63,    64,    65,   191,   245,   194,   195,   248,   182,
     184,   196,   355,   -30,   200,   203,   204,   205,   220,   182,
     190,   228,   230,   192,   258,   182,   222,   223,   229,   197,
     234,   261,     1,   253,   237,   219,   202,   247,   246,     3,
     269,   273,   251,    89,   272,   276,   270,   277,   278,     6,
      57,    58,    59,    60,    61,    62,    63,    64,    65,   279,
     301,   305,   306,   308,     7,     8,   312,     9,    10,    66,
     310,   336,   150,  -110,   351,   359,   357,   360,   361,   362,
     232,   182,   363,   364,   367,   387,    11,    12,  -113,    13,
      14,    15,    16,    17,    18,   400,   401,   408,   142,   409,
     412,   411,   416,   250,   415,   436,   252,   453,   457,    25,
       1,   255,   460,   462,   464,   487,   458,     3,   501,   467,
     493,   505,   502,   504,   312,   512,   506,     6,   143,    58,
      59,    60,    61,    62,    63,    64,    65,   513,   514,   312,
     515,   516,     7,     8,   517,     9,    10,   302,    92,   308,
      94,   410,   312,   267,   236,   312,    58,    59,    60,    61,
      62,    63,    64,    65,    11,    12,   491,    13,    14,    15,
      16,    17,    18,     0,    73,   438,     0,     0,     0,     0,
       0,   150,     0,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,   312,     0,     0,   312,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,     0,   454,   455,   456,     0,     0,
       0,     0,     0,   494,     0,     0,     0,   465,   466,     0,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,     0,
       0,     0,     0,     0,    36,   146,    58,    59,    60,    61,
      62,    63,    64,    65,     0,   490,     0,     1,     0,     2,
       0,     0,     0,     0,     3,     0,   495,     0,     4,   498,
       5,     0,     0,     0,     6,     0,     0,     0,   507,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     0,     9,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   508,   509,     0,     0,   510,   511,     0,
       0,    11,    12,     0,    13,    14,    15,    16,    17,    18,
       0,     0,     0,     0,     0,    19,     0,    20,    21,    22,
      23,     1,    24,     2,    25,    26,    27,    28,     3,     0,
       0,     0,     4,     0,     0,     0,     0,   318,     6,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,     0,   331,     7,     8,     0,     9,    10,     0,     0,
       0,     0,     0,     0,     0,   332,   333,   334,   335,     0,
       0,     0,     0,     0,     0,    11,    12,     0,    13,    14,
      15,    16,    17,    18,     0,     0,     0,     0,     0,    19,
       0,    20,    21,    22,    23,     0,    24,     1,    25,    26,
      27,    28,   153,     0,     3,     0,     0,     0,     4,     0,
       0,     0,     0,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     7,
       8,     0,     9,    10,   198,     3,     0,     0,     0,     4,
       0,     0,     0,     0,     0,     6,     0,     0,     0,     0,
       0,    11,    12,     0,    13,    14,    15,    16,    17,    18,
       7,     8,     0,     9,    10,    19,     0,    20,    21,    22,
      23,     0,    24,     0,    25,    26,    27,    28,     0,     0,
       0,     0,    11,    12,     0,    13,    14,    15,    16,    17,
      18,     0,     0,     0,     0,     0,    19,     0,    20,    21,
      22,    23,     1,    24,     0,    25,    26,    27,    28,     3,
       0,     0,     0,     4,     0,     0,     0,     0,     0,     6,
       0,   283,     0,   284,     0,     0,     0,   285,     0,     0,
     286,     0,     1,     0,     7,     8,     0,     9,    10,     3,
       0,   287,   288,   289,   290,   291,   292,   293,   294,     6,
       0,     0,     0,     0,     0,     0,    11,    12,     0,    13,
      14,    15,    16,    17,    18,     0,     0,     9,    10,     0,
      19,     0,    20,    21,    22,    23,     0,    24,     0,    25,
      26,    27,    28,     0,     0,     0,    11,    12,     0,    13,
      14,    15,    16,    17,    18,     0,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,     0,     0,    25,
     403,   404,   405,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435
};

static const yytype_int16 yycheck[] =
{
       2,     0,    32,     5,    85,   195,    36,     3,   142,     3,
       3,    14,     3,    10,   148,   139,    18,   336,    10,   307,
       0,     1,    27,     3,     3,    30,    21,     3,    23,     9,
      10,    30,   351,    32,    14,    11,    21,    36,    23,    10,
      20,    25,    26,     8,     8,   364,    33,    34,   367,    14,
      14,    36,     6,    37,     3,    35,    36,    10,    38,    39,
      55,    56,    59,     1,    66,    59,    96,    59,     6,     3,
     204,     3,    14,     7,    70,     7,    78,    57,    58,    70,
      60,    61,    62,    63,    64,    65,    79,     5,    79,   408,
       3,    71,   411,    73,    74,    75,    76,    96,    78,     1,
      80,    81,    82,    83,    10,    28,    29,     9,    31,    32,
      22,    24,    24,    67,   304,    28,    18,   119,   120,   206,
      74,     7,     8,   153,   248,    79,   213,   214,   215,   216,
       3,    11,    10,   135,     7,    15,    66,    67,    68,    69,
     264,     0,     3,   224,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   277,   153,    49,   280,    14,    50,   246,
      51,     3,    52,    59,    66,    67,    68,    69,    81,    82,
     251,    53,     4,   254,    11,    10,    14,     3,    14,    10,
      14,     8,    40,     4,   186,    59,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   492,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    11,   217,    11,    15,   220,   132,
     133,    14,   303,     3,    74,     4,    15,    11,    16,   142,
     143,     9,    77,   146,   236,   148,    11,    11,    10,   152,
       6,   243,     3,    10,     9,   247,   159,    15,     8,    10,
      72,   253,    11,    14,    11,    79,    14,     3,    10,    20,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     3,
       9,    14,     3,   275,    35,    36,   278,    38,    39,    59,
       3,    10,   195,    19,    10,     3,    11,    11,    10,     3,
     203,   204,    11,    10,    10,    10,    57,    58,    19,    60,
      61,    62,    63,    64,    65,    17,    19,    15,    10,    14,
       8,    15,    19,   226,    17,    11,   229,    11,    11,    80,
       3,   234,    11,     9,    11,     3,   407,    10,    19,    11,
      14,    19,    17,     9,   336,     3,    17,    20,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     9,     9,   351,
       9,     9,    35,    36,    11,    38,    39,   268,    30,   361,
      33,   361,   364,   247,   207,   367,    41,    42,    43,    44,
      45,    46,    47,    48,    57,    58,   457,    60,    61,    62,
      63,    64,    65,    -1,    59,   387,    -1,    -1,    -1,    -1,
      -1,   304,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   408,    -1,    -1,   411,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,    -1,   403,   404,   405,    -1,    -1,
      -1,    -1,    -1,   463,    -1,    -1,    -1,   415,   416,    -1,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,    -1,
      -1,    -1,    -1,    -1,   463,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,   453,    -1,     3,    -1,     5,
      -1,    -1,    -1,    -1,    10,    -1,   464,    -1,    14,   467,
      16,    -1,    -1,    -1,    20,    -1,    -1,    -1,   500,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   501,   502,    -1,    -1,   505,   506,    -1,
      -1,    57,    58,    -1,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,    75,
      76,     3,    78,     5,    80,    81,    82,    83,    10,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    22,    20,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    35,    36,    -1,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    -1,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    73,    74,    75,    76,    -1,    78,     3,    80,    81,
      82,    83,     8,    -1,    10,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    35,
      36,    -1,    38,    39,     9,    10,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    57,    58,    -1,    60,    61,    62,    63,    64,    65,
      35,    36,    -1,    38,    39,    71,    -1,    73,    74,    75,
      76,    -1,    78,    -1,    80,    81,    82,    83,    -1,    -1,
      -1,    -1,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,    74,
      75,    76,     3,    78,    -1,    80,    81,    82,    83,    10,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    21,    -1,    23,    -1,    -1,    -1,    27,    -1,    -1,
      30,    -1,     3,    -1,    35,    36,    -1,    38,    39,    10,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    -1,    60,
      61,    62,    63,    64,    65,    -1,    -1,    38,    39,    -1,
      71,    -1,    73,    74,    75,    76,    -1,    78,    -1,    80,
      81,    82,    83,    -1,    -1,    -1,    57,    58,    -1,    60,
      61,    62,    63,    64,    65,    -1,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,    -1,    -1,    80,
     352,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,    10,    14,    16,    20,    35,    36,    38,
      39,    57,    58,    60,    61,    62,    63,    64,    65,    71,
      73,    74,    75,    76,    78,    80,    81,    82,    83,    85,
      86,    89,    91,    92,    97,   155,   156,   157,   158,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   173,   176,   178,   183,   186,   188,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    59,   172,   174,     3,
      97,   157,    97,    59,   172,   174,   173,   173,    10,     3,
      97,    10,    10,    10,   187,   189,   157,    14,    14,    14,
     157,     0,    89,   155,    91,     3,     1,   155,    14,    49,
      50,    51,    52,    53,    33,    34,    28,    29,    31,    32,
      27,    30,    22,    24,    25,    26,    37,    21,    23,    55,
      56,   157,   157,   157,   157,   157,   157,   157,   157,   157,
       3,    97,    10,    40,   174,    59,    93,    94,    11,    14,
      90,     3,    10,    40,   174,    97,    40,   174,    10,   157,
     157,   182,   184,     8,   154,   156,   154,    14,    14,    40,
     155,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,    97,
      97,   172,   157,   159,   157,     8,     4,    90,    87,   159,
     157,    11,   157,   159,    11,    15,    14,   157,     9,   155,
      74,   190,   157,     4,    15,    11,     1,    18,    66,    67,
      68,    69,    95,    98,   133,   142,   144,   153,    96,    97,
      16,    88,    11,    11,   175,   182,   179,   185,     9,    10,
      77,   191,   157,   159,     6,    95,   153,     9,    95,    95,
      95,    95,     3,    70,    79,    97,     8,    15,    97,   154,
     157,    11,   157,    10,   192,   157,     3,    70,    97,   143,
      79,    97,     3,     7,     3,     7,    95,    96,    90,    72,
      14,   154,    11,    97,   154,    10,    79,     3,    10,     3,
       3,     7,   147,    21,    23,    27,    30,    41,    42,    43,
      44,    45,    46,    47,    48,     8,    90,   145,    21,    23,
      36,     9,    88,   177,   180,    14,     3,   193,    97,   150,
       3,    90,    97,   149,   148,     8,    90,   146,    22,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    37,    50,    51,    52,    53,    10,   100,   102,   113,
     114,   105,   106,   107,   108,   109,   110,   111,   112,   134,
     138,    10,    99,   101,   103,   154,   182,    11,   191,     3,
      11,    10,     3,    11,    10,   136,   140,    10,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     104,   127,   130,   128,   131,   129,   149,    10,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
      17,    19,   149,   132,   132,   132,   181,   194,    15,    14,
     150,    15,     8,   151,   149,    17,    19,   149,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,    11,    11,    97,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,    11,   151,   151,   151,    11,   154,   149,
      11,   149,     9,   152,    11,   151,   151,    11,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,     3,   135,   139,
     151,   154,   195,    14,   155,   151,   137,   141,   151,    11,
      15,    19,    17,   191,     9,    19,    17,    97,   151,   151,
     151,   151,     3,     9,     9,     9,     9,    11
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    85,    85,    87,    86,    88,    88,
      89,    89,    89,    90,    90,    91,    91,    93,    92,    94,
      92,    95,    95,    95,    95,    95,    95,    96,    96,    96,
      97,    97,    99,    98,   100,    98,   101,    98,   102,    98,
     103,    98,   104,    98,   105,    98,   106,    98,   107,    98,
     108,    98,   109,    98,   110,    98,   111,    98,   112,    98,
     113,    98,   114,    98,   115,    98,   116,    98,   117,    98,
     118,    98,   119,    98,   120,    98,   121,    98,   122,    98,
     123,    98,   124,    98,   125,    98,   126,    98,   127,    98,
     128,    98,   129,    98,   130,    98,   131,    98,   132,   132,
     132,   133,   133,   133,   134,   135,   133,   136,   137,   133,
     138,   139,   133,   140,   141,   133,   143,   142,   142,   145,
     144,   146,   144,   147,   144,   148,   144,   144,   149,   149,
     149,   150,   150,   150,   152,   151,   151,   153,   153,   153,
     153,   154,   154,   154,   155,   155,   155,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   157,
     158,   159,   159,   159,   160,   160,   161,   161,   162,   162,
     163,   163,   164,   164,   165,   165,   165,   166,   166,   166,
     166,   166,   167,   167,   167,   168,   168,   168,   169,   169,
     169,   169,   170,   170,   170,   170,   170,   171,   171,   171,
     172,   172,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     174,   174,   174,   174,   174,   174,   174,   174,   175,   176,
     177,   176,   179,   180,   181,   178,   182,   182,   182,   184,
     185,   183,   187,   186,   189,   190,   188,   191,   192,   193,
     191,   194,   195,   191
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     0,     5,     0,     4,
       1,     2,     1,     1,     2,     1,     2,     0,     6,     0,
       8,     0,     2,     2,     2,     2,     2,     1,     2,     3,
       1,     3,     0,     7,     0,     7,     0,     7,     0,     7,
       0,     7,     0,     8,     0,     7,     0,     7,     0,     7,
       0,     7,     0,     7,     0,     7,     0,     7,     0,     7,
       0,     7,     0,     7,     0,     8,     0,     8,     0,     8,
       0,     8,     0,     8,     0,     8,     0,     8,     0,     8,
       0,     8,     0,     8,     0,     8,     0,     8,     0,     8,
       0,     8,     0,     8,     0,     8,     0,     8,     2,     4,
       7,     4,     5,     5,     0,     0,    11,     0,     0,    12,
       0,     0,    11,     0,     0,    12,     0,     7,     7,     0,
       8,     0,     9,     0,     8,     0,     9,     9,     0,     2,
       4,     0,     2,     4,     0,     4,     2,     1,     1,     1,
       1,     1,     2,     3,     1,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     2,     3,     3,     2,     2,     1,
       3,     0,     1,     3,     1,     5,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     3,     3,     1,     2,     2,
       2,     3,     5,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     4,     3,     2,
       2,     2,     2,     5,     7,     5,     4,     3,     4,     3,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     6,
       0,     9,     0,     0,     0,    12,     0,     1,     3,     0,
       0,     7,     0,     8,     0,     0,     5,     0,     0,     0,
       5,     0,     0,     9
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (scanner, helper, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YAOOSL_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner, helper); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t scanner, struct yaoosl_yyhelper* helper)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (scanner);
  YYUSE (helper);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t scanner, struct yaoosl_yyhelper* helper)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner, helper);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, yyscan_t scanner, struct yaoosl_yyhelper* helper)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , scanner, helper);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, helper); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YAOOSL_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YAOOSL_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YAOOSL_DEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YAOOSL_DEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YAOOSL_DEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YAOOSL_DEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, yyscan_t scanner, struct yaoosl_yyhelper* helper)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  YYUSE (helper);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 3: /* YST_NAME  */
#line 150 "yaoosl.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); }
#line 1875 "yaoosl.tab.c" /* yacc.c:1257  */
        break;

    case 63: /* YST_STRING  */
#line 150 "yaoosl.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); }
#line 1881 "yaoosl.tab.c" /* yacc.c:1257  */
        break;

    case 64: /* YST_CHAR  */
#line 150 "yaoosl.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); }
#line 1887 "yaoosl.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* ident  */
#line 150 "yaoosl.y" /* yacc.c:1257  */
      { free(((*yyvaluep).str)); }
#line 1893 "yaoosl.tab.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, struct yaoosl_yyhelper* helper)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 3:
#line 250 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(block_pop(helper->handle)); }
#line 2174 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 251 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(block_pop(helper->handle)); }
#line 2180 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 254 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(block_push(helper->handle)); YSEMIT(push_string(helper->handle, (yyvsp[-1].str))); YSEMIT(block_prefix(helper->handle)); }
#line 2186 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 257 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_string(helper->handle, (yyvsp[-2].str))); YSEMIT(block_prefix(helper->handle)); }
#line 2192 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 260 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(prepend_scope_allocate_a(helper->handle, (uint16_t)helper->vars_size)); }
#line 2198 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 261 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(prepend_scope_allocate_a(helper->handle, (uint16_t)helper->vars_size)); }
#line 2204 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 267 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(prepend_class_declaration(helper->handle, (yyvsp[0].str))); helper->current_class = strdup((yyvsp[0].str)); YSEMITCC(begin_a(helper->handle, (yyvsp[0].str))); }
#line 2210 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 267 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCC(end(helper->handle)); free(helper->current_class); }
#line 2216 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 268 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(prepend_class_declaration(helper->handle, (yyvsp[0].str))); helper->current_class = strdup((yyvsp[0].str)); YSEMITCC(begin_a(helper->handle, (yyvsp[0].str))); }
#line 2222 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 268 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCC(end(helper->handle)); free(helper->current_class); }
#line 2228 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 277 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCC(baseclass2(helper->handle, (yyvsp[0].str))); }
#line 2234 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 278 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCC(baseclass2(helper->handle, (yyvsp[-1].str))); }
#line 2240 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 279 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCC(baseclass2(helper->handle, (yyvsp[-2].str))); }
#line 2246 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 281 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 2252 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 282 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.str) = yystring_join_strings_3((yyvsp[-2].str), ".", (yyvsp[0].str)); }
#line 2258 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 284 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_INCREASE))); }
#line 2264 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 284 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2270 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 285 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_INCREASE))); }
#line 2276 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 285 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2282 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 286 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_DECREASE))); }
#line 2288 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 286 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2294 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 287 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_DECREASE))); }
#line 2300 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 287 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2306 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 288 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_INVERT))); }
#line 2312 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 288 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2318 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 289 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_NOT))); }
#line 2324 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 289 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2330 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 290 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_XOR))); }
#line 2336 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 290 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2342 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 291 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_OR))); }
#line 2348 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 291 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2354 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 292 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_AND))); }
#line 2360 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 292 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2366 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 293 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_DIVIDE))); }
#line 2372 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 293 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2378 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 294 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_MULTIPLICATE))); }
#line 2384 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 294 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2390 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 295 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_SUBTRACT))); }
#line 2396 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 295 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2402 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 296 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_ADD))); }
#line 2408 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 296 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2414 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 297 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_MODULO))); }
#line 2420 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 297 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2426 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 298 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_BITSHIFT_LEFT))); }
#line 2432 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 298 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2438 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 299 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_BITSHIFT_RIGHT))); }
#line 2444 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 299 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2450 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 300 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_ADD))); }
#line 2456 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 300 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2462 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 301 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SUBTRACT))); }
#line 2468 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 301 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2474 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 302 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_MULTIPLICATE))); }
#line 2480 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 302 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2486 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 303 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_DIVIDE))); }
#line 2492 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 303 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2498 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 304 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_BITSHIFT_LEFT))); }
#line 2504 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 304 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2510 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 305 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LESS_THEN_OR_EQUAL))); }
#line 2516 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 305 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2522 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 306 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LESS_THEN))); }
#line 2528 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 306 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2534 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 307 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_BITSHIFT_RIGHT))); }
#line 2540 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 307 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2546 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 308 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LARGER_THEN_OR_EQUAL))); }
#line 2552 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 308 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2558 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 309 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LARGER_THEN))); }
#line 2564 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 309 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2570 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 310 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_EQUALS))); }
#line 2576 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 310 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2582 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 311 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_EQUALS_NOT))); }
#line 2588 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 311 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2594 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 312 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_MODULO))); }
#line 2600 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 312 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2606 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 313 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_AND))); }
#line 2612 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 313 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2618 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 314 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_AND))); }
#line 2624 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 314 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2630 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 315 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_OR))); }
#line 2636 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 315 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2642 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 316 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_OR))); }
#line 2648 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 316 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(return2(helper->handle, (yyvsp[-5].str))); YSEMITCM(end(helper->handle)); }
#line 2654 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 319 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(arg2(helper->handle, (yyvsp[-2].str), (yyvsp[-1].str))); }
#line 2660 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 320 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(arg2(helper->handle, (yyvsp[-5].str), (yyvsp[-4].str))); YSEMITCM(arg2(helper->handle, (yyvsp[-2].str), (yyvsp[-1].str))); }
#line 2666 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 322 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCP(begin(helper->handle)); YSEMITCP(return2(helper->handle, (yyvsp[-2].str))); YSEMITCP(name2(helper->handle, (yyvsp[-1].str))); YSEMITCP(end(helper->handle)); }
#line 2672 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 323 "yaoosl.y" /* yacc.c:1646  */
    { DROP((yyvsp[-2].str)); DROP((yyvsp[-1].str)); yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED); }
#line 2678 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 324 "yaoosl.y" /* yacc.c:1646  */
    { DROP((yyvsp[-2].str)); DROP((yyvsp[-1].str)); }
#line 2684 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 326 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, (yyvsp[-2].str)));
            YSEMITCP(name2(helper->handle, (yyvsp[-1].str)));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, (yyvsp[-2].str)));
        }
#line 2698 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 336 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, (yyvsp[-5].str), "value"));
            yaoosl_yyvar_index(helper, "value");
        }
#line 2711 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 345 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
#line 2720 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 351 "yaoosl.y" /* yacc.c:1646  */
    {
            yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, (yyvsp[-2].str)));
            YSEMITCP(name2(helper->handle, (yyvsp[-1].str)));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, (yyvsp[-2].str)));
        }
#line 2735 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 362 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, (yyvsp[-5].str), "value"));
            yaoosl_yyvar_index(helper, "value");
        }
#line 2748 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 371 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
#line 2757 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 377 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, (yyvsp[-2].str)));
            YSEMITCP(name2(helper->handle, (yyvsp[-1].str)));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, (yyvsp[-2].str), "value"));
            yaoosl_yyvar_index(helper, "value");
        }
#line 2772 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 388 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, (yyvsp[-5].str)));
        }
#line 2784 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 396 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
#line 2793 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 401 "yaoosl.y" /* yacc.c:1646  */
    {
            yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, (yyvsp[-2].str)));
            YSEMITCP(name2(helper->handle, (yyvsp[-1].str)));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, (yyvsp[-2].str), "value"));
            yaoosl_yyvar_index(helper, "value");
        }
#line 2809 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 413 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, (yyvsp[-5].str)));
        }
#line 2821 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 421 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
#line 2830 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 427 "yaoosl.y" /* yacc.c:1646  */
    {
                 if (!yaoosl_yy_is_constructor(helper->current_class, (yyvsp[0].str)))
                 {
                     yyerror(scanner, helper, ERRMSG_EXPECTED_CONSTRUCTOR);
                 }
                 YSEMITCM(begin(helper->handle));
                 YSEMITCM(return2(helper->handle, helper->current_class));
                 YSEMITCM(name2(helper->handle, (yyvsp[0].str)));
                 helper->is_constructor = true; helper->is_void = true;
             }
#line 2845 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 438 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); helper->is_constructor = false; }
#line 2851 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 439 "yaoosl.y" /* yacc.c:1646  */
    { DROP((yyvsp[-4].str)); }
#line 2857 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 442 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(return2(helper->handle, (yyvsp[-1].str)));
            YSEMITCM(name2(helper->handle, (yyvsp[0].str)));
            helper->is_void = false;
        }
#line 2868 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 449 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2874 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 451 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(return2(helper->handle, (yyvsp[-1].str)));
            YSEMITCM(name2(helper->handle, (yyvsp[0].str)));
            helper->is_void = false;
        }
#line 2885 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 458 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2891 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 460 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, (yyvsp[0].str)));
            helper->is_void = true;
        }
#line 2901 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 466 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2907 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 468 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, (yyvsp[0].str)));
            helper->is_void = true;
        }
#line 2917 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 474 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(end(helper->handle)); }
#line 2923 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 475 "yaoosl.y" /* yacc.c:1646  */
    { DROP((yyvsp[-4].str)); }
#line 2929 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 478 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(arg2(helper->handle, (yyvsp[-1].str), (yyvsp[0].str))); }
#line 2935 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 479 "yaoosl.y" /* yacc.c:1646  */
    { YSEMITCM(arg2(helper->handle, (yyvsp[-3].str), (yyvsp[-2].str))); }
#line 2941 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 482 "yaoosl.y" /* yacc.c:1646  */
    { DROP((yyvsp[-1].str)); DROP((yyvsp[0].str)); }
#line 2947 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 483 "yaoosl.y" /* yacc.c:1646  */
    { DROP((yyvsp[-3].str)); DROP((yyvsp[-2].str)); }
#line 2953 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 485 "yaoosl.y" /* yacc.c:1646  */
    {
                yaoosl_yyhelper_store_jump(helper);
                YSEMITCM(codeblock_a64(helper->handle, 0));
                yaoosl_yyhelper_store_jump(helper);
                
                yaoosl_yyhelper_store_jump(helper);
                YSEMIT(scope_allocate_a16(helper->handle, 0));
                yaoosl_yyhelper_store_jump(helper);
            }
#line 2967 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 495 "yaoosl.y" /* yacc.c:1646  */
    {
                // Ensure that we always return something
                if (helper->is_constructor)
                {
                    YSEMIT(push_this(helper->handle));
                    YSEMIT(scope_pop(helper->handle));
                }
                else
                {
                    YSEMIT(push_null(helper->handle));
                    YSEMIT(scope_pop(helper->handle));   
                }
                yaoosl_yyhelper_store_jump(helper);
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 5];
                YSEMITCM(codeblock_a64(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 4]));
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
                
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
                YSEMIT(scope_allocate_a16(helper->handle, helper->vars_size));
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
                helper->jump_offsets_size -= 5;
                helper->vars_size = 0;
            }
#line 2995 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 518 "yaoosl.y" /* yacc.c:1646  */
    {
                // Ensure that we always return something
                if (helper->is_constructor)
                {
                    YSEMIT(push_this(helper->handle));
                    YSEMIT(scope_pop(helper->handle));
                }
                else
                {
                    YSEMIT(push_null(helper->handle));
                    YSEMIT(scope_pop(helper->handle));   
                }
                YSEMITCM(codeblock_a64(helper->handle, 0));
            }
#line 3014 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 547 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(pop_value(helper->handle)); }
#line 3020 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 553 "yaoosl.y" /* yacc.c:1646  */
    { if (!helper->is_void) { yyerror(scanner, helper, ERRMSG_EXPECTED_VALUE); } YSEMIT(scope_pop(helper->handle)); }
#line 3026 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 554 "yaoosl.y" /* yacc.c:1646  */
    { if (helper->is_void) { yyerror(scanner, helper, ERRMSG_EXPECTED_NO_VALUE); } YSEMIT(scope_pop(helper->handle)); }
#line 3032 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 555 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(block_throw(helper->handle)); }
#line 3038 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 557 "yaoosl.y" /* yacc.c:1646  */
    {
        if (helper->break_offsets_size > 0)
        {
            YSEMIT(jump_off_a32(helper->handle, helper->break_offsets[helper->break_offsets_size - 1] - helper->handle->bytes_size));
        }
        else
        {
            yyerror(scanner, helper, ERRMSG_UNEXPECTED_BREAK);
        }
    }
#line 3053 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 568 "yaoosl.y" /* yacc.c:1646  */
    {
        if (helper->continue_offsets_size > 0)
        {
            YSEMIT(jump_off_a32(helper->handle, helper->continue_offsets[helper->continue_offsets_size - 1] - helper->handle->bytes_size));
        }
        else
        {
            yyerror(scanner, helper, ERRMSG_UNEXPECTED_BREAK);
        }
    }
#line 3068 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 582 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.i) = 0; }
#line 3074 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 583 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.i) = 1; }
#line 3080 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 584 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.i) = 1 + (yyvsp[0].i); }
#line 3086 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 590 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_or(helper->handle)); }
#line 3092 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 593 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_and(helper->handle)); }
#line 3098 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 596 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_or(helper->handle)); }
#line 3104 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 599 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_and(helper->handle)); }
#line 3110 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 602 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_equals(helper->handle)); }
#line 3116 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 603 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_equals_not(helper->handle)); }
#line 3122 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 606 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_less_then_or_equal(helper->handle)); }
#line 3128 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 607 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_less_then(helper->handle)); }
#line 3134 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 608 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_greater_then_or_equal(helper->handle)); }
#line 3140 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 609 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_greater_then(helper->handle)); }
#line 3146 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 612 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_bitshift_left(helper->handle)); }
#line 3152 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 613 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_bitshift_right(helper->handle)); }
#line 3158 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 616 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_add(helper->handle)); }
#line 3164 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 617 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_subtract(helper->handle)); }
#line 3170 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 620 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_multiplicate(helper->handle)); }
#line 3176 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 621 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_divide(helper->handle)); }
#line 3182 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 622 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_modulo(helper->handle)); }
#line 3188 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 625 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(increment(helper->handle)); }
#line 3194 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 626 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(decrement(helper->handle)); }
#line 3200 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 628 "yaoosl.y" /* yacc.c:1646  */
    {
         YSEMIT(push_string(helper->handle, (yyvsp[0].str)));
         YSEMIT(resolve_type(helper->handle));
         YSEMIT(is_type(helper->handle));
         YSEMIT(logical_not(helper->handle));
     }
#line 3211 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 635 "yaoosl.y" /* yacc.c:1646  */
    {
         YSEMIT(push_string(helper->handle, (yyvsp[0].str)));
         YSEMIT(resolve_type(helper->handle));
         YSEMIT(is_type(helper->handle));
     }
#line 3221 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 644 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(logical_not(helper->handle)); }
#line 3227 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 645 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(a_invert(helper->handle)); }
#line 3233 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 648 "yaoosl.y" /* yacc.c:1646  */
    { yystring_push(helper->sstack, (yyvsp[0].str), 0); (yyval.i) = 1; }
#line 3239 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 649 "yaoosl.y" /* yacc.c:1646  */
    { yystring_push(helper->sstack, (yyvsp[-1].str), 0); (yyval.i) = 1 + (yyvsp[0].i); }
#line 3245 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 651 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_string(helper->handle, (yyvsp[-3].str))); YSEMIT(resolve_type(helper->handle)); YSEMIT(push_new_a8(helper->handle, (yyvsp[-1].i))); }
#line 3251 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 652 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_string(helper->handle, (yyvsp[-1].str))); YSEMIT(resolve_type(helper->handle)); }
#line 3257 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 653 "yaoosl.y" /* yacc.c:1646  */
    { yaoosl_yytransform_string((yyvsp[0].str)); YSEMIT(push_string(helper->handle, (yyvsp[0].str))); }
#line 3263 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 654 "yaoosl.y" /* yacc.c:1646  */
    { yaoosl_yytransform_string((yyvsp[0].str)); YSEMIT(push_char_a8(helper->handle, (yyvsp[0].str)[0])); }
#line 3269 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 655 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_double_a64(helper->handle, (yyvsp[0].d))); }
#line 3275 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 656 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_int32_a32(helper->handle, (yyvsp[0].ll))); }
#line 3281 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 657 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_int32_a32(helper->handle, (yyvsp[0].ll))); }
#line 3287 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 658 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_true(helper->handle)); }
#line 3293 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 659 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_false(helper->handle)); }
#line 3299 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 660 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_null(helper->handle)); }
#line 3305 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 661 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(push_this(helper->handle)); }
#line 3311 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 663 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[0].str)))); }
#line 3317 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 664 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(duplicate_value(helper->handle)); YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-2].str)))); }
#line 3323 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 665 "yaoosl.y" /* yacc.c:1646  */
    { DROP((yyvsp[-3].str)); YSEMIT(duplicate_value(helper->handle)); YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-2].str)))); }
#line 3329 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 666 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(duplicate_value(helper->handle)); YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-2].str)))); }
#line 3335 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 667 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(duplicate_value(helper->handle)); YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-1].str)))); (yyvsp[0].emit)(helper->handle); }
#line 3341 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 668 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(duplicate_value(helper->handle)); YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-1].str)))); (yyvsp[0].emit)(helper->handle); }
#line 3347 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 669 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(duplicate_value(helper->handle)); YSEMIT(push_this(helper->handle)); (yyvsp[0].emit)(helper->handle); }
#line 3353 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 671 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[0].i);
           if (yaoosl_yyvar_exists(helper, (yyvsp[-1].str)))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-1].str))));
               while (helper->sstack->size != helper->tmp_size)
               {
                   helper->sstack->size--;
                   YSEMIT(navigate_property_a(helper->handle,
                       helper->sstack->strings[helper->sstack->size].string));
               }
           }
           else
           {
               yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
           }
           helper->sstack->size = helper->tmp_size;
       }
#line 3376 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 689 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[0].i);
           YSEMIT(push_this(helper->handle));
           while (helper->sstack->size != helper->tmp_size)
           {
               helper->sstack->size--;
               YSEMIT(navigate_property_a(helper->handle,
                   helper->sstack->strings[helper->sstack->size].string));
           }
           helper->sstack->size = helper->tmp_size;
       }
#line 3392 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 701 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[-3].i);
           if (yaoosl_yyvar_exists(helper, (yyvsp[-4].str)))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-4].str))));
               while (helper->sstack->size != helper->tmp_size + 1)
               {
                   helper->sstack->size--;
                   YSEMIT(navigate_property_a(helper->handle,
                       helper->sstack->strings[helper->sstack->size].string));
               }
               YSEMIT(call_self_a_b8(helper->handle, helper->sstack->strings[--helper->sstack->size].string, (yyvsp[-1].i)));
           }
           else
           {
               yystring_push(helper->sstack, (yyvsp[-4].str), 0);
               yystring_reverse_stack(helper->sstack, helper->tmp_size);
               free((yyvsp[-4].str));
               (yyvsp[-4].str) = yystring_join_stack(helper->sstack, ".", 0);
               YSEMIT(call_a_b8(helper->handle, (yyvsp[-4].str), (yyvsp[-1].i)));
           }
           helper->sstack->size = helper->tmp_size;
       }
#line 3420 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 724 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[-5].i);
           
           yystring_push(helper->sstack, (yyvsp[-6].str), 0);
           yystring_reverse_stack(helper->sstack, helper->tmp_size);
           free((yyvsp[-6].str));
           (yyvsp[-6].str) = yystring_join_stack(helper->sstack, ".", 0);
           YSEMIT(call_self_a_b8(helper->handle, (yyvsp[-6].str), (yyvsp[-3].i)));
           
           helper->sstack->size = helper->tmp_size;
       }
#line 3436 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 735 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[-3].i);
           YSEMIT(push_this(helper->handle));
           while (helper->sstack->size != helper->tmp_size + 1)
           {
               helper->sstack->size--;
               YSEMIT(navigate_property_a(helper->handle,
                   helper->sstack->strings[helper->sstack->size].string));
           }
           YSEMIT(call_self_a_b8(helper->handle, helper->sstack->strings[--helper->sstack->size].string, (yyvsp[-1].i)));
           helper->sstack->size = helper->tmp_size;
       }
#line 3453 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 748 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[-2].i);
           YSEMIT(duplicate_value(helper->handle));
           if (yaoosl_yyvar_exists(helper, (yyvsp[-3].str)))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-3].str))));
               while (helper->sstack->size != helper->tmp_size + 1)
               {
                   helper->sstack->size--;
                   YSEMIT(navigate_property_a(helper->handle,
                       helper->sstack->strings[helper->sstack->size].string));
               }
               YSEMIT(set_property_a(helper->handle, helper->sstack->strings[--helper->sstack->size].string));
           }
           else
           {
               yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
           }
           helper->sstack->size = helper->tmp_size;
       }
#line 3478 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 768 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[-1].i);
           YSEMIT(duplicate_value(helper->handle));
           if (yaoosl_yyvar_exists(helper, (yyvsp[-2].str)))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-2].str))));
               while (helper->sstack->size != helper->tmp_size)
               {
                   helper->sstack->size--;
                   YSEMIT(navigate_property_a(helper->handle,
                       helper->sstack->strings[helper->sstack->size].string));
               }
               (yyvsp[0].emit)(helper->handle);
           }
           else
           {
               yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
           }
           helper->sstack->size = helper->tmp_size;
       }
#line 3503 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 788 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[-2].i);
           YSEMIT(duplicate_value(helper->handle));
           YSEMIT(push_this(helper->handle));
           while (helper->sstack->size != helper->tmp_size + 1)
           {
               helper->sstack->size--;
               YSEMIT(navigate_property_a(helper->handle,
                   helper->sstack->strings[helper->sstack->size].string));
           }
           YSEMIT(set_property_a(helper->handle, helper->sstack->strings[--helper->sstack->size].string));
           helper->sstack->size = helper->tmp_size;
       }
#line 3521 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 801 "yaoosl.y" /* yacc.c:1646  */
    {
           helper->tmp_size = helper->sstack->size - (yyvsp[-1].i);
           YSEMIT(duplicate_value(helper->handle));
           YSEMIT(push_this(helper->handle));
           while (helper->sstack->size != helper->tmp_size)
           {
               helper->sstack->size--;
               YSEMIT(navigate_property_a(helper->handle,
                   helper->sstack->strings[helper->sstack->size].string));
           }
           (yyvsp[0].emit)(helper->handle);
           helper->sstack->size = helper->tmp_size;
       }
#line 3539 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 816 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_xor); }
#line 3545 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 817 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_or); }
#line 3551 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 818 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_and); }
#line 3557 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 819 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_divide); }
#line 3563 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 820 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_multiplicate); }
#line 3569 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 821 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_subtract); }
#line 3575 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 822 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_add); }
#line 3581 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 823 "yaoosl.y" /* yacc.c:1646  */
    { (yyval.emit) = YSEMIT(a_self_subtract); }
#line 3587 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 826 "yaoosl.y" /* yacc.c:1646  */
    {
        YSEMIT(skip_if_true(helper->handle));
       
        // Allocate jump to "end-if"
        yaoosl_yyhelper_store_jump(helper);
        YSEMIT(jump_off_a32(helper->handle, 0));
        yaoosl_yyhelper_store_jump(helper);
   }
#line 3600 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 835 "yaoosl.y" /* yacc.c:1646  */
    {
            // Write "end-if"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
            
            helper->jump_offsets_size -= 3;
        }
#line 3614 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 844 "yaoosl.y" /* yacc.c:1646  */
    {
            // Allocate jump to "end-else"
            yaoosl_yyhelper_store_jump(helper);
            YSEMIT(jump_off_a32(helper->handle, 0));
            yaoosl_yyhelper_store_jump(helper);
            
            // Write "end-if"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 5];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 4]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
        }
#line 3631 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 856 "yaoosl.y" /* yacc.c:1646  */
    {
            // Write "end-else"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 4];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 3]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
            
            helper->jump_offsets_size -= 6;
        }
#line 3645 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 865 "yaoosl.y" /* yacc.c:1646  */
    {
            yaoosl_yyhelper_store_jump(helper);
         }
#line 3653 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 868 "yaoosl.y" /* yacc.c:1646  */
    {
            YSEMIT(skip_if_true(helper->handle));
            
            // Allocate jump to "end-forloop"
            yaoosl_yyhelper_store_jump(helper);
            YSEMIT(jump_off_a32(helper->handle, 0));
            yaoosl_yyhelper_store_jump(helper);
            
            // Allocate jump to "begin-codebody"
            yaoosl_yyhelper_store_jump(helper);
            YSEMIT(jump_off_a32(helper->handle, 0));
            yaoosl_yyhelper_store_jump(helper);
         }
#line 3671 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 881 "yaoosl.y" /* yacc.c:1646  */
    {
            // Jump to expression
            YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 5] - (int64_t)helper->handle->bytes_size));
            
            // Write "begin-codebody"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
         }
#line 3686 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 891 "yaoosl.y" /* yacc.c:1646  */
    {
            // Loopback to expression
            YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 2] - (int64_t)helper->handle->bytes_size));
            
            // Write "end-forloop"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 6];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 5]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
            
            
            helper->jump_offsets_size -= 7;
         }
#line 3704 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 906 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(pop_value(helper->handle)); }
#line 3710 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 907 "yaoosl.y" /* yacc.c:1646  */
    { YSEMIT(pop_value(helper->handle)); }
#line 3716 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 909 "yaoosl.y" /* yacc.c:1646  */
    { yaoosl_yyhelper_store_jump(helper); }
#line 3722 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 909 "yaoosl.y" /* yacc.c:1646  */
    {
             YSEMIT(skip_if_true(helper->handle));
             yaoosl_yyhelper_store_jump(helper);
             YSEMIT(jump_off_a32(helper->handle, 0));
             yaoosl_yyhelper_store_jump(helper);
         }
#line 3733 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 915 "yaoosl.y" /* yacc.c:1646  */
    {
             // Emit Jump-Start
             YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 3] - (int64_t)helper->handle->bytes_size));
             
             yaoosl_yyhelper_store_jump(helper);
             helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
             YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
             helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
             helper->jump_offsets_size -= 4;
         }
#line 3748 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 926 "yaoosl.y" /* yacc.c:1646  */
    {
                yaoosl_yyhelper_store_jump(helper);
             }
#line 3756 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 929 "yaoosl.y" /* yacc.c:1646  */
    {
                YSEMIT(skip_if_false(helper->handle));
                YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - (int64_t)helper->handle->bytes_size));
                helper->jump_offsets_size -= 1;
             }
#line 3766 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 935 "yaoosl.y" /* yacc.c:1646  */
    {
            // Create Block
            YSEMIT(block_push(helper->handle));
            
            // Allocate "jump-start-catchblocks"
            yaoosl_yyhelper_store_jump(helper);
            YSEMIT(jump_off_a32(helper->handle, 0));
            yaoosl_yyhelper_store_jump(helper);
            
            // Mark Try-Codeblock
            yaoosl_yyhelper_store_jump(helper);
        }
#line 3783 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 947 "yaoosl.y" /* yacc.c:1646  */
    {
            // Allocate "jump-end-catchblocks"
            yaoosl_yyhelper_store_jump(helper);
            YSEMIT(jump_off_a32(helper->handle, 0));
            yaoosl_yyhelper_store_jump(helper);
            
            // Update "jump-start-catchblocks"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 6];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 5]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
        }
#line 3800 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 959 "yaoosl.y" /* yacc.c:1646  */
    {
            // Jump to Try-Codeblock
            YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 4] - (int64_t)helper->handle->bytes_size));
            
            // Update "jump-end-catchblocks"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 4];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 3]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
            
            // Destroy block
            YSEMIT(block_pop(helper->handle));
            
            helper->jump_offsets_size -= 7;
        }
#line 3820 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 976 "yaoosl.y" /* yacc.c:1646  */
    {
                // Load type onto value stack and anounce catch
                YSEMIT(push_string(helper->handle, "Yaoosl.Exception"));
                YSEMIT(resolve_type(helper->handle));
                YSEMIT(block_catch(helper->handle));
                
                // Skip unless in exception
                YSEMIT(skip_if_in_exception(helper->handle));
                
                // Allocate "skip-codebody"
                yaoosl_yyhelper_store_jump(helper);
                YSEMIT(jump_off_a32(helper->handle, 0));
                yaoosl_yyhelper_store_jump(helper);
                
                // Pop exception from value stack
                YSEMIT(pop_value(helper->handle));
             }
#line 3842 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 993 "yaoosl.y" /* yacc.c:1646  */
    {
                // Emit "jump-to-jump-end-catchblocks" (Exception handled, leave catchblock)
                YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 5] - (int64_t)helper->handle->bytes_size));
                 
                // Update "skip-codebody"
                yaoosl_yyhelper_store_jump(helper);
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
                YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
                
                helper->jump_offsets_size -= 3;
             }
#line 3859 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1007 "yaoosl.y" /* yacc.c:1646  */
    {
                // Load type onto value stack and anounce catch
                YSEMIT(push_string(helper->handle, (yyvsp[-2].str)));
                YSEMIT(resolve_type(helper->handle));
                YSEMIT(block_catch(helper->handle));
                
                // Skip unless in exception
                YSEMIT(skip_if_in_exception(helper->handle));
                
                // Allocate "skip-codebody"
                yaoosl_yyhelper_store_jump(helper);
                YSEMIT(jump_off_a32(helper->handle, 0));
                yaoosl_yyhelper_store_jump(helper);
                
                // Load exception into variable
                YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, (yyvsp[-1].str))));
             }
#line 3881 "yaoosl.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1024 "yaoosl.y" /* yacc.c:1646  */
    {
                // Emit "jump-to-jump-end-catchblocks" (Exception handled, leave catchblock)
                YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 5] - (int64_t)helper->handle->bytes_size));
                 
                // Update "skip-codebody"
                yaoosl_yyhelper_store_jump(helper);
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
                YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
                
                helper->jump_offsets_size -= 3;
             }
#line 3898 "yaoosl.tab.c" /* yacc.c:1646  */
    break;


#line 3902 "yaoosl.tab.c" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, helper, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, helper, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner, helper);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, scanner, helper);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, helper, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner, helper);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner, helper);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1038 "yaoosl.y" /* yacc.c:1906  */


/* Start code copied to scanner output */


struct yaoosl_string_stack* yystring_create_stack()
{
    struct yaoosl_string_stack* sstack = malloc(sizeof(struct yaoosl_string_stack));
    if (sstack)
    {
        sstack->strings = 0;
        sstack->size = 0;
        sstack->capacity = 0;
    }
    return sstack;
}
void yystring_destroy_stack(struct yaoosl_string_stack* sstack)
{
    size_t i;
    for (i = 0; i < sstack->capacity && sstack->strings[i].string; i++)
    {
        free(sstack->strings[i].string);
    }
    if (sstack->strings)
    {
        free(sstack->strings);
    }
    free(sstack);
}
static bool yystring_push(struct yaoosl_string_stack* sstack, const char* begin, const char* end)
{
    void* tmp;
    size_t i;
    if (!end)
    {
        end = begin + strlen(begin);
    }
    if (sstack->capacity == sstack->size)
    {
        tmp = realloc(sstack->strings, sizeof(struct yaoosl_yystring) * (sstack->capacity + sstack->capacity + 1));
        if (!tmp)
        {
            return false;
        }
        sstack->strings = tmp;
        for (i = sstack->capacity; i < sstack->capacity + sstack->capacity + 1; i++)
        {
            sstack->strings[i].capacity = 0;
            sstack->strings[i].length = 0;
            sstack->strings[i].string = 0;
        }
        sstack->capacity = sstack->capacity + sstack->capacity + 1;
    }
    if (sstack->strings[sstack->size].string)
    {
        if (sstack->strings[sstack->size].capacity < end - begin + 1)
        {
            tmp = realloc(sstack->strings[sstack->size].string, sizeof(char) * (end - begin + 1));
            if (!tmp)
            {
                return false;
            }
            sstack->strings[sstack->size].string = tmp;
            sstack->strings[sstack->size].capacity = end - begin + 1;
        }
    }
    else
    {
        sstack->strings[sstack->size].string = malloc(sizeof(char) * (end - begin + 1));
        if (!sstack->strings[sstack->size].string)
        {
            return false;
        }
        sstack->strings[sstack->size].capacity = end - begin + 1;
    }
    sstack->strings[sstack->size].length = end - begin;
    strncpy(sstack->strings[sstack->size].string, begin, sstack->strings[sstack->size].length);
    sstack->strings[sstack->size].string[sstack->strings[sstack->size].length] = '\0';
    sstack->size++;
    return true;
}

static void yystring_reverse_stack(struct yaoosl_string_stack* sstack, size_t offset)
{
    struct yaoosl_yystring tmp;
    size_t i = offset, j = sstack->size - 1;
    for (; i < j && i != j; i++, j--)
    {
        tmp = sstack->strings[i];
        sstack->strings[i] = sstack->strings[j];
        sstack->strings[j] = tmp;
    }
}
static char* yystring_join_stack(struct yaoosl_string_stack* sstack, const char* join, size_t offset)
{
    char* str, * str2;
    size_t size = 0;
    size_t i;
    size_t join_len = strlen(join);
    if (sstack->size == offset)
    {
        return NULL;
    }
    for (i = offset; i < sstack->size; i++)
    {
        size += sstack->strings[i].length;
        size += join_len;
    }
    size -= join_len;
    str = malloc(sizeof(char) * (size + 1));
    if (str)
    {
        str2 = str;
        for (i = offset; i < sstack->size; i++)
        {
            strncpy(str2, sstack->strings[i].string, sstack->strings[i].length);
            str2 += sstack->strings[i].length;
            strncpy(str2, join, join_len);
            str2 += join_len;
        }
        str[size] = '\0';
    }
    return str;
}
static char* yystring_join_strings_3(const char* l, const char* d, const char* r)
{
    size_t lend = strlen(d);
    size_t lenl = strlen(l);
    size_t lenr = strlen(r);
    size_t len = lend + lenl + lenr;
    char* str = malloc(sizeof(char) * (len + 1));
    if (str)
    {
        str[len] = '\0';
        strncpy(str, l, lenl);
        strncpy(str + lenl, d, lend);
        strncpy(str + lenl + lend, r, lenr);
    }
    return str;
}

static short yaoosl_yyvar_index(struct yaoosl_yyhelper* helper, const char* varname)
{
    size_t i;
    struct yaoosl_yyvar* tmp;
    size_t varname_len = strlen(varname);
    for (i = 0; i < helper->vars_size; i++)
    {
        if (!str_cmp(helper->vars[i].str, helper->vars[i].str_len, varname, varname_len))
        {
            return (short)i;
        }
    }
    if (helper->vars_size == helper->vars_capacity)
    {
        tmp = realloc(helper->vars, sizeof(struct yaoosl_yyvar) * (helper->vars_capacity + helper->vars_capacity + 1));
        if (!tmp)
        {
            return false;
        }
        helper->vars = tmp;
        helper->vars_capacity = helper->vars_capacity + helper->vars_capacity + 1;
    }
    helper->vars[helper->vars_size].str = varname;
    helper->vars[helper->vars_size].str_len = varname_len;
    return (short)(helper->vars_size++);
}

static bool yaoosl_yyvar_exists(struct yaoosl_yyhelper* helper, const char* varname)
{
    size_t i;
    size_t varname_len = strlen(varname);
    for (i = 0; i < helper->vars_size; i++)
    {
        if (!str_cmp(helper->vars[i].str, helper->vars[i].str_len, varname, varname_len))
        {
            return true;
        }
    }
    return false;
}

static bool yaoosl_yyhelper_push_break(struct yaoosl_yyhelper* helper, uint64_t offset)
{
    size_t* tmp;
    if (helper->break_offsets_size == helper->break_offsets_capacity)
    {
        tmp = realloc(helper->break_offsets, sizeof(uint64_t) * (helper->break_offsets_capacity + helper->break_offsets_capacity + 1));
        if (!tmp)
        {
            return false;
        }
        helper->break_offsets = tmp;
        helper->break_offsets_capacity = helper->break_offsets_capacity + helper->break_offsets_capacity + 1;
    }
    helper->break_offsets[helper->break_offsets_size++] = offset;
    return true;
}

static bool yaoosl_yyhelper_push_continue(struct yaoosl_yyhelper* helper, uint64_t offset)
{
    size_t* tmp;
    if (helper->continue_offsets_size == helper->continue_offsets_capacity)
    {
        tmp = realloc(helper->continue_offsets, sizeof(uint64_t) * (helper->continue_offsets_capacity + helper->continue_offsets_capacity + 1));
        if (!tmp)
        {
            return false;
        }
        helper->continue_offsets = tmp;
        helper->continue_offsets_capacity = helper->continue_offsets_capacity + helper->continue_offsets_capacity + 1;
    }
    helper->continue_offsets[helper->continue_offsets_size++] = offset;
    return true;
}

static bool yaoosl_yyhelper_push_jump(struct yaoosl_yyhelper* helper, int64_t offset)
{
    size_t* tmp;
    if (helper->jump_offsets_size == helper->jump_offsets_capacity)
    {
        tmp = realloc(helper->jump_offsets, sizeof(int64_t) * (helper->jump_offsets_capacity + helper->jump_offsets_capacity + 1));
        if (!tmp)
        {
            return false;
        }
        helper->jump_offsets = tmp;
        helper->jump_offsets_capacity = helper->jump_offsets_capacity + helper->jump_offsets_capacity + 1;
    }
    helper->jump_offsets[helper->jump_offsets_size++] = offset;
    return true;
}

static bool yaoosl_yyhelper_store_jump(struct yaoosl_yyhelper* helper)
{
    return yaoosl_yyhelper_push_jump(helper, helper->handle->bytes_size);
}

static void yaoosl_yytransform_string(char* str)
{
    size_t i, j, len = strlen(str);
    for (i = 1, j = 0; i < len - 1; i++, j++)
    {
        if (str[i] == '\\')
        {
            i++;
            switch (str[i])
            {
            case 'a': str[i] = '\a'; break;
            case 'b': str[i] = '\b'; break;
            case 'f': str[i] = '\f'; break;
            case 'n': str[i] = '\n'; break;
            case 'r': str[i] = '\r'; break;
            case 't': str[i] = '\t'; break;
            case 'v': str[i] = '\v'; break;
                // case '\\': str[i] = '\\'; break;
                // case '\'': str[i] = '\''; break;
                // case '"': str[i] = '"'; break;
            case '0': str[i] = '\0'; break;
            }
        }
        str[j] = str[i];
    }
    str[j] = '\0';
}

static int yaoosl_error(yyscan_t scanner, struct yaoosl_yyhelper* helper, const char* msg)
{
    size_t start, end, i, max_len = 0;

    // Find line start
    max_len += 50;
    for (i = helper->code_index; i != ~(size_t)0 && max_len > 0; i--, max_len--)
    {
        if (helper->code[i] == '\n')
        {
            break;
        }
    }
    start = i + 1;

    // Find line end
    max_len += 50;
    for (i = helper->code_index; i != SIZE_MAX && max_len > 0; i++, max_len--)
    {
        if (helper->code[i] == '\n' || helper->code[i] == '\0')
        {
            break;
        }
    }
    end = i;

    printf("%.*s\n", (unsigned int)(end - start), helper->code + start);
    for (i = start; i < end; i++)
    {
        if (i == helper->code_index)
        {
            printf("^");
        }
        else if (helper->code[i] == '\t')
        {
            printf("\t");
        }
        else
        {
            printf(" ");
        }
    }


    printf("\n[L%lld|C%lld] %s\n", helper->code_line + 1, helper->code_column + 1, msg);
    helper->errored = true;
    return 0;
}

int yaoosl_yylex_get_next_char(struct yaoosl_yyhelper* helper, char* buffer, int max_buffer)
{
    char c = helper->code[helper->code_index];
    if (c == 0) { return 0; }
    helper->code_index++;
    buffer[0] = c;
    switch (c)
    {
        case '\n':
            helper->code_line++;
            helper->code_column = 0;
            break;
        default:
            helper->code_column++;
            break;
    }
    return c == 0 ? 0 : 1;
}


static unsigned int yaoosl_yy_is_constructor(const char* classname, const char* methodname)
{
	unsigned int i, j;
	unsigned int llen = strlen(classname);
	unsigned int rlen = strlen(methodname);
	char lc, rc;
	if (llen < rlen) { return 0; }
	for (i = llen, j = rlen; i != ~(unsigned int)0 && j != ~(unsigned int)0; i--, j--)
	{
		lc = classname[i];
		rc = methodname[j];
		if (lc != rc)
		{
			return 0;
		}
	}
	if (i != ~(unsigned int)0 && classname[i] == '.')
	{
		return 1;
	}
	return 0;
}
/* End code copied to scanner output */
