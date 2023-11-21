#include "../inc/delaunay.h"

void	com_add_point(void* data) {
	t_vars*		vars;
	t_point*	point;
	
	vars = (t_vars*) data;
	point = init_point();
	randomize_point(point, vars->id->width, vars->id->height);
	lstadd_back(&(vars->point_lst), lstnew(point));
	vars->point_count = vars->point_count + 1;
}

void	com_pop_point(void* data) {
	t_vars*		vars;
	
	vars = (t_vars*) data;
	lstdellast(vars->point_lst, free_point);
	vars->point_count = vars->point_count - 1;
}
