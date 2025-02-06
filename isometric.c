/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:09:51 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/02/04 13:09:55 by dgomez-a         ###   ########.fr       */
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

void	center_map(t_map *map)
{
	float	x_range;
	float	y_range;

	define_limits(map);
	x_range = map->max_x - map->min_x;
	y_range = map->max_y - map->min_y;
	map->offset_x = (WIDTH - (x_range * map->scale)) / 2 - map->min_x
		* map->scale;
	map->offset_y = (HEIGHT - (y_range * map->scale)) / 2 - map->min_y
		* map->scale;
}

void	scale_map(t_map *map)
{
	float	x_range;
	float	y_range;
	float	multiplier;

	x_range = map->max_x - map->min_x;
	y_range = map->max_y - map->min_y;
	if (x_range > y_range)
		multiplier = (WIDTH * SCALE_FACTOR) / x_range;
	else
		multiplier = (HEIGHT * SCALE_FACTOR) / y_range;
	map->scale = multiplier;
	if (map->scale < 1)
		map->scale = 1;
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
			map->grid[i][j].x = round(map->grid[i][j].x * map->scale)
				+ map->offset_x;
			map->grid[i][j].y = round(map->grid[i][j].y * map->scale)
				+ map->offset_y;
			map->grid[i][j].z = round(map->grid[i][j].z * (map->scale / 2));
			j++;
		}
		i++;
	}
}
