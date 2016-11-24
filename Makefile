# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/24 09:06:32 by rbromilo          #+#    #+#              #
#    Updated: 2016/11/24 09:27:12 by rbromilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

SRC			=	src/main.c				\
				src/game_loop.c			\
				src/draw.c				\
				src/env_init.c			\
				src/key_events.c		\
				src/dda.c

CFLAGS		=	-Wall -Wextra -Werror -g3
INCLUDES	=	-I includes
LIBFT		=	-I libft/includes -L libft -lft
SDL			=	-framework SDL2 -framework Cocoa

all: $(NAME)

$(NAME):
	cd libft; make all
	gcc $(CFLAGS) $(INCLUDES) $(SRC) $(SDL) $(LIBFT) -o $(NAME) -lm

clean:
	cd libft; make clean
	rm -rf assembley

fclean: clean
	cd libft; make fclean
	rm -f $(NAME)

re: fclean all

run:
	rm -f $(NAME)
	@$(MAKE) all
	./$(NAME)

assembley:
	rm -f $(NAME)
	cd libft; make all
	gcc $(CFLAGS) $(INCLUDES) $(SRC) $(SDL_LINUX) $(LIBFT) -S -lm
	mkdir -p assembley
	mv *.s assembley
