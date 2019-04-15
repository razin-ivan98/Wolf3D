#include "wolf3d.h"

void parse_string(t_wolf3d *wolf3d, char *line, int row)
{
	int col;

	char *ptr;

	ptr = line;
	col = 0;
	while (col < wolf3d->cols)
	{
		wolf3d->map[col][row] = atoi(ptr);
		if (col < wolf3d->cols - 1)
			ptr = strchr(ptr, ' ');
		while (*ptr == ' ')
			ptr++;
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
	int i;
	int ret;

	fd = open(file_name, O_RDONLY);
	//	err_exit();
	get_next_line(fd, &line);///////check
	wolf3d->cols = ft_atoi(line);
	free (line);

	get_next_line(fd, &line);///////check
	wolf3d->rows = ft_atoi(line);
	free (line);

	allocate_arr(wolf3d);

	get_next_line(fd, &line);//// пустая строка
	free (line);

	int row = 0;
	while (row < wolf3d->rows)
	{
		get_next_line(fd, &line);
		puts(line);
		parse_string(wolf3d, line, row);
		free(line);
		row++;
	}

	get_next_line(fd, &line);//// пустая строка
	free (line);

	char *ptr;

	i = 0;
	while (get_next_line(fd, &line))////check
	{
		//wolf3d->doors[i].file_name = malloc(56);
		ft_strcpy((wolf3d->doors[i].file_name), line);
		*ft_strchr(wolf3d->doors[i].file_name, ' ') = 0;

		ptr = ft_strchr(line, ' ');
		while (*ptr == ' ')
			ptr++;
		wolf3d->doors[i].pos_x = (float)ft_atoi(ptr) + 0.5;

		ptr = ft_strchr(ptr, ' ');
		while (*ptr == ' ')
			ptr++;
		wolf3d->doors[i].pos_y = (float)ft_atoi(ptr) + 0.5;


		printf("\nx = %f\n", wolf3d->doors[i].pos_x);
		printf("y = %f\n", wolf3d->doors[i].pos_y);

		free (line);
		i++;
	}

	i = 0;
	while (i < 10)
	{
		puts(wolf3d->doors[i].file_name);
		i++;
	}

	close (fd);
/*
	for (int i = 0; i < wolf3d->rows; i++)
	{
		for (int j = 0; j < wolf3d->cols; j++)
		{
			printf("%d\t", wolf3d->map[j][i]);
		}
		printf("\n");
	}*/

}
