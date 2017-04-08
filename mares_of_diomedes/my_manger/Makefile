# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/16 23:07:18 by irhett            #+#    #+#              #
#    Updated: 2017/04/07 20:34:07 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	my_manger
CC			=	gcc
FLAG		=	-Wall -Werror -Wextra

DIR			=	src/
SRCFILES	=	main.c
SRCS		=	$(addprefix $(DIR), $(SRCFILES))

LIBDIR		=	libft/
LIB			=	$(LIBDIR)libft.a

.PHONY: all clean fclean re libft

all: $(NAME)

$(NAME): 
	$(CC) $(FLAG) $(SRCS) -I $(LIBDIR)includes/ $(LIB) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
