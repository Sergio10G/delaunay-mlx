#include "../includes/delaunay.h"

void	update(t_vars* vars)
{
	t_list*	point_lst;

	point_lst = vars->point_lst;
	while (point_lst)
	{
		update_point_physics((t_point*)point_lst->content, vars->id->width, vars->id->height);
		point_lst = point_lst->next;
	}
	gen_line_array(vars);
}

void	render(t_vars* vars)
{
	t_list*	line_lst;
	t_list*	point_lst;

	clear_img(vars->id);
	line_lst = vars->line_lst;
	while (line_lst)
	{
		draw_line(vars->id, ((t_line*)line_lst->content)->p1, ((t_line*)line_lst->content)->p2);
		line_lst = line_lst->next;
	}
	point_lst = vars->point_lst;
	while (point_lst) {
		draw_point(vars->id, (t_point*)point_lst->content);
		point_lst = point_lst->next;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->id->img, 0, 0);
}
