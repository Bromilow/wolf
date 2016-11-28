/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:26:38 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/28 13:29:01 by rbromilo         ###   ########.fr       */
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

	fd = open("resources/maps/wolf.map", O_RDONLY);
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

uint32_t	**load_texture(char *file)
{
	int				fd;
	size_t			y;
	size_t			x;
	unsigned char	line[TEX * TEX];
	uint32_t		**tex;

	ft_printf("Loading Texture : %s\n", file);
	if ((tex = (uint32_t **)malloc(sizeof(uint32_t *) * TEX)) == NULL)
	{
		perror("Malloc failed for loading texture");
		return (NULL);
	}
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		perror("Error opening texture file");
		return (NULL);
	}
	y = 0;
	while (y < TEX)
	{
		if ((tex[y] = (uint32_t *)malloc(sizeof(uint32_t) * TEX)) == NULL)
		{
			perror("Malloc failed for loading texture");
			return (NULL);
		}
		++y;
	}
	y = 0;
	while (y < TEX)
	{
		x = 0;
		if ((read(fd, &line, (TEX * 4))) != (TEX * 4))
		{
			perror("Texture reading error");
			close(fd);
			return (NULL);
		}
		while (x < TEX)
		{
			tex[x][y] = 0;
			tex[x][y] |= *(uint32_t *)(line + x * 4) & 0xFFFFFF;
			tex[x][y] |= (0xFF - *(line + x * 4 + 3)) << 24;
			++x;
		}
		++y;
	}
	close(fd);
	return (tex);
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
	e.img = SDL_CreateTexture(e.rend, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_X, WIN_Y);
	e.tex = (uint32_t ***)malloc(sizeof(uint32_t **) * 50);
	if ((e.tex[0] = load_texture("resources/textures/brick_wall1024.data")) == NULL)
		return (0);
	if ((e.tex[1] = load_texture("resources/textures/mossy_wall1024.data")) == NULL)
		return (0);
	if ((e.tex[2] = load_texture("resources/textures/mossy_cracked_wall1024.data")) == NULL)
		return (0);
	if ((e.tex[3] = load_texture("resources/textures/floor1024.data")) == NULL)
		return (0);
	if ((e.tex[4] = load_texture("resources/textures/roof1024.data")) == NULL)
		return (0);
	if ((e.tex[5] = load_texture("resources/textures/chizzeled1024.data")) == NULL)
		return (0);
	game_loop(&e);
	ft_putstr("Shutting down...\n");
	SDL_ShowCursor(1);
	SDL_DestroyTexture(e.img);
	SDL_DestroyRenderer(e.rend);
	SDL_DestroyWindow(e.win);
	return (0);
}
