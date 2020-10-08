%option noyywrap
%{
#include <stdio.h>
#include "parse.tab.h"
%}

digit   [0-9]
letter  [a-zA-Z]

%%

[ \t\n\r]   /* skip whitespace */

"void"      { return VOID; }
"int"       { return INT; }
"fn"        { return FN; }
"let"       { return LET; }

{letter}({letter}|{digit})*     { yylval.strval = strdup(yytext); return ID; }
{digit}+                        { yylval.ival = atoi(yytext); return ICONST; }

"+"     { return PLUS; }
"-"     { return DASH; }
"*"     { return STAR; }
"/"     { return FSLASH; }
"="     { return EQUAL; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"["     { return LBRACKET; }
"]"     { return RBRACKET; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
";"     { return SEMI; }
","     { return COMMA; }
":"     { return COLON; }

%%