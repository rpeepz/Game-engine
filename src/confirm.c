/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:54:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/25 06:12:54 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_engine.h"
#include "../includes/placeholder.h"

static int			box_x(int key, char type, char pos)
{
	if (type == BOX_STAGE)
	{
		if (key == KEY_ONE || key == KEY_FOUR)
			return (pos % 2 ? 65 : 390);
		if (key == KEY_TWO || key == KEY_FIVE)
			return (pos % 2 ? 486 : 810);
		return (pos % 2 ? 895 : 1219);
	}
	if (key == KEY_ONE)
		return (pos % 2 ? 70 : 195);
	if (key == KEY_TWO)
		return (pos % 2 ? 226 : 351);
	if (key == KEY_THREE)
		return (pos % 2 ? 382 : 539);
	if (key == KEY_FOUR)
		return (pos % 2 ? 697 : 822);
	if (key == KEY_FIVE)
		return (pos % 2 ? 872 : 997);
	return (pos % 2 ? 1019 : 1175);
}

static int			box_y(int key, char type, char pos)
{
	if (type == BOX_STAGE)
	{
		return ((key == KEY_ONE || key == KEY_TWO || key == KEY_THREE) ?
		(pos % 2 ? 36 : 224) : (pos % 2 ? 311 : 499));
	}
	return (pos % 2 ? 178 : 417);
}

void				print_box2(int key, t_engine engine, char type, int i)
{
	char	*wide;

	wide = "-------------";
	if (key == KEY_THREE || key == KEY_SIX)
		wide = "----------------";
	mlx_string_put(engine.mlx, engine.win, box_x(key, type, 1),\
	box_y(key, type, 1), 0xee0000, wide);
	mlx_string_put(engine.mlx, engine.win, box_x(key, type, 1),\
	box_y(key, type, 2), 0xee0000, wide);
	while (i < 23)
	{
		mlx_string_put(engine.mlx, engine.win, box_x(key, type, 1) - 5,\
		box_y(key, type, 1) + 8 + (i * 10), 0xee0000, "|");
		mlx_string_put(engine.mlx, engine.win, box_x(key, type, 2),\
		box_y(key, type, 1) + 8 + (i * 10), 0xee0000, "|");
		i++;
	}
}

void				print_box(int key, t_engine engine, char type, int i)
{
	if (type == BOX_CHARACTER)
	{
		print_box2(key, engine, type, i);
		return ;
	}
	mlx_string_put(engine.mlx, engine.win, box_x(key, type, 1),\
	box_y(key, type, 1), 0xee0000, "---------------------------------");
	mlx_string_put(engine.mlx, engine.win, box_x(key, type, 1),\
	box_y(key, type, 2), 0xee0000, "---------------------------------");
	while (i < 18)
	{
		mlx_string_put(engine.mlx, engine.win, box_x(key, type, 1) - 5,\
		box_y(key, type, 1) + 8 + (i * 10), 0xee0000, "|");
		mlx_string_put(engine.mlx, engine.win, box_x(key, type, 2),\
		box_y(key, type, 1) + 8 + (i * 10), 0xee0000, "|");
		i++;
	}
}

void				confirm(int key, char type, t_menu *m)
{
	int			i;
	t_engine	engine;
	char		*confirm;

	i = 0;
	confirm = "123465";
	engine = *m->engine;
	print_box(key, *m->engine, type, 0);
	if (type == BOX_STAGE)
		m->fight->stage = confirm[key - 18];
	else if (type == BOX_CHARACTER)
		m->fight->player[0] = confirm[key - 18];
	ft_printf("Confim %s %c ?\r", type & 0x4 ? "Stage" : "Fighter",
	type & 0x4 ? m->fight->stage : m->fight->player[0]);
}
