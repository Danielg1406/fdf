/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:04:41 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/10/25 17:46:17 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 800
# define HEIGHT 600

# include "libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <stdio.h>
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img_ptr;
	int	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}		t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}		t_mlx;

typedef struct s_p2D
{
	double	x;
	double	y;
}		t_p2D;

typedef struct s_p3D
{
	float	x;
	float	y;
	float	z;
}		t_p3D;

typedef struct	s_vertex
{
	t_p3D	local;
	t_p3D	world;
	t_p3D	aligned;
}		t_vertex;

typedef struct s_map
{
	int	height;
	int	width;
	t_p3D	coordinates;
	t_p2D	limits;
	unsigned int	color;
}		t_map;

// MAP
int	ft_define_map(t_map *map, char *file_name);

// HOOKS
int	handle_key(int keysym, t_mlx *mlx);

#endif
