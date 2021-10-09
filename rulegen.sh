bison --defines=include/parser.hpp --output=src/parser.cpp rules/grammar.y
flex --outfile=src/lexer.cpp rules/tokens.l