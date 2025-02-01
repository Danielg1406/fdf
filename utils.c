/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:24:16 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/19 17:45:04 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_projection(t_p3D *point)
{
	int	previous_x;
	int	previous_y;

	previous_x = point->x;
	previous_y = point->y;
	point->x = (previous_x - previous_y) * cos(0.523599);
	point->y = (previous_x + previous_y) * sin(0.523599) - point->z;
}

// TODO: REFACTOR TO FOLLOW NORMINETTE
void	define_limits(t_map *map)
{
	int	i;
	int	j;

	map->min_x = map->grid[0][0].x;
	map->min_y = map->grid[0][0].y;
	map->min_z = map->grid[0][0].z;
	map->max_x = map->grid[0][0].x;
	map->max_y = map->grid[0][0].y;
	map->max_z = map->grid[0][0].z;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j].x < map->min_x)
				map->min_x = map->grid[i][j].x;
			if (map->grid[i][j].y < map->min_y)
				map->min_y = map->grid[i][j].y;
			if (map->grid[i][j].z < map->min_z)
				map->min_z = map->grid[i][j].z;
			if (map->grid[i][j].x > map->max_x)
				map->max_x = map->grid[i][j].x;
			if (map->grid[i][j].y > map->max_y)
				map->max_y = map->grid[i][j].y;
			if (map->grid[i][j].z > map->max_z)
				map->max_z = map->grid[i][j].z;
			j++;
		}
		i++;
	}
}

void	center_map(t_map *map)
{
	int	max_pixel_width;
	int	max_pixel_height;
	int	total_height;

	max_pixel_width = abs(map->max_x - map->min_x);
	max_pixel_height = abs(map->max_y - map->min_y);
	total_height = max_pixel_height + abs(map->max_z - map->min_z);
	map->offset_x = (WIDTH - max_pixel_width) / 2;
	map->offset_y = (HEIGHT - total_height) / 2;
	if (map->min_x < 0)
		map->offset_x += abs(map->min_x);
	if (map->min_y < 0)
		map->offset_y += abs(map->min_y);
}

// TODO: MAKE IT FOLLOW NORMINETTE
void	scale_map(t_map *map)
{
	float	max_scale_width;
	float	max_scale_height;
	float	max_scale_depth;
	int	i;
	int	j;

	max_scale_width = WIDTH / map->width;
	max_scale_height = HEIGHT / map->height;
	max_scale_depth = HEIGHT / (map->max_z - map->min_z + 1);
	map->scale = (max_scale_width < max_scale_height) ? 
		max_scale_width : max_scale_height;
	map->scale = (map->scale < max_scale_depth) ? map->scale : max_scale_depth;
	map->scale *= 0.5;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			map->grid[i][j].x = round(map->grid[i][j].x * map->scale);
			map->grid[i][j].y = round(map->grid[i][j].y * map->scale);
			map->grid[i][j].z = round(map->grid[i][j].z * (map->scale / 2));
		}
	}
}

void	apply_transformations(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->grid[i][j].x += map->offset_x;
			map->grid[i][j].y += map->offset_y;
			j++;
		}
		i++;
	}
}

