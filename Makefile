NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS_GNL = -Wall -Wextra -Werror -D BUFFER_SIZE=10
M = mandatory
B = bonus
S = src
U = util
MAND_SRC = \
	$(M)/$(S)/main.c \
	$(M)/$(S)/check_cmd.c \
	$(M)/$(S)/status.c \
	$(M)/$(S)/stderr.c \
	$(M)/$(U)/str_join.c \
	$(M)/$(U)/str_split.c \
	$(M)/$(U)/str_search.c
MAND_OBJ = $(MAND_SRC:%.c=%.o)
BONUS_SRC = \
	$(B)/$(S)/main_bonus.c \
	$(B)/$(S)/check_cmd_bonus.c \
	$(B)/$(S)/child_bonus.c \
	$(B)/$(S)/heredoc/heredoc_bonus.c \
	$(B)/$(S)/heredoc/get_next_line_utils_bonus.c \
	$(B)/$(S)/status_bonus.c \
	$(B)/$(S)/stderr_bonus.c \
	$(B)/$(U)/str_split_bonus.c \
	$(B)/$(U)/str_search_bonus.c
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)
BONUS_GNL_SRC = $(B)/$(S)/heredoc/get_next_line_bonus.c
BONUS_GNL_OBJ = $(B)/$(S)/heredoc/get_next_line_bonus.o

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

re_bonus: fclean bonus

fclean: clean
	rm -f pipex

clean:
	rm -f .bonus
	rm -f $(MAND_OBJ) $(BONUS_OBJ) $(BONUS_GNL_OBJ)

.phony = all bonus re re_bonus fclean clean