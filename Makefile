NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS_GNL = -Wall -Wextra -Werror -D BUFFER_SIZE=10
SRC = \
	src/main.c \
	src/check_cmd.c \
	src/child.c \
	src/heredoc/heredoc.c \
	src/heredoc/util/get_next_line_utils.c \
	src/status.c \
	src/stderr.c \
	util/str_split.c \
	util/str_search.c
OBJ = $(SRC:%.c=%.o)
GNL_SRC = src/heredoc/util/get_next_line.c
GNL_OBJ = src/heredoc/util/get_next_line.o

all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJ)
	$(CC) $(FLAGS) $(OBJ) $(GNL_OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(GNL_OBJ): $(GNL_SRC)
	$(CC) $(FLAGS_GNL) -c $< -o $@

re: fclean all

fclean: clean
	rm -f pipex

clean:
	rm -f $(OBJ) $(GNL_OBJ)

.phony = all re fclean clean