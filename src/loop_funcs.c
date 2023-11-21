#include "../inc/delaunay.h"

void	update(t_vars* vars)
{
	t_list*		point_lst;
	t_point*	point;
	int			color_off = 0;
	int			color_off_mask = 0;

	point_lst = vars->point_lst;
	while (point_lst)
	{
		point = (t_point *)point_lst->content;
		update_point_physics((t_point*)point_lst->content, vars->id->width, vars->id->height);
		color_off = (int)(normrand() * 30) % 3;
		color_off_mask = 1 << (8 * color_off);
		point->color = point->color + (1 << color_off_mask);
		if ((point->color & (1 << color_off_mask)) > 255)
			// If there is a god, please, forgive me for what I'm about to do...
			point->color = (point->color & (1 << (8 * (color_off + 1) % 3))) + (point->color & (1 << (8 * (color_off + 1) % 3)));
		point_lst = point_lst->next;
	}
	gen_line_list(vars);
}

void	render(t_vars* vars)
{
	t_list*	line_lst;
	t_list*	point_lst;

	//clear_img(vars->id);
	fade_img(vars->id);
	line_lst = vars->line_lst;
	while (line_lst)
	{
		draw_line(vars->id, (t_line*)line_lst->content);
		line_lst = line_lst->next;
	}
	point_lst = vars->point_lst;
	while (point_lst) {
		draw_point(vars->id, (t_point*)point_lst->content);
		point_lst = point_lst->next;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->id->img, 0, 0);
}

void	exec_commands(t_vars* vars) {
	t_list		*lst;
	t_command	*com;

	pthread_mutex_lock(vars->command_lst_mtx);
	lst = vars->command_lst;
	while (lst) {
		com = (t_command *)lst->content;
		com->callback(vars);
		lst = lst->next;
	}
	lstclear(&(vars->command_lst), free_command);
	pthread_mutex_unlock(vars->command_lst_mtx);
}
