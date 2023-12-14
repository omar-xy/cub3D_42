/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:20:47 by otaraki           #+#    #+#             */
/*   Updated: 2023/12/14 21:41:35 by otaraki          ###   ########.fr       */
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

int ft_parse_map(t_cub *cub, int fd)
{
    char *line;
    char *hold_file;
    int flg;
    int count;

    flg = 0;
    count = 0;
    hold_file = ft_strdup("");
    while(true)
    {
        line =  get_next_line(fd);
        if (!line)
            break;
        if ((detect_map(line) || line[0] == '\n'))
        {
            if (detect_map(line))
                flg = 1;
            hold_file = ft_strjoin_free(hold_file, line);
        }
        if (line[0] != '\n' && !detect_map(line))
        {
            if (flg == 1)
                return (ft_error(cub, "Error: Wrong map, 0\n"));
            if (!store_textures(cub, line))
                return (0);
            count++;
        }
        free(line);
    }
    if (count != 6)
        return (ft_error(cub, "Error: Wrong map, 1\n"));
    hold_file = ft_strtrim(hold_file, "\n");
    if (ft_strnstr(hold_file, "\n\n", ft_strlen(hold_file)))
        return (ft_error(cub, "Error: Wrong map, 2\n"));
    cub->map.store_map = ft_split(hold_file, '\n');
    free(line);
    free(hold_file);
    calculate_map_size(cub);
    fill_empty_spaces(cub);
    // int i = -1;
    // while (cub->map.store_map[++i])
    //     printf("[%s]\n", cub->map.store_map[i]);
    if (!check_textures(cub))
        return (ft_error(cub, "Error: Wrong texture P\n"));
    if (!check_map(cub))
        return (ft_error(cub, "Error: Wrong map, 2\n"));
    return (1);
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
    return (1);
}

void lk(void)
{
    system("leaks cub3d");
}



int		main(int argc, char **argv)
{
    t_cub	cub;
    char *str;



    atexit(lk);
    if (argc != 2)
        return (ft_error(&cub, "Error\nWrong number of arguments\n"));
    str = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
    if (!str || ft_strncmp(str, ".cub", 5))
        return (ft_error(&cub, "Error: the map must end with .cub\n"));
    if (!ft_parse_cub(&cub, argv[1]))
        return (ft_error(&cub, "ft_parse_cub() failed\n"));
    free_towd(cub.map.store_map);
    free(cub.map.no_path);
    free(cub.map.so_path);
    free(cub.map.we_path);
    free(cub.map.ea_path);
    // ft_init_cub3d(&cub);
    // if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
    //     ft_save_bmp(&cub);
    // else
    //     ft_start_game(&cub);
    return (0);
}