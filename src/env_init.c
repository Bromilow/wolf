/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adippena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 16:58:51 by adippena          #+#    #+#             */
/*   Updated: 2016/06/19 17:01:23 by adippena         ###   ########.fr       */
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
	e->rot = 0;
	e->clocks = CLOCKS_PER_SEC >> 5;
	e->time_old = clock();
	rotate(e, 270);
	fill_map(e);
}
