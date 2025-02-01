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

int	interpolate_color(int color_start, int color_end, int step, int distance)
{
	int	red;
	int	green;
	int	blue;

	red = ((color_end >> 16) & 0xFF) * step / distance + ((color_start
				>> 16) & 0xFF) * (distance - step) / distance;
	green = ((color_end >> 8) & 0xFF) * step / distance + ((color_start
				>> 8) & 0xFF) * (distance - step) / distance;
	blue = (color_end & 0xFF) * step / distance + (color_start & 0xFF)
		* (distance - step) / distance;
	return ((red << 16) | (green << 8) | blue);
}

void	plot_point(t_p3D start, t_p3D end, t_fdf *fdf, t_bresenham bres)
{
	int	color;

	if ((int)start.x >= 0 && (int)start.x < WIDTH && (int)start.y >= 0
		&& (int)start.y < HEIGHT)
	{
		color = interpolate_color(start.color, end.color, bres.step,
				bres.distance);
		fdf->mlx.img.data[(int)start.y * WIDTH + (int)start.x] = color;
	}
}

void	draw_line(t_p3D start, t_p3D end, t_fdf *fdf, t_bresenham bres)
{
	bres.distance = sqrt(bres.dx * bres.dx + bres.dy * bres.dy);
	bres.step = 0;
	while ((int)start.x != (int)end.x || (int)start.y != (int)end.y)
	{
		plot_point(start, end, fdf, bres);
		update_bresenham(&start, &bres);
		bres.step++;
	}
}

void	bresenham(t_p3D start, t_p3D end, t_fdf *fdf)
{
	t_bresenham	bres;

	init_bresenham(&bres, start, end);
	draw_line(start, end, fdf, bres);
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
