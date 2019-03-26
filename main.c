#include "wolf3d.h"
/*
void cast_x(t_wolf3d *wolf3d)
{
	float new_x;
	float new_y;
	float distance;

	new_x = floor(wolf3d->player.pos_x);
	new_y = wolf3d->player.pos_y + (new_x - wolf3d->player.pos_x) * wolf3d->curr_cast.tan_a;
	if (wolf3d->curr_cast.cos_a > 0)
	{

		while (new_y > 0.0 && new_y < wolf3d->rows && new_x < wolf3d->cols)
		{
			puts("1");
			if ((wolf3d->curr_cast.type = get_tile(new_x + 0.1, new_y, wolf3d)))
				break ;
			new_x += 1.0;
			new_y = new_y + wolf3d->curr_cast.tan_a;
		}
		distance = sqrt((new_x - wolf3d->player.pos_x) * (new_x - wolf3d->player.pos_x) + (new_y - wolf3d->player.pos_y)*(new_y - wolf3d->player.pos_y)) ;
	}
	else
	{
		while (new_y > 0.0 && new_y < wolf3d->rows && new_x > 0.0)
		{
			puts("2");
			if ((wolf3d->curr_cast.type = get_tile(new_x - 0.1, new_y, wolf3d)))
				break ;
			new_x -= 1.0;
			new_y = new_y + wolf3d->curr_cast.tan_a;
		}
		distance = sqrt(((double)new_x - wolf3d->player.pos_x) * ((double)new_x - wolf3d->player.pos_x) + ((double)new_y - wolf3d->player.pos_y)*((double)new_y - wolf3d->player.pos_y));
	}

	wolf3d->curr_cast.intersect_x = new_x;
	wolf3d->curr_cast.intersect_y = new_y;
	wolf3d->curr_cast.distance = distance;
}

void cast_y(t_wolf3d *wolf3d)
{
	float new_x;
	float new_y;
	float distance;


	new_y = floor(wolf3d->player.pos_y);
	new_x = wolf3d->player.pos_x + (new_y - wolf3d->player.pos_y) / wolf3d->curr_cast.tan_a;
	if (wolf3d->curr_cast.sin_a > 0)
	{
		while (new_x > 0.0 && new_x < wolf3d->cols &&  new_y < wolf3d->rows)
		{
			puts("3");
			if ((wolf3d->curr_cast.type = get_tile(new_x, new_y + 0.1, wolf3d)))
				break ;
			new_y += 1.0;
			new_x = new_x + 1 / wolf3d->curr_cast.tan_a;
		}
		distance = sqrt((new_x - wolf3d->player.pos_x) * (new_x - wolf3d->player.pos_x) + (new_y - wolf3d->player.pos_y)*(new_y - wolf3d->player.pos_y)) ;
	}
	else
	{
		while (new_x > 0.0 && new_x < wolf3d->cols && new_y > 0.0)
		{
			puts("4");
			if ((wolf3d->curr_cast.type = get_tile(new_x, new_y - 0.1, wolf3d)))
				break ;
			new_y -= 1.0;
			new_x = new_x + 1 / wolf3d->curr_cast.tan_a;
		}
		distance = sqrt(((double)new_x - wolf3d->player.pos_x) * ((double)new_x - wolf3d->player.pos_x) + ((double)new_y - wolf3d->player.pos_y)*((double)new_y - wolf3d->player.pos_y));
	}

	if (distance < wolf3d->curr_cast.distance)
	{
		wolf3d->curr_cast.intersect_x = new_x;
		wolf3d->curr_cast.intersect_y = new_y;
		wolf3d->curr_cast.distance = distance;
	}

}
*/
void cast(t_wolf3d *wolf3d)
{
	//float dist_x;
	//float dist_y;
/*
	float new_x;
	float new_y;

	float dist_x;
	float dist_y;
	*/
/*	if (wolf3d->curr_cast.cos_a != 0)
		cast_x(wolf3d);
	if (wolf3d->curr_cast.sin_a != 0)
		cast_y(wolf3d);*/

	//wolf3d->curr_cast.distance = dist_x < dist_y ? dist_x : dist_y;




	float sin_a = sin(wolf3d->curr_cast.angle);
	float cos_a = cos(wolf3d->curr_cast.angle);

	wolf3d->curr_cast.intersect_x = wolf3d->player.pos_x;
	wolf3d->curr_cast.intersect_y = wolf3d->player.pos_y;
	wolf3d->curr_cast.distance = 0.0;


	while (!(wolf3d->curr_cast.type = get_tile(wolf3d->curr_cast.intersect_x, wolf3d->curr_cast.intersect_y, wolf3d)))
	{
		wolf3d->curr_cast.intersect_x = wolf3d->player.pos_x + wolf3d->curr_cast.distance*cos_a;
		wolf3d->curr_cast.intersect_y = wolf3d->player.pos_y + wolf3d->curr_cast.distance*sin_a;
		wolf3d->curr_cast.distance += 0.01;
	}




}

void draw(t_wolf3d *wolf3d, int x, int wall, int col)
{
	int row;
	float delta_wall, floor_dist;
	delta_wall = 32.0 / wall;

	float floor_x;
	float floor_y;

	float cos_ang_minus_pl = cos(wolf3d->curr_cast.angle - wolf3d->player.angle);
	//float sin_ang = sin(wolf3d->curr_cast.angle);
	//float cos_ang = cos(wolf3d->curr_cast.angle);

	int CH_div_2 = CH / 2;
	int wall_div_2 = wall / 2;

	int f_col;
	int f_row;

	for (int y = 0; y < CH; y++)
	{
		if ((y >= CH_div_2 + wall_div_2 && y < CH) || (y >= 0 && y <= CH_div_2 - wall_div_2))
		{
			if (y < CH_div_2)
			{
				floor_dist = CW / (2.0 * (CH - y) - CH) / cos_ang_minus_pl;

				floor_x = wolf3d->player.pos_x + floor_dist * wolf3d->curr_cast.cos_a;
				floor_y = wolf3d->player.pos_y + floor_dist * wolf3d->curr_cast.sin_a;

				f_col = (int)((floor_x - (int)(floor_x)) * 32.0);
				f_row = (int)((floor_y - (int)(floor_y)) * 32.0);
				put_point_to_image(wolf3d->image_data, x, y, calculate_light(get_rgb_from_texture(f_col, f_row, wolf3d->textures[wood].image_data), floor_dist));//seiling
			}
			else
			{
				floor_dist = CW / (2.0 * y - CH) / cos_ang_minus_pl;

				floor_x = wolf3d->player.pos_x + floor_dist * wolf3d->curr_cast.cos_a;
				floor_y = wolf3d->player.pos_y + floor_dist * wolf3d->curr_cast.sin_a;

				f_col = (int)((floor_x - (int)(floor_x)) * 32.0);
				f_row = (int)((floor_y - (int)(floor_y)) * 32.0);
				put_point_to_image(wolf3d->image_data, x, y, calculate_light(get_rgb_from_texture(f_col, f_row, wolf3d->textures[wood].image_data), floor_dist));//floor
			}
		}
		else if (y > CH_div_2 - wall_div_2 && y <= CH_div_2 + wall_div_2)
		{
			row = (int)((y - (CH_div_2 - wall_div_2)) * delta_wall);
			put_point_to_image(wolf3d->image_data, x, y, calculate_light(get_rgb_from_texture(col, row, wolf3d->textures[wolf3d->curr_cast.compas].image_data), wolf3d->curr_cast.distance));
		}
	}
}

void provider(t_wolf3d *wolf3d)
{
	float delta = FOV / CW;
	int wall;
	int col;

	for (int x = 0; x < CW; x++)
	{
		wolf3d->curr_cast.angle = wolf3d->player.angle - FOV_DIV_2 + delta * x;
		wolf3d->curr_cast.sin_a = sin(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.cos_a = cos(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.tan_a = tan(wolf3d->curr_cast.angle);


		cast(wolf3d);
		wall =  CW / wolf3d->curr_cast.distance / cos(wolf3d->curr_cast.angle - wolf3d->player.angle);

		if (!(get_tile(wolf3d->curr_cast.intersect_x + 0.01, wolf3d->curr_cast.intersect_y, wolf3d)) && cos(wolf3d->curr_cast.angle) < 0)
		{
			col = (int)((wolf3d->curr_cast.intersect_y - (int)(wolf3d->curr_cast.intersect_y)) * 32);
			wolf3d->curr_cast.compas = east;
		}
		else if (!(get_tile(wolf3d->curr_cast.intersect_x - 0.01, wolf3d->curr_cast.intersect_y, wolf3d)) && cos(wolf3d->curr_cast.angle) > 0)
		{
			col = (int)((wolf3d->curr_cast.intersect_y - (int)(wolf3d->curr_cast.intersect_y)) * 32);
			wolf3d->curr_cast.compas = west;
		}
		else if	(!(get_tile(wolf3d->curr_cast.intersect_x, wolf3d->curr_cast.intersect_y + 0.01, wolf3d)))
		{
			col = (int)((wolf3d->curr_cast.intersect_x - (int)(wolf3d->curr_cast.intersect_x)) * 32);
			wolf3d->curr_cast.compas = north;
		}
		else
		{
			col = (int)((wolf3d->curr_cast.intersect_x - (int)(wolf3d->curr_cast.intersect_x)) * 32);
			wolf3d->curr_cast.compas = south;
		}
		draw(wolf3d, x, wall, col);
	}
	mlx_put_image_to_window(wolf3d->mlx_ptr, wolf3d->win_ptr, wolf3d->image, 0, 0);
}

int nothing_happened(t_wolf3d *wolf3d)
{
	puts("lol");
	provider(wolf3d);
}

int main(int ac, char **av)
{

	t_wolf3d wolf3d;

	if (ac != 2)
		err_exit();

	wolf3d_init(&wolf3d, av[1]);


	provider(&wolf3d);


	mlx_hook(wolf3d.win_ptr, 2, 1L << 0, key_pressed, &wolf3d);
	//mlx_hook(wolf3d.win_ptr, 14, 1L << 0, nothing_happened, &wolf3d);
	//mlx_expose_hook(wolf3d.win_ptr, nothing_happened, &wolf3d);

	mlx_loop(wolf3d.mlx_ptr);

}