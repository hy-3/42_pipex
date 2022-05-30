NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
MAND_SRC = \
	mandatory/src/main.c \
	mandatory/util/check.c \
	mandatory/util/stderr.c \
	mandatory/util/str_join.c \
	mandatory/util/str_split.c 
MAND_OBJ = $(MAND_SRC:%.c=%.o)
BONUS_SRC = \
	bonus/src/main_bonus.c \
	bonus/util/check_bonus.c \
	bonus/util/stderr_bonus.c \
	bonus/util/str_join_bonus.c \
	bonus/util/str_split_bonus.c 
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(MAND_OBJ)
	$(CC) $(FLAGS) $(MAND_OBJ) -o $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(FLAGS) $(BONUS_OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

re: fclean all

fclean: clean
	rm -f pipex

clean:
	rm -f $(MAND_OBJ) $(BONUS_OBJ)

.phony = all bonus re fclean clean