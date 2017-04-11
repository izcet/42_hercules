# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 13:24:17 by irhett            #+#    #+#              #
#    Updated: 2017/04/11 13:34:42 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	mindrazor

SRC		=	src
COR		=	cor

ASM		=	assembler

.PHONY: assembler corewar championships cor src

all: $(NAME)

$(NAME):
	./$(ASM) $(SRC)/$(NAME).s
	mv $(SRC)/$(NAME).cor $(COR)

clean:
	rm -rf $(COR)/$(NAME).cor

fclean: clean

re: fclean all
