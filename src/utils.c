#include "../includes/delaunay.h"

double	normrand(void)
{
	return (double)random() / (double)RAND_MAX;
}

void	scramble_point(t_point* p, int width, int height)
{
	//	Randomize position
	p->x = (int)(normrand() * width);
	p->y = (int)(normrand() * height);
	//	Randomize velocity
	p->vel_x = (normrand() * 2) - 1.0;
	p->vel_y = (normrand() * 2) - 1.0;
	//	Randomize color
	p->color = 0;
	p->color += (int)(normrand() * 255.0);		//	Blue
	p->color += (int)(normrand() * 255.0) << 8;	//	Green
	p->color += (int)(normrand() * 255.0) << 16;//	Red
	//printf("[%d]\t{%d, %d}\n", i, p->x, p->y);
}

void	scramble_points(t_vars* vars)
{
	t_list*	point_lst;

	point_lst = vars->point_lst;
	while (point_lst) {
		scramble_point((t_point*)point_lst->content, vars->id->width, vars->id->height);
		point_lst = point_lst->next;
	}
}

void	free_point(void* content)
{
	free((t_point*)content);
}

void	free_line(void* content)
{
	free((t_line*)content);
}

void	gen_line_list(t_vars* vars)
{
	t_list*	point_lst;

	point_lst = vars->point_lst;
	if (vars->line_lst)
		lstclear(&vars->line_lst, &free_line);
	while (point_lst->next)
	{
		t_list*	point_lst_sec = point_lst->next;
		while (point_lst_sec)
		{
			t_line*	line_new = init_line((t_point*)point_lst->content, (t_point*)point_lst_sec->content);
			if (!line_new)
			{
				free_vars(vars);
				error("Malloc error.");
			}
			t_list*	lst_new = lstnew(line_new);
			if (!lst_new)
			{
				free(line_new);
				free_vars(vars);
				error("Malloc error.");
			}
			lstadd_back(&vars->line_lst, lst_new); 
			point_lst_sec = point_lst_sec->next;
		}
		point_lst = point_lst->next;
	}
}
