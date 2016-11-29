/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:26:38 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/29 11:17:19 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static uint32_t	**malloc_texture(void)
{
	uint32_t	**tex;
	size_t		y;

	if ((tex = (uint32_t **)malloc(sizeof(uint32_t *) * TEX)) == NULL)
	{
		perror("Malloc failed for loading texture");
		return (0);
	}
	y = 0;
	while (y < TEX)
		if ((tex[y++] = (uint32_t *)malloc(sizeof(uint32_t) * TEX)) == NULL)
		{
			perror("Malloc failed for loading texture");
			return (0);
		}
	return (tex);
}

static int		open_texture(char *file)
{
	int		fd;

	file = ft_strjoin("resources/textures/", file);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		perror("Error opening texture file");
		return (0);
	}
	return (fd);
}

uint32_t		**lt(char *file)
{
	int				fd;
	t_v2dint		v;
	unsigned char	line[TEX * TEX];
	uint32_t		**tex;

	tex = malloc_texture();
	if ((fd = open_texture(file)) == 0)
		return (NULL);
	v.y = -1;
	while (++v.y < TEX)
	{
		v.x = -1;
		read(fd, &line, (TEX * 4));
		while (++v.x < TEX)
		{
			tex[v.x][v.y] = 0;
			tex[v.x][v.y] |= *(uint32_t *)(line + v.x * 4) & 0xFFFFFF;
			tex[v.x][v.y] |= (0xFF - *(line + v.x * 4 + 3)) << 24;
		}
	}
	close(fd);
	return (tex);
}

int				main(void)
{
	t_env	e;

	init_env(&e);
	e.win = SDL_CreateWindow("Wolf3D",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_X, WIN_Y, SDL_WINDOW_INPUT_GRABBED);
	e.rend = SDL_CreateRenderer(e.win, -1, SDL_RENDERER_ACCELERATED);
	e.img = SDL_CreateTexture(e.rend, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_X, WIN_Y);
	e.tex = (uint32_t ***)malloc(sizeof(uint32_t **) * 50);
	if ((e.tex[0] = lt("brick_wall1024.data")) == NULL)
		return (0);
	if ((e.tex[3] = lt("floor1024.data")) == NULL)
		return (0);
	if ((e.tex[4] = lt("roof1024.data")) == NULL)
		return (0);
	game_loop(&e);
	ft_putstr("Shutting down...\n");
	SDL_ShowCursor(1);
	SDL_DestroyTexture(e.img);
	SDL_DestroyRenderer(e.rend);
	SDL_DestroyWindow(e.win);
	return (0);
}
