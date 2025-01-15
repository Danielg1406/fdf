/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:04:41 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/15 19:01:49 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 800
# define HEIGHT 800

# include "get_next_line/get_next_line.h"
# include "libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

typedef struct s_img
{
	void			*img_ptr;
	int				*data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_img;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
}					t_mlx;

typedef struct s_p3D
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}					t_p3D;

typedef struct s_map
{
	int				height;
	int				width;
	t_p3D			**grid;
}					t_map;

typedef struct s_fdf
{
	t_mlx			mlx;
	t_map			map;
}					t_fdf;

// MAP
int					ft_define_map(t_map *map, char *file_name);

// HOOKS
int					handle_key(int keysym, t_mlx *mlx);

// RENDERING
void				render_grid(t_map *map, t_img *img);

#endif
