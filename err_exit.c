/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:48:44 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 15:46:21 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_map(t_wolf3d *wolf3d)
{
	int i;

	i = 0;
	if (!wolf3d->map)
		return ;
	while (i < wolf3d->cols)
	{
		if (wolf3d->map[i])
			ft_memdel((void **)&wolf3d->map[i]);
		i++;
	}
	if (wolf3d->map)
		ft_memdel((void **)&wolf3d->map);
}

void	free_doors(t_wolf3d *wolf3d)
{
	int i;

	i = 0;
	while (i < 10)
	{
		if (wolf3d->doors[i].file_name)
			ft_strdel(&wolf3d->doors[i].file_name);
		i++;
	}
}

void	free_textures(t_wolf3d *wolf3d)
{
	int i;

	i = 0;
	while (i < 10)
	{
		if (wolf3d->textures[i].image)
			mlx_destroy_image(wolf3d->mlx_ptr, wolf3d->textures[i].image);
		i++;
	}
	if (wolf3d->skybox.image)
		mlx_destroy_image(wolf3d->mlx_ptr, wolf3d->skybox.image);
	if (wolf3d->minimap.image)
		mlx_destroy_image(wolf3d->mlx_ptr, wolf3d->minimap.image);
	if (wolf3d->menu.image)
		mlx_destroy_image(wolf3d->mlx_ptr, wolf3d->menu.image);
	if (wolf3d->image.image)
		mlx_destroy_image(wolf3d->mlx_ptr, wolf3d->image.image);
}

int		exit_full(t_wolf3d *wolf3d)
{
	system("sh scripts/stop_back.sh &");
	system("sh scripts/stop_step.sh &");
	if (wolf3d->line)
		ft_strdel(&wolf3d->line);
	free_map(wolf3d);
	free_doors(wolf3d);
	free_textures(wolf3d);
	if (wolf3d->win_ptr)
		mlx_destroy_window(wolf3d->mlx_ptr, wolf3d->win_ptr);
	if (wolf3d->menu_win_ptr)
		mlx_destroy_window(wolf3d->mlx_ptr, wolf3d->menu_win_ptr);
	exit(1);
}

void	err_exit(t_wolf3d *wolf3d)
{
	ft_putendl("error");
	exit_full(wolf3d);
}
