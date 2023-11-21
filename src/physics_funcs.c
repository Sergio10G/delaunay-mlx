#include "../inc/delaunay.h"

void	update_point_physics(t_point* p, int width, int height)
{
	if (p->vel_x == 0)
		p->vel_x = 0.5 * (normrand() > 0.5 ? 1 : -1) + 0.2;
	if (p->vel_y == 0)
		p->vel_y = 0.5 * (normrand() > 0.5 ? 1 : -1) + 0.2;
	p->x += (int)(p->vel_x * 10);
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
	p->y += (int)(p->vel_y * 10);
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
