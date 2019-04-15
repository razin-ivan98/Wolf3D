#include "wolf3d.h"


void parse_string(t_wolf3d *wolf3d, char *line, int row)
{
	int col;

	char *ptr;

	ptr = line;
	col = 0;
	while (col < wolf3d->cols)
	{
		wolf3d->map[col][row] = ft_atoi(ptr);
		if (!((wolf3d->map[col][row] >= -1 && wolf3d->map[col][row] <= 5) || (wolf3d->map[col][row] >= 91 && wolf3d->map[col][row] <= 99)  ))
			err_exit(wolf3d);
		if ((col == 0 || col == wolf3d->cols - 1 || row == 0 || row == wolf3d->rows - 1) && wolf3d->map[col][row] <= 0)
			err_exit(wolf3d);
		if (ft_strchr(ptr, ' '))
			ptr = ft_strchr(ptr, ' ');
		while (*ptr == ' ')
			ptr++;
		col++;
	}
}

void allocate_arr(t_wolf3d *wolf3d)
{
	int i;

	i = 0;
	wolf3d->map = (int **)ft_memalloc(sizeof(int *) * wolf3d->cols);
	if (!wolf3d->map)
		err_exit(wolf3d);
	while (i < wolf3d->cols)
	{
		wolf3d->map[i] = (int *)ft_memalloc(sizeof(int) * wolf3d->rows);
		if (!wolf3d->map[i])
			err_exit(wolf3d);
		i++;
	}
}

void read_map_from_file(t_wolf3d *wolf3d, char *file_name)
{
	int fd;
	int i;
	int ret;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		err_exit(wolf3d);
	if ((get_next_line(fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	if ((wolf3d->cols = ft_atoi(wolf3d->line)) < 3)
		err_exit(wolf3d);
	ft_strdel(&wolf3d->line);

	if ((get_next_line(fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	if ((wolf3d->rows = ft_atoi(wolf3d->line)) < 3)
		err_exit(wolf3d);

	if ((get_next_line(fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	ft_strdel(&wolf3d->line);

	allocate_arr(wolf3d);

	int row = 0;
	while (row < wolf3d->rows)
	{
		if ((get_next_line(fd, &wolf3d->line)) < 0)
			err_exit(wolf3d);
		//puts(wolf3d->line);
		parse_string(wolf3d, wolf3d->line, row);////////////////////
		ft_strdel(&wolf3d->line);

		row++;
	}

	if ((get_next_line(fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	ft_strdel(&wolf3d->line);


	char *ptr;

	i = 0;
	while (1)
	{
		if ((ret = get_next_line(fd, &wolf3d->line)) < 0)
			err_exit(wolf3d);
		if (!ret)
			break ;
		ft_strcpy((wolf3d->doors[i].file_name), wolf3d->line);
		if (!(ptr = ft_strchr(wolf3d->doors[i].file_name, ' ')))
			err_exit(wolf3d);

		*ptr = 0;
		if (!(ptr = ft_strchr(wolf3d->line, ' ')))
			err_exit(wolf3d);
		while (*ptr == ' ')
			ptr++;
		if ((wolf3d->doors[i].pos_x = (float)ft_atoi(ptr) + 0.5) < 1.5)
			err_exit(wolf3d);

		if (!(ptr = ft_strchr(ptr, ' ')))
			err_exit(wolf3d);
		while (*ptr == ' ')
			ptr++;
		if ((wolf3d->doors[i].pos_y = (float)ft_atoi(ptr) + 0.5) < 1.5)
			err_exit(wolf3d);

		ft_strdel(&wolf3d->line);

		i++;
	}

	close (fd);
}
