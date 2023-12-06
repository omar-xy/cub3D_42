/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:20:47 by otaraki           #+#    #+#             */
/*   Updated: 2023/12/06 22:52:24 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

/*
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture


F 220,100,0
C 225,30,0




1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111

i nedd to check if the map is closed
i need to check if the map is valid
i need to check the ARGB values
i need to check if the textures are valid
i need to check if the resolution is valid

*/


int		ft_error(t_cub *cub, char *str)
{
    (void)cub;
    ft_putstr_fd(str, 2);
    // ft_free_cub(cub);
    return (0);
}


int set_color(t_cub *cub, char **str, char flag)
{
    if (flag == 'F')
    {
        if ((ft_atoi(str[0]) < 0 && ft_atoi(str[0]) > 255) || (ft_atoi(str[1]) < 0 && ft_atoi(str[1]) > 255) 
            ||(ft_atoi(str[2]) < 0 && ft_atoi(str[2]) > 255))
            return (0);
        cub->map.floor.r = ft_atoi(str[0]);
        cub->map.floor.g = ft_atoi(str[1]);
        cub->map.floor.b = ft_atoi(str[2]);
    }
    else if (flag == 'C')
    {
        if ((ft_atoi(str[0]) < 0 && ft_atoi(str[0]) > 255) || (ft_atoi(str[1]) < 0 && ft_atoi(str[1]) > 255) 
            ||(ft_atoi(str[2]) < 0 && ft_atoi(str[2]) > 255))
                return (0);
        cub->map.ceiling.r = ft_atoi(str[0]);
        cub->map.ceiling.g = ft_atoi(str[1]);
        cub->map.ceiling.b = ft_atoi(str[2]);
    }
    return 1;
}

int parse_color(t_cub *cub, char *line, char flag)
{
    int i;
    int j;
    char **str;

    i = 0;
    j = 0;
    char numbers =  ft_substr(line, 1, ft_strlen(line));
    str = ft_split(numbers, ',');
    while (str[i])
        i++;
    if (i != 2)
        return (ft_error(cub, "Error: Wrong color\n"));
    while(str[i])
    {
        while(str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (ft_error(cub, "Error: Wrong color\n"));
            j++;
        }
        i++;
    }
    if (!set_color(cub, str, flag))
        return (ft_error(cub, "Error: Wrong color\n"));
}

int ft_parse_map(t_cub *cub, int fd)
{
    char *line;
    char *hold_file;


    hold_file = ft_strdup("");
    while(true)
    {
        line =  get_next_line(fd);
        if (!line)
            break;
        hold_file = ft_strjoin(hold_file, line);
    }
    cub->map.store_map = ft_split(hold_file, '\n');
    free(line);
    free(hold_file);
    // i need to parse the textures

    int i;
    char *str;

    i = 0;
    while(cub->map.store_map[i])
    {
        str = ft_strtrim(cub->map.store_map[i], " ");
        i++;
    }
    i = 0;
    while(cub->map.store_map[i])
    {
        printf("%s\n", cub->map.store_map[i]);
        i++;
    }
    i = 0;
    while(cub->map.store_map[i] && i < 4)
    {
        if (!ft_strncmp(cub->map.store_map[i], "NO", 2))
            cub->map.no_path = ft_substr(cub->map.store_map[i], 3, ft_strlen(cub->map.store_map[i]));
        else if (!ft_strncmp(cub->map.store_map[i], "SO", 2))
            cub->map.so_path = ft_substr(cub->map.store_map[i], 3, ft_strlen(cub->map.store_map[i]));
        else if (!ft_strncmp(cub->map.store_map[i], "WE", 2))
            cub->map.we_path = ft_substr(cub->map.store_map[i], 3, ft_strlen(cub->map.store_map[i]));
        else if (!ft_strncmp(cub->map.store_map[i], "EA", 2))
            cub->map.ea_path = ft_substr(cub->map.store_map[i], 3, ft_strlen(cub->map.store_map[i]));
        else
            return (ft_error(cub, "Error: Wrong texture path\n"));
        i++;
    }
    while(cub->map.store_map[i] && i < 6)
    {
        if (!ft_strncmp(cub->map.store_map[i], "F", 1) || !ft_strncmp(cub->map.store_map[i], "C", 1))
        {
            if (!parse_color(cub, cub->map.store_map[i], cub->map.store_map[i][0]))
                return (0);
        }
        else
            return (ft_error(cub, "Error: Wrong color\n"));
        i++;
    }
    // parse map check if map is valid
    check_map(cub, &cub->map.store_map[i]);
    return (1);
}

int ft_parse_cub(t_cub *cub, char *arg)
{
    int fd;

    fd = open(arg, O_RDONLY);

    if (fd < 0)
        return (ft_error(cub, "Error\nCan't open file\n"));
    if (!ft_parse_map(cub, fd))
        return (0);
    return (1);  
}

int calculate_map_height(char **map)
{
    int i;

    i = 0;
    while (map[i])
        i++;
    return (i);
}


int ft_check_map(t_cub *cub, char **map)
{
    int i;
    int j;

    i = 0;
    cub->map.height = calculate_map_height(map);
    while (i < cub->map.height)
    {
        j = 0;
        while (j < cub->map.width)
        {
            if (map[i][j] == '0' || map[i][j] == '2')
            {
                if (i == 0 || i == cub->map.height - 1 || j == 0 || j == cub->map.width - 1)
                    return (ft_error(cub, "Error\nMap is not closed\n"));
                if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
                    return (ft_error(cub, "Error\nMap is not closed\n"));
            }
            j++;
        }
        i++;
    }
    return (1);
}



// void	ft_init_cub(t_cub *cub)
// {
//     ft_bzero((void *)cub, sizeof(t_cub));
    
// }
// int		ft_init_cub3d(t_cub *cub)
// {
//     ft_init_cub(cub);
//     if (!ft_init_mlx(cub))
//         return (0);
//     return (1);
// }   

int		main(int argc, char **argv)
{
    t_cub	cub;
    char *str;

    if (argc != 2)
        return (ft_error(&cub, "Error\nWrong number of arguments\n"));
    str = ft_strnstr(argv[1], ".cub", strlen(argv[1]));
    if (!str || ft_strncmp(str, ".cub", 5))
        return (ft_error(&cub, "Error: the map must end with .cub\n"));
    if (!ft_parse_cub(&cub, argv[1]))
        return (ft_error(&cub, "ft_parse_cub() failed\n"));
    // ft_init_cub3d(&cub);
    // if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
    //     ft_save_bmp(&cub);
    // else
    //     ft_start_game(&cub);
    return (0);
}