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

int			get_tex_x(t_env *e)
{
	int		tex_x;
	double	wallx;

	if (e->side)
		wallx = e->ray.loc.x + e->total_dist * e->ray.rot.x;
	else
		wallx = e->ray.loc.y + e->total_dist * e->ray.rot.y;
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (double)(TEX_X));
	if ((e->side && e->ray.rot.y < 0) || (!e->side && e->ray.rot.x > 0))
		tex_x = TEX_X - tex_x - 1;
	return (tex_x);
}

uint32_t	get_colour(unsigned char *tex, int tex_x, int tex_y)
{
	uint32_t	colour;

	colour = 0;
	colour |= tex[tex_x * TEX_Y + tex_y * 4 + 0] << 16;
	colour |= tex[tex_x * TEX_Y + tex_y * 4 + 1] << 8;
	colour |= tex[tex_x * TEX_Y + tex_y * 4 + 2];
	colour |= tex[tex_x * TEX_Y + tex_y * 4 + 3] << 24;
	return (colour);
}

void		draw_vscan_line(t_env *e, size_t x)
{
	int			tex_x;
	int			tex_no;
	int			d;
	int			tex_y;
	size_t		px;

	tex_no = e->world[e->map.y][e->map.x] - 1;
	tex_x = get_tex_x(e);
	d = 0;
	while (d < e->start)
	{
		px = d * e->px_pitch + (x << 2);
		*(int *)(e->pixels + px) = 0x00000000;
		d++;
	}
	while (e->start <= e->end)
	{
		d = (e->start << 8) - (WIN_Y << 7) + (e->line_height << 7);
		tex_y = ((d * TEX_Y) / e->line_height) >> 8;
		px = e->start * e->px_pitch + (x << 2);
		*(int *)(e->pixels + px) = get_colour(e->tex[tex_no], tex_x, tex_y);
		++e->start;
	}
	d = e->end + 1;
	while (d < WIN_Y)
	{
		px = d * e->px_pitch + x * 4;
		*(int *)(e->pixels + px) = 0x00000000;
		d++;
	}
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
