#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include "../include/lexer.hpp"
#include "../include/token.hpp"

namespace thimble {
  TEST(LexerTest, Program1) {
    std::ifstream fin("tests/program1.txt");

    std::vector<Token> ans = {
      Token(T_K_LET, 0, 0),
      Token(T_ID, "a", 0, 4),
      Token(T_COLON, 0, 5),
      Token(T_K_INT, 0, 7),
      Token(T_SEMI, 0, 10),
      Token(T_ID, "a", 1, 0),
      Token(T_EQUAL, 1, 2),
      Token(T_INT, 5, 1, 4),
      Token(T_SEMI, 1, 5)
    };

    Lexer lexer(fin);
    Token tok = lexer.get_next_token();
    int i = 0;
    while (tok.type != T_EOF && i < int(ans.size())) {
      EXPECT_EQ(tok.type, ans[i].type) << "For token number (1-indexed): " << i+1;
      EXPECT_EQ(tok.loc.line, ans[i].loc.line) << "For token number (1-indexed): " << i+1;
      EXPECT_EQ(tok.loc.col, ans[i].loc.col) << "For token number (1-indexed): " << i+1;
      tok = lexer.get_next_token();
      ++i;
    } 
    EXPECT_EQ(tok.type, T_EOF);
  }
}
