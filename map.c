/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:55:48 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/15 19:02:11 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_define_map_width(char *line)
{
	char	**cols;
	int		width;

	width = 0;
	cols = ft_split(line, ' ');
	if (!cols)
		return (-1);
	while (cols[width])
		width++;
	ft_free_split(cols, width);
	return (width);
}

t_p3D	**allocate_grid(int width, int height)
{
	t_p3D	**grid;
	int		i;

	grid = (t_p3D **)malloc(sizeof(t_p3D *) * height);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = (t_p3D *)malloc(sizeof(t_p3D) * width);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

void	parse_line_to_grid(t_p3D *row, char *line, int y)
{
	char	**cols;
	int		x;

	cols = ft_split(line, ' ');
	if (!cols)
		return ;
	x = 0;
	while (cols[x])
	{
		row[x].x = x;
		row[x].y = y;
		row[x].z = ft_atoi(cols[x]);
		row[x].color = 0xFFFFFF;
		x++;
	}
	ft_free_split(cols, x);
}

void	apply_scaling_and_offset(t_map *map)
{
	float	hypo;
	float	scaling_factor;
	int		offset_x;
	int		offset_y;
	int		i;
	int		j;

	hypo = sqrt(map->width * map->width + map->height * map->height);
	scaling_factor = 0.9 * fmin(WIDTH, HEIGHT) / hypo;
	offset_x = WIDTH / 2 - (map->width * scaling_factor) / 2;
	offset_y = HEIGHT / 2 - (map->height * scaling_factor) / 2;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->grid[i][j].x = round(map->grid[i][j].x * scaling_factor)
				+ offset_x;
			map->grid[i][j].y = round(map->grid[i][j].y * scaling_factor)
				+ offset_y;
			map->grid[i][j].z = round(map->grid[i][j].z * scaling_factor);
			j++;
		}
		i++;
	}
}

int	ft_define_map(t_map *map, char *file_name)
{
	int		fd;
	char	*line;
	int		y;

	if (!ft_strnstr(file_name, ".fdf", ft_strlen(file_name)))
		return (1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (1);
	map->height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (map->height == 0)
			map->width = ft_define_map_width(line);
		map->height++;
		free(line);
	}
	close(fd);
	map->grid = allocate_grid(map->width, map->height);
	if (!map->grid)
		return (1);
	fd = open(file_name, O_RDONLY);
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		parse_line_to_grid(map->grid[y], line, y);
		free(line);
		y++;
	}
	close(fd);
	apply_scaling_and_offset(map);
	return (0);
}
