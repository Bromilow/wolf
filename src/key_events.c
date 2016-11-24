/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:26:34 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 10:27:10 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	key_down(SDL_Keycode key, t_env *e)
{
	if (key == SDLK_w)
		e->key.w_key = 1;
	else if (key == SDLK_a)
		e->key.a_key = 1;
	else if (key == SDLK_s)
		e->key.s_key = 1;
	else if (key == SDLK_d)
		e->key.d_key = 1;
	else if (key == SDLK_LSHIFT)
		set_run(e);
	else if (key == SDLK_LEFT)
		e->key.l_key = 1;
	else if (key == SDLK_RIGHT)
		e->key.r_key = 1;
}

void	key_up(SDL_Keycode key, t_env *e)
{
	if (key == SDLK_w)
		e->key.w_key = 0;
	else if (key == SDLK_a)
		e->key.a_key = 0;
	else if (key == SDLK_s)
		e->key.s_key = 0;
	else if (key == SDLK_d)
		e->key.d_key = 0;
	else if (key == SDLK_LEFT)
		e->key.l_key = 0;
	else if (key == SDLK_RIGHT)
		e->key.r_key = 0;
}

void	move_player(t_env *e)
{
	float	rotx;
	float	roty;

	if (e->run)
	{
		rotx = e->player.rot.x / 8.0F;
		roty = e->player.rot.y / 8.0F;
		rotate(e, -e->rot);
		e->plane.y = 0.66;
		rotate(e, e->rot);
	}
	else
	{
		rotx = e->player.rot.x / 16.0F;
		roty = e->player.rot.y / 16.0F;
		rotate(e, -e->rot);
		e->plane.y = 0.69;
		rotate(e, e->rot);
	}
	if (e->key.w_key)
	{
			e->player.loc.x += rotx;
			e->player.loc.y += roty;
	}
	else if (e->key.s_key)
	{
			e->player.loc.x -= rotx;
			e->player.loc.y -= roty;
	}
	if (e->key.a_key)
	{
			e->player.loc.x -= roty;
			e->player.loc.y += rotx;
	}
	else if (e->key.d_key)
	{
			e->player.loc.x += roty;
			e->player.loc.y -= rotx;
	}
	if (e->key.w_key || e->key.s_key || e->key.a_key || e->key.d_key)
	{
		while (e->world[(int)(e->player.loc.y + 0.25)][(int)e->player.loc.x])
			e->player.loc.y -= 0.001;
		while (e->world[(int)(e->player.loc.y - 0.25)][(int)e->player.loc.x])
			e->player.loc.y += 0.001;
		while (e->world[(int)e->player.loc.y][(int)(e->player.loc.x + 0.25)])
			e->player.loc.x -= 0.001;
		while (e->world[(int)e->player.loc.y][(int)(e->player.loc.x - 0.25)])
			e->player.loc.x += 0.001;
	}
	if (e->key.l_key)
		rotate(e, 5.0);
	if (e->key.r_key)
		rotate(e, -5.0);
}
