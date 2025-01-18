/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:04:41 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/18 16:51:04 by dgomez-a         ###   ########.fr       */
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
	int				scale;
	int				offset_x;
	int				offset_y;
	t_p3D			**grid;
}					t_map;

typedef struct s_fdf
{
	t_mlx			mlx;
	t_map			map;
}					t_fdf;

// MAP
int					ft_define_map_width(char *line);
t_p3D				**allocate_grid(int width, int height);
void				parse_line_to_grid(t_p3D *row, char *line, int y);
int					ft_define_map(t_map *map, char *file_name);

// UTILS
void				iso_projection(t_p3D *point);
void				center_map(t_map *map);
void				scale_map(t_map *map);
void				apply_transformations(t_map *map);
int					handle_key(int keysym, t_mlx *mlx);

// RENDERING
void				draw_line(t_p3D start, t_p3D end, t_img *img);
void				render_grid(t_map *map, t_img *img);

#endif
