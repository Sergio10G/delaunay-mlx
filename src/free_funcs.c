#include "../inc/delaunay.h"

void	free_vars(t_vars* vars)
{
	if (!vars)
		return ;
	if (vars->id)
	{
		if (vars->id->img)
			mlx_destroy_image(vars->mlx, vars->id->img);
		free(vars->id);
	}
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->point_lst)
		lstclear(&vars->point_lst, &free_point);
	if (vars->line_lst)
		lstclear(&vars->line_lst, &free_line);
	free(vars);
}

void	free_point(void* content)
{
	free((t_point*)content);
}

void	free_line(void* content)
{
	free((t_line*)content);
}

void	free_command(void *data) {
	t_command*	com;

	com = (t_command*) data;
	free(com);
}
