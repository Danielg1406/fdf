/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:55:48 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/19 17:42:21 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		grid[i] = (t_p3D *)ft_calloc(width, sizeof(t_p3D));
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

void	parse_line_to_grid(t_p3D *row, char *line, int y, int map_width)
{
	char	**cols;
	char	**value_and_color;
	int		x;

	cols = ft_split(line, ' ');
	if (!cols)
		return ;
	x = 0;
	while (cols[x] && x < map_width)
	{
		value_and_color = ft_split(cols[x], ',');
		row[x].x = x;
		row[x].y = y;
		row[x].z = ft_atoi(value_and_color[0]);
		if (value_and_color[1])
			row[x].color = ft_atoi_base(value_and_color[1], 16);
		else
			row[x].color = 0xFFFFFF;
		ft_free_split(value_and_color);
		x++;
	}
	ft_free_split(cols);
}

int	allocate_and_parse_grid(t_map *map, const char *file_name)
{
	int		fd;
	char	*line;
	int		y;

	map->grid = allocate_grid(map->width, map->height);
	if (!map->grid)
		return (1);
	fd = open_file(file_name);
	if (fd == -1)
		return (1);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_line_to_grid(map->grid[y], line, y, map->width);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	apply_transformations_and_scale(t_map *map)
{
	int	i;
	int	j;

	define_limits(map);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			iso_projection(&map->grid[i][j]);
	}
	scale_map(map);
	center_map(map);
	apply_transformations(map);
}

int	ft_define_map(t_map *map, char *file_name)
{
	if (!ft_strnstr(file_name, ".fdf", ft_strlen(file_name)))
		return (1);
	if (calculate_map_dimensions(map, file_name))
		return (1);
	if (allocate_and_parse_grid(map, file_name))
		return (1);
	apply_transformations_and_scale(map);
	return (0);
}
