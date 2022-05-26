NAME = pipex
CC = gcc
#FLAGS = -Wall -Wextra -Werror
SRC = \
	src/main.c \
	util/check.c \
	util/stderr.c \
	util/str_join.c \
	util/str_split.c 
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

re: fclean all

fclean: clean
	rm -f pipex

clean:
	rm -f $(OBJ)

.phony = all re fclean clean