# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/16 23:07:18 by irhett            #+#    #+#              #
#    Updated: 2017/02/17 15:16:25 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	hydra
CC			=	gcc
FLAG		=	-Wall -Werror -Wextra
DIR			=	source/
SRCFILES	=	bind_local_socket.c open_inet_socket.c
SRCS		=	$(addprefix $(DIR), $(SRCFILES))
SRV			=	server
CLI			=	client
LIBDIR		=	libft/
LIB			=	$(LIBDIR)libft.a
INC			=	-I $(LIBDIR)includes -I inc
S_EXEC		=	srv_exec
C_EXEC		=	cli_exec

.PHONY: all clean fclean re server client

all: $(NAME)

$(NAME): 
	@make $(SRV)
	@make $(CLI)

$(SRV):
	$(CC) $(FLAG) $(DIR)$(SRV).c $(SRCS) $(LIB) $(INC) -o $(S_EXEC)

$(CLI):
	$(CC) $(FLAG) $(DIR)$(CLI).c $(SRCS) $(LIB) $(INC) -o $(C_EXEC)

clean:
	@rm -rf $(SRV).o
	@rm -rf $(CLI).o

fclean: clean
	rm -rf $(S_EXEC)
	rm -rf $(C_EXEC)

re: fclean all
