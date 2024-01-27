# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 23:12:18 by otaraki           #+#    #+#              #
#    Updated: 2024/01/27 11:27:20 by otaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := cub3d

ARCH := libft/libft.a
MLX := MLX42/build/libmlx42.a


# MLX_FLAGS := -L MLX42 -lmlx -framework OpenGL -framework AppKit
MLX_FLAGS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit

CC := cc 
CFLAGS := -g -Wall -Wextra -Werror -Ofast 

I = -I /Users/${USER}/.brew/Cellar/glfw/3.3.9/include/GLFW
L = -L /Users/${USER}/.brew/Cellar/glfw/3.3.9/lib

# I := -I inc -I libft -I MLX42
# L := -L libft -L MLX42

HEADER := inc/cub3d.h

FILES := cub3d parse_utils raycasting keyhandle

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

library :
	make -C libft

$(EXE) : $(OBJ) | library
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(ARCH) $(MLX) $(L) $(I) -o $(EXE) 

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(I)

clean :
	make clean -C libft
	$(RM) $(OBJ)

fclean : clean
	make fclean -C libft
	$(RM) $(EXE)

re : fclean all

run:
	make all;
	./cub3d map.cub

git :
	git add .
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git
