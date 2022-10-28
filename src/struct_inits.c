#include "../includes/delaunay.h"
#include <stdlib.h>
#include <unistd.h>

t_vars*	init_vars(void)
{
	t_vars*	vars;
	vars = calloc(sizeof(t_vars), 1);
	if (!vars)
		return 0;
	vars->scale = 1.0;
	vars->offset_x = 0.0;
	vars->offset_y = 0.0;
	vars->mlx = mlx_init();
	for (int i = 0; i < MAX_POINTS; i++)
	{
		t_point*	point_new = init_point();
		if (!point_new) {
			free_vars(vars);
			error("Malloc error.");
		}
		t_list*	lst_new = lstnew(point_new);
		if (!lst_new) {
			free(point_new);
			free_vars(vars);
			error("Malloc error.");
		}
		lstadd_back(&vars->point_lst, lst_new);
	}
	return vars;
}

t_imgdata*	init_imgdata(t_vars* vars)
{
	t_imgdata*	id;

	id = calloc(sizeof(t_imgdata), 1);
	if(!id)
		return 0;
	id->width = DEF_WIDTH;
	id->height = DEF_HEIGHT;
	id->img = mlx_new_image(vars->mlx, id->width, id->height);
	id->addr = mlx_get_data_addr(id->img, &(id->bits_per_pixel), &(id->line_length), &(id->endian));
	return id;
}

t_point*	init_point(void)
{
	t_point*	p;

	p = calloc(sizeof(t_point), 1);
	if (!p)
		return 0;
	p->x = 0;
	p->y = 0;
	p->radius = DEF_RADIUS;
	p->color = DEF_COLOR;
	return p;
}

t_line*	init_line(t_point* p1, t_point* p2)
{
	t_line*	l;

	l = calloc(sizeof(t_line), 1);
	if (!l)
		return 0;
	l->p1 = p1;
	l->p2 = p2;
	l->length = ((p2->x - p1->x) * (p2->x - p1->x)) + ((p2->y - p1->y) * (p2->y - p1->y));
	return l;
}
