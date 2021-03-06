# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chorange <chorange@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/18 18:53:25 by chorange          #+#    #+#              #
#    Updated: 2019/04/17 17:55:09 by chorange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3D

FLAGS = -Wextra -Wall -Werror

OBJECTS = main.o color.o err_exit.o image.o init.o keys_handling.o map.o \
	read_map_from_file.o textures.o get_next_line/get_next_line.o minimap.o menu.o \
	menu_provider.o parse_string.o cast.o draw.o
LIBS = -L./minilibx -lmlx -L./libft -lft -lm -framework OpenGL -framework AppKit

INCLUDES = -I./libft/libft.h -I./minilibx/mlx.h

MLXPATH = ./minilibx
FTPATH = ./libft

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C $(FTPATH)
	make -C $(MLXPATH)

	gcc $(FLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) -o $(NAME)

$(OBJECTS): %.o: %.c
	gcc $(FLAGS) -c  $< -o $@

clean:
	make -C $(FTPATH) clean
	make -C $(MLXPATH) clean
	/bin/rm -f $(OBJECTS)

fclean: clean
	make -C $(FTPATH) fclean
	make -C $(MLXPATH) clean
	/bin/rm -f $(NAME)

re: fclean all
