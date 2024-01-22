/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:20:47 by otaraki           #+#    #+#             */
/*   Updated: 2024/01/22 17:05:03 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

void ft_free_cub(t_cub *cub)
{
    int i;

    i = -1;
    if (cub->map.store_map)
    {
        while (cub->map.store_map[++i])
            free(cub->map.store_map[i]);
        free(cub->map.store_map);
    }
    cub->map.store_map = NULL;
    // if (cub->map.ea_path)
    //     free(cub->map.ea_path);
    // if (cub->map.we_path)
    //     free(cub->map.we_path);
    // if (cub->map.so_path)
    //     free(cub->map.so_path);
    // if (cub->map.no_path)
    //     free(cub->map.no_path);
    // make sure you check this out
}

int		ft_error(t_cub *cub, char *str)
{
    (void)cub;
    ft_putstr_fd(str, 2);
    ft_free_cub(cub);
    return (0);
}


int ft_parse_cub(t_cub *cub, char *arg)
{
    int fd;

    fd = open(arg, O_RDONLY);

    if (fd < 0)
        return (ft_error(cub, "Error\nCan't open file\n"));
    ft_bzero(&cub->map, sizeof(t_map));
    ft_bzero(cub, sizeof(t_cub));
    if (!ft_parse_map(cub, fd))
        return (0);
    if (!check_textures(cub))
        return (ft_error(cub, "Error: Wrong texture P\n"));
    if (!check_map(cub))
        return (ft_error(cub, "Error: Wrong map, 2\n"));
    return (1);
}

void check_angle(t_cub *cub)
{
    if (cub->player.dir == 'E')
        cub->player.angle = 0;
    else if (cub->player.dir == 'N')
        cub->player.angle = M_PI / 2;
    else if (cub->player.dir == 'W')
        cub->player.angle = M_PI;
    else if (cub->player.dir == 'S')
        cub->player.angle = 3 * M_PI / 2;
    else
        cub->player.angle = 0;
}
int		main(int argc, char **argv)
{
    t_cub	cub;
    char    *str;
    cub.player.fov = M_PI / 3;

    if (argc != 2)
        return (ft_error(&cub, "Error\nWrong number of arguments\n"));
    str = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
    if (!str || ft_strncmp(str, ".cub", 5))
        return (ft_error(&cub, "Error: the map must end with .cub\n"));
    if (!ft_parse_cub(&cub, argv[1]))
        return (ft_error(&cub, "ft_parse_cub() failed\n"));
   check_angle(&cub);

    init_window(&cub);
    mlx_image_to_window(cub.mlx.mlx, cub.mlx.img.img, 0, 0);
    // draw(&cub);
    raycaster(&cub);
    // mlx_image_to_window(cub.mlx.mlx, cub.mlx.img.img, 0, 0); 

    mlx_key_hook(cub.mlx.mlx, (void *)keyhandle, &cub);
    mlx_loop(cub.mlx.mlx);
    mlx_terminate(cub.mlx.mlx);
    return (0);
}
