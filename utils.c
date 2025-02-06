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

void	update_min_max(t_map *map, int i, int j)
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
}

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
			update_min_max(map, i, j);
			j++;
		}
		i++;
	}
}
