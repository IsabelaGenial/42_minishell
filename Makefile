# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/28 16:54:03 by igenial           #+#    #+#              #
#    Updated: 2023/11/28 17:46:19 by igenial          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
MANDATORY		=   minishell.c handler_input.c 
FILES			=	$(MANDATORY:%.c=%.o)
BONUS			=
HEADER			=	minishell.h
LIB				=	./libfstonk/libft.a
CC				=	cc
CFLAGS			=	-g3 -Wall -Wextra -Werror
VALGRIND		=	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes
GDB				=	gdb --tui --args

all: libft $(NAME)

$(NAME): $(FILES)
	@$(CC) $(CFLAGS) -I. $(FILES) $(LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:
	@make fclean
	@make MANDATORY="$(BONUS)"

libft:
	make -C libfstonk

clean:
	@rm -f $(FILES)

fclean: clean
	@rm -f $(NAME)
	@make fclean -Clibfstonk

re: fclean all

valgrind: all
	$(VALGRIND) ./$(NAME)

gdb: all
	$(GDB) ./$(NAME)

.PHONY:	all clean fclean re bonus libft valgrind gdb
