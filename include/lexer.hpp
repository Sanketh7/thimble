#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <iostream>
#include <deque>
#include <string>
#include <cassert>

#include "token.hpp"

namespace thimble {
  class Lexer {
    private:
      struct Buffer {
        std::deque<std::string> lines;
        int line_no; // which line was this (0 indexed)
        int pos; // pos/index in current line (0)
      };

      std::istream &input;
      Buffer buffer;

      bool read_line();
      char get_next_char();
      char peek();
      Token handle_id(char curr_char);
      Token handle_number(char curr_char);
      void unexpected_token_error();
    public:
      Lexer(std::istream &input);
      Token get_next_token();
  };
}; 

#endif