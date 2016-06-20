#include "wolf3d.h"

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
	e->line_height = (int)(WIN_Y / e->total_dist);
	e->start = -e->line_height / 2 + WIN_Y / 2;
	if (e->start < 0)
		e->start = 0;
	e->end = e->line_height / 2 + WIN_Y / 2;
	if (e->end >= WIN_Y)
		e->end = WIN_Y - 1;
}
