 /*******************************************************************************
 * Important links:                                                             *
 *   Error Reporting:                                                           *
 *     https://www.gnu.org/software/bison/manual/html_node/Error-Reporting.html *
 *   Action Features:                                                           *
 *     https://www.gnu.org/software/bison/manual/html_node/Action-Features.html *
 *   LAC - Lookahead Correction:                                                *
 *     https://www.gnu.org/software/bison/manual/html_node/LAC.html             *
 *******************************************************************************/

/* Start declarations and option settings */
    
    %code top {
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
    }
    %code requires {
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
    }
    
    %code {
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
    }
    
    
    %error-verbose
    %define parse.lac full
    %define api.prefix {yaoosl_}
    %start yaoosl
    %union {
      short s;
      int i;
      long l;
      long long ll;
      float f;
      double d;
      bool (*emit)(yaooslcodehandle code);
      
      char* str;
    }
    %destructor { free($$); } <str>
    
    %lex-param   { yyscan_t scanner }
    %parse-param { yyscan_t scanner }
    %parse-param { struct yaoosl_yyhelper* helper };
    
    /* Tokens */
    %token <str> YST_NAME
    %token YST_COLON
    %token YST_CLASS
    %token YST_WITH
    %token YST_OPERATOR
    %token YST_CURLYO
    %token YST_CURLYC
    %token YST_ROUNDO
    %token YST_ROUNDC
    %token YST_SQUAREO
    %token YST_SQUAREC
    %token YST_SC
    %token YST_COMMA
    %token YST_PREFIX
    %token YST_GET
    %token YST_EXTERN
    %token YST_SET
    %token YST_THIS
    %token YST_PLUSPLUS
    %token YST_PLUS
    %token YST_MINUSMINUS
    %token YST_MINUS
    %token YST_STAR
    %token YST_SLASH
    %token YST_LTLT
    %token YST_LTEQ
    %token YST_LT
    %token YST_GTGT
    %token YST_GTEQ
    %token YST_GT
    %token YST_EQEQ
    %token YST_NOTEQ
    %token YST_NOT
    %token YST_INVERT
    %token YST_MODULO
    %token YST_TYPEOF
    %token YST_VAR
    %token YST_EQ
    %token YST_EQXOR
    %token YST_EQOR
    %token YST_EQAND
    %token YST_EQSLAH
    %token YST_EQSTAR
    %token YST_EQMINUS
    %token YST_EQPLUS
    %token YST_EQMODULO
    %token YST_QUESTIONMARK
    %token YST_LOGICAL_OR
    %token YST_LOGICAL_AND
    %token YST_ARITHMETICAL_OR
    %token YST_ARITHMETICAL_AND
    %token YST_AS
    %token YST_IS
    %token YST_IS_NOT
    %token YST_TRUE
    %token YST_FALSE
    %token YST_DOT
    %token <d> YST_NUMBER
    %token <ll> YST_HEXNUMBER
    %token <ll> YST_BINARYNUMBER
    %token <str> YST_STRING
    %token <str> YST_CHAR
    %token YST_NEW
    %token YST_PRIVATE
    %token YST_PROTECTED
    %token YST_INTERNAL
    %token YST_PUBLIC
    %token YST_STATIC
    %token YST_IF
    %token YST_ELSE
    %token YST_FOR
    %token YST_WHILE
    %token YST_DO
    %token YST_TRY
    %token YST_CATCH
    %token YST_THROW
    %token YST_VOID
    %token YST_NULL
    %token YST_BREAK
    %token YST_CONTINUE
    %token YST_RETURN
    
%type <str> ident
%type <i> propertynav
%type <i> expressionlist
%type <emit> assignment

    
/* End declarations and option settings */

%%

yaoosl: %empty
      | yaoosl_prefix                { YSEMIT(block_pop(helper->handle)); }
      | yaoosl_prefix yaoosl_body    { YSEMIT(block_pop(helper->handle)); }
      | yaoosl_body
      ;
yaoosl_prefix: YST_PREFIX ident sc { YSEMIT(block_push(helper->handle)); YSEMIT(push_string(helper->handle, $2)); YSEMIT(block_prefix(helper->handle)); } yaoosl_prefix2
            ;
yaoosl_prefix2: %empty
            | YST_PREFIX ident sc yaoosl_prefix2 { YSEMIT(push_string(helper->handle, $2)); YSEMIT(block_prefix(helper->handle)); }
            ;
yaoosl_body: classes
           | classes multicode { YSEMIT(prepend_scope_allocate_a(helper->handle, (uint16_t)helper->vars_size)); }
           | multicode { YSEMIT(prepend_scope_allocate_a(helper->handle, (uint16_t)helper->vars_size)); }
           ;
sc: YST_SC | YST_SC sc;
classes: class
       | class classes
       ;
class: YST_CLASS ident { YSEMIT(prepend_class_declaration(helper->handle, $2)); helper->current_class = strdup($2); YSEMITCC(begin_a(helper->handle, $2)); } YST_CURLYO classbody YST_CURLYC { YSEMITCC(end(helper->handle)); free(helper->current_class); }
     | YST_CLASS ident { YSEMIT(prepend_class_declaration(helper->handle, $2)); helper->current_class = strdup($2); YSEMITCC(begin_a(helper->handle, $2)); } YST_COLON baseclasslist YST_CURLYO classbody YST_CURLYC { YSEMITCC(end(helper->handle)); free(helper->current_class); }
     ;
classbody: %empty
         | constructor classbody
         | method classbody
         | property classbody
         | operator classbody
         | error classbody
         ;
baseclasslist: ident { YSEMITCC(baseclass2(helper->handle, $1)); }
         | ident YST_COMMA { YSEMITCC(baseclass2(helper->handle, $1)); }
         | ident YST_COMMA baseclasslist { YSEMITCC(baseclass2(helper->handle, $1)); }
         ;
ident: YST_NAME { $$ = $1; }
     | YST_NAME YST_DOT ident { $$ = yystring_join_strings_3($1, ".", $3); }
     ;
operator: encapsulation ident YST_OPERATOR YST_PLUSPLUS                    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_INCREASE))); }       op_args methodbody      { YSEMITCM(return2(helper->handle, $2)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_PLUSPLUS                 { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_INCREASE))); }       op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation ident YST_OPERATOR YST_MINUSMINUS                  { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_DECREASE))); }       op_args methodbody      { YSEMITCM(return2(helper->handle, $2)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_MINUSMINUS               { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_DECREASE))); }       op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation ident YST_OPERATOR YST_INVERT                      { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_INVERT))); }         op_args methodbody      { YSEMITCM(return2(helper->handle, $2)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_NOT              { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_NOT))); }                      op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQXOR                    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_XOR))); }            op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQOR                     { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_OR))); }             op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQAND                    { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_AND))); }            op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQSLAH                   { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_DIVIDE))); }         op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQSTAR                   { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_MULTIPLICATE))); }   op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQMINUS                  { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_SUBTRACT))); }       op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQPLUS                   { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_ADD))); }            op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_EQMODULO                 { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_MODULO))); }         op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_LTLT                     { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_BITSHIFT_LEFT))); }  op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_VOID YST_OPERATOR YST_GTGT                     { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SELF_BITSHIFT_RIGHT))); } op_args methodbody      { YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_PLUS             { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_ADD))); }                 op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_MINUS            { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_SUBTRACT))); }            op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_STAR             { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_MULTIPLICATE))); }        op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_SLASH            { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_DIVIDE))); }              op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_LTLT             { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_BITSHIFT_LEFT))); }       op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_LTEQ             { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LESS_THEN_OR_EQUAL))); }       op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_LT               { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LESS_THEN))); }                op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_GTGT             { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_BITSHIFT_RIGHT))); }      op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_GTEQ             { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LARGER_THEN_OR_EQUAL))); }     op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_GT               { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_LARGER_THEN))); }              op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_EQEQ             { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_EQUALS))); }                   op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_NOTEQ            { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_EQUALS_NOT))); }               op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_MODULO           { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_MODULO))); }              op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_LOGICAL_AND      { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_AND))); }                      op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_ARITHMETICAL_AND { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_AND))); }                 op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_LOGICAL_OR       { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_LOGICAL_OR))); }                       op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_OPERATOR YST_ARITHMETICAL_OR  { YSEMITCM(begin(helper->handle)); YSEMITCM(name2(helper->handle, YSSTR(OP_ARITHMETICAL_OR))); }                  op_args methodbody      { YSEMITCM(return2(helper->handle, $3)); YSEMITCM(end(helper->handle)); }
        ;
op_args: YST_ROUNDO YST_ROUNDC
       | YST_ROUNDO ident YST_NAME YST_ROUNDC { YSEMITCM(arg2(helper->handle, $2, $3)); }
       | YST_ROUNDO ident YST_NAME YST_COMMA ident YST_NAME YST_ROUNDC { YSEMITCM(arg2(helper->handle, $2, $3)); YSEMITCM(arg2(helper->handle, $5, $6)); }
       ;
property: encapsulation ident YST_NAME sc { YSEMITCP(begin(helper->handle)); YSEMITCP(return2(helper->handle, $2)); YSEMITCP(name2(helper->handle, $3)); YSEMITCP(end(helper->handle)); }
        | encapsulation YST_STATIC ident YST_NAME sc { DROP($3); DROP($4); yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED); }
        | YST_EXTERN encapsulation ident YST_NAME sc { DROP($3); DROP($4); }
        | encapsulation ident YST_NAME YST_CURLYO
        {
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, $2));
            YSEMITCP(name2(helper->handle, $3));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, $2));
        }
        YST_GET methodbody
        {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, $2, "value"));
            yaoosl_yyvar_index(helper, "value");
        }
        YST_SET methodbody YST_CURLYC
        {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
        
        | encapsulation YST_STATIC ident YST_NAME YST_CURLYO
        {
            yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, $3));
            YSEMITCP(name2(helper->handle, $4));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, $3));
        }
        YST_GET methodbody
        {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, $3, "value"));
            yaoosl_yyvar_index(helper, "value");
        }
        YST_SET methodbody YST_CURLYC
        {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
        
        | encapsulation ident YST_NAME YST_CURLYO
        {
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, $2));
            YSEMITCP(name2(helper->handle, $3));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, $2, "value"));
            yaoosl_yyvar_index(helper, "value");
        }
        YST_SET methodbody
        {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, $2));
        }
        YST_GET methodbody YST_CURLYC
        {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
        | encapsulation YST_STATIC ident YST_NAME YST_CURLYO
        {
            yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
            YSEMITCP(begin(helper->handle));
            YSEMITCP(return2(helper->handle, $3));
            YSEMITCP(name2(helper->handle, $4));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "set"));
            YSEMITCM(arg2(helper->handle, $3, "value"));
            yaoosl_yyvar_index(helper, "value");
        }
        YST_SET methodbody
        {
            YSEMITCM(end(helper->handle));
            
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, "get"));
            YSEMITCM(return2(helper->handle, $3));
        }
        YST_GET methodbody YST_CURLYC
        {
            YSEMITCM(end(helper->handle));
            YSEMITCP(end(helper->handle));
        }
        ;
constructor: encapsulation YST_NAME
             {
                 if (!yaoosl_yy_is_constructor(helper->current_class, $2))
                 {
                     yyerror(scanner, helper, ERRMSG_EXPECTED_CONSTRUCTOR);
                 }
                 YSEMITCM(begin(helper->handle));
                 YSEMITCM(return2(helper->handle, helper->current_class));
                 YSEMITCM(name2(helper->handle, $2));
                 helper->is_constructor = true; helper->is_void = true;
             }
             YST_ROUNDO methodargs YST_ROUNDC methodbody
             { YSEMITCM(end(helper->handle)); helper->is_constructor = false; }
           | YST_EXTERN encapsulation YST_NAME YST_ROUNDO methodargs_nc YST_ROUNDC YST_SC { DROP($3); }
           ;
method: encapsulation ident YST_NAME
        {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(return2(helper->handle, $2));
            YSEMITCM(name2(helper->handle, $3));
            helper->is_void = false;
        }
        YST_ROUNDO methodargs YST_ROUNDC methodbody
        { YSEMITCM(end(helper->handle)); }
      | encapsulation YST_STATIC ident YST_NAME
        {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(return2(helper->handle, $3));
            YSEMITCM(name2(helper->handle, $4));
            helper->is_void = false;
        }
        YST_ROUNDO methodargs YST_ROUNDC methodbody
        { YSEMITCM(end(helper->handle)); }
      | encapsulation YST_VOID YST_NAME
        {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, $3));
            helper->is_void = true;
        }
        YST_ROUNDO methodargs YST_ROUNDC methodbody
        { YSEMITCM(end(helper->handle)); }
      | encapsulation YST_STATIC YST_VOID YST_NAME
        {
            YSEMITCM(begin(helper->handle));
            YSEMITCM(name2(helper->handle, $4));
            helper->is_void = true;
        }
        YST_ROUNDO methodargs YST_ROUNDC methodbody
        { YSEMITCM(end(helper->handle)); }
      | YST_EXTERN encapsulation YST_STATIC YST_VOID YST_NAME YST_ROUNDO methodargs_nc YST_ROUNDC YST_SC { DROP($5); }
      ;
methodargs: %empty
          | ident YST_NAME { YSEMITCM(arg2(helper->handle, $1, $2)); }
          | ident YST_NAME YST_COMMA methodargs { YSEMITCM(arg2(helper->handle, $1, $2)); }
          ;
methodargs_nc: %empty
          | ident YST_NAME                      { DROP($1); DROP($2); }
          | ident YST_NAME YST_COMMA methodargs { DROP($1); DROP($2); }
          ;
methodbody: YST_CURLYO {
                yaoosl_yyhelper_store_jump(helper);
                YSEMITCM(codeblock_a64(helper->handle, 0));
                yaoosl_yyhelper_store_jump(helper);
                
                yaoosl_yyhelper_store_jump(helper);
                YSEMIT(scope_allocate_a16(helper->handle, 0));
                yaoosl_yyhelper_store_jump(helper);
            }
            multicode YST_CURLYC
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
          | YST_CURLYO YST_CURLYC {
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
          ;
encapsulation: YST_PUBLIC
             | YST_INTERNAL
             | YST_PROTECTED
             | YST_PRIVATE
             ;
codebody: code
        | YST_CURLYO YST_CURLYC
        | YST_CURLYO multicode YST_CURLYC
        ;
multicode: code
         | code multicode
         | code error multicode
         ;
code: YST_SC
    | expression YST_SC { YSEMIT(pop_value(helper->handle)); }
    | ifthen
    | forloop
    | whileloop
    | dowhileloop
    | trycatch
    | YST_RETURN YST_SC { if (!helper->is_void) { yyerror(scanner, helper, ERRMSG_EXPECTED_VALUE); } YSEMIT(scope_pop(helper->handle)); }
    | YST_RETURN expression YST_SC { if (helper->is_void) { yyerror(scanner, helper, ERRMSG_EXPECTED_NO_VALUE); } YSEMIT(scope_pop(helper->handle)); }
    | YST_THROW expression YST_SC { YSEMIT(block_throw(helper->handle)); }
    | YST_BREAK YST_SC
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
    | YST_CONTINUE YST_SC
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
    ;

expression: exp01;
bracedexpression: YST_ROUNDO expression YST_ROUNDC;
expressionlist: %empty                              { $$ = 0; }
              | expression                          { $$ = 1; }
              | expression YST_COMMA expressionlist { $$ = 1 + $3; }
              ;
exp01: exp02
     | exp02 YST_QUESTIONMARK expression YST_COLON expression
     ;
exp02: exp03
     | exp03 YST_LOGICAL_OR expression       { YSEMIT(logical_or(helper->handle)); }
     ;
exp03: exp04
     | exp04 YST_LOGICAL_AND expression      { YSEMIT(logical_and(helper->handle)); }
     ;
exp04: exp05
     | exp05 YST_ARITHMETICAL_OR expression  { YSEMIT(a_or(helper->handle)); }
     ;
exp05: exp06
     | exp06 YST_ARITHMETICAL_AND expression { YSEMIT(a_and(helper->handle)); }
     ;
exp06: exp07
     | exp07 YST_EQEQ expression             { YSEMIT(logical_equals(helper->handle)); }
     | exp07 YST_NOTEQ expression            { YSEMIT(logical_equals_not(helper->handle)); }
     ;
exp07: exp08
     | exp08 YST_LTEQ expression             { YSEMIT(logical_less_then_or_equal(helper->handle)); }
     | exp08 YST_LT expression               { YSEMIT(logical_less_then(helper->handle)); }
     | exp08 YST_GTEQ expression             { YSEMIT(logical_greater_then_or_equal(helper->handle)); }
     | exp08 YST_GT expression               { YSEMIT(logical_greater_then(helper->handle)); }
     ;
exp08: exp09
     | exp09 YST_LTLT expression             { YSEMIT(a_bitshift_left(helper->handle)); }
     | exp09 YST_GTGT expression             { YSEMIT(a_bitshift_right(helper->handle)); }
     ;
exp09: exp10
     | exp10 YST_PLUS expression             { YSEMIT(a_add(helper->handle)); }
     | exp10 YST_MINUS expression            { YSEMIT(a_subtract(helper->handle)); }
     ;
exp10: exp11
     | exp11 YST_STAR expression             { YSEMIT(a_multiplicate(helper->handle)); }
     | exp11 YST_SLASH expression            { YSEMIT(a_divide(helper->handle)); }
     | exp11 YST_MODULO expression           { YSEMIT(a_modulo(helper->handle)); }
     ;
exp11: exp12
     | exp12 YST_PLUSPLUS                    { YSEMIT(increment(helper->handle)); }
     | exp12 YST_MINUSMINUS                  { YSEMIT(decrement(helper->handle)); }
     | exp12 YST_IS_NOT ident
     {
         YSEMIT(push_string(helper->handle, $3));
         YSEMIT(resolve_type(helper->handle));
         YSEMIT(is_type(helper->handle));
         YSEMIT(logical_not(helper->handle));
     }
     | exp12 YST_IS ident
     {
         YSEMIT(push_string(helper->handle, $3));
         YSEMIT(resolve_type(helper->handle));
         YSEMIT(is_type(helper->handle));
     }
     ;
exp12: exp13
     /*| YST_PLUSPLUS exp13                    { YSEMIT(logical_greater_then(helper->handle)); }*/
     /*| YST_MINUSMINUS exp13                  { YSEMIT(logical_greater_then(helper->handle)); }*/
     | YST_NOT exp13                         { YSEMIT(logical_not(helper->handle)); }
     | YST_INVERT exp13                      { YSEMIT(a_invert(helper->handle)); }
     ;
     
propertynav: YST_DOT YST_NAME { yystring_push(helper->sstack, $2, 0); $$ = 1; }
     | YST_DOT YST_NAME propertynav { yystring_push(helper->sstack, $2, 0); $$ = 1 + $3; }
     ;
exp13: YST_NEW ident YST_ROUNDO expressionlist YST_ROUNDC { YSEMIT(push_string(helper->handle, $2)); YSEMIT(resolve_type(helper->handle)); YSEMIT(push_new_a8(helper->handle, $4)); }
     | YST_TYPEOF YST_ROUNDO ident YST_ROUNDC             { YSEMIT(push_string(helper->handle, $3)); YSEMIT(resolve_type(helper->handle)); }
     | YST_STRING                                         { yaoosl_yytransform_string($1); YSEMIT(push_string(helper->handle, $1)); }
     | YST_CHAR                                           { yaoosl_yytransform_string($1); YSEMIT(push_char_a8(helper->handle, $1[0])); }
     | YST_NUMBER                                         { YSEMIT(push_double_a64(helper->handle, $1)); }
     | YST_HEXNUMBER                                      { YSEMIT(push_int32_a32(helper->handle, $1)); }
     | YST_BINARYNUMBER                                   { YSEMIT(push_int32_a32(helper->handle, $1)); }
     | YST_TRUE                                           { YSEMIT(push_true(helper->handle)); }
     | YST_FALSE                                          { YSEMIT(push_false(helper->handle)); }
     | YST_NULL                                           { YSEMIT(push_null(helper->handle)); }
     | YST_THIS                                           { YSEMIT(push_this(helper->handle)); }
     | bracedexpression
     | YST_NAME                                           { YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, $1))); }
     | YST_NAME YST_EQ expression                         { YSEMIT(duplicate_value(helper->handle)); YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, $1))); }
     | ident YST_NAME YST_EQ expression                   { DROP($1); YSEMIT(duplicate_value(helper->handle)); YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, $2))); }
     | YST_VAR YST_NAME YST_EQ expression                 { YSEMIT(duplicate_value(helper->handle)); YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, $2))); }
     | YST_VAR YST_NAME assignment                        { YSEMIT(duplicate_value(helper->handle)); YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, $2))); $3(helper->handle); }
     | YST_NAME assignment                                { YSEMIT(duplicate_value(helper->handle)); YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, $1))); $2(helper->handle); }
     | YST_THIS assignment                                { YSEMIT(duplicate_value(helper->handle)); YSEMIT(push_this(helper->handle)); $2(helper->handle); }
     /* Get Value */
     | YST_NAME propertynav {
           helper->tmp_size = helper->sstack->size - $2;
           if (yaoosl_yyvar_exists(helper, $1))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, $1)));
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
     | YST_THIS propertynav {
           helper->tmp_size = helper->sstack->size - $2;
           YSEMIT(push_this(helper->handle));
           while (helper->sstack->size != helper->tmp_size)
           {
               helper->sstack->size--;
               YSEMIT(navigate_property_a(helper->handle,
                   helper->sstack->strings[helper->sstack->size].string));
           }
           helper->sstack->size = helper->tmp_size;
       }
     /* Call */
     | YST_NAME propertynav YST_ROUNDO expressionlist YST_ROUNDC {
           helper->tmp_size = helper->sstack->size - $2;
           if (yaoosl_yyvar_exists(helper, $1))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, $1)));
               while (helper->sstack->size != helper->tmp_size + 1)
               {
                   helper->sstack->size--;
                   YSEMIT(navigate_property_a(helper->handle,
                       helper->sstack->strings[helper->sstack->size].string));
               }
               YSEMIT(call_self_a_b8(helper->handle, helper->sstack->strings[--helper->sstack->size].string, $4));
           }
           else
           {
               yystring_push(helper->sstack, $1, 0);
               yystring_reverse_stack(helper->sstack, helper->tmp_size);
               free($1);
               $1 = yystring_join_stack(helper->sstack, ".", 0);
               YSEMIT(call_a_b8(helper->handle, $1, $4));
           }
           helper->sstack->size = helper->tmp_size;
       }
     | YST_NAME propertynav YST_ROUNDO expressionlist YST_ROUNDC YST_WITH expression {
           helper->tmp_size = helper->sstack->size - $2;
           
           yystring_push(helper->sstack, $1, 0);
           yystring_reverse_stack(helper->sstack, helper->tmp_size);
           free($1);
           $1 = yystring_join_stack(helper->sstack, ".", 0);
           YSEMIT(call_self_a_b8(helper->handle, $1, $4));
           
           helper->sstack->size = helper->tmp_size;
       }
     | YST_THIS propertynav YST_ROUNDO expressionlist YST_ROUNDC {
           helper->tmp_size = helper->sstack->size - $2;
           YSEMIT(push_this(helper->handle));
           while (helper->sstack->size != helper->tmp_size + 1)
           {
               helper->sstack->size--;
               YSEMIT(navigate_property_a(helper->handle,
                   helper->sstack->strings[helper->sstack->size].string));
           }
           YSEMIT(call_self_a_b8(helper->handle, helper->sstack->strings[--helper->sstack->size].string, $4));
           helper->sstack->size = helper->tmp_size;
       }
     /* Set Value */
     | YST_NAME propertynav YST_EQ expression {
           helper->tmp_size = helper->sstack->size - $2;
           YSEMIT(duplicate_value(helper->handle));
           if (yaoosl_yyvar_exists(helper, $1))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, $1)));
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
     | YST_NAME propertynav assignment {
           helper->tmp_size = helper->sstack->size - $2;
           YSEMIT(duplicate_value(helper->handle));
           if (yaoosl_yyvar_exists(helper, $1))
           {
               YSEMIT(get_value_a(helper->handle, yaoosl_yyvar_index(helper, $1)));
               while (helper->sstack->size != helper->tmp_size)
               {
                   helper->sstack->size--;
                   YSEMIT(navigate_property_a(helper->handle,
                       helper->sstack->strings[helper->sstack->size].string));
               }
               $3(helper->handle);
           }
           else
           {
               yyerror(scanner, helper, ERRMSG_STATIC_VARIABLE_NOT_SUPPORTED);
           }
           helper->sstack->size = helper->tmp_size;
       }
     | YST_THIS propertynav YST_EQ expression {
           helper->tmp_size = helper->sstack->size - $2;
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
     | YST_THIS propertynav assignment {
           helper->tmp_size = helper->sstack->size - $2;
           YSEMIT(duplicate_value(helper->handle));
           YSEMIT(push_this(helper->handle));
           while (helper->sstack->size != helper->tmp_size)
           {
               helper->sstack->size--;
               YSEMIT(navigate_property_a(helper->handle,
                   helper->sstack->strings[helper->sstack->size].string));
           }
           $3(helper->handle);
           helper->sstack->size = helper->tmp_size;
       }
     /*| YST_ROUNDO ident YST_ROUNDC expression             {  }*/
     ;
assignment: YST_EQXOR expression    { $$ = YSEMIT(a_self_xor); }
          | YST_EQOR expression     { $$ = YSEMIT(a_self_or); }
          | YST_EQAND expression    { $$ = YSEMIT(a_self_and); }
          | YST_EQSLAH expression   { $$ = YSEMIT(a_self_divide); }
          | YST_EQSTAR expression   { $$ = YSEMIT(a_self_multiplicate); }
          | YST_EQMINUS expression  { $$ = YSEMIT(a_self_subtract); }
          | YST_EQPLUS expression   { $$ = YSEMIT(a_self_add); }
          | YST_EQMODULO expression { $$ = YSEMIT(a_self_subtract); }
          ;
          
ifthen_midaction_helper: %empty {
        YSEMIT(skip_if_true(helper->handle));
       
        // Allocate jump to "end-if"
        yaoosl_yyhelper_store_jump(helper);
        YSEMIT(jump_off_a32(helper->handle, 0));
        yaoosl_yyhelper_store_jump(helper);
   };
ifthen: YST_IF YST_ROUNDO expression YST_ROUNDC ifthen_midaction_helper
        codebody {
            // Write "end-if"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
            
            helper->jump_offsets_size -= 3;
        }
      | YST_IF YST_ROUNDO expression YST_ROUNDC ifthen_midaction_helper codebody YST_ELSE {
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
        codebody {
            // Write "end-else"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 4];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 3]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
            
            helper->jump_offsets_size -= 6;
        }
forloop: YST_FOR YST_ROUNDO fl_arg YST_SC {
            yaoosl_yyhelper_store_jump(helper);
         }
         expression YST_SC {
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
         fl_arg {
            // Jump to expression
            YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 5] - (int64_t)helper->handle->bytes_size));
            
            // Write "begin-codebody"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
         }
         YST_ROUNDC codebody {
            // Loopback to expression
            YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 2] - (int64_t)helper->handle->bytes_size));
            
            // Write "end-forloop"
            yaoosl_yyhelper_store_jump(helper);
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 6];
            YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 5]));
            helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
            
            
            helper->jump_offsets_size -= 7;
         }
       ;
fl_arg: %empty
       | expression                     { YSEMIT(pop_value(helper->handle)); }
       | expression YST_COMMA fl_arg    { YSEMIT(pop_value(helper->handle)); }
       ;
whileloop: YST_WHILE YST_ROUNDO { yaoosl_yyhelper_store_jump(helper); } expression {
             YSEMIT(skip_if_true(helper->handle));
             yaoosl_yyhelper_store_jump(helper);
             YSEMIT(jump_off_a32(helper->handle, 0));
             yaoosl_yyhelper_store_jump(helper);
         }
         YST_ROUNDC codebody {
             // Emit Jump-Start
             YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 3] - (int64_t)helper->handle->bytes_size));
             
             yaoosl_yyhelper_store_jump(helper);
             helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
             YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
             helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
             helper->jump_offsets_size -= 4;
         }
         ;
dowhileloop: YST_DO {
                yaoosl_yyhelper_store_jump(helper);
             }
             codebody YST_WHILE YST_ROUNDO expression YST_ROUNDC YST_SC {
                YSEMIT(skip_if_false(helper->handle));
                YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - (int64_t)helper->handle->bytes_size));
                helper->jump_offsets_size -= 1;
             }
           ;
trycatch: YST_TRY {
            // Create Block
            YSEMIT(block_push(helper->handle));
            
            // Allocate "jump-start-catchblocks"
            yaoosl_yyhelper_store_jump(helper);
            YSEMIT(jump_off_a32(helper->handle, 0));
            yaoosl_yyhelper_store_jump(helper);
            
            // Mark Try-Codeblock
            yaoosl_yyhelper_store_jump(helper);
        }
        codebody {
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
        catchblocks {
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
        ;
catchblocks: %empty
           | YST_CATCH {
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
             codebody {
                // Emit "jump-to-jump-end-catchblocks" (Exception handled, leave catchblock)
                YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 5] - (int64_t)helper->handle->bytes_size));
                 
                // Update "skip-codebody"
                yaoosl_yyhelper_store_jump(helper);
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
                YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
                
                helper->jump_offsets_size -= 3;
             }
             catchblocks
           ;
           | YST_CATCH YST_ROUNDO ident YST_NAME YST_ROUNDC {
                // Load type onto value stack and anounce catch
                YSEMIT(push_string(helper->handle, $3));
                YSEMIT(resolve_type(helper->handle));
                YSEMIT(block_catch(helper->handle));
                
                // Skip unless in exception
                YSEMIT(skip_if_in_exception(helper->handle));
                
                // Allocate "skip-codebody"
                yaoosl_yyhelper_store_jump(helper);
                YSEMIT(jump_off_a32(helper->handle, 0));
                yaoosl_yyhelper_store_jump(helper);
                
                // Load exception into variable
                YSEMIT(set_value_a(helper->handle, yaoosl_yyvar_index(helper, $4)));
             }
             codebody {
                // Emit "jump-to-jump-end-catchblocks" (Exception handled, leave catchblock)
                YSEMIT(jump_off_a(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 5] - (int64_t)helper->handle->bytes_size));
                 
                // Update "skip-codebody"
                yaoosl_yyhelper_store_jump(helper);
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 3];
                YSEMIT(jump_off_a32(helper->handle, helper->jump_offsets[helper->jump_offsets_size - 1] - helper->jump_offsets[helper->jump_offsets_size - 2]));
                helper->handle->bytes_size = helper->jump_offsets[helper->jump_offsets_size - 1];
                
                helper->jump_offsets_size -= 3;
             }
             catchblocks
           ;
%%

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