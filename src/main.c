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


void		calc_init_dist(t_env *e)
{
	if (e->ray.rot.x < 0)
	{
		e->step.x = -1;
		e->dist.x = e->ray.loc.x - e->map.x;
	}
	else
	{
		e->step.x = 1;
		e->dist.x = e->map.x + 1.0 - e->ray.loc.x;
	}
	if (e->ray.rot.y < 0)
	{
		e->step.y = -1;
		e->dist.y = e->ray.loc.y - e->map.y;
	}
	else
	{
		e->step.y = 1;
		e->dist.y = e->map.y + 1.0 - e->ray.loc.y;
	}
	e->dist.x *= e->delta_dist.x;
	e->dist.y *= e->delta_dist.y;
}

void		calc_ray_loc_rot(t_env *e, size_t x)
{
	e->camera.x = 2 * x / (float)(WIN_X) - 1;
	e->ray.loc.x = e->player.loc.x;
	e->ray.loc.y = e->player.loc.y;
	e->ray.rot.x = e->player.rot.x + e->plane.x * e->camera.x;
	e->ray.rot.y = e->player.rot.y + e->plane.y * e->camera.x;
}

void		dda(t_env *e)
{
	size_t		hit;

	hit = 0;
	while (!hit)
	{
		if (e->dist.x < e->dist.y)
		{
			e->dist.x += e->delta_dist.x;
			e->map.x += e->step.x;
			e->side = 0;
		}
		else
		{
			e->dist.y += e->delta_dist.y;
			e->map.y += e->step.y;
			e->side = 1;
		}
		if (e->world[e->map.y][e->map.x] > 0)
			hit = 1;
	}
	if (e->side == 0)
		e->total_dist = (e->map.x - e->ray.loc.x + (1 - e->step.x) / 2) / e->ray.rot.x;
	else
		e->total_dist = (e->map.y - e->ray.loc.y + (1 - e->step.y) / 2) / e->ray.rot.y;
}

void		calc_line(t_env *e)
{
	int		line_height;

	line_height = (int)(WIN_Y / e->total_dist);
	e->start = -line_height / 2 + WIN_Y / 2;
	if (e->start < 0)
		e->start = 0;
	e->end = line_height / 2 + WIN_Y / 2;
	if (e->end >= WIN_Y)
		e->end = WIN_Y - 1;
}

int			main(void)
{
	t_env	e;

	init_env(&e);
	e.win = SDL_CreateWindow("Wolf3D",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_X, WIN_Y, SDL_WINDOW_INPUT_GRABBED);
	e.rend = SDL_CreateRenderer(e.win, -1, SDL_RENDERER_ACCELERATED);
	e.img = SDL_CreateTexture(e.rend, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_X, WIN_Y);
	game_loop(&e);
	return (0);
}
