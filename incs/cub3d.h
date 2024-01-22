/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:14:10 by otaraki           #+#    #+#             */
/*   Updated: 2024/01/22 16:08:13 by ahamrad          ###   ########.fr       */
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
# include "defines.h"

// # include "structs.h"


// # include "prototypes.h"
typedef struct s_floor
{
    char *floor;
    int		r;
    int		g;
    int		b;
}				t_floor;

typedef struct s_ceiling
{
    char *ceiling;
    int		r;
    int		g;
    int		b;
}				t_ceiling;

typedef struct s_map
{
    int		width;
    int		height;
    t_floor	floor;
    t_ceiling	ceiling;
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    char	**store_map;
}				t_map;

typedef struct s_player
{
    double	x;
    double	y;
    char	dir;
    double	fov; // 60
    double  angle; // 3 * M_PI / 2
}				t_player;

typedef struct s_ray
{
    // double	xh; _
    // double	yh;
    // double	xv; |
    // double	yv;
    double  deltax;
    double  deltay;
    int up_or_down;
    int h_y_p;
    int v_x_p;
    int right_or_left;
    double  angle_ray;
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


int     ft_parse_map(t_cub *cub, int fd);
bool    detect_map(char *line);
int     store_textures(t_cub *cub, char *line);
int     parse_color(t_cub *cub, char *line, char flag);
int     set_color(t_cub *cub, char **str, char flag);
void    calculate_map_size(t_cub *cub);
void    fill_empty_spaces(t_cub *cub);
int     check_map(t_cub *cub);
int     check_textures(t_cub *cub);
int		ft_error(t_cub *cub, char *str);
void    free_towd(char **str);

void    init_window(t_cub *cub);
void    draw(t_cub *cub);
// void    keyhandle(t_cub *cub);
void    keyhandle(mlx_key_data_t key_data, void *cub);
void    draw_player(t_cub *cub);

int     is_wall(t_cub *cub, double x, double y);
void    draw_line(double angle, double x, double y, double len, t_cub *cub);
void    raycaster(t_cub *cub);
void    rendering(t_cub *cub, double angle_ray, int j);

double  normalize_angle(double angle);

#endif