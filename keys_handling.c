#include "wolf3d.h"

int key_pressed(int key, t_wolf3d *wolf3d)
{

	if (key == 0x35 || key == 0xff1b)
	{
		
		exit_full(wolf3d);
	}

	else if (key == 0x07C || key == 0xff53)
	{
		wolf3d->player.angle += M_PI/48;
	}
	else if (key ==0x07B || key == 0xff51)
	{
		wolf3d->player.angle -= M_PI/48;
	}
	else if (key ==0x07E  || key == 0xff52)
	{
		if (get_tile(wolf3d->player.pos_x + 0.6*cos(wolf3d->player.angle), wolf3d->player.pos_y + 0.6*sin(wolf3d->player.angle), wolf3d) <= 0)
		{
			wolf3d->player.pos_x += 0.3*cos(wolf3d->player.angle);
			wolf3d->player.pos_y += 0.3*sin(wolf3d->player.angle);
			wolf3d->door = 0;
		}
		else if (get_tile(wolf3d->player.pos_x + 0.6*cos(wolf3d->player.angle), wolf3d->player.pos_y + 0.6*sin(wolf3d->player.angle), wolf3d) / 10 == 9)
			wolf3d->door = get_tile(wolf3d->player.pos_x + 0.6*cos(wolf3d->player.angle), wolf3d->player.pos_y + 0.6*sin(wolf3d->player.angle), wolf3d) % 10 ;
	}
	else if (key ==0x07D || key == 0xff54)
	{
		if (get_tile(wolf3d->player.pos_x - 0.6*cos(wolf3d->player.angle), wolf3d->player.pos_y - 0.6*sin(wolf3d->player.angle), wolf3d) <= 0)
		{
			wolf3d->player.pos_x -= 0.3*cos(wolf3d->player.angle);
			wolf3d->player.pos_y -= 0.3*sin(wolf3d->player.angle);
			wolf3d->door = 0;
		}
	}

	else if (key == 0x03 || key == 0x66)
	{
		if (wolf3d->door)
		{
			free_map(wolf3d);
			wolf3d->player.pos_x = wolf3d->doors[wolf3d->door - 1].pos_x;
			wolf3d->player.pos_y = wolf3d->doors[wolf3d->door - 1].pos_y;
			wolf3d_init(wolf3d, (wolf3d->doors[wolf3d->door - 1].file_name));
			//check
		}
	}


	provider(wolf3d);
	return (0);
}
