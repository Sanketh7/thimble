#include "../include/lexer.hpp"

namespace thimble {
  Lexer::Lexer(std::istream &input) : input(input) {
    buffer.line_no = -1;
  }

  Token Lexer::get_next_token() {
    char curr_char;

    // skip whitespace
    while ((curr_char = get_next_char()) && isspace(curr_char)) {}

    // '\0' means EOF
    if (!curr_char)
      return Token(T_EOF);

    // identifiers are [a-z]([a-z0-9])*
    if (isalpha(curr_char)) {
      return handle_id(curr_char);
    }

    // numbers
    if (isnumber(curr_char)) {
      return handle_number(curr_char);
    }

    // single character tokens
    switch (curr_char) {
      case '+': return Token(T_PLUS); break;
      case '-': return Token(T_MINUS); break;
      case '*': return Token(T_STAR); break;
      case '/': return Token(T_SLASH); break;
      case '=': return Token(T_EQUAL); break;
      case '(': return Token(T_LPAREN); break;
      case ')': return Token(T_RPAREN); break;
      case '[': return Token(T_LBRACKET); break;
      case ']': return Token(T_RBRACKET); break;
      case '{': return Token(T_LBRACE); break;
      case '}': return Token(T_RBRACE); break;
      case ';': return Token(T_SEMI); break;
      case ',': return Token(T_COMMA); break;
      case ':': return Token(T_COLON); break;
    }

    // couldn't match token -> error
    unexpected_token_error();
    return Token(); // never actually returned, just to suppress compiler warning
  }

  bool Lexer::read_line() {
    std::string line;
    if (std::getline(input, line)) {
      buffer.lines.push_back(line);
      return true;
    } else {
      return false;
    }
  }

  char Lexer::get_next_char() {
    if (buffer.lines.empty()) {
      // load initial line
      ++buffer.line_no;
      if (read_line()) {
        buffer.pos = 0;
        return buffer.lines.front()[buffer.pos];
      } else {
        // no more lines to read
        return '\0';
      }
    } else if (buffer.pos+1 >= (int)buffer.lines.front().size()) {
      // current line is done -> get next line
      buffer.lines.pop_front();
      ++buffer.line_no;

      if (buffer.lines.empty()) {
        // need to load another line
        if (read_line()) {
          buffer.pos = 0;
          return buffer.lines.front()[buffer.pos];
        } else {
          // couldn't load another line -> EOF
          return '\0';
        }
      } else {
        buffer.pos = 0;
        return buffer.lines.front()[buffer.pos];
      }
    } else {
      return buffer.lines.front()[++buffer.pos];
    }
  }

  Token Lexer::handle_id(char curr_char) {
    std::string name(1, curr_char);
    while (isalpha(peek()) || isnumber(peek())) {
      name += get_next_char();
    }

    // match with keywords
    if (name == "int") return Token(T_K_INT);
    else if (name == "void") return Token(T_K_VOID);
    else if (name == "fn") return Token(T_K_FN);
    else if (name == "let") return Token(T_K_LET);
    // otherwise it's a generic id
    else return Token(T_ID, name);
  }

  // TODO: support floating point numbers
  Token Lexer::handle_number(char curr_char) {
    std::string str_value(1, curr_char);
    while (isnumber(peek())) {
      str_value += get_next_char();
    }
    return Token(T_INT, std::stoi(str_value));
  }

  char Lexer::peek() {
    assert(!buffer.lines.empty());
    if (buffer.pos+1 >= (int)buffer.lines.front().size()) {
      // go to next line
      if (buffer.lines.size() == 1) {
        // need to load another line
        if (read_line()) {
          return buffer.lines[1][0];
        } else {
          return '\0';
        }
      } else {
        return buffer.lines[1][0];
      }
    } else {
      return buffer.lines.front()[buffer.pos+1];
    }
  }

  void Lexer::unexpected_token_error() {
    std::cerr << "Unexpected token at line " << buffer.line_no+1 << " pos " << buffer.pos+1 << std::endl;
    std::cerr << buffer.lines.front() << std::endl;
    std::cerr << std::string(buffer.pos, ' ') << "^" << std::endl;
    exit(EXIT_FAILURE);
  }
};