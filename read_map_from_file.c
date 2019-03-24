#include "wolf3d.h"

void parse_string(t_wolf3d *wolf3d, char *line, int row)
{
	int col;

	char *ptr;

	ptr = line;
	col = 0;
	while (col < wolf3d->cols)
	{
		wolf3d->map[col][row] = atoi(ptr);//////forbidden funtion
		ptr = strchr(ptr, ' ') + 1;
		col++;
	}
}

void allocate_arr(t_wolf3d *wolf3d)
{
	int i;

	i = 0;
	wolf3d->map = (int **)malloc(sizeof(int *) * wolf3d->cols);///////check

	while (i < wolf3d->cols)
	{
		wolf3d->map[i] = (int *)malloc(sizeof(int) * wolf3d->rows);///////check
		i++;
	}
}

void read_map_from_file(t_wolf3d *wolf3d, char *file_name)
{
	int fd;
	char *line;

	fd = open(file_name, O_RDONLY);
	//	err_exit();
	get_next_line(fd, &line);///////check
	wolf3d->cols = atoi(line);//////forbidden funtion
	free (line);

	get_next_line(fd, &line);///////check
	wolf3d->rows = atoi(line);//////forbidden funtion
	free (line);

	allocate_arr(wolf3d);

	get_next_line(fd, &line);//// пустая строка
	free (line);

	int row = 0;
	while (row < wolf3d->rows)
	{
		get_next_line(fd, &line);
		parse_string(wolf3d, line, row);
		free(line);
		row++;
	}
	close (fd);
}
