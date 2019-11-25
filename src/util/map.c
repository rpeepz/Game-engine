/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 19:32:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/24 19:30:56 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game_engine.h"

static int	create_map(int height, int width, char *buf, t_map *map)
{
	char	**lines;
	char	**values;

	if (!(lines = ft_strsplit(buf, '\n')))
		return (-42);
	if (!(map->cell = ft_memalloc(sizeof(int *) * height)))
		return (del_array(lines, height));
	map->height = -1;
	while (++map->height < height)
	{
		if (!lines[map->height])
			return (del_array(lines, height) + 1);
		if (!(values = ft_strsplit(lines[map->height], ' ')))
			return (del_array(lines, height));
		if (!(map->cell[map->height] = ft_memalloc(sizeof(int) * width)))
		{
			del_map(&map);
			return (del_array(values, width));
		}
		map->width = -1;
		while (++map->width < width && values[map->width])
			map->cell[map->height][map->width] = ft_atoi(values[map->width]);
		del_array(values, width);
	}
	return (del_array(lines, height) + 43);
}

int			validate_map(char *filename, t_map *map)
{
	char	buf[PAGESIZE + 1];
	char	size[16];
	int		fd;
	int		ret;

	if ((fd = open(filename, O_RDONLY)) < 3)
		return (-1);
	ft_bzero(buf, 16);
	ft_bzero(size, 16);
	while (1)
	{
		read(fd, buf, 1);
		if (*buf == '\n')
			break ;
		if (!ft_isdigit(*buf) && *buf != ' ')
			return (-2);
		ft_strncpy(&size[LEN(size)], buf, 1);
	}
	ft_bzero(buf, PAGESIZE + 1);
	ret = read(fd, buf, 4096);
	close(fd);
	if (ret > 4000)
		return (-3);
	return (create_map(ft_atoi(size), ft_atoi(ft_strchr(size, ' ')), buf, map));
}
