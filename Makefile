# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 23:12:18 by otaraki           #+#    #+#              #
#    Updated: 2023/11/26 23:38:57 by otaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



EXE := cub3d

ARCH := libft/libft.a
MLX := minilibx/libmlx.a

MLX_FLAGS := -L minilibx -lmlx -framework OpenGL -framework AppKit

CC := cc 

# I := -I inc -I libft -I minilibx
# L := -L libft -L minilibx
CFLAGS := -g  -Wall -Wextra -Werror
# -fsanitize=address

HEADER := inc/cub3d.h

FILES := cub3d

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

library:
	make -C libft

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(ARCH) $(MLX) $(MLX_FLAGS) -o $(EXE) 

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C libft
	$(RM) $(OBJ)

fclean : clean
	make fclean -C libft
	$(RM) $(EXE)

re : fclean all

git :
	git add .
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git
