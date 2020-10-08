%code top {
    #include <stdlib.h>
    #include <string.h>

    #define YYDEBUG 1
}

%code requires {
    #include "ast.h"
}

%union {
    char* strval;
    int ival;

    Node* node_val;
    DataType datatype_val;
}

%code {
    Node* tree;
}

%token VOID INT 
%token FN LET 
%token <strval> ID 
%token <ival> ICONST
%token PLUS DASH STAR FSLASH EQUAL 
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE 
%token SEMI COMMA COLON

%start program

%type <node_val> program statement statementlist vardecl varassign
%type <node_val> expr term factor var
%type <datatype_val> datatype 

%%

program: statementlist          { tree = $1; }
    ;

statement:
    LBRACE statementlist RBRACE     { $$ = $2; }
    | varassign                     
    | vardecl
    ;

statementlist:  
    statement                       { $$ = make_statementlist(); statementlist_addchild($$, $1); }
    | statementlist statement       { $$ = $1; statementlist_addchild($1, $2); }
    ;

vardecl: LET var COLON datatype SEMI     { $$ = make_vardecl($2, $4); }
    ;

varassign: var EQUAL expr SEMI           { $$ = make_varassign($1, $3); }
    ;

var: ID     { $$ = make_var(yylval.strval); }
    ;

datatype:
    VOID    { $$ = DT_VOID; }
    | INT   { $$ = DT_INT; }
    ;

expr: 
    expr PLUS term      { $$ = make_binop($1, $3, O_ADD); }
    | expr DASH term    { $$ = make_binop($1, $3, O_SUB); }
    | term              
    ;

term:
    term STAR factor        { $$ = make_binop($1, $3, O_MULT); }
    | term FSLASH factor    { $$ = make_binop($1, $3, O_DIV); }
    | factor
    ;

factor:
    PLUS factor             { $$ = make_unop($2, O_ADD); }
    | DASH factor           { $$ = make_unop($2, O_SUB); }
    | ICONST                { $$ = make_intconst(yylval.ival); }
    | LPAREN expr RPAREN    { $$ = $2; }
    | ID                    { $$ = make_var(yylval.strval); }
    ;

%%

void yyerror(char* s) {
    fprintf(stderr, "Syntax error: %s\n", s);
    exit(1);
}

/*
int main(int argc, char* argv[]) {
    extern FILE *yyin;
    yyin = fopen("sample.txt", "r");
    yydebug = 1;
    yyparse();
    printf("Done.\n");
}
*/
