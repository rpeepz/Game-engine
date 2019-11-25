/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:50:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/25 07:15:47 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_engine.h"
#include "../includes/placeholder.h"

static int		hook_close(t_engine *engine)
{
	hook_keydown(KEY_ESC, engine);
	return (1);
}

static int		check_menu_input(int key, t_menu *m)
{
	if (key == KEY_ONE || key == KEY_TWO || key == KEY_THREE ||
		key == KEY_FOUR || key == KEY_FIVE || key == KEY_SIX)
	{
		mlx_put_image_to_window(m->engine->mlx, m->engine->win,\
		m->engine->scene[L_MENU], 0, 0);
		confirm(key, m->type, m);
	}
	if (key == KEY_ENTER &&
	(m->type & 0x4 ? m->fight->stage : m->fight->player[0]))
	{
		ft_printf("%s %c chosen !\n", m->type & 0x4 ? "Stage" : "Fighter",\
		m->type & 0x4 ? m->fight->stage : m->fight->player[0]);
		start_engine(m->engine);
	}
	if (key == KEY_ESC)
		hook_close(m->engine);
	return (0);
}

void			menu(t_engine *engine, char type, t_fight *f)
{
	int		tw;
	int		th;
	t_menu	m;

	tw = 0;
	th = 0;
	ft_menus(type & 0x4 ? 1 : 0);
	engine->scene[L_MENU] = mlx_xpm_to_image(engine->mlx,\
	type & 0x4 ? _stages_ : _chars_, &tw, &th);
	m.engine = engine;
	m.fight = f;
	m.type = type;
	// mlx_put_image_to_window(engine->mlx, engine->win,\
	// mlx_xpm_to_image(engine->mlx, _bridge_, &tw, &th), 0, 0);
	mlx_put_image_to_window(engine->mlx, engine->win,\
	engine->scene[L_MENU], 0, 0);
	mlx_hook(engine->win, 2, 0, check_menu_input, &m);
	mlx_hook(engine->win, 17, 0, hook_close, engine);
	mlx_loop(engine->mlx);
}

void			top_down(t_engine *engine)
{
	static t_fight		f;
	char				*backgrounds[6];
	int					tw;
	int					th;

	tw = 0;
	th = 0;
	if (TOP_DOWN && !f.stage)
		menu(engine, BOX_STAGE, &f);
	if (TOP_DOWN && !f.player[0])
		menu(engine, BOX_CHARACTER, &f);
	backgrounds[0] = mlx_xpm_to_image(engine->mlx, _bridge_, &tw, &th);
	backgrounds[1] = mlx_xpm_to_image(engine->mlx, _castle_, &tw, &th);
	backgrounds[2] = mlx_xpm_to_image(engine->mlx, _city_, &tw, &th);
	backgrounds[3] = mlx_xpm_to_image(engine->mlx, _garden_, &tw, &th);
	backgrounds[4] = mlx_xpm_to_image(engine->mlx, _dock_, &tw, &th);
	backgrounds[5] = mlx_xpm_to_image(engine->mlx, _park_, &tw, &th);
	engine->scene[L_BACK] = backgrounds[f.stage - '1'];
	render_top(engine, f);
	mlx_hook(engine->win, 2, 0, hook_keydown, engine);
	mlx_hook(engine->win, 17, 0, hook_close, engine);
	mlx_loop(engine->mlx);
}
