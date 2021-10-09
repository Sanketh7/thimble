#include <iostream>
#include "include/ast.hpp"

extern StatementList* program;
extern int yyparse(FILE* fp);

int main() {
  FILE* fp = fopen("../test.txt", "a");
  yyparse(fp);
  std::cout << program->statements.size() << std::endl;
  return 0;
}
