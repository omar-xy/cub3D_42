# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 23:12:18 by otaraki           #+#    #+#              #
#    Updated: 2023/12/14 21:40:25 by otaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



EXE := cub3d

ARCH := libft/libft.a
MLX := minilibx/libmlx.a

# MLX_FLAGS := -L minilibx -lmlx -framework OpenGL -framework AppKit

CC := cc 

# I := -I inc -I libft -I minilibx
# L := -L libft -L minilibx
CFLAGS := -g  -Wall -Wextra
# -fsanitize=address

HEADER := inc/cub3d.h

FILES := cub3d parse_utils

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

library :
	make -C libft

$(EXE) : $(OBJ) | library
	$(CC) $(CFLAGS) $(OBJ) $(ARCH) -o $(EXE) 

%.o : %.c $(HEADER)
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
