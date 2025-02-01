/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:09:05 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/18 20:01:55 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_init(t_fdf *fdf)
{
	fdf->mlx.mlx_ptr = mlx_init();
	if (fdf->mlx.mlx_ptr == NULL)
		return (1);
	fdf->mlx.win_ptr = mlx_new_window(fdf->mlx.mlx_ptr, WIDTH, HEIGHT, "FDF");
	if (fdf->mlx.win_ptr == NULL)
	{
		mlx_destroy_display(fdf->mlx.mlx_ptr);
		free(fdf->mlx.mlx_ptr);
		return (1);
	}
	return (0);
}

void	clean_exit(t_fdf *fdf)
{
	int	i;

	if (fdf->mlx.img.img_ptr)
		mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img.img_ptr);
	if (fdf->mlx.win_ptr)
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	if (fdf->mlx.mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx.mlx_ptr);
		free(fdf->mlx.mlx_ptr);
	}
	i = -1;
	while (++i < fdf->map.height)
		free(fdf->map.grid[i]);
	free(fdf->map.grid);
	exit(0);
}

int	clean_exit_wrapper(void *param)
{
	clean_exit((t_fdf *)param);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (1);
	if (ft_define_map(&fdf.map, argv[1]))
	{
		write(2, "Error Map\n", 10);
		return (1);
	}
	if (fdf_init(&fdf))
		return (1);
	fdf.mlx.img.img_ptr = mlx_new_image(fdf.mlx.mlx_ptr, WIDTH, HEIGHT);
	fdf.mlx.img.data = (int *)mlx_get_data_addr(fdf.mlx.img.img_ptr,
			&fdf.mlx.img.bits_per_pixel, &fdf.mlx.img.size_line,
			&fdf.mlx.img.endian);
	render_grid(&fdf.map, &fdf);
	mlx_put_image_to_window(fdf.mlx.mlx_ptr, fdf.mlx.win_ptr,
		fdf.mlx.img.img_ptr, 0, 0);
	mlx_hook(fdf.mlx.win_ptr, 17, 0, clean_exit_wrapper, &fdf);
	mlx_key_hook(fdf.mlx.win_ptr, handle_key, &fdf.mlx);
	mlx_loop(fdf.mlx.mlx_ptr);
	clean_exit(&fdf);
	return (0);
}
