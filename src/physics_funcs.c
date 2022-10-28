#include "../includes/delaunay.h"

void	update_point_physics(t_point* p, int width, int height)
{
	p->x += (int)(p->vel_x * 5);
	if (p->x + p->radius >= width)
	{
		p->x = width - p->radius;
		p->vel_x *= -1;
	}
	else if (p->x <= 0)
	{
		p->x = 0;
		p->vel_x *= -1;
	}
	p->y += (int)(p->vel_y * 5);
	if (p->y + p->radius >= height)
	{
		p->y = height - p->radius;
		p->vel_y *= -1;
	}
	else if (p->y <= 0)
	{
		p->y = 0;
		p->vel_y *= -1;
	}
}
