/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:04:41 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/10/23 16:57:31 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 800
# define HEIGHT 500

# include "libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img_ptr;
	int	*data;
	int		bpp;
	int		line_length;
	int		endian;
}		t_img;

typedef struct s_mlx
{
	void	*init;
	void	*window;
	t_img	img;
}		t_mlx;

#endif
