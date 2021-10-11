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
      return Token(T_EOF, buffer.line_no, buffer.pos);

    // identifiers are [a-z]([a-z0-9])*
    if (isalpha(curr_char)) {
      return handle_id(curr_char);
    }

    // numbers
    if (isnumber(curr_char)) {
      return handle_number(curr_char);
    }

    // single character tokens
    TokenType type = (TokenType)0;
    switch (curr_char) {
      case '+': type = T_PLUS; break;
      case '-': type = T_MINUS; break;
      case '*': type = T_STAR; break;
      case '/': type = T_SLASH; break;
      case '=': type = T_EQUAL; break;
      case '(': type = T_LPAREN; break;
      case ')': type = T_RPAREN; break;
      case '[': type = T_LBRACKET; break;
      case ']': type = T_RBRACKET; break;
      case '{': type = T_LBRACE; break;
      case '}': type = T_RBRACE; break;
      case ';': type = T_SEMI; break;
      case ',': type = T_COMMA; break;
      case ':': type = T_COLON; break;
    }
    if (type) {
      return Token(type, buffer.line_no, buffer.pos);
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
    // calculate 0-indexed line and col number for the start of the token
    int line = buffer.line_no;
    int col = buffer.pos - (int(name.size()) - 1);
    if (name == "int") return Token(T_K_INT, line, col);
    else if (name == "void") return Token(T_K_VOID, line, col);
    else if (name == "fn") return Token(T_K_FN, line, col);
    else if (name == "let") return Token(T_K_LET, line, col);
    // otherwise it's a generic id
    else return Token(T_ID, name, line, col);
  }

  // TODO: support floating point numbers
  Token Lexer::handle_number(char curr_char) {
    std::string str_value(1, curr_char);
    while (isnumber(peek())) {
      str_value += get_next_char();
    }
    int line = buffer.line_no;
    int col = buffer.pos - (int(str_value.size()) - 1);
    return Token(T_INT, std::stoi(str_value), line, col);
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