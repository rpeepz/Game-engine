/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:46:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/24 18:50:23 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_engine.h"
#include "../includes/placeholder.h"

int		hook_close(t_engine *engine)
{
	hook_keydown(KEY_ESC, engine);
	return (1);
}

int		press_start(int key, t_engine *engine)
{
	if (key == KEY_ENTER)
	{
		engine->started = 1;
		start_engine(engine);
	}
	if (key == KEY_ESC)
		hook_close(engine);
	return (0);
}

void	splash(t_engine *engine)
{
	int tw;
	int th;

	tw = 0;
	th = 0;
	ft_help();
	mlx_put_image_to_window(engine->mlx, engine->win,
	mlx_xpm_to_image(engine->mlx, _splash_, &tw, &th),
	(WIDTH / 2 - (tw / 2)), (HEIGHT / 2 - (th / 2)));
	mlx_string_put(engine->mlx, engine->win, (WIDTH * 10 / 20), (HEIGHT * 10 / 50),
	(0xffefd5), "Press Enter");
	mlx_hook(engine->win, 2, 0, press_start, engine);
	mlx_hook(engine->win, 17, 0, hook_close, engine);
	mlx_loop(engine->mlx);
}

/*
**	run 'press start' screen and enter render loop
*/

void	start_engine(t_engine *engine)
{
	if (!engine->started)
		splash(engine);
	render(engine);
	// mlx_do_key_autorepeaton(engine->mlx);
	mlx_hook(engine->win, 2, 0, hook_keydown, engine);
	mlx_hook(engine->win, 4, 0, hook_mousedown, engine);
	mlx_hook(engine->win, 6, 0, hook_mousemove, engine);
	mlx_hook(engine->win, 17, 0, hook_close, engine);
	mlx_loop(engine->mlx);
}
