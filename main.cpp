#include <iostream>
#include <fstream>
#include "include/ast.hpp"
#include "include/lexer.hpp"
using namespace thimble;

int main(int argc, char *argv[]) {
  if (argc == 2) {
    std::ifstream fin(argv[1]);
    Lexer l(fin);
    Token tok;
    do {
      tok = l.get_next_token();
    } while (tok.type != T_EOF);

    return 0;
  } else {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  return 0;
}
