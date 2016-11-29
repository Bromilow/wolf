/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:16:54 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/29 11:19:57 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		redraw(t_env *e)
{
	move_player(e);
	draw_frame(e);
}

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

static void	get_value(t_env *e, t_split_string split, char *line, int fd)
{
	size_t			row;
	size_t			col;

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

void		fill_map(t_env *e)
{
	int				fd;
	char			*line;
	t_split_string	split;

	fd = open("resources/maps/wolf.map", O_RDONLY);
	ft_gnl(fd, &line);
	if ((fd < 0) || (!ft_strncmp(line, "MAP: ", 5)))
	{
		printf("error\n");
		exit(0);
	}
	split = ft_nstrsplit(line, ' ');
	if (split.words != 3)
	{
		ft_printf("Bad map file. Map definition error. Exiting\n");
		exit(0);
	}
	get_value(e, split, line, fd);
}
