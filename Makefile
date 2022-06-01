NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS_GNL = -Wall -Wextra -Werror -D BUFFER_SIZE=10
MAND_SRC = \
	mandatory/src/main.c \
	mandatory/src/check_cmd.c \
	mandatory/src/stderr.c \
	mandatory/util/str_join.c \
	mandatory/util/str_split.c \
	mandatory/util/strnstr.c
MAND_OBJ = $(MAND_SRC:%.c=%.o)
BONUS_SRC = \
	bonus/src/main_bonus.c \
	bonus/src/child_bonus.c \
	bonus/src/heredoc/heredoc_bonus.c \
	bonus/src/heredoc/get_next_line_utils_bonus.c \
	bonus/util/check_bonus.c \
	bonus/util/stderr_bonus.c \
	bonus/util/str_split_bonus.c \
	bonus/util/strnstr_bonus.c
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)
BONUS_GNL_SRC = bonus/src/heredoc/get_next_line_bonus.c
BONUS_GNL_OBJ = bonus/src/heredoc/get_next_line_bonus.o

all: $(NAME)

$(NAME): $(MAND_OBJ)
	$(CC) $(FLAGS) $(MAND_OBJ) -o $(NAME)

bonus: .bonus

.bonus: $(BONUS_OBJ) $(BONUS_GNL_OBJ)
	@touch .bonus
	$(CC) $(FLAGS) $(BONUS_OBJ) $(BONUS_GNL_OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(BONUS_GNL_OBJ): $(BONUS_GNL_SRC)
	$(CC) $(FLAGS_GNL) -c $< -o $@

re: fclean all

fclean: clean
	rm -f pipex

clean:
	rm -f .bonus
	rm -f $(MAND_OBJ) $(BONUS_OBJ) $(BONUS_GNL_OBJ)

.phony = all bonus re fclean clean