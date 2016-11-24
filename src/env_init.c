/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 09:26:28 by rbromilo          #+#    #+#             */
/*   Updated: 2016/11/24 10:32:13 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_env(t_env *e)
{
	e->player.loc.x = 1.5;
	e->player.loc.y = 1.5;
	e->player.rot.x = -1;
	e->player.rot.y = 0;
	e->plane.x = 0;
	e->plane.y = 0.69 ;
	e->key.w_key = 0;
	e->key.a_key = 0;
	e->key.s_key = 0;
	e->key.d_key = 0;
	e->key.l_key = 0;
	e->key.r_key = 0;
	e->rot = 0;
	e->time_old = ft_get_time();
	rotate(e, 270);
	e->tick = 0;
	e->activated = 0;
	fill_map(e);
}
