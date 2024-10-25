/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:09:05 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/10/25 16:25:25 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		printf("the %d key (ESC) has been pressed\n", keysym);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	printf("the %d key has been pressed\n", keysym);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;
	int			y;
	int			x;

	y = 49;
	srand(time(NULL));
	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
		return (1);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "my first window");
	if (mlx.win_ptr == NULL)
	{
		mlx_destroy_display(mlx.mlx_ptr);
		free(mlx.mlx_ptr);
		return (1);
	}
	mlx_key_hook(mlx.win_ptr, handle_input, &mlx);
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bits_per_pixel, &mlx.img.size_line, &mlx.img.endian);
	while(++y < HEIGHT * 0.9)
	{
		x = 49;
		while(++x < WIDTH * 0.9)
		{
			if (x % 2)
				mlx.img.data[y * WIDTH + x] = rand() % 0x1000000;
			else
				mlx.img.data[y * WIDTH + x] = 0;
		}
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_string_put(mlx.mlx_ptr, mlx.win_ptr, WIDTH * 0.8, HEIGHT * 0.95, rand(), "Daniel");
	mlx_loop(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	return (0);
}
