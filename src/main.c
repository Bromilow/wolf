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

int		load_texture(char *file, unsigned char *tex)
{
ft_putstr("Loading texture\n");
	int				fd;
	int				rderr;
//	ssize_t			offset;
//	unsigned char	*temp;
//	uint32_t		px;
//	size_t			y;
//	size_t			x;
//	unsigned char	line[TEX_X << 2];

	if ((tex = (unsigned char *)malloc(TEX_X * TEX_Y * 4 + 1)) == NULL)
	{
		ft_putstr("Malloc failed for loading texture!\n");
		return (-1);
	}
ft_putstr("MALLOC\n");
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr("Error loading texture\n");
		return (-1);
	}
	if ((rderr = read(fd, &tex, TEX_X * TEX_Y * 4)) != TEX_X * TEX_Y * 4)
	{
		ft_printf("Texture read error: %d\n", rderr);
		perror("");
		close(fd);
		return (-1);
	}
//ft_putstr("OPEN\n");
//	temp = tex;
//printf("Loading texture: %p\n", temp);
//	while ((offset = read(fd, &temp, TEX_X * 4)) > 0)
//	{
//printf("OFFSET: %ld    ", offset);
//		temp += offset;
//printf("Loading texture: %p\n", temp);
//	}

//printf("File opened\n");
//	y = 0;
//	while (y < TEX_Y)
//	{
//		x = 0;
//		tex[y] = (uint32_t *)malloc(sizeof(uint32_t) * TEX_X);
//		read(fd, &line, TEX_X << 2);
//		while (x < TEX_X)
//		{
//			px = 0;
//			px |= *(uint32_t *)(line + (x << 2)) & 0xFFFFFF;
//			px |= (0xFF - *(line + ((x << 2) + 3))) << 24;
//printf("PX: %X : %X\n", (unsigned int)(y * TEX_Y + x), px);
//			tex[x][y] = px;
//			++x;
//		}
//		++y;
//	}
	close(fd);
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

	e.tex = (unsigned char **)malloc(sizeof(unsigned char *) * 5);
	if (load_texture("brick_wall.data", e.tex[0]) == -1)
		return (0);
	ft_putstr("Loaded brick_wall.data");
	if (load_texture("stonebrick_mossy.RGBA", e.tex[1]) == -1)
		return (0);
	if (load_texture("stonebrick_cracked.RGBA", e.tex[2]) == -1)
		return (0);
	if (load_texture("angus.data", e.tex[4]) == -1)
		return (0);




	game_loop(&e);
	ft_putstr("Shutting down...\n");
	SDL_ShowCursor(1);
	SDL_DestroyTexture(e.img);
	SDL_DestroyRenderer(e.rend);
	SDL_DestroyWindow(e.win);
	return (0);
}
