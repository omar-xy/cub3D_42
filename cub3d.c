/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:20:47 by otaraki           #+#    #+#             */
/*   Updated: 2023/12/05 22:38:41 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

int		ft_error(t_cub *cub, char *str)
{
    ft_putstr_fd(str, 1);
    ft_free_cub(cub);
    return (0);
}

int ft_parse_cub(t_cub *cub, char *arg)
{
    int fd;

    fd = open(arg, O_RDONLY);
    if (fd < 0)
        return (ft_error(cub, "Error\nCan't open file\n"));
    if (!ft_parse_map(cub, fd))
        return (0);
    if (!ft_check_map(cub))
        return (0);
    if (!ft_check_cub(cub))
        return (0);
    return (1);  
}

int ft_parse_map(t_cub cub, int fd)
{
    char *line;
    int ret;

    while((ret = ))
    
    
}

// int ft_parse_file(t_cub *cubi, int fd)
// {
//     char *line;
//     int ret;

//     while ((ret = get_next_line(fd, &line)) > 0)
//     {
//         if (!ft_parse_line(cubi, line))
//         {
//             free(line);
//             return (0);
//         }
//         free(line);
//     }
//     if (ret < 0)
//     {
//         free(line);
//         return (ft_error(cubi, "Error\nget_next_line() failed\n"));
//     }
//     if (!ft_parse_line(cubi, line))
//     {
//         free(line);
//         return (0);
//     }
//     free(line);
//     return (1);

// }

// int ft_parse_map(t_cub *cubi, int fd)
// {
    
// }

// int ft_check_map(t_cub *cubi)
// {
//     int i;
//     int j;

//     i = 0;
//     while (i < cubi->map.height)
//     {
//         j = 0;
//         while (j < cubi->map.width)
//         {
//             if (cubi->map.map[i][j] == '0' || cubi->map.map[i][j] == '2')
//             {
//                 if (i == 0 || i == cubi->map.height - 1 || j == 0 || j == cubi->map.width - 1)
//                     return (ft_error(cubi, "Error\nMap is not closed\n"));
//                 if (cubi->map.map[i - 1][j] == ' ' || cubi->map.map[i + 1][j] == ' ' || cubi->map.map[i][j - 1] == ' ' || cubi->map.map[i][j + 1] == ' ')
//                     return (ft_error(cubi, "Error\nMap is not closed\n"));
//             }
//             j++;
//         }
//         i++;
//     }
//     return (1);   
// }



void	ft_init_cub(t_cub *cub)
{
    ft_bzero((void *)cub, sizeof(t_cub));
    
}
int		ft_init_cub3d(t_cub *cub)
{
    ft_init_cub(cub);
    if (!ft_init_mlx(cub))
        return (0);
    return (1);
}   

int		main(int argc, char **argv)
{
    t_cub	cub;

    if (argc < 2 || argc > 3)
        return (ft_error(&cub, "Error\nWrong number of arguments\n"));
    if (!ft_parse_cub(&cub, argv[1]))
        return (ft_error(&cub, "Error\nft_parse_cub() failed\n"));
    ft_init_cub3d(&cub);
    if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
        ft_save_bmp(&cub);
    else
        ft_start_game(&cub);
    return (0);
}