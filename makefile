CC=gcc -Wall -Wextra  -ansi
OBJ=main.o Token.o Stack_token.o  Text.o

all: StackChess
%.o:%.c
	$(CC) -c $< -lm 
StackChess: $(OBJ)
	$(CC) -o $@ $^ -lm
