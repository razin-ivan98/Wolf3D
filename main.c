#include "wolf3d.h"

float cast(t_wolf3d *wolf3d, float angle, float *new_x, float *new_y, int *type)
{
	float x = wolf3d->player.pos_x;
	float y = wolf3d->player.pos_y;
	float distance = 0.0;
	int  ptr_type;

	float sin_a = sin(angle);
	float cos_a = cos(angle);

	while (!(ptr_type = get_tile(x, y, wolf3d)))
	{
		x = wolf3d->player.pos_x + distance*cos_a;
		y = wolf3d->player.pos_y + distance*sin_a;
		distance += 0.01;
	}
	*new_x = x;
	*new_y = y;
	*type = ptr_type;
	return(distance);
}

void draw(t_wolf3d *wolf3d, int x, int wall, int col, int type, int compas, float distance, float angle)
{
	int row;
	float delta_wall, floor_dist;
	delta_wall = 32.0 / wall;

	float floor_x;
	float floor_y;

	float cos_ang_minus_pl = cos(angle - wolf3d->player.angle);
	float sin_ang = sin(angle);
	float cos_ang = cos(angle);

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

				floor_x = wolf3d->player.pos_x + floor_dist * cos_ang;
				floor_y = wolf3d->player.pos_y + floor_dist * sin_ang;

				f_col = (int)((floor_x - floor(floor_x)) * 32.0);
				f_row = (int)((floor_y - floor(floor_y)) * 32.0);
				put_point_to_image(wolf3d->image_data, x, y, rgb_to_color(calculate_light(get_rgb_from_texture(f_col, f_row, wolf3d->textures[wood].image_data), floor_dist)));//seiling
			}
			else
			{
				floor_dist = CW / (2.0 * y - CH) / cos_ang_minus_pl;

				floor_x = wolf3d->player.pos_x + floor_dist * cos_ang;
				floor_y = wolf3d->player.pos_y + floor_dist * sin_ang;

				f_col = (int)((floor_x - floor(floor_x)) * 32.0);
				f_row = (int)((floor_y - floor(floor_y)) * 32.0);
				put_point_to_image(wolf3d->image_data, x, y, rgb_to_color(calculate_light(get_rgb_from_texture(f_col, f_row, wolf3d->textures[wood].image_data), floor_dist)));//floor
			}
		}
		else if (y > CH_div_2 - wall_div_2 && y <= CH_div_2 + wall_div_2)
		{
			row = (int)((y - (CH_div_2 - wall_div_2)) * delta_wall);
			put_point_to_image(wolf3d->image_data, x, y, rgb_to_color(calculate_light(get_rgb_from_texture(col, row, wolf3d->textures[compas].image_data), distance)));
		}
	}
} 

void provider(t_wolf3d *wolf3d)
{
	float delta = FOV / CW;
	float new_x;
	float new_y;
	int type;
	int compas;
	

	for (int x = 0; x < CW; x++)
	{
		float angle = wolf3d->player.angle - FOV_DIV_2 + delta * (float)x;
		float distance = cast(wolf3d, angle, &new_x, &new_y, &type);
		
		int wall =  CW / distance / cos(angle - wolf3d->player.angle);

		int col;

		if (!get_tile(new_x + 0.01, new_y, wolf3d) && cos(angle) < 0)
		{
			col = (int)((new_y - floor(new_y)) * 32);
			compas = east;
		}
		else if (!get_tile(new_x - 0.01, new_y, wolf3d) && cos(angle) > 0)
		{
			col = (int)((new_y - floor(new_y)) * 32);
			compas = west;
		}
		else if	(!get_tile(new_x, new_y + 0.01, wolf3d))
		{
			col = (int)((new_x - floor(new_x)) * 32);
			compas = north;
		}
		else 
		{
			col = (int)((new_x - floor(new_x)) * 32);
			compas = south;
		}
		draw(wolf3d, x, wall, col, type, compas, distance, angle);
	}	
	mlx_put_image_to_window(wolf3d->mlx_ptr, wolf3d->win_ptr, wolf3d->image, 0, 0);
}



int main(int ac, char **av)
{

	t_wolf3d wolf3d;

	if (ac != 2)
		err_exit();

	wolf3d_init(&wolf3d, av[1]);


	provider(&wolf3d);


	mlx_hook(wolf3d.win_ptr, 2, 1L << 0, key_pressed, &wolf3d);

	mlx_loop(wolf3d.mlx_ptr);

}