/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:02:28 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/24 19:53:38 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game_engine.h"

int			del_array(char **arr, int len)
{
	int		i;

	i = 0;
	if (!len || !arr)
		return (-42);
	while (i < len)
		ft_strdel(&(arr[i++]));
	ft_memdel((void **)&arr);
	return (-42);
}

void		del_map(t_map **amap)
{
	int		i;
	t_map	*map;

	map = *amap;
	i = 0;
	while (map->cell && i < map->height)
	{
		if (map->cell[i])
			ft_memdel((void **)&map->cell[i]);
		i++;
	}
	if (map->cell)
		ft_memdel((void **)&map->cell);
}

t_image		*del_image(t_engine *game, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(game->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_engine		*del_engine(t_engine **aengine, int i)
{
	t_engine	*engine;

	engine = *aengine;
	IF_THEN(engine->player, ft_memdel((void **)&engine->player));
	if (engine->scene)
		while (i < LAYERS)
			IF_THEN(engine->scene[i], ft_memdel((void **)&engine->scene[i++]));
	if (engine->in)
	{
		IF_THEN(engine->in->mouse, ft_memdel((void **)&engine->in->mouse));
		IF_THEN(engine->in->key, ft_memdel((void **)&engine->in->key));
	}
	IF_THEN(engine->in, ft_memdel((void **)&engine->in));
	IF_THEN(engine->image, del_image(engine, engine->image));
	IF_THEN(engine->scene, ft_memdel((void **)engine->scene));
	IF_THEN(engine->win, mlx_destroy_window(engine->mlx, engine->win));
	IF_THEN(engine->mlx, ft_memdel((void **)&engine->mlx));
	IF_THEN(engine->map, del_map(&engine->map));
	ft_memdel((void **)&engine);
	return (NULL);
}
