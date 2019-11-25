/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/24 22:36:38 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_engine.h"

/*
**	assign values to the colors array by [r, g, b] (with shading by distance)
*/

void	color_get(int *color, float distance, float depth)
{
	int		mod;
	float	dist;

	dist = distance / depth;
	mod = dist * 255;
	if (mod >= 250 && DEBUG)
		printf("too dark here\n");
	color[0] = (255 - mod) << 16;
	color[0] += (255 - mod) << 8;
	color[0] += (255 - mod);
	color[1] = (255 - mod) << 16;
	color[1] += (255 - mod);
	color[2] = (255 - mod) << 8;
	color[2] += (255 - mod);
	color[3] = (255 - mod) << 16;
	color[3] += (255 - mod) << 8;
	color[4] = (255 - mod) << 16;
	color[5] = (255 - mod) << 8;
	color[6] = (255 - mod);
}

/*
**	replace current image with a set layer
*/

void	set_layer(t_engine *engine, int l)
{
	ft_memmove(engine->image->pixels, engine->scene[l],
		sizeof(engine->image->pixels));
}

/*
**	get floor, ceiling, and wall pixel colors in current collumn
*/

void	get_hit(t_fprender *v, t_engine *engine)
{
	t_point		cast;

	v->distance = 0;
	v->hit = 0;
	while (!v->hit && v->distance < engine->player[0].depth)
	{
		v->distance += 0.008f;
		cast.x =\
		engine->player[0].loc.x + engine->player[0].eye.x * v->distance;
		cast.y =\
		engine->player[0].loc.y + engine->player[0].eye.y * v->distance;
		if ((int)cast.x < 0 || (int)cast.x >= engine->map->width ||
			(int)cast.y < 0 || (int)cast.y >= engine->map->height)
		{
			v->hit = 1;
			v->distance = engine->player[0].depth;
		}
		else
			v->hit = engine->map->cell[cast.y][cast.x];
	}
	v->ceiling = ((float)HEIGHT / 2) - HEIGHT / (float)v->distance;
	v->floor = HEIGHT - v->ceiling;
}

void	draw_(t_engine *engine, t_fprender v, t_point pixel, int *color)
{
	if ((int)pixel.y <= v.ceiling)
		*(int *)(engine->image->pixels +
		(pixel.x + pixel.y * WIDTH) * engine->image->bpp) = 0x2A2A2A;
	else if ((int)pixel.y > v.ceiling && (int)pixel.y <= v.floor)
		*(int *)(engine->image->pixels +
		(pixel.x + pixel.y * WIDTH) * engine->image->bpp) =
			color[v.hit ? v.hit - 1 : 0];
	else
		*(int *)(engine->image->pixels +
		(pixel.x + pixel.y * WIDTH) * engine->image->bpp) = 0x06A6A6A;
}

/*
**	calculate from the current player location, the angle from which the rays
**	are sent and draw column by column the values retrieved from get_hit
*/

void	render(t_engine *engine)
{
	t_point		pixel;
	t_fprender	v;
	int			color[7];

	set_layer(engine, 0);
	pixel.x = -1;
	while (++pixel.x < WIDTH)
	{
		v.ray_angle =\
		(engine->player[0].angle - (engine->player[0].fov / 2.0)) +\
		((float)pixel.x / (float)WIDTH) * engine->player[0].fov;
		engine->player[0].eye.x = sinf(v.ray_angle);
		engine->player[0].eye.y = cosf(v.ray_angle);
		get_hit(&v, engine);
		color_get(color, v.distance, engine->player[0].depth);
		pixel.y = -1;
		while (++pixel.y < HEIGHT)
			draw_(engine, v, pixel, color);
	}
	mlx_put_image_to_window(engine->mlx,\
	engine->win, engine->image->image, 0, 0);
}
