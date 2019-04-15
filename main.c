#include "wolf3d.h"

void cast_x(t_wolf3d *wolf3d)
{
	float new_x;
	float new_y;
	float distance;
	int type;
	int compas;

	//new_x = (wolf3d->curr_cast.cos_a > 0) ? floor(wolf3d->player.pos_x) : floor(wolf3d->player.pos_x) + 1;
	//new_y = wolf3d->player.pos_y + (new_x - wolf3d->player.pos_x) * wolf3d->curr_cast.tan_a;
	float dy =  wolf3d->curr_cast.tan_a;
	new_x = floor(wolf3d->player.pos_x) + (wolf3d->curr_cast.cos_a > 0.0 ? 1.0 : 0.0);
	new_y = wolf3d->player.pos_y + (new_x - wolf3d->player.pos_x) * /*(wolf3d->curr_cast.cos_a > 0.0 ? 1.0 : (1.0)) */ dy;

	///
	if (wolf3d->curr_cast.cos_a > 0)
	{

		while (new_x > 0.0 && new_y > 0.0 && new_y < (float)wolf3d->rows && new_x < (float)wolf3d->cols)
		{
			//puts("1");
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
			//puts("2");
			if ((type = get_tile(new_x - 0.001, new_y, wolf3d)) > 0)
				break ;
			new_x -= 1.0;
			new_y = new_y - dy;
		}
		//distance = sqrt(((double)new_x - wolf3d->player.pos_x) * ((double)new_x - wolf3d->player.pos_x) + ((double)new_y - wolf3d->player.pos_y)*((double)new_y - wolf3d->player.pos_y));
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

	//new_y = (wolf3d->curr_cast.sin_a > 0) ? floor(wolf3d->player.pos_y) : floor(wolf3d->player.pos_y) + 1;
	//new_x = wolf3d->player.pos_x + (new_y - wolf3d->player.pos_y) / wolf3d->curr_cast.tan_a;


	float dx =  1.0 / wolf3d->curr_cast.tan_a;
	
	new_y = floor(wolf3d->player.pos_y) + (wolf3d->curr_cast.sin_a > 0.0 ? 1.0 : 0.0);
	new_x = wolf3d->player.pos_x + (new_y - wolf3d->player.pos_y) * /*((wolf3d->curr_cast.sin_a > 0.0) ? 1.0 : -1.0)*/ dx;

	//
	if (wolf3d->curr_cast.sin_a > 0)
	{
		while (new_x > 0.0 && new_y > 0.0 && new_y < (float)wolf3d->rows && new_x < (float)wolf3d->cols)
		{
			//puts("3");
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
			//puts("4");
			if ((type = get_tile(new_x, new_y - 0.001, wolf3d)) > 0)
				break ;
			new_y -= 1.0;
			new_x = new_x - dx;
			//printf("new_x = %f\n", new_x);
		}
		//distance = sqrt(((double)new_x - wolf3d->player.pos_x) * ((double)new_x - wolf3d->player.pos_x) + ((double)new_y - wolf3d->player.pos_y)*((double)new_y - wolf3d->player.pos_y));
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
	//float dist_x;
	//float dist_y;

	float new_x;
	float new_y;

	float dist_x;
	float dist_y;
	
	wolf3d->curr_cast.distance = 9999.9;


	if (wolf3d->curr_cast.cos_a != 0)
		cast_x(wolf3d);
	if (wolf3d->curr_cast.sin_a != 0)
		cast_y(wolf3d);

	//wolf3d->curr_cast.distance = dist_x < dist_y ? dist_x : dist_y;



/*
	float sin_a = sin(wolf3d->curr_cast.angle);
	float cos_a = cos(wolf3d->curr_cast.angle);

	wolf3d->curr_cast.intersect_x = wolf3d->player.pos_x;
	wolf3d->curr_cast.intersect_y = wolf3d->player.pos_y;
	wolf3d->curr_cast.distance = 0.0;


	while ((wolf3d->curr_cast.type = get_tile(wolf3d->curr_cast.intersect_x, wolf3d->curr_cast.intersect_y, wolf3d)) <= 0)
	{
		wolf3d->curr_cast.intersect_x = wolf3d->player.pos_x + wolf3d->curr_cast.distance*cos_a;
		wolf3d->curr_cast.intersect_y = wolf3d->player.pos_y + wolf3d->curr_cast.distance*sin_a;
		wolf3d->curr_cast.distance += 0.01;
	}
	*/
	
	
	/*
	
	
	float dist_x = 9999.0;
	float dist_y = 9999.0;

	float int_x_x = 0.0;
	float int_y_x = 0.0;

	float int_x_y = 0.0;
	float int_y_y = 0.0;

	float dy;
	float dx;

	if (wolf3d->curr_cast.cos_a != 0.0)
	{
		dy =  wolf3d->curr_cast.tan_a;
		int_x_x = floor(wolf3d->player.pos_x) + (wolf3d->curr_cast.cos_a > 0 ? 1.0 : 0.0);
		int_y_x = wolf3d->player.pos_y + (int_x_x - wolf3d->player.pos_x) * (wolf3d->curr_cast.cos_a > 0 ? 1 : -1) * dy;
		while (wolf3d->curr_cast.type = get_tile(int_x_x, int_y_x, wolf3d) <= 0 && int_x_x > 0.0 && int_x_x < (float)wolf3d->cols && int_y_x > 0.0 && int_y_x < (float)wolf3d->rows)
		{
			int_x_x += (wolf3d->curr_cast.cos_a > 0 ? 1.0 : -1.0);
			int_y_x += dy;
		}
		dist_x = sqrt(pow((wolf3d->player.pos_x - int_x_x), 2) + pow((wolf3d->player.pos_y - int_y_x), 2));
	}
	if (wolf3d->curr_cast.sin_a != 0.0)
	{
		dx =  1 / wolf3d->curr_cast.tan_a;
		int_y_y = floor(wolf3d->player.pos_y) + (wolf3d->curr_cast.sin_a > 0 ? 1.0 : 0.0);
		int_x_y = wolf3d->player.pos_x + (int_y_y - wolf3d->player.pos_y) * (wolf3d->curr_cast.sin_a > 0 ? 1 : -1) * dx;
		while (wolf3d->curr_cast.type = get_tile(int_x_y, int_y_y, wolf3d) <= 0 && int_x_y > 0.0 && int_x_y < (float)wolf3d->cols && int_y_y > 0.0 && int_y_y < (float)wolf3d->rows)
		{
			int_y_y += (wolf3d->curr_cast.sin_a > 0 ? 1.0 : -1.0);
			int_x_y += dx;
		}
		dist_x = sqrt(pow((wolf3d->player.pos_x - int_x_y), 2) + pow((wolf3d->player.pos_y - int_y_y), 2));
	}

	if (dist_x < dist_y)
	{
		wolf3d->curr_cast.intersect_x = int_x_x;
		wolf3d->curr_cast.intersect_y = int_y_x;
		wolf3d->curr_cast.distance = dist_x;
	}
	else
	{
		wolf3d->curr_cast.intersect_x = int_x_y;
		wolf3d->curr_cast.intersect_y = int_y_y;
		wolf3d->curr_cast.distance = dist_y;
	}*/
/*
	if (wolf3d->curr_cast.intersect_x > (double)wolf3d->cols || wolf3d->curr_cast.intersect_x < 0.0 || wolf3d->curr_cast.intersect_y > (double)wolf3d->rows || wolf3d->curr_cast.intersect_y < 0.0)
	{
		printf("x %f\n", wolf3d->curr_cast.intersect_x);
		printf("y %f\n\n", wolf3d->curr_cast.intersect_y);
		exit(-2);
	}
*/
}

t_texture *get_true_texture(t_wolf3d *wolf3d)
{
	if (wolf3d->walls_mode && wolf3d->curr_cast.type > 0 && wolf3d->curr_cast.type < 9)
		return (&wolf3d->textures[wolf3d->curr_cast.compas]);
	else if (!wolf3d->walls_mode && wolf3d->curr_cast.type > 0 && wolf3d->curr_cast.type < 9)
		return (&wolf3d->textures[wolf3d->curr_cast.type - 1]);
	else if (wolf3d->curr_cast.type < 0)
	{
		return (&wolf3d->textures[-wolf3d->curr_cast.type - 1]);
	}
	else if (wolf3d->curr_cast.type > 8)
		return (&wolf3d->textures[9]);
	
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

	for (int y = 0; y < CH; y++)
	{
		if ((y >= CH_div_2 + wall_div_2 && y < CH) || (y >= 0 && y <= CH_div_2 - wall_div_2))
		{
			if (y < CH_div_2)
			{
				floor_dist = CW / (2.0 * (CH - y) - CH) / cos_ang_minus_pl;

				floor_x = wolf3d->player.pos_x + floor_dist * wolf3d->curr_cast.cos_a;
				floor_y = wolf3d->player.pos_y + floor_dist * wolf3d->curr_cast.sin_a;

				if (get_tile(floor_x, floor_y, wolf3d) == 0)
				{
					f_col = (wolf3d->curr_cast.angle / (2 * M_PI) * 960);

					if (f_col < 0)
						f_col = 960 + f_col;
					f_row = ((float)y / (float)(CH_div_2) * 100);
					put_point_to_image(&wolf3d->image, x, y, get_rgb_from_texture(f_col, f_row, &(wolf3d->skybox), wolf3d));//sky
				}
				else
				{

					f_col = ((floor_x - (int)(floor_x)) * wolf3d->tex_size);
					f_row = ((floor_y - (int)(floor_y)) * wolf3d->tex_size);
				/*	if (f_col < 0)
						f_col = -f_col;
					if (f_row < 0)
						f_row = -f_row;*/
					
					if (wolf3d->light)
						put_point_to_image(&wolf3d->image, x, y, calculate_light(get_rgb_from_texture(f_col, f_row, &(wolf3d->textures[wood]), wolf3d), floor_dist));//seiling
					else
						put_point_to_image(&wolf3d->image, x, y, get_rgb_from_texture(f_col, f_row, &(wolf3d->textures[wood]), wolf3d));
				}

			}
			else
			{
				floor_dist = CW / (2.0 * y - CH) / cos_ang_minus_pl;

				floor_x = wolf3d->player.pos_x + floor_dist * wolf3d->curr_cast.cos_a;
				floor_y = wolf3d->player.pos_y + floor_dist * wolf3d->curr_cast.sin_a;

				f_col = ((floor_x - (int)(floor_x)) * wolf3d->tex_size);
				f_row = ((floor_y - (int)(floor_y)) * wolf3d->tex_size);

			/*	if (f_col < 0)
						f_col = -f_col;
				if (f_row < 0)
						f_row = -f_row;
*/
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
				put_point_to_image(&wolf3d->image, x, y, get_rgb_from_texture(col, row, get_true_texture(wolf3d), wolf3d));
			else
				put_point_to_image(&wolf3d->image, x, y, calculate_light(get_rgb_from_texture(col, row, get_true_texture(wolf3d), wolf3d), wolf3d->curr_cast.distance));

		}
	}
}

void provider(t_wolf3d *wolf3d)
{

	int wall;
	//float col;

	float delta = FOV / CW;

	for (int x = 0; x < CW; x++)
	{
		wolf3d->curr_cast.angle = wolf3d->player.angle - FOV_DIV_2 + delta * x;
		wolf3d->curr_cast.sin_a = sin(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.cos_a = cos(wolf3d->curr_cast.angle);
		wolf3d->curr_cast.tan_a = tan(wolf3d->curr_cast.angle);


		cast(wolf3d);
		wall =  CW / wolf3d->curr_cast.distance / cos(wolf3d->curr_cast.angle - wolf3d->player.angle);
/*
		if ((get_tile(wolf3d->curr_cast.intersect_x + 0.02, wolf3d->curr_cast.intersect_y, wolf3d) <= 0) && cos(wolf3d->curr_cast.angle) < 0)
		{
			col = ((wolf3d->curr_cast.intersect_y - floor(wolf3d->curr_cast.intersect_y)) * wolf3d->tex_size);
			wolf3d->curr_cast.compas = east;
		}
		else if ((get_tile(wolf3d->curr_cast.intersect_x - 0.02, wolf3d->curr_cast.intersect_y, wolf3d) <= 0) && cos(wolf3d->curr_cast.angle) > 0)
		{
			col = ((wolf3d->curr_cast.intersect_y - floor(wolf3d->curr_cast.intersect_y)) * wolf3d->tex_size);
			wolf3d->curr_cast.compas = west;
		}
		else if	((get_tile(wolf3d->curr_cast.intersect_x, wolf3d->curr_cast.intersect_y + 0.02, wolf3d) <= 0))
		{
			col = ((wolf3d->curr_cast.intersect_x - floor(wolf3d->curr_cast.intersect_x)) * wolf3d->tex_size);
			wolf3d->curr_cast.compas = north;
		}
		else
		{
			col = ((wolf3d->curr_cast.intersect_x - floor(wolf3d->curr_cast.intersect_x)) * wolf3d->tex_size);
			wolf3d->curr_cast.compas = south;
		}*/
		/*if (col < 0)
			col = -col;*/
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
	mlx_hook(wolf3d->win_ptr, 17, 1L << 0, exit_full, NULL);
	mlx_loop(wolf3d->mlx_ptr);



}

int main(int ac, char **av)
{
	t_wolf3d wolf3d;

	if (ac != 2)
		err_exit();


	wolf3d.mlx_ptr = mlx_init();
	ft_strcpy(wolf3d.file_name, av[1]);
	menu_init(&wolf3d);




}