# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/05 16:18:21 by irhett            #+#    #+#              #
#    Updated: 2017/05/07 20:23:53 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cerberus

CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra -g

SRC_DIR		=	src
SRC_FILES	=	#source files
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

CLI			= 	client
CLI_SRC		=	$(addprefix $(SRC_DIR)/, $(CLI_SRC))

SRV			=	server
SRV_SRC		=	$(addprefix $(SRC_DIR)/, $(SRV_SRC))

OBJ_DIR		=	obj
OBJ_FILE	=	$(SRC_FILES:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR)/, $(OBJ_FILE))

LIBFT_DIR	=	libft
LIBFT_INC	=	$(LIBFT_DIR)/includes
LIBFT		=	$(LIBFT_DIR)/libft.a

LIB			=	$(LIBFT)

INC_DIR		=	-I $(LIBFT_INC) -I inc

.PHONY: all clean fclean re

all: $(LIB) $(NAME)

$(NAME): $(OBJS)
	$(SRV)
	$(CLI)

$(SRV): $(OBJS)
	$(CC) $(FLAGS) $(SRV_SRC).c $(LIB) $(OBJS) $(INC_DIR) -o $(SRV)

$(CLI): $(OBJS)
	$(CC) $(FLAGS) $(CLI_SRC).c $(LIB) $(OBJS) $(INC_DIR) -o $(CLI)


$(OBJ_DIR)/%.o: $(SRV_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $^ $(FLAGS) $(INC_DIR) -o $@

clean:
	@cd $(LIBFT_DIR) && make clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(SRV)
	rm -f $(CLI)
	@cd $(LIBFT_DIR) && make fclean

re: fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
