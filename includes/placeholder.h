/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:22:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/25 06:27:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLACEHOLDER_H
# define PLACEHOLDER_H

# include "game_engine.h"
# include "../resources/splash.xpm"
# include "../resources/characters/chars.xpm"
// # include "../resources/characters/AOF_Geese.xpm"
// # include "../resources/characters/AOF_John.xpm"
// # include "../resources/characters/AOF_King.xpm"
// # include "../resources/characters/AOF_Kisaragi.xpm"
// # include "../resources/characters/AOF_Micky.xpm"
// # include "../resources/characters/AOF_Rody.xpm"
// # include "../resources/characters/AOF_Yuri.xpm"
# include "../resources/stages/stages.xpm"
# include "../resources/stages/bridge.xpm"
# include "../resources/stages/castle.xpm"
# include "../resources/stages/city.xpm"
# include "../resources/stages/dock.xpm"
# include "../resources/stages/garden.xpm"
# include "../resources/stages/park.xpm"

# define USAGE "usage: ./placeholder"
# define BOX_CONFIRM 0x1
# define BOX_CHARACTER 0x2
# define BOX_STAGE 0x4
# define LAYERS 5
# define L_MENU 1
# define L_BACK 2
# define L_PLAY 3

typedef struct			s_fight
{
	char				stage;
	char				player[2];
	int					hitbox_p1[2];
	int					hurtbox_p1[2];
	int					hitbox_p2[2];
	int					hurtbox_p2[2];
}						t_fight;

typedef struct			s_menu
{
	t_engine			*engine;
	t_fight				*fight;
	char				type;
}						t_menu;

void					confirm(int key, char type, t_menu *m);
void					render_top(t_engine *eng, t_fight f);
void					menu(t_engine *eng, char type, t_fight *f);
void					top_down(t_engine *eng);
void					ft_menus(int type);

#endif
