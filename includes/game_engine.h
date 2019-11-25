/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 00:21:10 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/25 04:08:18 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENGINE_H
# define GAME_ENGINE_H

# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/includes/mlx.h"
# include "keys.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720
# define VALID_IN_X(x) (x == KEY_RIGHT || x == KEY_LEFT)
# define VALID_IN_Y(x) (x == KEY_UP || x == KEY_DOWN)
# define VALID_IN_Z(x) (x == KEY_PLUS || x == KEY_MINUS || x == KEY_SPACE)
# define STATIC_ZOOM(x) (x == PG_UP || x == PG_DOWN)
# define PI 3.1415926535
# define TOP_DOWN 1
# define SINGLE_CORE 1
# define THREAD_COUNT 8
# ifdef _DEBUG_RULE_
#  define DEBUG 1
# else
#  define DEBUG 0
# endif

/*
**	STRUCTS
*/

typedef struct			s_2dp
{
	double				x;
	double				y;
}						t_2dp;

typedef struct			s_map
{
	int					width;
	int					height;
	int					**cell;
}						t_map;

typedef struct			s_image
{
	void				*image;
	char				*pixels;
	int					bpp;
	int					stride;
	int					endian;
}						t_image;

/*
**	unused in engine
*/
typedef struct			s_camera
{
	double				offsetz;
	double				zoom;
}						t_camera;

/*
**	`key_down` is a cache for held down keys
*/
typedef struct			s_input
{
	struct s_keys		*key;
	struct s_mouse		*mouse;
	char				key_down[8];
}						t_input;

/*
**	player location and view direction on 2d map
**	`depth` is how far a player can see
*/
typedef struct			s_player
{
	char				name[16];
	t_2dp				loc;
	t_2dp				eye;
	float				angle;
	float				fov;
	float				depth;
}						t_player;

/*
**	render struct for 1st person
*/
typedef struct			s_fprender
{
	float				ray_angle;
	float				distance;
	int					hit;
	int					ceiling;
	int					floor;
}						t_fprender;

typedef struct			s_engine
{
	char				started;
	int					player_count;
	t_camera			cam;
	t_map				*map;
	void				*mlx;
	void				*win;
	char				**scene;
	t_image				*image;
	t_input				*in;
	t_player			*player;
}						t_engine;

/*
**	struct to hold values passed around in different threads
*/
typedef struct			s_game_thread
{
	t_engine			*engine;
	int					i;
}						t_engine_thread;

/*
**void					render_thread(t_engine *game);
*/

int						del_array(char **arr, int len);
int						help(void);
int						ft_out(int key);

void					render_fp(t_engine *eng);
void					start_engine(t_engine *eng);

int						del_players(t_player **aplayers, int i);
t_player				*init_players(t_engine *eng);

t_image					*del_image(t_engine *eng, t_image *img);
t_engine				*del_engine(t_engine **aeng, int i);
t_engine				*init_engine(char *title, t_map *map);

void					del_map(t_map **amap);
int						validate_map(char *file, t_map *map);

int						hook_keydown(int key, t_engine *eng);
int						hook_keyup(int key, t_engine *eng);
int						hook_mousedown(int button, int x, int y, t_engine *eng);
int						hook_mousemove(int x, int y, t_engine *eng);

#endif
