/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:24:16 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/10/25 17:21:28 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_hooks(t_mlx *mlx)
{
	mlx_do_key_autorepeatoff(mlx->mlx_ptr);
	mlx_hook(mlx->win_ptr, 2, 0, key_press_hook, mlx);
	mlx_hook(mlx->win_ptr, 3, 0, key_release_hook, mlx);
	mlx_hook(mlx->win_ptr, 4, 0, mouse_press_hook, mlx);
	mlx_hook(mlx->win_ptr, 5, 0, mouse_release_hook, mlx);
	mlx_hook(mlx->win_ptr, 6, 0, motion_hook, mlx);
	mlx_hook(mlx->win_ptr, 12, 0, expose_hook, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, exit_hook, mlx);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	iso(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;
	
	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}
