/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:01:45 by adippena          #+#    #+#             */
/*   Updated: 2016/06/19 18:46:00 by adippena         ###   ########.fr       */
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
}

void	move_player(t_env *e)
{
	float	rotx;
	float	roty;

	if (e->run_time > ft_get_time())
	{
		rotx = e->player.rot.x / 8.0F;
		roty = e->player.rot.y / 8.0F;
		rotate(e, -e->rot);
		e->plane.y = 0.61;
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
		if (!e->world[(int)e->player.loc.y][(int)(e->player.loc.x + rotx)])
			e->player.loc.x += rotx;
		if (!e->world[(int)(e->player.loc.y + roty)][(int)e->player.loc.x])
			e->player.loc.y += roty;
	}
	if (e->key.s_key)
	{
		if (!e->world[(int)e->player.loc.y][(int)(e->player.loc.x - rotx)])
			e->player.loc.x -= rotx;
		if (!e->world[(int)(e->player.loc.y - roty)][(int)e->player.loc.x])
			e->player.loc.y -= roty;
	}
	if (e->key.a_key)
	{
		if (!e->world[(int)e->player.loc.y][(int)(e->player.loc.x - roty)])
			e->player.loc.x -= roty;
		if (!e->world[(int)(e->player.loc.y + rotx)][(int)e->player.loc.x])
			e->player.loc.y += rotx;
	}
	if (e->key.d_key)
	{
		if (!e->world[(int)e->player.loc.y][(int)(e->player.loc.x + roty)])
			e->player.loc.x += roty;
		if (!e->world[(int)(e->player.loc.y - rotx)][(int)e->player.loc.x])
			e->player.loc.y -= rotx;
	}
}
