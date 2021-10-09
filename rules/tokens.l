%option noyywrap
%option nounput
%option noinput
%{
#include <string>
#include "parser.hpp"
%}

digit   [0-9]
letter  [a-zA-Z]

%%

[ \t\n\r]   /* skip whitespace */

"void"      { return VOID; }
"int"       { return INT; }
"fn"        { return FN; }
"let"       { return LET; }

{letter}({letter}|{digit})*     { yylval.strVal = new std::string(yytext); return ID; }
{digit}+                        { yylval.intVal = atoi(yytext); return ICONST; }

"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULT; }
"/"     { return DIV; }
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