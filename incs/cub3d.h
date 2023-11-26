/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:14:10 by otaraki           #+#    #+#             */
/*   Updated: 2023/11/26 23:29:46 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// # include "structs.h"

# include "defines.h"

// # include "prototypes.h"

typedef struct s_map
{
    int		width;
    int		height;
    char	**map;
}				t_map;

typedef struct s_player
{
    double	x;
    double	y;
    double	dir;
    double	fov;
}				t_player;

typedef struct s_ray
{
    double	x;
    double	y;
    double	dir;
    double	fov;
}				t_ray;

typedef struct s_img
{
    void	*img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
}				t_img;

typedef struct s_mlx
{
    void	*mlx;
    void	*win;
    t_img	img;
}				t_mlx;

typedef struct s_cub
{
    t_map		map;
    t_player	player;
    t_ray		ray;
    t_mlx		mlx;
}				t_cub;



#endif