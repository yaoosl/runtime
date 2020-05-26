/* Start declarations and option settings */

%option prefix="yaoosl_"
%option nounistd
%option never-interactive
%option noyywrap
%option nounput
%option noinput
%option reentrant


/* Include bison file at the very top */
%top {
    #include "yaoosl_opcodes.h"
    #include "yaoosl_emit.h"
    #include "yaoosl.tab.h"
    #include <stdarg.h>
    #include <stdio.h>
    #define YY_DECL int yylex(struct yaoosl_yyhelper* yyscanner)
    #define YY_INPUT(buf,result,max_size)  {\
        result = yaoosl_yylex_get_next_char(yyget_extra(yyscanner), buf, max_size); \
        if (result <= 0) { result = YY_NULL; }\
    }
    
    
        
    static void yaoosl_emit_dbgsmbl(struct yaoosl_yyhelper* helper, const char* text, size_t text_len)
    {
        size_t len;
        if (helper->debug_symbols)
        {
            yaoosl_emit_opcode(helper->handle, OPC_DIAG_a16);
            yaoosl_emit_uint16(helper->handle,
            1 + 8 +                             // O UINT64
            1 + 8 +                             // L UINT64
            1 + 8 +                             // C UINT64
            1 + 1 + helper->code_file_len + 1 + // F "STRING"
            1 + text_len);                      // T "STRING"
            yaoosl_emit_int8(helper->handle, 'O');
            yaoosl_emit_uint64(helper->handle, helper->code_index);
            yaoosl_emit_int8(helper->handle, 'L');
            yaoosl_emit_uint64(helper->handle, helper->code_line);
            yaoosl_emit_int8(helper->handle, 'C');
            yaoosl_emit_uint64(helper->handle, helper->code_column);
            yaoosl_emit_int8(helper->handle, 'F');
            yaoosl_emit_int8(helper->handle, '"');
            for (
                len = 0;
                len < helper->code_file_len;
                len++)
            {
                yaoosl_emit_int8(helper->handle, helper->code_file[len]);
            }
            yaoosl_emit_int8(helper->handle, '"');
            yaoosl_emit_int8(helper->handle, 'T');
            for (
                len = 0;
                len < text_len;
                len++)
            {
                yaoosl_emit_int8(helper->handle, text[len]);
            }
        }
    }
    #define DBGSMB yaoosl_emit_dbgsmbl(((struct yaoosl_yyhelper*)yyget_extra(yyscanner)), yytext, strlen(yytext));
}


%s CCOMMENT

%%


"//".*                                 ;
"/*"                                   { BEGIN(CCOMMENT); }
<CCOMMENT>{
    "*/"                               { BEGIN(INITIAL); }
    "*"                                ; // eat the lone star
    \n                                 { yylineno++; }
    [^*\n]+                            ; // eat comment in chunks 
}
":"                                    { DBGSMB; return YST_COLON; }
"prefix"                               { DBGSMB; return YST_PREFIX; }
"extern"                               { DBGSMB; return YST_EXTERN; }
"with"                                 { DBGSMB; return YST_WITH; }
"class"                                { DBGSMB; return YST_CLASS; }
"operator"                             { DBGSMB; return YST_OPERATOR; }
"{"                                    { DBGSMB; return YST_CURLYO; }
"}"                                    { DBGSMB; return YST_CURLYC; }
"("                                    { DBGSMB; return YST_ROUNDO; }
")"                                    { DBGSMB; return YST_ROUNDC; }
"["                                    { DBGSMB; return YST_SQUAREO; }
"]"                                    { DBGSMB; return YST_SQUAREC; }
";"                                    { DBGSMB; return YST_SC; }
","                                    { DBGSMB; return YST_COMMA; }
"get"                                  { DBGSMB; return YST_GET; }
"set"                                  { DBGSMB; return YST_SET; }
"this"                                 { DBGSMB; return YST_THIS; }
"++"                                   { DBGSMB; return YST_PLUSPLUS; }
"+"                                    { DBGSMB; return YST_PLUS; }
"--"                                   { DBGSMB; return YST_MINUSMINUS; }
"-"                                    { DBGSMB; return YST_MINUS; }
"*"                                    { DBGSMB; return YST_STAR; }
"/"                                    { DBGSMB; return YST_SLASH; }
"<<"                                   { DBGSMB; return YST_LTLT; }
"<="                                   { DBGSMB; return YST_LTEQ; }
"<"                                    { DBGSMB; return YST_LT; }
">>"                                   { DBGSMB; return YST_GTGT; }
">="                                   { DBGSMB; return YST_GTEQ; }
">"                                    { DBGSMB; return YST_GT; }
"=="                                   { DBGSMB; return YST_EQEQ; }
"!="                                   { DBGSMB; return YST_NOTEQ; }
"!"                                    { DBGSMB; return YST_NOT; }
"~"                                    { DBGSMB; return YST_INVERT; }
"%"                                    { DBGSMB; return YST_MODULO; }
"typeof"                               { DBGSMB; return YST_TYPEOF; }
"var"                                  { DBGSMB; return YST_VAR; }
"="                                    { DBGSMB; return YST_EQ; }
"^="                                   { DBGSMB; return YST_EQXOR; }
"|="                                   { DBGSMB; return YST_EQOR; }
"&="                                   { DBGSMB; return YST_EQAND; }
"/="                                   { DBGSMB; return YST_EQSLAH; }
"*="                                   { DBGSMB; return YST_EQSTAR; }
"-="                                   { DBGSMB; return YST_EQMINUS; }
"+="                                   { DBGSMB; return YST_EQPLUS; }
"%="                                   { DBGSMB; return YST_EQMODULO; }
"?"                                    { DBGSMB; return YST_QUESTIONMARK; }
"||"                                   { DBGSMB; return YST_LOGICAL_OR; }
"&&"                                   { DBGSMB; return YST_LOGICAL_AND; }
"|"                                    { DBGSMB; return YST_ARITHMETICAL_OR; }
"&"                                    { DBGSMB; return YST_ARITHMETICAL_AND; }
"as"                                   { DBGSMB; return YST_AS; }
"is"                                   { DBGSMB; return YST_IS; }
"isnot"                                { DBGSMB; return YST_IS_NOT; }
"true"                                 { DBGSMB; return YST_TRUE; }
"false"                                { DBGSMB; return YST_FALSE; }
"."                                    { DBGSMB; return YST_DOT; }
[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)? { DBGSMB; yaoosl_lval.d = strtol(yytext, NULL, 10); return YST_NUMBER; }
0[xX][a-zA-Z0-9]+                      { DBGSMB; yaoosl_lval.ll = strtol(yytext + 2, NULL, 16); return YST_HEXNUMBER; }
0[bB][01_]+                            { DBGSMB; yaoosl_lval.ll = strtol(yytext + 2, NULL, 2); return YST_BINARYNUMBER; }
\"(([^\"]|\\\")*[^\\])?\"              { DBGSMB; yaoosl_lval.str = strdup(yytext); return YST_STRING; }
\'(([^']|\\\')*[^\\])?\'               { DBGSMB; yaoosl_lval.str = strdup(yytext); return YST_CHAR; }
"new"                                  { DBGSMB; return YST_NEW; }
"private"                              { DBGSMB; return YST_PRIVATE; }
"protected"                            { DBGSMB; return YST_PROTECTED; }
"internal"                             { DBGSMB; return YST_INTERNAL; }
"public"                               { DBGSMB; return YST_PUBLIC; }
"static"                               { DBGSMB; return YST_STATIC; }
"if"                                   { DBGSMB; return YST_IF; }
"else"                                 { DBGSMB; return YST_ELSE; }
"for"                                  { DBGSMB; return YST_FOR; }
"while"                                { DBGSMB; return YST_WHILE; }
"do"                                   { DBGSMB; return YST_DO; }
"try"                                  { DBGSMB; return YST_TRY; }
"catch"                                { DBGSMB; return YST_CATCH; }
"throw"                                { DBGSMB; return YST_THROW; }
"void"                                 { DBGSMB; return YST_VOID; }
"null"                                 { DBGSMB; return YST_NULL; }
"break"                                { DBGSMB; return YST_BREAK; }
"continue"                             { DBGSMB; return YST_CONTINUE; }
"return"                               { DBGSMB; return YST_RETURN; }
[ \t\r\n]                              ;

[a-zA-Z_][a-zA-Z0-9_]*                 { DBGSMB; yaoosl_lval.str = strdup(yytext); return YST_NAME; }

%%

/* Start code copied to scanner output */

void yaoosl_yyscan_string(const char* str, yyscan_t yyscanner)
{
    yy_scan_string(str, yyscanner);
}

/* End code copied to scanner output */