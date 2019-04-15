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
//# define TEX_SIZE 32
# define FOV M_PI/3
# define FOV_DIV_2 FOV / 2



typedef enum
{
	north,
	south,
	east,
	west
}		kompas;

typedef enum
{
	stone,
	grass,
	brick,
	metal,
	wood
}		textures;
/*
typedef struct s_wall_col
{
	int compas;
	int height;
	float angle;
	int type;
	float distance;
}			t_wall_col;
*/
typedef struct s_texture
{
	void *image;
	char *image_data;
	int len;
}				t_texture;

typedef struct s_door
{
	char *file_name;
	float pos_x;
	float pos_y;
	float angle;
}				t_door;

typedef struct s_ray_cast
{
	float intersect_x;
	float intersect_y;
	float angle;
	float sin_a;
	float cos_a;
	float tan_a;
	float distance;
	int type;
	int compas;
	float col;
}				t_ray_cast;

typedef struct s_player
{
	float pos_x;
	float pos_y;
	float angle;
}				t_player;

typedef struct s_wolf3d
{
	char file_name[24];

	t_player player;
	void *mlx_ptr;
	void *win_ptr;
	void *menu_win_ptr;
	t_texture menu;
	int tex_size;

	int walls_mode;
	int filtr;
	t_texture textures[10];
	t_texture skybox;
	t_texture image;
	int **map;
	int cols;
	int rows;

	int door;

	int hd;
	int light;
	t_texture minimap;

	t_ray_cast curr_cast;

	t_door doors[10];
	int menu_selected;

	int minimap_scale;
}				t_wolf3d;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
}				t_rgb;

void *shell_do(char *str);

void wolf3d_init(t_wolf3d *wolf3d, char *file_name);

void init_minimap(t_wolf3d *wolf3d);

void read_map_from_file(t_wolf3d *wolf3d, char *file_name);

void run_game(t_wolf3d *wolf3d);

void provider(t_wolf3d *wolf3d);

void	put_point_to_image(t_texture *image, int x, int y, t_rgb rgb);

t_rgb get_rgb_from_texture(float col, float row, t_texture *texture, t_wolf3d *wolf3d);
t_rgb calculate_light(t_rgb rbg, float distance);

void draw_minimap(t_wolf3d *wolf3d);

int key_pressed(int key, t_wolf3d *wolf3d);

int get_tile(float x, float y, t_wolf3d *wolf3d);

t_rgb color_to_rgb(int color);
int rgb_to_color(t_rgb rgb);

void err_exit(void);



void menu_init(t_wolf3d *wolf3d);
void menu_provider(t_wolf3d *wolf3d);


int exit_full(void);



double ft_atof(char *str);

#endif