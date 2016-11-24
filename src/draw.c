/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:26:21 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 09:26:22 by rbromilo         ###   ########.fr       */
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

	if (e->side)
		e->wall.x = e->ray.loc.x + e->total_dist * e->ray.rot.x;
	else
		e->wall.x = e->ray.loc.y + e->total_dist * e->ray.rot.y;
	e->wall.x -= (int)e->wall.x;
	tex_x = (int)(e->wall.x * (double)(TEX));
	if ((e->side && e->ray.rot.y < 0) || (!e->side && e->ray.rot.x > 0))
		tex_x = TEX - tex_x - 1;
	return (tex_x);
}

void		get_floor_xy(t_env *e, t_v2d *floor_wall)
{
	if (e->side == 0 && e->ray.rot.x > 0)
	{
		floor_wall->x = e->map.x;
		floor_wall->y = e->map.y + e->wall.x;
	}
	else if (e->side == 0 && e->ray.rot.x < 0)
	{
		floor_wall->x = e->map.x + 1.0;
		floor_wall->y = e->map.y + e->wall.x;
	}
	else if (e->side == 1 && e->ray.rot.y > 0)
	{
		floor_wall->x = e->map.x + e->wall.x;
		floor_wall->y = e->map.y;
	}
	else
	{
		floor_wall->x = e->map.x + e->wall.x;
		floor_wall->y = e->map.y + 1.0;
	}
}

void		cast_floor(t_env *e, size_t x)
{
	t_v2d		floor_wall;
	double		d;
	t_v2dint	floor_tex;

	get_floor_xy(e, &floor_wall);
	while (++e->end < WIN_Y)
	{
		d = ((double)WIN_Y / ((double)(e->end << 1) - (double)WIN_Y)) /
			e->total_dist;
		floor_tex.x = (int)((d * floor_wall.x + (1.0 - d) * e->player.loc.x) *
			(double)TEX) % TEX;
		floor_tex.y = (int)((d * floor_wall.y + (1.0 - d) * e->player.loc.y) *
			(double)TEX) % TEX;
		*(int *)(e->pixels + (e->end * e->px_pitch + (x * 4))) =
			e->tex[3][floor_tex.x][floor_tex.y];
		*(int *)(e->pixels + ((WIN_Y - e->end) * e->px_pitch + (x * 4))) =
			e->tex[4][floor_tex.x][floor_tex.y];

	}
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
	while (e->start <= e->end)
	{
		d = (e->start << 8) - (WIN_Y << 7) + (e->line_height << 7);
		tex_y = ((d * TEX) / e->line_height) >> 8;
		px = e->start * e->px_pitch + (x * 4);
		*(int *)(e->pixels + px) = e->tex[tex_no][tex_x][tex_y];
		++e->start;
	}
	cast_floor(e, x);
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
		e->delta_dist.x = sqrt(1 + (e->ray.rot.y * e->ray.rot.y) /
			(e->ray.rot.x * e->ray.rot.x));
		e->delta_dist.y = sqrt(1 + (e->ray.rot.x * e->ray.rot.x) /
			(e->ray.rot.y * e->ray.rot.y));
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
