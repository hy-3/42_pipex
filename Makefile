NAME = pipex
CC = gcc
#FLAGS = -Wall -Wextra -Werror
SRC = src/main.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

re: fclean all

fclean: clean

clean:

.phony = all re fclean clean