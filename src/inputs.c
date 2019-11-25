/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/24 20:04:51 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_engine.h"

/*
**	No mouse buttons are supported at this time
*/

int				hook_mousedown(int in, int x, int y, t_engine *engine)
{
	// double		zoom;

	(void)y;
	(void)x;
	if (in == SCROLL_UP || in == SCROLL_DOWN || STATIC_ZOOM(in))
	{
		// zoom = (engine->cam.zoom / 100 + 1);
		// if ((in == SCROLL_DOWN || in == PG_DOWN) && (zoom > engine->cam.zoom))
		// 	(DEBUG ? printf("Minimum Zoom reached\n") : 0);
		// else
		// {
		// 	if ((in == SCROLL_UP || in == PG_UP) && (DEBUG ? ft_out(in) : 1))
		// 		engine->cam.zoom += zoom;
		// 	else if ((in == SCROLL_DOWN || in == PG_DOWN) &&
		// 		(DEBUG ? ft_out(in) : 1))
		// 		engine->cam.zoom -= zoom;
		// 	if (DEBUG ? printf("%f\n", engine->cam.zoom) : 1 && !STATIC_ZOOM(in))
		// 	{
		// 		;
		// 	}
		printf("%d\n", in);
		if (in == SCROLL_UP)
		{
			hook_keydown(KEY_UP, engine);
		}
		else if (in == SCROLL_DOWN)
		{
			hook_keydown(KEY_DOWN, engine);
		}
		(void)engine;
			// render(engine);
		// }
	}
	return (0);
}

/*
**	turn player camera with mouse
*/

int				hook_mousemove(int x, int y, t_engine *engine)
{
	if (!engine->in->mouse->lock)
	{
		if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
		{
			engine->player[0].angle = map_zero(x, WIDTH, -(PI * 2) + 1, (PI * 2) - 1);
			printf("%f\n", engine->player[0].angle);
			engine->in->mouse->lastx = engine->in->mouse->x;
			engine->in->mouse->lasty = engine->in->mouse->y;
			engine->in->mouse->x = x;
			engine->in->mouse->y = y;
			render(engine);
		}
	}
	else
	{
		;
	}
	return (0);
}

/*
**	calculate if the next input causes the player to collide with a wall
*/

static int		check_clip(t_engine engine, int key)
{
	t_2dp	loc;

	loc = engine.player[0].loc;
	loc.x += sinf(engine.player[0].angle) * ((key == KEY_UP) ?
	0.5f : -0.5f);
	loc.y += cosf(engine.player[0].angle) * ((key == KEY_UP) ?
	0.5f : -0.5f);
	if ((int)loc.y < 0 || (int)loc.y > engine.map->height
	|| (int)loc.x < 0|| (int)loc.x > engine.map->width ||
	!(engine.map->cell[(int)loc.y][(int)loc.x]))
		return (0);
	return (1);
}

/*
**	process a valid input key
*/

static void		in_key(t_engine *engine, int key)
{
	if ((key == KEY_PLUS || key == KEY_MINUS) && (DEBUG ? ft_out(key) : 1))
	{
		if ((key == KEY_PLUS && engine->cam.offsetz < (HEIGHT - 2)) ||
		(key == KEY_MINUS && engine->cam.offsetz > (2 - HEIGHT)))
			engine->cam.offsetz += (key == KEY_PLUS) ? 2 : -2;
		(DEBUG ? printf("%f\n", engine->cam.offsetz) : 0);
	}
	else if ((VALID_IN_Y(key)) && (DEBUG ? ft_out(key) : 1))
	{
		if (check_clip(*engine, key))
			return ;
		engine->player[0].loc.x += sinf(engine->player[0].angle) * ((key == KEY_UP) ?
		0.5f : -0.5f);
		engine->player[0].loc.y += cosf(engine->player[0].angle) * ((key == KEY_UP) ?
		0.5f : -0.5f);
	}
	else if ((VALID_IN_X(key)) && (DEBUG ? ft_out(key) : 1))
		engine->player[0].angle -= (key == KEY_LEFT) ? 0.03f : -0.03f;
	(DEBUG && VALID_IN_X(key)) ? printf("%f\n", engine->player[0].angle) : 0;
	(DEBUG && VALID_IN_Y(key)) ? printf("%f, %f\n",
		engine->player[0].loc.x, engine->player[0].loc.y) : 0;
}

/*
**	validate the input on current hook
*/

int				hook_keydown(int key, t_engine *engine)
{
	if (VALID_IN_X(key) || VALID_IN_Y(key) || VALID_IN_Z(key))
		in_key(engine, key);
	else if (STATIC_ZOOM(key))
		hook_mousedown(key, 0, 0, engine);
	else if (key == KEY_P && printf("Key: 'P' Pause: %s\n",
		engine->in->mouse->lock ? "Off" : "On"))
		engine->in->mouse->lock = (engine->in->mouse->lock) ? 0 : 1;
	else if (key == KEY_R && (DEBUG ? ft_out(key) : 1))
	{
		DEBUG ? printf("z %f\n", engine->cam.offsetz) : 0;
		engine->cam.offsetz = 0.0f;
		engine->cam.zoom = 1.0f;
		engine->player[0].fov = 3.14285f / 4.0f;
	}
	else if (printf("---\n") && key == KEY_ESC && printf("Goodbye!\n"))
	{
		(DEBUG ? system("leaks engine") : 1);
		exit((int)del_engine(&engine, 0));
	}
	if (VALID_IN_X(key) || VALID_IN_Y(key) || VALID_IN_Z(key) || key == KEY_R)
		render(engine);
	return (0);
}
