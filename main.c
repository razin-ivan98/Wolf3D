#include "wolf3d.h"

void cast_x(t_wolf3d *wolf3d)
{
	float new_x;
	float new_y;
	float distance;
	int type;
	int compas;

	float dy =  wolf3d->curr_cast.tan_a;
	new_x = floor(wolf3d->player.pos_x) + (wolf3d->curr_cast.cos_a > 0.0 ? 1.0 : 0.0);
	new_y = wolf3d->player.pos_y + (new_x - wolf3d->player.pos_x) * dy;

	if (wolf3d->curr_cast.cos_a > 0)
	{

		while (new_x > 0.0 && new_y > 0.0 && new_y < (float)wolf3d->rows && new_x < (float)wolf3d->cols)
		{
			if ((type = get_tile(new_x + 0.001, new_y, wolf3d)) > 0)
				break ;
			new_x += 1.0;
			new_y = new_y + dy;
		}
		distance = sqrt(pow((wolf3d->player.pos_x - new_x), 2) + pow((wolf3d->player.pos_y - new_y), 2));
		compas = east;
	}
	else
	{
		while (new_x > 0.0 && new_y > 0.0 && new_y < (float)wolf3d->rows && new_x < (float)wolf3d->cols)
		{
			if ((type = get_tile(new_x - 0.001, new_y, wolf3d)) > 0)
				break ;
			new_x -= 1.0;
			new_y = new_y - dy;
		}

		distance = sqrt(pow((wolf3d->player.pos_x - new_x), 2) + pow((wolf3d->player.pos_y - new_y), 2));
		compas = west;
	}
	wolf3d->curr_cast.col = ((new_y - floor(new_y)) * wolf3d->tex_size);
	wolf3d->curr_cast.compas = compas;
	wolf3d->curr_cast.intersect_x = new_x;
	wolf3d->curr_cast.intersect_y = new_y;
	wolf3d->curr_cast.distance = distance;
	wolf3d->curr_cast.type = type;
}

void cast_y(t_wolf3d *wolf3d)
{
	float new_x;
	float new_y;
	float distance;
	int type;
	int compas;

	float dx =  1.0 / wolf3d->curr_cast.tan_a;
	
	new_y = floor(wolf3d->player.pos_y) + (wolf3d->curr_cast.sin_a > 0.0 ? 1.0 : 0.0);
	new_x = wolf3d->player.pos_x + (new_y - wolf3d->player.pos_y) * dx;

	if (wolf3d->curr_cast.sin_a > 0)
	{
		while (new_x > 0.0 && new_y > 0.0 && new_y < (float)wolf3d->rows && new_x < (float)wolf3d->cols)
		{
			if ((type = get_tile(new_x, new_y + 0.001, wolf3d)) > 0)
				break ;
			new_y += 1.0;
			new_x = new_x + dx;
		}
		distance = sqrt(pow((wolf3d->player.pos_x - new_x), 2) + pow((wolf3d->player.pos_y - new_y), 2));
		compas = south;
	}
	else
	{
		while (new_x > 0.0 && new_y > 0.0 && new_y < (float)wolf3d->rows && new_x < (float)wolf3d->cols)
		{
			if ((type = get_tile(new_x, new_y - 0.001, wolf3d)) > 0)
				break ;
			new_y -= 1.0;
			new_x = new_x - dx;
		}
		distance = sqrt(pow((wolf3d->player.pos_x - new_x), 2) + pow((wolf3d->player.pos_y - new_y), 2));
		compas = north;
	}

	if (distance < wolf3d->curr_cast.distance)
	{
		wolf3d->curr_cast.col = ((new_x - floor(new_x)) * wolf3d->tex_size);
		wolf3d->curr_cast.compas = compas;
		wolf3d->curr_cast.intersect_x = new_x;
		wolf3d->curr_cast.intersect_y = new_y;
		wolf3d->curr_cast.distance = distance;
		wolf3d->curr_cast.type = type;
	}

}

void cast(t_wolf3d *wolf3d)
{
	float new_x;
	float new_y;

	float dist_x;
	float dist_y;
	
	wolf3d->curr_cast.distance = 9999.9;


	if (wolf3d->curr_cast.cos_a != 0)
		cast_x(wolf3d);
	if (wolf3d->curr_cast.sin_a != 0)
		cast_y(wolf3d);
}

t_texture *get_true_texture(t_wolf3d *wolf3d, int type)
{
	if (!type)
		type = wolf3d->curr_cast.type;
	if (wolf3d->walls_mode && type > 0 && type < 9)
		return (&wolf3d->textures[wolf3d->curr_cast.compas]);
	else if (!wolf3d->walls_mode && type > 0 && type < 9)
		return (&wolf3d->textures[type - 1]);
	else if (type < 0)
		return (&wolf3d->textures[-type - 1]);
	else if (type > 8)
		return (&wolf3d->textures[9]);
	return (NULL);
}


void draw(t_wolf3d *wolf3d, int x, int wall, float col)
{
	float row;
	float delta_wall, floor_dist;
	delta_wall = (float)wolf3d->tex_size / wall;

	float floor_x;
	float floor_y;

	float cos_ang_minus_pl = cos(wolf3d->curr_cast.angle - wolf3d->player.angle);

	int CH_div_2 = CH / 2;
	int wall_div_2 = wall / 2;

	float f_col;
	float f_row;

	int type;

	for (int y = 0; y < CH; y++)
	{
		if ((y >= CH_div_2 + wall_div_2 && y < CH) || (y >= 0 && y <= CH_div_2 - wall_div_2))
		{
			if (y < CH_div_2)
			{
				floor_dist = CW / (2.0 * (CH - y) - CH) / cos_ang_minus_pl;

				floor_x = wolf3d->player.pos_x + floor_dist * wolf3d->curr_cast.cos_a;
				floor_y = wolf3d->player.pos_y + floor_dist * wolf3d->curr_cast.sin_a;

				if ((type = get_tile(floor_x, floor_y, wolf3d)) == 0)
				{
					f_col = (wolf3d->curr_cast.angle / (2 * M_PI) * 960);

					if (f_col < 0.0)
						f_col = 960.0 * (-floor(wolf3d->curr_cast.angle / 2 / M_PI)) + f_col;
					if (f_col > 960.0)
						f_col = f_col - 960.0 * floor(wolf3d->curr_cast.angle / 2 / M_PI);
					f_row = ((float)y / (float)(CH_div_2) * 100);
					put_point_to_image(&wolf3d->image, x, y, get_rgb_from_texture(f_col, f_row, &(wolf3d->skybox), wolf3d));//sky
				}
				else
				{

					f_col = ((floor_x - (int)(floor_x)) * wolf3d->tex_size);
					f_row = ((floor_y - (int)(floor_y)) * wolf3d->tex_size);
					if (wolf3d->light)
						put_point_to_image(&wolf3d->image, x, y, calculate_light(get_rgb_from_texture(f_col, f_row, get_true_texture(wolf3d, type), wolf3d), floor_dist));//seiling
					else
						put_point_to_image(&wolf3d->image, x, y, get_rgb_from_texture(f_col, f_row, get_true_texture(wolf3d, type), wolf3d));
				}

			}
			else
			{
				floor_dist = CW / (2.0 * y - CH) / cos_ang_minus_pl;

				floor_x = wolf3d->player.pos_x + floor_dist * wolf3d->curr_cast.cos_a;
				floor_y = wolf3d->player.pos_y + floor_dist * wolf3d->curr_cast.sin_a;

				f_col = ((floor_x - (int)(floor_x)) * wolf3d->tex_size);
				f_row = ((floor_y - (int)(floor_y)) * wolf3d->tex_size);

				if (get_tile(floor_x, floor_y, wolf3d) != 0 && wolf3d->light)
					put_point_to_image(&wolf3d->image, x, y, calculate_light(get_rgb_from_texture(f_col, f_row, &(wolf3d->textures[wood]), wolf3d), floor_dist));//floor
				else
					put_point_to_image(&wolf3d->image, x, y, get_rgb_from_texture(f_col, f_row, &(wolf3d->textures[wood]), wolf3d));//floor

			}
		}
		else if (y > CH_div_2 - wall_div_2 && y <= CH_div_2 + wall_div_2)
		{
			row = ((y - (CH_div_2 - wall_div_2)) * delta_wall);
			if (!wolf3d->light ||
				get_tile(wolf3d->curr_cast.intersect_x + 0.2, wolf3d->curr_cast.intersect_y, wolf3d) == 0 ||
				get_tile(wolf3d->curr_cast.intersect_x - 0.2, wolf3d->curr_cast.intersect_y, wolf3d) == 0 ||
				get_tile(wolf3d->curr_cast.intersect_x, wolf3d->curr_cast.intersect_y + 0.2, wolf3d) == 0 ||
				get_tile(wolf3d->curr_cast.intersect_x, wolf3d->curr_cast.intersect_y - 0.2, wolf3d) == 0)
				put_point_to_image(&wolf3d->image, x, y, get_rgb_from_texture(col, row, get_true_texture(wolf3d, 0), wolf3d));
			else
				put_point_to_image(&wolf3d->image, x, y, calculate_light(get_rgb_from_texture(col, row, get_true_texture(wolf3d, 0), wolf3d), wolf3d->curr_cast.distance));

		}
	}
}

void provider(t_wolf3d *wolf3d)
{

	int wall;

	float delta = FOV / CW;

	for (int x = 0; x < CW; x++)
	{
		wolf3d->curr_cast.angle = wolf3d->player.angle - FOV_DIV_2 + delta * x;
		wolf3d->curr_cast.sin_a = sin(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.cos_a = cos(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.tan_a = tan(wolf3d->curr_cast.angle);


		cast(wolf3d);
		wall =  CW / wolf3d->curr_cast.distance / cos(wolf3d->curr_cast.angle - wolf3d->player.angle);
		draw(wolf3d, x, wall, wolf3d->curr_cast.col);
	}
	mlx_put_image_to_window(wolf3d->mlx_ptr, wolf3d->win_ptr, wolf3d->image.image, 0, 0);

	draw_minimap(wolf3d);
	if (wolf3d->door)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->win_ptr, CW / 2 - 20, CH / 2, 0xFFFF00, "Press F");
}

void run_game(t_wolf3d *wolf3d)
{
	wolf3d_init(wolf3d, wolf3d->file_name);


	provider(wolf3d);


	mlx_hook(wolf3d->win_ptr, 2, 1L << 0, key_pressed, wolf3d);
	mlx_hook(wolf3d->win_ptr, 17, 1L << 0, exit_full, wolf3d);
	mlx_loop(wolf3d->mlx_ptr);



}

void null_all(t_wolf3d *wolf3d)
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

int main(int ac, char **av)
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