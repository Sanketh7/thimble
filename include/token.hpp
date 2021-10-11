#pragma once

#include <string>

namespace thimble {
  enum TokenType {
    T_EOF = 0,

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
    
    struct {
      int line, col;
    } loc;
    
    Token() {}
    Token(TokenType type, int line, int col) : type(type), loc({line, col}) {}
    Token(TokenType type, int val, int line, int col) : type(type), int_val(val), loc({line, col}) {}
    Token(TokenType type, std::string& val, int line, int col) : type(type), str_val(val), loc({line, col}) {}
    Token(TokenType type, const char *val, int line, int col) : type(type), str_val(val), loc({line, col}) {}
  };
};