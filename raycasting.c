/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:23:30 by ahamrad           #+#    #+#             */
/*   Updated: 2024/01/22 18:32:49 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

double  distance(double x1, double x2, double y1, double y2)
{
    return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

int get_ceiling(t_ceiling *ceiling)
{
    return (ceiling->r << 16 | ceiling->g << 8 | ceiling->b);
}

int get_floor(t_floor *floor)
{
    return (floor->r << 16 | floor->g << 8 | floor->b);
}


void    check_directions(t_cub *cub, double angle_ray)
{
    if (angle_ray > 0 && angle_ray < M_PI)
        cub->ray.up_or_down = 0;
    else 
        cub->ray.up_or_down = 1;
    if (angle_ray > (M_PI / 2) && angle_ray < (3 * M_PI / 2))
        cub->ray.right_or_left = 0;
    else
        cub->ray.right_or_left = 1;
}

// double adjust_x(t_cub *cub, double angle_ray, int v_h)
// {
//     check_directions(cub, angle_ray);
//     if (v_h == 'v' && cub->ray.right_or_left)
//         cub->ray.v_x_p = 1;
//     else if (v_h == 'v' && !cub->ray.right_or_left)
//         cub->ray.v_x_p = 0;
//     else if (v_h == 'h' && cub->ray.up_or_down)
//         cub->ray.h_y_p = 1;
//     else if (v_h == 'h' && !cub->ray.up_or_down)
//         cub->ray.h_y_p = 0;
//     if (!cub->ray.right_or_left)
//         return (64);
//     return (0);
    
// } 

// double adjust_y(t_cub *cub, double angle_ray, int v_h)
// {
//     (void)v_h;
//     check_directions(cub, angle_ray);
//     if ((!cub->ray.up_or_down) && (cub->ray.right_or_left))
//         return (0);
//     if (!cub->ray.up_or_down)
//         return (64);
//     return (0);
// } 

double     horizontal_inter(t_cub *cub, double angle_ray)
{
    double  xa;
    double  ya;
    double  y;
    
    check_directions(cub, angle_ray);
    if (cub->ray.up_or_down == 1)
        y = -1;
    else
        y = 1;
    
    // xa = cub->player.x + ((int)cub->player.y % 64) / tan(angle_ray) + adjust_x(cub, angle_ray, 'h');
    // ya = cub->player.y - ((int)cub->player.y % 64) + adjust_y(cub, angle_ray, 'h');
    ya = cub->player.y - ((int)cub->player.y % 64);
    if (cub->ray.up_or_down == 0)
        ya += 64;
    xa = cub->player.x + (ya - cub->player.y) / tan(angle_ray);
    if (is_wall(cub, xa, ya + y))
        return (distance(xa, cub->player.x, ya, cub->player.y));
    if (tan(angle_ray) == 0)
        cub->ray.deltax = 64;
    else
        cub->ray.deltax = 64 / tan(angle_ray);
    cub->ray.deltay = 64;
    if (cub->ray.up_or_down == 1)
        cub->ray.deltay *= -1;
    if (cub->ray.right_or_left == 0 && cub->ray.deltax > 0)
        cub->ray.deltax *= -1;
    if (cub->ray.right_or_left == 1 && cub->ray.deltax < 0)
        cub->ray.deltax *= -1;
    while (is_wall(cub, xa, ya + y) != 1)
    {
        xa += cub->ray.deltax;
        ya += cub->ray.deltay;
    }
    return (distance(xa, cub->player.x, ya, cub->player.y));
}

double     vertical_inter(t_cub *cub, double angle_ray)
{
    double  xa;
    double  ya;
    double  x;

    check_directions(cub, angle_ray);
    if (cub->ray.right_or_left == 1)
        x = 1;
    else
        x = -1;
    // xa = cub->player.x - ((int)cub->player.x % 64) + adjust_x(cub, angle_ray, 'v');
    // ya = cub->player.y - ((((int)cub->player.x) % 64) * tan(angle_ray)) + adjust_y(cub, angle_ray, 'v');
    xa = cub->player.x - ((int)cub->player.x % 64);
    if (cub->ray.right_or_left == 1)
        xa += 64;
    ya = cub->player.y + (xa - cub->player.x) * tan(angle_ray);
    if (is_wall(cub, xa + x, ya))
        return (distance(xa, cub->player.x, ya, cub->player.y));
    cub->ray.deltax = 64;
    cub->ray.deltay = 64 * tan(angle_ray);
    if (cub->ray.right_or_left == 0)
        cub->ray.deltax *= -1;
    if (cub->ray.up_or_down == 1 && cub->ray.deltay > 0)
        cub->ray.deltay *= -1;
    if (cub->ray.up_or_down == 0 && cub->ray.deltay < 0) 
        cub->ray.deltay *= -1;
    while (is_wall(cub, xa + x, ya) != 1)
    {
        xa += cub->ray.deltax;
        ya += cub->ray.deltay; 
    }
    return (distance(xa, cub->player.x, ya, cub->player.y));
}

double     get_ray_length(t_cub *cub, double angle_ray)
{
    double  h;
    double  v;

    h = horizontal_inter(cub, angle_ray);
    v = vertical_inter(cub, angle_ray);
    if (h > v)
        return (v);
    return (h);
}

void    rendering(t_cub *cub, double angle_ray, int j)
{
    double  distance_to_wall = get_ray_length(cub, angle_ray) * cos(angle_ray - cub->player.angle);
    double  wall_projection = (WINDOW_WIDTH / 2) / tan(30 * M_PI / 180);
    double  wall = (64 / distance_to_wall) * wall_projection;

    double  start = (WINDOW_HEIGHT / 2) - (wall / 2);
    int i = 0;
    // if (wall >= WINDOW_HEIGHT)
    // {
    //     while (i < WINDOW_HEIGHT)
    //     {
    //         mlx_put_pixel(cub->mlx.img.img, j, i, 0x159463);
    //         i++;
    //     }
    //     return ;
    // }
    while (i < start)
    {
        // printf("%f : start\n", start);
        // // printf("%i : i\n", i);     
        // // printf("%f wall\n", wall);
        // printf("%f : angle ray\n", cos(angle_ray));
        // printf("%i : i\n", i);
        // printf("%i : j\n", j);
        if (i < WINDOW_HEIGHT && j < WINDOW_WIDTH && i > 0 && j > 0)
            mlx_put_pixel(cub->mlx.img.img, j, i, get_ceiling(&cub->map.ceiling));
        i++;
    }
    while (i < start + wall)
    {
        if (i < WINDOW_HEIGHT && j < WINDOW_WIDTH && i > 0 && j > 0)
            mlx_put_pixel(cub->mlx.img.img, j, i, 0x159463);
        i++;
    }
    while (i < WINDOW_HEIGHT)
    {
        if (i < WINDOW_HEIGHT && j < WINDOW_WIDTH && i > 0 && j > 0)
            mlx_put_pixel(cub->mlx.img.img, j, i, get_floor(&cub->map.floor));
        i++;
    }
}

void    raycaster(t_cub *cub)
{
    double  mini_angle = FOV_ANGLE / WINDOW_WIDTH;// 0.0523599
    double  angle_ray = normalize_angle(cub->player.angle - (FOV_ANGLE / 2));
    int     j = 0;
    // printf("%f : ray angle\n", angle_ray);
    // printf("%f : limit\n",  cub->player.angle + (FOV_ANGLE / 2));
    // printf("%f : fov\n", (FOV_ANGLE / 2));
    while (angle_ray < cub->player.angle + (FOV_ANGLE / 2) + 10 && j < WINDOW_WIDTH)
    {
        // printf("salam\n");
        // draw_line(angle_ray, cub->player.x, cub->player.y, get_ray_length(cub, angle_ray), cub);
        rendering(cub, angle_ray, j);
        angle_ray = normalize_angle(mini_angle + angle_ray);
        j++;
    }
}


int     is_wall(t_cub *cub, double x, double y)
{
    if (y >= WINDOW_WIDTH || x >= WINDOW_HEIGHT || x < 0 || y < 0)
        return 1;
    if (cub->map.store_map[(int)(y / 64)][(int)(x / 64)] == '1')
        return 1;
    return 0;
}

void    draw_line(double angle, double x, double y, double len, t_cub *cub)
{
    int i = 0;
    int xx;
    int yy;
    while (i < len)
    {
        xx = cos(angle) * i;
        yy = sin(angle) * i;
        if ((x + xx) < WINDOW_WIDTH && (y + yy) < WINDOW_HEIGHT && (x + xx) > 0 && (y + yy) > 0)
            mlx_put_pixel(cub->mlx.img.img, (int)x + xx, (int)y + yy, 0xfff);
        i++;
    }
}

void    draw_player(t_cub *cub)
{  
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x, (int)cub->player.y, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x, (int)cub->player.y + 1, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x, (int)cub->player.y - 1, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x + 1, (int)cub->player.y, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x - 1, (int)cub->player.y, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x - 1, (int)cub->player.y - 1, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x - 1, (int)cub->player.y + 1, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x + 1, (int)cub->player.y + 1, 0xffffff);
    mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x + 1, (int)cub->player.y - 1, 0xffffff);
    int i;
    int xx;
    int yy;
    
    i = 0;
    while (i < 20)
    {
        xx = cos(cub->player.angle) * i;
        yy = sin(cub->player.angle) * i;
        mlx_put_pixel(cub->mlx.img.img, (int)cub->player.x + xx, (int)cub->player.y + yy, 0xffffff);
        i++;
    }

}

void    init_window(t_cub *cub)
{
    cub->mlx.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
    cub->mlx.img.img = mlx_new_image(cub->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
}

// static int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }


void    draw(t_cub *cub)
{
    //         int color = ft_pixel(
	// rand() % 0xFF, // R
	// rand() % 0xFF, // G
	// rand() % 0xFF, // B
	// rand() % 0xFF );
    // for (int i = 0; i <  WINDOW_HEIGHT; i++)
    // {
    //     // printf("%s\n", cub->map.store_map[i]);
    //     for (int j = 0; j < WINDOW_WIDTH; j++)
    //     {
    //         if(cub->map.store_map[i / TILE_SIZE][j / TILE_SIZE] == '1')
    //         {
                
    //             mlx_put_pixel(cub->mlx.img.img, j, i, 0xFFFF);
    //         }
    //         // else if(cub->map.store_map[i / 64][j / 64] == 'N')// 'N' is the player 
    //         // {
    //         //     mlx_put_pixel(cub->mlx.img.img, (int)cub->player.y, (int)cub->player.x, 0xffffff);
                
    //         // }
    //         else
    //             mlx_put_pixel(cub->mlx.img.img, j, i, color);
    //     }
    // }
    // mlx_put_pixel(cub->mlx.img.img, (int)cub->player.y, (int)cub->player.x, 0xffffff);
    for (int i = 0; i <= WINDOW_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_HEIGHT; j = j + 64)
        {
            mlx_put_pixel(cub->mlx.img.img, i, j, 0xADFF2F);
        }
    }
    for (int i = 0; i <= WINDOW_HEIGHT; i = i + 64)
    {
        for (int j = 0; j < WINDOW_WIDTH; j++)
        {
            mlx_put_pixel(cub->mlx.img.img, i, j, 0xADFF2F);
        }
    }
}
