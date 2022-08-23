# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amenadue <amenadue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:19:23 by amenadue          #+#    #+#              #
#    Updated: 2022/08/23 14:54:59 by amenadue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	norminette

INCDIR	=	includes

SRCDIR	=	source

SRC		=	lexer/*.c \
			rules/*.c \
			util/*.c \
			main.c \
			exceptions.c

################################################################################

CC		=	gcc

CCFLAGS	=	-Wall -Werror -Wextra -I$(INCDIR) -g3

all: 
	@printf "Making libftx\n"
	@$(MAKE) re -s -C libftx || $(MAKE) -s error
	@printf "Building norminette\n"
	@$(CC) $(CCFLAGS) $(foreach CFILE,$(SRC),$(SRCDIR)/$(CFILE) )libftx/libftx.a -o $(NAME) || $(MAKE) -s error
	@printf "Built norminette\n"

clean:
	@printf "Cleaning objs\n"
	@$(MAKE) clean -s -C libftx
	@printf "Cleaned objs\n"

fclean: clean
	@printf "Full cleansing\n"
	@$(MAKE) fclean -s -C libftx
	-@rm -f $(NAME) || true
	@printf "Cleansed\n"

re: fclean all

error:
	printf "\e[31m\e[1m[ERROR]\e[0m Please report this issue at \e[94m\e[4mhttps://github.com/IsCoffeeTho/norminette/issues\e[0m\n"
	exit 1

.PHONY: all clean fclean re