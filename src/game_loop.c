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

void	game_loop(t_env *e)
{
	SDL_Event	event;
	int			loop;
	int			mouse_x;
	int			mouse_y;

	(void)mouse_y;
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(1);
	loop = 42;
	while (loop)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = 0;
			else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
				if (event.key.keysym.sym == SDLK_ESCAPE)
					loop = 0;
				else
					key_down(event.key.keysym.sym, e);
			else if (event.type == SDL_KEYUP && event.key.repeat == 0)
				key_up(event.key.keysym.sym, e);
			else if (event.type == SDL_MOUSEMOTION)
			{
				SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
				rotate(e, -(mouse_x >> 3));
			}
		}
		redraw(e);
		SDL_Delay(16);
	}
}
