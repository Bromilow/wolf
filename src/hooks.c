#include "wolf3d.h"

void	rotate(t_env *e, float rot)
{
	float	old_player_rot;
	float	old_plane_rot;

	if (e->rot != -rot && e->rot != rot)
		e->rot += rot;
	rot *= 0.0174;
	old_player_rot = e->player.rot.x;
	e->player.rot.x = e->player.rot.x * cos(rot) - e->player.rot.y * sin(rot);
	e->player.rot.y = old_player_rot * sin(rot) + e->player.rot.y * cos(rot);
	old_plane_rot = e->plane.x;
	e->plane.x = e->plane.x * cos(rot) - e->plane.y * sin(rot);
	e->plane.y = old_plane_rot * sin(rot) + e->plane.y * cos(rot);
}

void		set_run(t_env *e)
{
	size_t	now;

	now = ft_get_time();
	if (e->run_cooldown	< now)
	{
		e->run_time = now + 5000000;
		e->run_cooldown = now + 1000000;
	}
}
