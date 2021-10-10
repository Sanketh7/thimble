#include <iostream>
#include <fstream>
#include "include/ast.hpp"
#include "include/lexer.hpp"
using namespace thimble;

int main() {
  std::ifstream fin("test.txt", std::ifstream::in);
  Lexer l(fin);
  Token tok;
  do {
    tok = l.get_next_token();
  } while (tok.type != T_EOF);
  return 0;
}
