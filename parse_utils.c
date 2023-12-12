/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:03:19 by otaraki           #+#    #+#             */
/*   Updated: 2023/12/12 23:52:23 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "incs/cub3d.h"

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
        if ((i < 0 || i > 255) || (j < 0 || j > 255) || (k < 0 || k > 255))
            return (0);
        cub->map.floor.floor = "F";
        cub->map.floor.r = i;
        cub->map.floor.g = j;
        cub->map.floor.b = k;
    }
    else if (flag == 'C')
    {
        if ((i < 0 || i > 255) || (j < 0 || j > 255) || (k < 0 || k > 255))
            return (0);
        cub->map.ceiling.ceiling = "C";
        cub->map.ceiling.r = i;
        cub->map.ceiling.g = j;
        cub->map.ceiling.b = k;
    }
    return 1;
}


static int count_comas(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(line[i])
    {
        if (line[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        return (0);
    return (1);
}
int count_towd_arr(char **str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

int parse_color(t_cub *cub, char *line, char flag)
{
    int i;
    int j;
    char **str;

    i = 0;
    if (!line)
        return (ft_error(cub, "Error: Wrong color0\n"));
    if (!count_comas(line))
        return (ft_error(cub, "Error: Wrong color1\n"));
    str = ft_split(line, ',');
    i = count_towd_arr(str);
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
    char **str2;
    int bool_color = 0;

    str = ft_strtrim(line, "\n");
    if (!str)
        return (0);
    str2 = ft_split(str, ' ');
    if (!str2)
        return (0);
    if (str2[1])
    {
        if (!ft_strncmp(str2[0], "NO", 3))
            cub->map.no_path = ft_strdup(str2[1]);
        else if (!ft_strncmp(str2[0], "SO", 3))
            cub->map.so_path = ft_strdup(str2[1]);
        else if (!ft_strncmp(str2[0], "WE", 3))
            cub->map.we_path = ft_strdup(str2[1]);
        else if (!ft_strncmp(str2[0], "EA", 3))
            cub->map.ea_path = ft_strdup(str2[1]);
        else if (!ft_strncmp(str2[0], "F", 2))
        {
            bool_color = parse_color(cub, str2[1], 'F');
            if (bool_color == 0)
                return (0);
        }
        else if (!ft_strncmp(str2[0], "C", 2))
        {
            bool_color = parse_color(cub, str2[1], 'C');
            if (bool_color == 0)
                return (0);
        }
        else
            return (ft_error(cub, "Error: in map\n"));
    }
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

void fill_empty_spaces(t_cub *cub)
{
    int i;
    int j;
    char **map;

    map = cub->map.store_map;
    i = -1;
    while(map[++i])
    {
        j = ft_strlen(map[i]);
        while(j < cub->map.width)
        {
            map[i] = ft_strjoin(map[i], " ");
            j++;
        }
    }
    cub->map.store_map = map;
}

int check_textures(t_cub *cub)
{
    int i;

    if (!cub->map.no_path || !cub->map.so_path || !cub->map.we_path || !cub->map.ea_path
        || !cub->map.floor.floor || !cub->map.ceiling.ceiling)
        return (0);
    i = 0;
    if (open(cub->map.no_path, O_RDONLY) < 0 || open(cub->map.so_path, O_RDONLY) < 0 
        || open(cub->map.we_path, O_RDONLY) < 0 || open(cub->map.ea_path, O_RDONLY) < 0)
        return (0);
    return (1);
}
int check_map(t_cub *cub)
{
    char **map;
    int i = -1;
    int j;


    cub->player.dir = '\0';
    map = cub->map.store_map;
    while(map[++i])
    {
        j = -1;
        while(map[i][++j])
        {
            if (!(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E'
                    || map[i][j] == '0' || map[i][j] == '1' || map[i][j] == ' '))
                return (0);
            if (i == 0 || i == cub->map.height - 1 || j == 0 || j == cub->map.width - 1)
            {
                if (map[i][j] != '1' && map[i][j] != ' ')
                    return (0);
            }
            else if (i > 0 && j > 0 && (i < cub->map.height - 1) && (j < cub->map.width - 1) 
                && (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E'))
            {
                if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
                    return (0);
            }
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            {
                cub->player.x = j;
                cub->player.y = i;
                cub->player.dir = map[i][j];
            }
        }
    }
    if (cub->player.dir == '\0')
        return (0);
	return (1);
}