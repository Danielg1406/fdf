/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:56:10 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/19 17:44:01 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//void	draw_line(t_p3D start, t_p3D end, t_fdf *fdf)
//{
//	bresenham(start, end, fdf);
//}

void	bresenham(t_p3D start, t_p3D end, t_fdf *fdf)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs((int)end.x - (int)start.x);
	dy = abs((int)end.y - (int)start.y);
	sx = (start.x < end.x) ? 1 : -1;
	sy = (start.y < end.y) ? 1 : -1;
	err = dx - dy;
	while ((int)start.x != (int)end.x || (int)start.y != (int)end.y)
	{
		if ((int)start.x >= 0 && (int)start.x < WIDTH && (int)start.y >= 0
			&& (int)start.y < HEIGHT)
		{
			fdf->mlx.img.data[(int)start.y * WIDTH
				+ (int)start.x] = start.color;
		}
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}

void	render_grid(t_map *map, t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (j < map->width - 1)
				bresenham(map->grid[i][j], map->grid[i][j + 1], fdf);
			if (i < map->height - 1)
				bresenham(map->grid[i][j], map->grid[i + 1][j], fdf);
			j++;
		}
		i++;
	}
}
