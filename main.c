/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:09:05 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/10/23 13:10:11 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("the %d key (ESC) has been pressed\n", keysym);
		mlx_destroy_window(data->init, data->window);
		mlx_destroy_display(data->init);
		free(data->init);
		exit(1);
	}
	printf("the %d key has been pressed\n", keysym);
	return (0);
}

int	main(void)
{
	t_mlx_data	data;
	int			y;
	int			x;

	y = HEIGHT * 0.1;
	srand(time(NULL));
	data.init = mlx_init();
	if (data.init == NULL)
		return (1);
	data.window = mlx_new_window(data.init, WIDTH, HEIGHT, "my first window");
	if (data.window == NULL)
	{
		mlx_destroy_display(data.init);
		free(data.init);
		return (1);
	}
	mlx_key_hook(data.window, handle_input, &data);
	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(data.init, data.window, x, y, rand() % 0x1000000);
			x++;
		}
		y++;
	}
	mlx_string_put(data.init, data.window, WIDTH * 0.8, HEIGHT * 0.95, rand(), "Daniel");
	mlx_loop(data.init);
	mlx_destroy_window(data.init, data.window);
	mlx_destroy_display(data.init);
	free(data.init);
	return (0);
}
