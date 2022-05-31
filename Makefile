NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS_BONUS = -Wall -Wextra -Werror -D BUFFER_SIZE=10
MAND_SRC = \
	mandatory/src/main.c \
	mandatory/util/check.c \
	mandatory/util/stderr.c \
	mandatory/util/str_join.c \
	mandatory/util/str_split.c \
	mandatory/util/strnstr.c
MAND_OBJ = $(MAND_SRC:%.c=%.o)
BONUS_SRC = \
	bonus/src/main_bonus.c \
	bonus/src/child_bonus.c \
	bonus/src/heredoc/heredoc_bonus.c \
	bonus/src/heredoc/get_next_line_bonus.c \
	bonus/src/heredoc/get_next_line_utils_bonus.c \
	bonus/util/check_bonus.c \
	bonus/util/stderr_bonus.c \
	bonus/util/str_split_bonus.c \
	bonus/util/strnstr_bonus.c
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(MAND_OBJ)
	$(CC) $(FLAGS) $(MAND_OBJ) -o $(NAME)

bonus: .bonus

.bonus: $(BONUS_OBJ)
	@touch .bonus
	$(CC) $(FLAGS) $(BONUS_OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS_BONUS) -c $< -o $@ 
# TODO: seperate flag Mand and Bonus.

re: fclean all

fclean: clean
	rm -f pipex

clean:
	rm -f .bonus
	rm -f $(MAND_OBJ) $(BONUS_OBJ)

.phony = all bonus re fclean clean