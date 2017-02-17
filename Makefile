# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/16 23:07:18 by irhett            #+#    #+#              #
#    Updated: 2017/02/16 23:26:46 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	hydra
CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra
SERVER		=	server
CLIENT		=	client
LIBDIR		=	libft/
LIB			=	$(LIBDIR)libft.a
INC			=	-I $(LIBDIR)includes
S_EXEC		=	serv_exec
C_EXEC		=	cli_exec

.PHONY: all clean fclean re server client

all: $(NAME)

$(NAME): 
	@make $(SERVER)
	@make $(CLIENT)

$(SERVER):
	$(CC) $(FLAGS) $(SERVER).c $(LIB) $(INC) -o $(S_EXEC)

$(CLIENT):
	$(CC) $(FLAGS) $(CLIENT).c $(LIB) $(INC) -o $(C_EXEC)

clean:
	@rm -rf $(SERVER).o
	@rm -rf $(CLIENT).o

fclean: clean
	rm -rf $(S_EXEC)
	rm -rf $(C_EXEC)

re: fclean all
