/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 04:17:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/24 19:53:48 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game_engine.h"

static t_image	*new_image(t_engine *engine)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->image = mlx_new_image(engine->mlx, WIDTH, HEIGHT)))
		return (del_image(engine, img));
	img->pixels = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}

t_input				*init_input()
{
	t_input		*in;
	
	if (!(in = ft_memalloc(sizeof(t_input))) ||
		!(in->key = ft_memalloc(sizeof(t_keys))) ||
		!(in->mouse = ft_memalloc(sizeof(t_mouse))))
		return (NULL);
	return (in);
}

t_engine			*init_engine(char *title, t_map *map)
{
	t_engine	*engine;
	int			i;

	if (!(engine = ft_memalloc(sizeof(t_engine))))
		return (NULL);
	engine->map = map;
	if (!(engine->mlx = mlx_init()) ||
		!(engine->win = mlx_new_window(engine->mlx, WIDTH, HEIGHT, title)) ||
		!(engine->scene = ft_memalloc(sizeof(char *) * LAYERS)) ||
		!(engine->image = new_image(engine)) ||
		!(engine->in = init_input()))
		return (del_engine(&engine, 0));
	i = 0;
	while (i < LAYERS)
		engine->scene[i++] = ft_memalloc(sizeof(engine->image->pixels));
	engine->player_count = 1;
	engine->player = init_players(engine);
	engine->cam.offsetz = 0.0f;
	engine->cam.zoom = 1.0f;
	return (engine);
}

t_player			*init_players(t_engine *engine)
{
	t_player	*players;
	int			i;

	if (!(players = ft_memalloc(sizeof(t_player) * engine->player_count)))
		return (NULL);
	i = 0;
	while (i < engine->player_count)
	{
		players[i].loc.x = (float)engine->map->width / 2;
		players[i].loc.y = (float)engine->map->height / 2;
		players[i].angle = 0.0f;
		players[i].fov = 3.14159f / 4.0f;
		players[i].depth = engine->map->width;
		i++;
	}
	return (players);
}
