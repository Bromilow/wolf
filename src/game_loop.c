/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:26:30 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/28 17:46:00 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		rotate(t_env *e, double rot)
{
	double	temp;

	if (e->rot != -rot && e->rot != rot)
		e->rot += rot;
	rot *= 3.14159265359F / 180.0;
	temp = e->player.rot.x;
	e->player.rot.x = e->player.rot.x * cos(rot) - e->player.rot.y * sin(rot);
	e->player.rot.y = temp * sin(rot) + e->player.rot.y * cos(rot);
	temp = e->plane.x;
	e->plane.x = e->plane.x * cos(rot) - e->plane.y * sin(rot);
	e->plane.y = temp * sin(rot) + e->plane.y * cos(rot);
}

void		set_run(t_env *e)
{
	size_t	now;

	now = ft_get_time();
	if (e->run_cooldown < now)
	{
		e->run_time = now + 5000000;
		e->run_cooldown = now + 10000000;
	}
}

void		game_loop(t_env *e)
{
	SDL_Event	event;
	int			loop;

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
		}
		redraw(e);
		SDL_Delay(16);
	}
}
