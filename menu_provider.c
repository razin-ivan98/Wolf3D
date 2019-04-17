/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_provider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:08:59 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 14:14:50 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		normed_menu_provider(t_wolf3d *wolf3d)
{
	if (wolf3d->walls_mode)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
		60, 80, wolf3d->menu_selected == 1 ? 0xFF0000 : 0x555500,
		"compas textures enable");
	else
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
		60, 80, wolf3d->menu_selected == 1 ? 0xFF0000 : 0x555500,
		"compas textures disable");
	if (wolf3d->light)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
		60, 110, wolf3d->menu_selected == 2 ? 0xFF0000 : 0x555500,
		"light mode enable");
	else
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
		60, 110, wolf3d->menu_selected == 2 ? 0xFF0000 : 0x555500,
		"light mode disable");
	if (wolf3d->filtr)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
		60, 140, wolf3d->menu_selected == 3 ? 0xFF0000 : 0x555500,
		"bilinear filtration enable");
	else
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
		60, 140, wolf3d->menu_selected == 3 ? 0xFF0000 : 0x555500,
		"bilinear filtration disable");
}

void			menu_provider(t_wolf3d *wolf3d)
{
	mlx_put_image_to_window(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
	wolf3d->menu.image, 0, 0);
	mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
	120, 20, 0x555500, "Wolf3D");
	if (wolf3d->hd)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 60, 50,
		wolf3d->menu_selected == 0 ? 0xFF0000 : 0x555500,
		"HD textures enable");
	else
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
		60, 50, wolf3d->menu_selected == 0 ? 0xFF0000 : 0x555500,
		"HD textures disable");
	normed_menu_provider(wolf3d);
	mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
	60, 170, wolf3d->menu_selected == 4 ? 0xFF0000 : 0x555500, "Play");
	mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr,
	60, 200, wolf3d->menu_selected == 5 ? 0xFF0000 : 0x555500, "Exit");
}
