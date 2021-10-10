#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include "../include/lexer.hpp"
#include "../include/token.hpp"
#include <filesystem>

namespace thimble {
  TEST(LexerTest, Program1) {
    std::ifstream fin("tests/program1.txt");

    std::vector<Token> ans = {
      Token(T_K_LET),
      Token(T_ID, "a"),
      Token(T_COLON),
      Token(T_K_INT),
      Token(T_SEMI),
      Token(T_ID, "a"),
      Token(T_EQUAL),
      Token(T_INT, 5),
      Token(T_SEMI)
    };

    Lexer lexer(fin);
    Token tok;
    int i = 0;
    do {
      tok = lexer.get_next_token();
      EXPECT_EQ(tok.type, ans[i].type) << "At token index: " << i;
      ++i;
    } while (tok.type != T_EOF);
    EXPECT_EQ(tok.type, T_EOF);
  }
}
