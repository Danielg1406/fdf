/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:09:05 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/10/23 17:08:23 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		printf("the %d key (ESC) has been pressed\n", keysym);
		mlx_destroy_window(mlx->init, mlx->window);
		mlx_destroy_display(mlx->init);
		free(mlx->init);
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

	y = -1;
//	srand(time(NULL));
	mlx.init = mlx_init();
	if (mlx.init == NULL)
		return (1);
	mlx.window = mlx_new_window(mlx.init, WIDTH, HEIGHT, "my first window");
	if (mlx.window == NULL)
	{
		mlx_destroy_display(mlx.init);
		free(mlx.init);
		return (1);
	}
	mlx_key_hook(mlx.window, handle_input, &mlx);
	mlx.img.img_ptr = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.line_length, &mlx.img.endian);
	while(++y < HEIGHT)
	{
		x = -1;
		while(++x < WIDTH)
		{
			if (x % 2)
				mlx.img.data[y * WIDTH + x] = 0xFFFFFF;
			else
				mlx.img.data[y * WIDTH + x] = 0;
		}
	}
	mlx_put_image_to_window(mlx.init, mlx.window, mlx.img.img_ptr, 0, 0);
/*	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(data.init, data.window, x, y, rand() % 0x1000000);
			x++;
		}
		y++;
	}
	mlx_string_put(data.init, data.window, WIDTH * 0.8, HEIGHT * 0.95, rand(), "Daniel");*/
	mlx_loop(mlx.init);
//	mlx_destroy_window(mlx.init, mlx.window);
//	mlx_destroy_display(mlx.init);
	free(mlx.init);
	return (0);
}
