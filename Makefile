# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adippena <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/05 13:18:57 by adippena          #+#    #+#              #
#    Updated: 2016/06/19 18:13:33 by adippena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

SRC			=	src/main.c				\
				src/game_loop.c			\
				src/hooks.c				\
				src/draw.c				\
				src/env_init.c			\
				src/game_loop.c			\
				src/key_events.c		\
				src/mouse.c

CFLAGS		=	-Wall -Wextra -Werror -g3
INCLUDES	=	-I includes
LIBFT		=	-I libft/includes -L libft -lft
SDL_LINUX	=	-lSDL2
SDL_MAC		=	-framework SDL2 -framework Cocoa

all: $(NAME)

$(NAME):
	cd libft; make all
	gcc $(CFLAGS) $(INCLUDES) $(SRC) $(SDL_LINUX) $(LIBFT) -o $(NAME) -lm

clean:
	cd libft; make clean

fclean: clean
	cd libft; make fclean
	rm -f $(NAME)

re: fclean all

run:
	rm -f $(NAME)
	@$(MAKE) all
	@clear
	@./$(NAME) 42.fdf
