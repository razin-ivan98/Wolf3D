/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:56:49 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 18:27:03 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		provider(t_wolf3d *wolf3d)
{
	int		wall;
	float	delta;
	int		x;

	x = 0;
	delta = FOV / CW;
	while (x < CW)
	{
		wolf3d->curr_cast.angle = wolf3d->player.angle - FOV_DIV_2 + delta * x;
		wolf3d->curr_cast.sin_a = sin(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.cos_a = cos(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.tan_a = tan(wolf3d->curr_cast.angle);
		cast(wolf3d);
		wall = CW / wolf3d->curr_cast.distance /
						cos(wolf3d->curr_cast.angle - wolf3d->player.angle);
		draw(wolf3d, x, wall, wolf3d->curr_cast.col);
		x++;
	}
	mlx_put_image_to_window(wolf3d->mlx_ptr, wolf3d->win_ptr,
						wolf3d->image.image, 0, 0);
	draw_minimap(wolf3d);
	if (wolf3d->door)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->win_ptr, CW / 2 - 20, CH / 2,
						0xFFFF00, "Press F");
}

void		run_game(t_wolf3d *wolf3d)
{
	wolf3d_init(wolf3d, wolf3d->file_name);
	wolf3d->step = 0;
	system("sh scripts/play_back.sh &");
	provider(wolf3d);
	mlx_hook(wolf3d->win_ptr, 2, 1L << 0, key_pressed, wolf3d);
	mlx_hook(wolf3d->win_ptr, 17, 1L << 0, exit_full, wolf3d);
	mlx_hook(wolf3d->win_ptr, 3, 1L << 0, key_released, wolf3d);
	mlx_loop(wolf3d->mlx_ptr);
}

static void	null_all(t_wolf3d *wolf3d)
{
	int i;

	i = 0;
	while (i < 10)
	{
		wolf3d->textures[i].image = NULL;
		wolf3d->doors[i].file_name = NULL;
		i++;
	}
	wolf3d->map = NULL;
	wolf3d->line = NULL;
	wolf3d->skybox.image = NULL;
	wolf3d->minimap.image = NULL;
	wolf3d->menu.image = NULL;
	wolf3d->image.image = NULL;
	wolf3d->win_ptr = NULL;
	wolf3d->menu_win_ptr = NULL;
}

int			main(int ac, char **av)
{
	t_wolf3d wolf3d;

	null_all(&wolf3d);
	if (ac != 2)
		err_exit(&wolf3d);
	null_all(&wolf3d);
	wolf3d.mlx_ptr = mlx_init();
	ft_strcpy(wolf3d.file_name, av[1]);
	menu_init(&wolf3d);
}
