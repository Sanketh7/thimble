#pragma once

#include <string>

namespace thimble {
  enum TokenType {
    T_EOF,

    // value types
    T_ID,
    T_INT,

    // keywords
    T_K_VOID,
    T_K_INT,
    T_K_FN,
    T_K_LET,

    // operators
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_EQUAL,

    // grouping
    T_LPAREN,
    T_RPAREN,
    T_LBRACKET,
    T_RBRACKET,
    T_LBRACE,
    T_RBRACE,

    // punctuation
    T_SEMI,
    T_COMMA,
    T_COLON
  };

  struct Token {
    TokenType type;
    int int_val;
    std::string str_val;
    
    Token() {}
    Token(TokenType type) : type(type) {}
    Token(TokenType type, int val) : type(type), int_val(val) {}
    Token(TokenType type, std::string& val) : type(type), str_val(val) {}
    Token(TokenType type, const char *val) : type(type), str_val(val) {}

    friend bool operator==(const Token& a, const Token& b) {
      if (a.type == T_INT) return a.type == b.type && a.int_val == b.int_val;
      if (a.type == T_ID) return a.type == b.type && a.str_val == b.str_val;
      return a.type == b.type;
    }
  };
};