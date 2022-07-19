# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:19:23 by amenadue          #+#    #+#              #
#    Updated: 2022/07/20 01:05:22 by amenadue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	norminette

INCDIR	=	includes

SRCDIR	=	source

SRC		=	lexer/*.c \
			rules/*.c \
			util/*.c \
			main.c

################################################################################

CC		=	gcc

CCFLAGS	=	-Wall -Werror -Wextra -I$(INCDIR)

all: 
	-@printf "Making libft\n"
	-@$(MAKE) re -s -C libft
	-@printf "Making norminette\n"
	-@$(CC) $(CCFLAGS) $(foreach CFILE,$(SRC),$(SRCDIR)/$(CFILE) )libft.a -o $(NAME)
	-@printf "Installing norminette\n"

clean:
	-@$(MAKE) clean -s -C libft

fclean: clean
	-@$(MAKE) fclean -s -C libft
	-@rm $(NAME)

.PHONY: all clean fclean re