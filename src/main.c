/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:38:46 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/24 19:36:57 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_engine.h"
#include "../includes/placeholder.h"

/*
** Validate map, init game, and start game
*/

int		main(int ac, char **av)
{
	t_engine	*game;
	t_map		map;
	int			ret;

	ft_bzero(&map, sizeof(map));
	if (ac != 2)
		return (ft_printf("%s\n", USAGE));
	if (!ft_strcmp(av[1], "help"))
		return (ft_help());
	if ((ret = validate_map(av[1], &map)) <= 0)
		return (ft_out(ret));
	if (!(game = init_engine("Fighter", &map)))
		return (ft_out(-42));
	start_engine(game);
	return (0);
}
