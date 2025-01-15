/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:56:10 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/15 19:17:55 by dgomez-a         ###   ########.fr       */
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

void	draw_line(t_p3D start, t_p3D end, t_img *img)
{
	float	dx;
	float	dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		pixel_index;
	int		i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = start.x;
	y = start.y;
	i = 0;
	while (i <= steps)
	{
		pixel_index = (int)(y)*WIDTH + (int)(x);
		if (pixel_index >= 0 && pixel_index < WIDTH * HEIGHT)
			img->data[pixel_index] = 0xFFFFFF;
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	render_grid(t_map *map, t_img *img)
{
	int		i;
	int		j;
	t_p3D	current;
	t_p3D	right;
	t_p3D	bottom;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			current = map->grid[i][j];
			iso_projection(&current);
			if (j < map->width - 1)
			{
				right = map->grid[i][j + 1];
				iso_projection(&right);
				draw_line(current, right, img);
			}
			if (i < map->height - 1)
			{
				bottom = map->grid[i + 1][j];
				iso_projection(&bottom);
				draw_line(current, bottom, img);
			}
			j++;
		}
		i++;
	}
}
