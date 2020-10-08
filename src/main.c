#include "parse.tab.h"
#include "ast.h"
#include "draw.h"

#include <stdlib.h>
#include <stdio.h>

extern int yydebug;
extern Node* tree;

int main(int argc, char* argv[]) {
    extern FILE *yyin;
    yyin = fopen("sample.txt", "r");
    yydebug = 1;
    yyparse();

    emit_dot(tree);

    printf("Done.\n");
}