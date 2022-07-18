# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:19:23 by amenadue          #+#    #+#              #
#    Updated: 2022/07/18 17:58:35 by amenadue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	norminette


################################################################################

CC		=	gcc

CCFLAGS	=	-Wall -Werror -Wextra

all:
	

clean:
	

fclean: clean
	-@$(CC) $(CCFLAGS) -o $(NAME)

re: fclean all

.PHONY: all clean fclean re