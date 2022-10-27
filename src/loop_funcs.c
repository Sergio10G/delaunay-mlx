#include "../includes/delaunay.h"

void	update(t_vars* vars)
{
	for (int i = 0; i < vars->point_count; i++)
	{
		vars->points[i]->x += (int)(vars->points[i]->vel_x * 5);
		if (vars->points[i]->x + vars->points[i]->radius >= vars->id->width)
		{
			vars->points[i]->x = vars->id->width - vars->points[i]->radius;
			vars->points[i]->vel_x *= -1;
		}
		else if (vars->points[i]->x <= 0)
		{
			vars->points[i]->x = 0;
			vars->points[i]->vel_x *= -1;
		}
		vars->points[i]->y += (int)(vars->points[i]->vel_y * 5);
		if (vars->points[i]->y + vars->points[i]->radius >= vars->id->height)
		{
			vars->points[i]->y = vars->id->height - vars->points[i]->radius;
			vars->points[i]->vel_y *= -1;
		}
		else if (vars->points[i]->y <= 0)
		{
			vars->points[i]->y = 0;
			vars->points[i]->vel_y *= -1;
		}
	}
	gen_line_array(vars);
}

void	render(t_vars* vars)
{
	clear_img(vars->id);
	for (int i = 0; i < vars->line_count; i++)
	{
		draw_line(vars->id, vars->lines[i]->p1, vars->lines[i]->p2);
		//printf("line from {%d, %d} to {%d, %d}\n", (vars->points[0])->x, (vars->points[0])->y, (vars->points[1])->x, (vars->points[1])->y);
	}
	for (int i = 0; i < vars->point_count; i++)
		draw_point(vars->id, vars->points[i]);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->id->img, 0, 0);
}