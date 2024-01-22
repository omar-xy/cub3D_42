/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:23:52 by ahamrad           #+#    #+#             */
/*   Updated: 2024/01/22 17:28:30 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

void    close_window(t_cub *cub)
{
    mlx_close_window(cub->mlx.mlx);
    exit(EXIT_SUCCESS);
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return (angle);
}

void move_player(t_cub *cub, int turn_D, int walk_D)
{
    int  i;
    int  j;

    cub->player.angle = normalize_angle(cub->player.angle + (15 * (M_PI / 180) * turn_D));
    if (cub->player.angle < 0)
       cub->player.angle = normalize_angle(cub->player.angle + 2 * M_PI);
    // if (cub->player.angle > 2 * M_PI)
    //    cub->player.angle = 0;
    j = cub->player.x + (cos(cub->player.angle) * 15 * walk_D);
    i = cub->player.y + (sin(cub->player.angle) * 15 * walk_D);
    if (cub->map.store_map[(i / TILE_SIZE)][(j / TILE_SIZE)] == '1')// check next tile
        return ;
    cub->player.x = j;
    cub->player.y = i;
    // draw(cub);
    // draw_player(cub);
    raycaster(cub);
}

void keyhandle(mlx_key_data_t key_data, void *cub)
{
    if (key_data.key == MLX_KEY_ESCAPE)
        close_window(cub);
    if (key_data.key == MLX_KEY_UP)
        move_player(cub, 0, 1);
    if (key_data.key == MLX_KEY_DOWN)
        move_player(cub, 0, -1);
    if (key_data.key == MLX_KEY_LEFT)
        move_player(cub, -1, 0);
    if (key_data.key == MLX_KEY_RIGHT)
        move_player(cub, 1, 0);
    // mlx_delete_image(p->mlx.mlx, p->mlx.img.img);
}

// void    keyhandle(void *cub)
// {
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_ESCAPE))
//     {
//         close_window(cub);
//     }
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_UP))
//         move_player(cub, 0, 1);
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_DOWN))
//         move_player(cub, 0, -1);
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_LEFT))
//         move_player(cub, -1, 0);
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_RIGHT))
//         move_player(cub, 1, 0);
// }