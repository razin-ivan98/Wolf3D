/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:23:06 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 17:55:33 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				key_released(int key, t_wolf3d *wolf3d)
{
	(void)key;
	system("sh scripts/stop_step.sh &");
	wolf3d->step = 0;
	return (0);
}

static void		step_forward(t_wolf3d *wolf3d)
{
	if (!wolf3d->step)
	{
		system("sh scripts/play_step.sh &");
		wolf3d->step = 1;
	}
	if (get_tile(wolf3d->player.pos_x + 0.6 * cos(wolf3d->player.angle),
	wolf3d->player.pos_y + 0.6 * sin(wolf3d->player.angle), wolf3d) <= 0)
	{
		wolf3d->player.pos_x += 0.3 * cos(wolf3d->player.angle);
		wolf3d->player.pos_y += 0.3 * sin(wolf3d->player.angle);
		wolf3d->door = 0;
	}
	else if (get_tile(wolf3d->player.pos_x + 0.6 * cos(wolf3d->player.angle),
	wolf3d->player.pos_y + 0.6 * sin(wolf3d->player.angle), wolf3d) / 10 == 9)
		wolf3d->door = get_tile(wolf3d->player.pos_x + 0.6 *
		cos(wolf3d->player.angle),
		wolf3d->player.pos_y + 0.6 * sin(wolf3d->player.angle), wolf3d) % 10;
}

static void		step_backwards(t_wolf3d *wolf3d)
{
	if (!wolf3d->step)
	{
		system("sh scripts/play_step.sh &");
		wolf3d->step = 1;
	}
	if (get_tile(wolf3d->player.pos_x - 0.6 * cos(wolf3d->player.angle),
	wolf3d->player.pos_y - 0.6 * sin(wolf3d->player.angle), wolf3d) <= 0)
	{
		wolf3d->player.pos_x -= 0.3 * cos(wolf3d->player.angle);
		wolf3d->player.pos_y -= 0.3 * sin(wolf3d->player.angle);
		wolf3d->door = 0;
	}
}

static void		open_door(t_wolf3d *wolf3d)
{
	if (wolf3d->door)
	{
		system("sh scripts/play_door.sh &");
		free_map(wolf3d);
		wolf3d->player.pos_x = wolf3d->doors[wolf3d->door - 1].pos_x;
		wolf3d->player.pos_y = wolf3d->doors[wolf3d->door - 1].pos_y;
		wolf3d_init(wolf3d, (wolf3d->doors[wolf3d->door - 1].file_name));
	}
}

int				key_pressed(int key, t_wolf3d *wolf3d)
{
	if (key == 0x35 || key == 0xff1b)
		exit_full(wolf3d);
	else if (key == 0x07C || key == 0xff53)
	{
		wolf3d->player.angle += M_PI / 48;
	}
	else if (key == 0x07B || key == 0xff51)
	{
		wolf3d->player.angle -= M_PI / 48;
	}
	else if (key == 0x07E || key == 0xff52)
	{
		step_forward(wolf3d);
	}
	else if (key == 0x07D || key == 0xff54)
	{
		step_backwards(wolf3d);
	}
	else if (key == 0x03 || key == 0x66)
	{
		open_door(wolf3d);
	}
	provider(wolf3d);
	return (0);
}
