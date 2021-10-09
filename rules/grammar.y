%code requires {
  #include <stdio.h>
  #include <string>
  #include "ast.hpp"
  #include "datatype.hpp"
  #include "operator.hpp"
}
%{
  #include <iostream>
  class StatementList;
  StatementList* program;

  extern int yylex();
  void yyerror(FILE* fp, const char *s) { std::cout << "PARSER ERROR: " << s << std::endl; }
%}

%parse-param { FILE* fp }

%union {
  std::string *strVal;
  int intVal;

  Expression *exprVal;
  Statement *stmtVal;
  DataType datatypeVal;
  Operator opVal;
}

%token VOID INT 
%token FN LET 
%token <strVal> ID 
%token <intVal> ICONST
%token PLUS MINUS MULT DIV EQUAL 
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE 
%token SEMI COMMA COLON

%type <stmtVal> program statement statementlist vardecl varassign
%type <exprVal> expr var
%type <datatypeVal> datatype 

/* Operator precedence */
%left PLUS MINUS
%left MULT DIV

%start program

%%

program: statementlist          { program = (StatementList*)$1; }
;

statement:
  LBRACE statementlist RBRACE     { $$ = $2; }
  | varassign                     
  | vardecl
  ;

statementlist:  
  statement                       { $$ = new StatementList(); ((StatementList*)$$)->addStatement($1); }
  | statementlist statement       { $$ = $1; ((StatementList*)$1)->addStatement($2); }
  ;

vardecl: LET var COLON datatype SEMI     { $$ = new VarDecl((Var*)$2, (DataType)$4); }
  ;

varassign: var EQUAL expr SEMI           { $$ = new VarAssign((Var*)$1, (Expression*)$3); }
  ;

var: ID     { $$ = new Var(*yylval.strVal); }
  ;

datatype:
  VOID    { $$ = (DataType)DT_VOID; }
  | INT   { $$ = (DataType)DT_INT; }
  ;

expr: 
  /*mathop expr           { $$ = new UnOp((Operation)$1, (Expression*)$2); }*/
  expr PLUS expr          { $$ = new BinOp((Expression*)$1, (Operator)OP_ADD, (Expression*)$3); }
  | expr MINUS expr       { $$ = new BinOp((Expression*)$1, (Operator)OP_MINUS, (Expression*)$3); } 
  | expr MULT expr        { $$ = new BinOp((Expression*)$1, (Operator)OP_MULT, (Expression*)$3); } 
  | expr DIV expr         { $$ = new BinOp((Expression*)$1, (Operator)OP_DIV, (Expression*)$3); } 

  | PLUS expr             { $$ = new UnOp((Operator)OP_ADD, (Expression*)$2); }
  | MINUS expr            { $$ = new UnOp((Operator)OP_MINUS, (Expression*)$2); }

  | LPAREN expr RPAREN    { $$ = $2; }
  | var                   { $$ = $1; }
  | ICONST                { $$ = new Integer(yylval.intVal); }
  ;

%%