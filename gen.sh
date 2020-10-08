rm ./src/lex.yy.c ./src/parse.tab.c
rm ./include/parse.tab.h

flex -o ./src/lex.yy.c lex.l
bison --defines=./include/parse.tab.h -o ./src/parse.tab.c parse.y