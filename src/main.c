/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 16:58:29 by adippena          #+#    #+#             */
/*   Updated: 2016/06/19 18:53:35 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

size_t		ft_get_time(void)
{
	struct timeval	t_now;

	gettimeofday(&t_now, NULL);
	return ((size_t)((t_now.tv_sec << 20) + t_now.tv_usec));
}


float		deg_to_rad(float deg)
{
	return (deg * 3.14159265359 / 180.0);
}

void		fill_map(t_env *e)
{
	int				fd;
	char			*line;
	t_split_string	split;
	size_t			row;
	size_t			col;

	fd = open("wolf.map", O_RDONLY);
	ft_gnl(fd, &line);
	if (fd < 0)
	{
		printf("File not found\n");
		exit(0);
	}
	if (!ft_strncmp(line, "MAP: ", 5))
	{
		ft_printf("Bad map file. No map size defined. ");
		ft_printf("Define map size with 'MAP: [x] [y]'\n");
		exit(0);
	}
	split = ft_nstrsplit(line, ' ');
	if (split.words != 3)
	{
		ft_printf("Bad map file. Map definition error. Exiting\n");
		exit(0);
	}
	e->rows = ft_atoi(split.strings[1]);
	e->cols = ft_atoi(split.strings[2]);
	e->world = (int **)malloc(sizeof(int *) * e->rows);
	row = 0;
	while (row < e->rows)
	{
		e->world[row] = (int *)malloc(sizeof(int) * e->cols);
		ft_gnl(fd, &line);
		split = ft_nstrsplit(line, ' ');
		col = 0;
		while (col < e->cols)
		{
			e->world[row][col] = ft_atoi(split.strings[col]);
			++col;
		}
		++row;
	}
}

int		load_texture(char *file, uint32_t tex[TEX_X][TEX_Y])
{
	int				fd;
	uint32_t		px;
	size_t			y;
	size_t			x;
	unsigned char	line[TEX_X * TEX_Y];

	if ((fd = open(file, O_RDONLY)) == 0)
		return (-1);
	y = 0;
	while (y < TEX_Y)
	{
		x = 0;
		read(fd, &line, TEX_X * 4);
		while (x < TEX_X)
		{
			px = 0;
			px |= *(uint32_t *)(line + x * 4) & 0xFFFFFF;
			px |= (0xFF - *(line + (x * 4 + 3))) << 24;
			tex[x][y] = px;
			++x;
		}
		++y;
	}
	return (1);
}


int			main(void)
{
	t_env	e;

	ft_putstr("Activated\n");
	init_env(&e);
	e.win = SDL_CreateWindow("Wolf3D",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_X, WIN_Y, SDL_WINDOW_INPUT_GRABBED);
	e.rend = SDL_CreateRenderer(e.win, -1, SDL_RENDERER_ACCELERATED);
	e.img = SDL_CreateTexture(e.rend, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_X, WIN_Y);

	load_texture("mossy.data", e.tex[0]);
	load_texture("angus.data", e.tex[4]);




	game_loop(&e);
	ft_putstr("Shutting down...\n");
	SDL_ShowCursor(1);
	SDL_DestroyTexture(e.img);
	SDL_DestroyRenderer(e.rend);
	SDL_DestroyWindow(e.win);
	return (0);
}
