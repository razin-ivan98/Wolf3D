/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:59:50 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 14:15:35 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			menu_image_init(t_wolf3d *wolf3d)
{
	int len;
	int endian;
	int bytes;
	int i;
	int j;

	bytes = 8;
	len = 0;
	endian = 0;
	wolf3d->menu_win_ptr = mlx_new_window(wolf3d->mlx_ptr, 400, 400, "Wolf3d");
	wolf3d->menu.image = mlx_new_image(wolf3d->mlx_ptr, 400, 400);
	wolf3d->menu.image_data = mlx_get_data_addr(wolf3d->menu.image,
	&bytes, &len, &endian);
	wolf3d->menu.len = 400;
	i = 0;
	while (i < 400)
	{
		j = 0;
		while (j < 400)
		{
			put_point_to_image(&wolf3d->menu, i, j, color_to_rgb(0xFFFF00));
			j++;
		}
		i++;
	}
}

static void		another_key(int key, t_wolf3d *wolf3d)
{
	if (key == 0x24 || key == 0xff0d)
	{
		if (wolf3d->menu_selected == 0)
			wolf3d->hd = wolf3d->hd ? 0 : 1;
		else if (wolf3d->menu_selected == 1)
			wolf3d->walls_mode = wolf3d->walls_mode ? 0 : 1;
		else if (wolf3d->menu_selected == 2)
			wolf3d->light = wolf3d->light ? 0 : 1;
		else if (wolf3d->menu_selected == 3)
			wolf3d->filtr = wolf3d->filtr ? 0 : 1;
		else if (wolf3d->menu_selected == 4)
		{
			mlx_destroy_window(wolf3d->mlx_ptr, wolf3d->menu_win_ptr);
			wolf3d->menu_win_ptr = NULL;
			run_game(wolf3d);
		}
		else if (wolf3d->menu_selected == 5)
		{
			exit_full(wolf3d);
		}
	}
}

int				menu_key_pressed(int key, t_wolf3d *wolf3d)
{
	if (key == 0x35)
	{
		exit(1);
	}
	else if (key == 0x07E || key == 0xff52)
	{
		if (wolf3d->menu_selected > 0)
			wolf3d->menu_selected--;
	}
	else if (key == 0x07D || key == 0xff54)
	{
		if (wolf3d->menu_selected < 5)
			wolf3d->menu_selected++;
	}
	else
		another_key(key, wolf3d);
	menu_provider(wolf3d);
	return (0);
}

void			menu_init(t_wolf3d *wolf3d)
{
	wolf3d->hd = 0;
	wolf3d->light = 0;
	wolf3d->walls_mode = 0;
	wolf3d->filtr = 0;
	wolf3d->menu_selected = 0;
	menu_image_init(wolf3d);
	menu_provider(wolf3d);
	mlx_hook(wolf3d->menu_win_ptr, 2, 1L << 0, menu_key_pressed, wolf3d);
	mlx_hook(wolf3d->menu_win_ptr, 17, 1L << 0, exit_full, NULL);
	mlx_loop(wolf3d->mlx_ptr);
}
