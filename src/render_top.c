/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/25 07:23:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_engine.h"
#include "../includes/placeholder.h"

static void		set_layer(t_engine *engine, int l)
{
	if (l >= LAYERS)
		l = 0;
	mlx_put_image_to_window(engine->mlx, engine->win,\
	engine->scene[l], 0, 0);
}

void			render_top(t_engine *engine, t_fight f)
{
	set_layer(engine, L_BACK);
	(void)f;
}
