/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:23:52 by ahamrad           #+#    #+#             */
/*   Updated: 2024/01/27 14:37:39 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

void    close_window(t_cub *cub)
{
    mlx_close_window(cub->mlx);
    exit(EXIT_SUCCESS);
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return (angle);
}

int is_up_down(t_player player)
{
    if (player.move_up == 1)
        return (1);
    if (player.move_down == -1)
        return (-1);
    return (0);
}

int is_left_right(t_player player)
{
    if (player.move_left == -1)
        return (-1);
    if (player.move_right == 1)
        return (1);
    return (0);
}

void move_player(t_cub *cub, int turn_D, int walk_D)
{
    // raycaster(cub);
    int  i;
    int  j;


    turn_D = is_left_right(cub->player);
    walk_D = is_up_down(cub->player);
    cub->player.angle = normalize_angle(cub->player.angle + (5 * (M_PI / 180) * turn_D));
    if (cub->player.angle < 0)
       cub->player.angle = normalize_angle(cub->player.angle + 2 * M_PI);
    // if (cub->player.angle > 2 * M_PI)
    //    cub->player.angle = 0;
    j = cub->player.x + (cos(cub->player.angle) * 5 * walk_D);
    i = cub->player.y + (sin(cub->player.angle) * 5 * walk_D);
    if (cub->map.store_map[(((int)i + 10) / TILE_SIZE)][(((int)j + 10) / TILE_SIZE)] == '1')// check next tile
        return ;
    if (cub->map.store_map[(((int)i - 10) / TILE_SIZE)][(((int)j - 10) / TILE_SIZE)] == '1')// check next tile
        return ;
    // if (cub->map.store_map[((int)i / TILE_SIZE)][(int)(cub->player.x / TILE_SIZE)] == '1')// check next tile
    //     return ;
    // if (cub->map.store_map[(int)(cub->player.y / TILE_SIZE)][((int)j / TILE_SIZE)] == '1')// check next tile
    //     return ;
    cub->player.x = j;
    cub->player.y = i;
    // draw(cub);
    // draw_player(cub);
    raycaster(cub);
}

int key_press(mlx_key_data_t key_data, t_cub *cub)
{
    (void)key_data;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_ESCAPE))
        close_window(cub);
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_UP))
        cub->player.move_up = 1;
    else
        cub->player.move_up = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_LEFT))
        cub->player.move_left = -1;
    else
        cub->player.move_left = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_RIGHT))
        cub->player.move_right = 1;
    else  
        cub->player.move_right = 0;
    if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
        cub->player.move_down = -1;
    else
        cub->player.move_down = 0;  
    return (0);
}

int    key_relase(mlx_key_data_t key_data, t_cub *cub)
{
    (void)key_data;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_UP))
        cub->player.move_up = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_LEFT))
        cub->player.move_left = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_RIGHT))
        cub->player.move_right = 0;
    if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
        cub->player.move_down = 0;  
    return (0);

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