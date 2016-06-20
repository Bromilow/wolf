/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:04:00 by adippena          #+#    #+#             */
/*   Updated: 2016/06/19 18:08:52 by adippena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		redraw(t_env *e)
{
		move_player(e);
		draw_frame(e);
}

/* void	draw_vscan_line(t_env *e, size_t x)
{
	int		colour;
	int		i;
	size_t	px;

	if (e->world[e->map.y][e->map.x] == 1)
		colour = 0x00FF0000;
	else if (e->world[e->map.y][e->map.x] == 2)
		colour = 0x0000FF00;
	else if (e->world[e->map.y][e->map.x] == 3)
		colour = 0x000000FF;
	else if (e->world[e->map.y][e->map.x] == 4)
		colour = 0x00FFFFFF;
	else
		colour = 0x00FF00FF;
	if (e->side == 0)
	{
		colour -= colour & 0x0000007F;
		colour -= colour & 0x00007F00;
		colour -= colour & 0x007F0000;
	}
	i = 0;
	while (i < e->start)
	{
		px = i * e->px_pitch + x * 4;
		*(int *)(e->pixels + px) = 0x00000000;
		i++;
	}
	while (e->start <= e->end)
	{
		px = e->start * e->px_pitch + x * 4;
		*(int *)(e->pixels + px) = colour;
		++e->start;
	}
	i = e->end + 1;
	while (i < WIN_Y)
	{
		px = i * e->px_pitch + x * 4;
		*(int *)(e->pixels + px) = 0x00000000;
		i++;
	}
} */

void		draw_vscan_line(t_env *e, size_t x)
{
	int		tex_no;
	int		tex_x;
	double	wallx;

	text_no = e->eorld_map[e->map.y][e->map.x] - 1;
	if (e->side)
		wallx = e->ray.loc.x + e->total_dist * e->ray.rot.x;
	else
		wallx = e->ray.loc.y + e->total_dist * e->ray.rot.y;
	wallx -= (int)wallx;
	tex_x = (int)(wallx * double(TEX_X);
	if ((e->side && e->ray.rot.x < 0) || (!e->side && e->ray.rot.x > 0))
		tex_x = TEX_X - tex_x - 1;
}

void		draw_frame(t_env *e)
{
	size_t		x;

	x = 0;
	SDL_LockTexture(e->img, NULL, &e->pixels, &e->px_pitch);
	while (x < WIN_X)
	{
		calc_ray_loc_rot(e, x);
		e->map.x = (int)e->ray.loc.x;
		e->map.y = (int)e->ray.loc.y;
		e->delta_dist.x = sqrt(1 + (e->ray.rot.y * e->ray.rot.y) / (e->ray.rot.x * e->ray.rot.x));
		e->delta_dist.y = sqrt(1 + (e->ray.rot.x * e->ray.rot.x) / (e->ray.rot.y * e->ray.rot.y));
		calc_init_dist(e);
		dda(e);
		calc_line(e);
		draw_vscan_line(e, x);
		++x;
	}
	SDL_UnlockTexture(e->img);
	SDL_RenderCopy(e->rend, e->img, NULL, NULL);
	SDL_RenderPresent(e->rend);
}
