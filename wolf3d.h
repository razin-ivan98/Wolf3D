/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:13:07 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 17:53:04 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include <pthread.h>
# include "get_next_line/get_next_line.h"

# define CW 640
# define CH  480
# define FOV M_PI/3
# define FOV_DIV_2 FOV / 2

typedef enum	e_kompas
{
	north,
	south,
	east,
	west
}				t_kompas;

typedef enum	e_textures
{
	stone,
	grass,
	brick,
	metal,
	wood
}				t_textures;

typedef	struct	s_biliear
{
	int			i1;
	int			i2;
	int			i3;
	int			i4;
	char		*ptr;
	int			x;
	int			y;
	int			c1;
	int			c2;
	int			c3;
	int			c4;
	double		u_ratio;
	double		v_ratio;
	double		u_opposite;
	double		v_opposite;
	int			result;
}				t_bilinear;

typedef struct	s_texture
{
	void		*image;
	char		*image_data;
	int			len;
}				t_texture;

typedef struct	s_door
{
	char		*file_name;
	float		pos_x;
	float		pos_y;
	float		angle;
}				t_door;

typedef struct	s_draw
{
	float		row;
	float		delta_wall;
	float		floor_dist;
	float		floor_x;
	float		floor_y;
	float		cos_ang_minus_pl;
	float		f_col;
	float		f_row;
	int			type;
	int			ch_div_2;
	int			wall_div_2;
	int			y;
}				t_draw;

typedef struct	s_cast
{
	float		new_x;
	float		new_y;
	float		distance;
	int			type;
	int			compas;
	float		d;
}				t_cast;

typedef struct	s_ray_cast
{
	float		intersect_x;
	float		intersect_y;
	float		angle;
	float		sin_a;
	float		cos_a;
	float		tan_a;
	float		distance;
	int			type;
	int			compas;
	float		col;
}				t_ray_cast;

typedef struct	s_player
{
	float		pos_x;
	float		pos_y;
	float		angle;
}				t_player;

typedef struct	s_wolf3d
{
	char		file_name[24];

	t_player	player;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*menu_win_ptr;
	t_texture	menu;
	int			tex_size;

	int			walls_mode;
	int			filtr;
	t_texture	textures[10];
	t_texture	skybox;
	t_texture	image;
	int			**map;
	int			cols;
	int			rows;

	int			door;
	int			hd;
	int			light;
	t_texture	minimap;

	t_ray_cast	curr_cast;

	t_door		doors[10];
	int			menu_selected;

	int			minimap_scale;
	char		*line;
	int			step;
}				t_wolf3d;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

void			cast(t_wolf3d *wolf3d);

void			wolf3d_init(t_wolf3d *wolf3d, char *file_name);

void			init_minimap(t_wolf3d *wolf3d);

void			read_map_from_file(t_wolf3d *wolf3d, char *file_name);
void			parse_string(t_wolf3d *wolf3d, char *line, int row);
void			allocate_arr(t_wolf3d *wolf3d);

void			run_game(t_wolf3d *wolf3d);

void			provider(t_wolf3d *wolf3d);

void			put_point_to_image(t_texture *image, int x, int y, t_rgb rgb);

t_rgb			get_rgb_from_texture(float col, float row,
					t_texture *texture, t_wolf3d *wolf3d);
t_texture		*get_true_texture(t_wolf3d *wolf3d, int type);
t_rgb			calculate_light(t_rgb rbg, float distance);

void			draw(t_wolf3d *wolf3d, int x, int wall, float col);
void			draw_minimap(t_wolf3d *wolf3d);

int				key_pressed(int key, t_wolf3d *wolf3d);
int				key_released(int key, t_wolf3d *wolf3d);

int				get_tile(float x, float y, t_wolf3d *wolf3d);

t_rgb			color_to_rgb(int color);
int				rgb_to_color(t_rgb rgb);

void			err_exit(t_wolf3d *wolf3d);
void			free_map(t_wolf3d *wolf3d);

void			menu_init(t_wolf3d *wolf3d);
void			menu_provider(t_wolf3d *wolf3d);

int				exit_full(t_wolf3d *wolf3d);

double			ft_atof(char *str);

#endif
