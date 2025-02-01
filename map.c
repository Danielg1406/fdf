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

int	ft_define_map_width(char *line)
{
	char	**cols;
	char	*trimmed_line;
	int		width;

	width = 0;
	trimmed_line = ft_strtrim(line, " \n");
	if (!trimmed_line)
		return (-1);
	cols = ft_split(trimmed_line, ' ');
	free(trimmed_line);
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

// TODO: Handle Color
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
		ft_free_split(value_and_color, 2);
		x++;
	}
	ft_free_split(cols, x);
}

int	ft_define_map(t_map *map, char *file_name)
{
	int		fd;
	char	*line;
	int		y;
	int		i;
	int		j;

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
		parse_line_to_grid(map->grid[y], line, y, map->width);
		free(line);
		y++;
	}
	close(fd);
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
	return (0);
}
