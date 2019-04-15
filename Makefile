NAME = Wolf3D

FLAGS =# -Wextra -Wall -Werror

OBJECTS = main.o color.o err_exit.o image.o init.o keys_handling.o map.o read_map_from_file.o textures.o get_next_line/get_next_line.o minimap.o menu.o
LIBS = -L. -lmlx_Linux -L./libft -lft -lm -lX11 -lXext

#INCLUDES = -I./libft/libft.h #-I./minilibx/mlx.h

#MLXPATH = ./minilibx
FTPATH = ./libft

all: $(NAME)



$(NAME): $(OBJECTS)
	make -C $(FTPATH)
	#make -C $(MLXPATH)

	gcc -g $(FLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) -o $(NAME)

$(OBJECTS): %.o: %.c
	gcc -g $(FLAGS) -c  $< -o $@

clean:
	make -C $(FTPATH) clean
	#make -C $(MLXPATH) clean
	/bin/rm -f $(OBJECTS)

fclean: clean
	make -C $(FTPATH) fclean
	#make -C $(MLXPATH) clean
	/bin/rm -f $(NAME)

re: fclean all
