# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 13:24:17 by irhett            #+#    #+#              #
#    Updated: 2017/04/12 23:15:39 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	heroes

SRC		=	src
HERO	=	mindrazor.s wallrazor.s wallblocker.s mindblocker.s \
			Master_Shredder.s brutadon.s \
			turtle.s \
			_.s \
			bee_gees.s \
			zork.s bigzork.s \
			knut.s \
			fluttershy.s \
			helltrain.s 
HEROS	=	$(addprefix $(SRC)/, $(HERO))

COR		=	cor
COMP	=	$(HERO:.s=.cor)
CORES	=	$(addprefix $(COR)/, $(COMP))

ASM		=	./assembler

.PHONY: assembler corewar championships cor src

all: $(NAME)

$(NAME): $(HEROS) | $(CORES)
	mv $(SRC)/*.cor $(COR)

$(COR)/%.cor: $(SRC)/%.s | $(COR)
	$(ASM) $^

$(COR):
	@mkdir -p $(COR)

clean:
	rm -rf $(COR)

fclean: clean

re: fclean all
