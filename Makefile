NAME=thimble

CC=g++
FLAGS=-Wall -Wextra
DEBUG_FLAGS=-g -fsanitize=address
SRC=*.cpp src/*.cpp
INCLUDE=include/
BIN=bin
LIBS=
OBJ=
RM =rm -rf

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(LIBS) $(SRC) -o $(BIN)/$(NAME) -I$(INCLUDE)

clean:
	$(RM) $(BIN)/*

run: 
	./$(BIN)/$(NAME)

debug: clean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(LIBS) $(SRC) -o $(NAME)
