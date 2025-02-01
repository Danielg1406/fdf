//TODO: Add 42 Header
#include "fdf.h"

void	init_bresenham(t_bresenham *bres, t_p3D start, t_p3D end)
{
	bres->dx = abs((int)end.x - (int)start.x);
	bres->dy = abs((int)end.y - (int)start.y);
	bres->sx = 1;
	if (start.x >= end.x)
		bres->sx = -1;
	bres->sy = 1;
	if (start.y >= end.y)
		bres->sy = -1;
	bres->err = bres->dx - bres->dy;
}

void	update_bresenham(t_p3D *start, t_bresenham *bres)
{
	bres->e2 = 2 * bres->err;
	if (bres->e2 > -bres->dy)
	{
		bres->err -= bres->dy;
		start->x += bres->sx;
	}
	if (bres->e2 < bres->dx)
	{
		bres->err += bres->dx;
		start->y += bres->sy;
	}
}
