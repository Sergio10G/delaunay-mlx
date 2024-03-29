#include "../inc/delaunay.h"

void	img_pixel_put(t_imgdata* id, int x, int y, int color)
{
	char	*dst;

	if (x >= id->width || y >= id->height)
		return ;
	dst = id->addr + (y * id->line_length + x * (id->bits_per_pixel / 8));
	*(int *)dst = color;
}

int	img_pixel_get(t_imgdata* id, int x, int y) {
	char	*dst;

	if (x >= id->width || y >= id->height)
		return 0;
	dst = id->addr + (y * id->line_length + x * (id->bits_per_pixel / 8));
	return *(int *)dst;
}

void	clear_img(t_imgdata* id)
{
	for (int y = 0; y < id->height; y++)
	{
		for (int x = 0; x < id->width; x++)
		{
			img_pixel_put(id, x, y, DEF_BG);
		}
	}
}

void	fade_img(t_imgdata* id)
{
	int	color;

	for (int y = 0; y < id->height; y++)
	{
		for (int x = 0; x < id->width; x++)
		{
			color = img_pixel_get(id, x, y);
			color -= (color & 0xFF) > 0 ? 1 : 0;
			color -= (color & 0xFF00) > 0 ? 0x0100 : 0;
			color -= (color & 0xFF0000) > 0 ? 0x010000 : 0;
			img_pixel_put(id, x, y, color);
		}
	}
}

void	draw_point(t_imgdata* id, t_point* point)
{
	int x_dist_sq;
	int	y_dist_sq;
	int rad_sq;

	rad_sq = point->radius * point->radius;
	for (int y = 0; y < point->radius * 2; y++)
	{
		if (point->y + y >= id->height)
			continue;
		y_dist_sq = (y - point->radius) * (y - point->radius);
		for (int x = 0; x < point->radius * 2; x++)
		{
			if (point->x + x >= id->width)
				continue;
			x_dist_sq = (x - point->radius) * (x - point->radius);
			if (x_dist_sq + y_dist_sq < rad_sq)
				img_pixel_put(id, point->x + x, point->y + y, point->color);
		}
	}
}

//	Thanks internet <3
void	draw_line(t_imgdata* id, t_line* line)
{
	t_point*	start;
	t_point*	end;
	int			dx;
	int			dy;

	if (abs(line->p2->y - line->p1->y) < abs(line->p2->x - line->p1->x))
	{
		if (line->p1->x > line->p2->x)
		{
			start = line->p2;
			end = line->p1;
		}
		else
		{
			start = line->p1;
			end = line->p2;
		}
	}
	else
	{
		if (line->p1->y > line->p2->y)
		{
			start = line->p2;
			end = line->p1;
		}
		else
		{
			start = line->p1;
			end = line->p2;
		}
	}
	dx = end->x - start->x;
	dy = end->y - start->y;
	if (dx > dy)
	{
		for (int x = start->x; x < end->x; x++)
		{
			int y = start->y + dy * (x - start->x) / dx;
			img_pixel_put(id, x + start->radius, y + start->radius, line->p1->color);
		}
	}
	else
	{
		for (int y = start->y; y < end->y; y++)
		{
			int x = start->x + dx * (y - start->y) / dy;
			img_pixel_put(id, x + start->radius, y + start->radius, line->p1->color);
		}
	}
}
