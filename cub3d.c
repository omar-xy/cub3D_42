/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:20:47 by otaraki           #+#    #+#             */
/*   Updated: 2023/12/11 20:56:11 by otaraki          ###   ########.fr       */
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
    int i;
    int j;
    int k;

    i = ft_atoi(str[0]);
    j = ft_atoi(str[1]);
    k = ft_atoi(str[2]);
    if (flag == 'F')
    {
        // if (i > 0 && i < 255)
        //     return (0);
        // printf("%d\n", ft_atoi(str[0]));
        cub->map.floor.r = ft_atoi(str[0]);
        cub->map.floor.g = ft_atoi(str[1]);
        cub->map.floor.b = ft_atoi(str[2]);
    }
    else if (flag == 'C')
    {
        // still need to check if the values are valid
        // if (!(ft_atoi(str[0]) < 0 && ft_atoi(str[0]) > 255) || !(ft_atoi(str[1]) < 0 && ft_atoi(str[1]) > 255) 
        //     || !(ft_atoi(str[2]) < 0 && ft_atoi(str[2]) > 255))
        //         return (0);
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
    char *numbers =  ft_substr(line, 2, ft_strlen(line));
    str = ft_split(numbers, ',');
    while (str[i])
        i++;
    if (i != 3)
        return (ft_error(cub, "Error: Wrong color2\n"));
    i = 0;
    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (ft_error(cub, "Error: Wrong color3\n"));
            j++;
        }
        i++;
    }
    if (!set_color(cub, str, flag))
        return (ft_error(cub, "Error: Wrong color4\n"));
    return (1);
}

int store_textures(t_cub *cub, char *line)
{
    char *str;
    int bool_color = 0;

    str = ft_strtrim(line, "\n");
    while(*str == ' ' || *str == '\t')
        str++;
    if (!ft_strncmp(str, "NO", 2))
        cub->map.no_path = ft_substr(str, 3, ft_strlen(str));
    else if (!ft_strncmp(str, "SO", 2))
        cub->map.so_path = ft_substr(str, 3, ft_strlen(str));
    else if (!ft_strncmp(str, "WE", 2))
        cub->map.we_path = ft_substr(str, 3, ft_strlen(str));
    else if (!ft_strncmp(str, "EA", 2))
        cub->map.ea_path = ft_substr(str, 3, ft_strlen(str));
    else if (!ft_strncmp(str, "F", 1))
    {
        bool_color = parse_color(cub, str, 'F');
        if (bool_color == 0)
            return (0);
    }
    else if (!ft_strncmp(str, "C", 1))
    {
        bool_color = parse_color(cub, str, 'C');
        if (bool_color == 0)
            return (0);
    }
    else
        return (ft_error(cub, "Error: Wrong texture path\n"));
    return (1);
}
bool detect_map(char *line)
{
    int i = -1;
    while (line[++i] == ' ' || line[i] == '\t')
        ;
    if (line[i] == '1')
        return (true);
    return (false);
}

void    calculate_map_size(t_cub *cub)
{
    int i;
	int j;
    int max_width;

    i = 0;
	max_width = 0;
    while (cub->map.store_map[i])
        i++;
    cub->map.height = i;
    i = 0;
    while(cub->map.store_map[i])
    {
        j = 0;
        while(cub->map.store_map[i][j])
            j++;
        if (j > max_width)
            max_width = j;
        i++;
    }
    cub->map.width = max_width;
}
int check_map(t_cub *cub)
{
    //check if the map is close srounded by 1
    char **map;
    int i = -1;
    int j;


    map = cub->map.store_map;
    while(map[++i])
    {
        j = -1;
        while(map[i][++j])
        {
            if (!(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E'
                    || map[i][j] == '0' || map[i][j] == '1' || map[i][j] == ' '))
                return (0);
            if (i == 0 || j == 0 || i == cub->map.height || j == cub->map.width)
            {
                if (map[i][j] != '1' && map[i][j] != ' ')
                {
                    printf("[i,j][%d,%d]--> [%d]\n", i, j, map[i][j]);
                    return (0);
                }
            }
            else if (i > 0 && j > 0 && i < cub->map.height && j < cub->map.width && map[i][j] == '0')
            {
                if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
                    return (0);
            }
            // if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            // {
            //     cub->player.x = j;
            //     cub->player.y = i;
            //     // cub->map.player.dir = map[i][j];
            // }
        }
		
    }
	return (1);
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
        if (line[0] != '\n' && !detect_map(line) && !store_textures(cub, line))
            return (0);
        else if (detect_map(line) || line[0] == '\n')
            hold_file = ft_strjoin(hold_file, line);
        free(line);
    }
    hold_file = ft_strtrim(hold_file, "\n");
    if (ft_strnstr(hold_file, "\n\n", ft_strlen(hold_file)))
        return (ft_error(cub, "Error: Wrong map, 1\n"));
    cub->map.store_map = ft_split(hold_file, '\n');
    free(line);
    free(hold_file);
    // int i = -1;
    // while (cub->map.store_map[++i])
    //     printf("%s\n", cub->map.store_map[i]);
    // parse map check if map is valid
    calculate_map_size(cub);
	// printf("width: %d\n", cub->map.width);
	// printf("height: %d\n", cub->map.height);
	// fill_empty_spaces(cub);
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
    if (!ft_parse_map(cub, fd))
        return (0);
    return (1);
}



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