/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:24:16 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/18 16:52:09 by dgomez-a         ###   ########.fr       */
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
	point->y = -point->z + (previous_x + previous_y) * sin(0.523599);
}

void	center_map(t_map *map)
{
	int	map_pixel_width;
	int	map_pixel_height;

	map_pixel_width = map->width * map->scale;
	map_pixel_height = map->height * map->scale;
	map->offset_x = (WIDTH - map_pixel_width) / 2;
	map->offset_y = (HEIGHT - map_pixel_height) / 2;
}

void	scale_map(t_map *map)
{
	int	max_scale_width;
	int	max_scale_height;

	max_scale_width = WIDTH / (map->width + 1);
	max_scale_height = HEIGHT / (map->height + 1);
	if (max_scale_width < max_scale_height)
		map->scale = max_scale_width;
	else
		map->scale = max_scale_height;
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
			j++;
		}
		i++;
	}
}
/*
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
*/
int	handle_key(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	return (0);
}
