NAME = minishell

CC = cc
FLAGS = -Wall -Werror -Wextra -g3

SRC	=	main.c  init.c
SRC +=	$(addprefix ./builtin, builtin.c builtin/export.c builtin/exit.c builtin/echo.c builtin/cd.c)
SRC +=	$(addprefix ./src,	cmd_list/cmd_list.c	cmd_list/cmd_list_utils.c cmd_list/hashtable.c)
SRC +=	$(addprefix ./src, error/error.c)
SRC +=	$(addprefix ./src , executor/expand_var.c executor/execute.c)
SRC +=	$(addprefix ./src, heredoc/heredoc.c)
SRC	+=	$(addprefix ./src, lexer/set_env.c, lexer/tokenizer.c lexer/token_utils.c lexer/lexer.c)
SRC	+=	$(addprefix ./parser, parser.c)
SRC	+=	$(addprefix ./signal, signals.c)


OBJ_DIR = obj
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(SRC:.c=.o))

LIBFT = libft/libft.a

LIBS = -lreadline -Llibft -lft

all: directory $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBS) -o $(NAME)

directory: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -I./includes/ -g3 -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

valgrind: all
	valgrind --leak-check=full --track-origins=yes --suppressions=supp.supp \
	--trace-children-skip='*/bin/*,*/sbin/*' --show-leak-kinds=all -q ./$(NAME)

gdb: all
	gdb --tui ./$(NAME)

run: all
	./$(NAME)

.PHONY: all clean fclean re directory valgrind run
