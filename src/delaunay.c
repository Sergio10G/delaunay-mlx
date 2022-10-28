#include "../includes/delaunay.h"
#include <unistd.h>

int	main(void)
{
	t_vars*     vars;

	vars = init_vars();
	if (!vars)
		error("Malloc error.");
	vars->id = init_imgdata(vars);
	if (!vars->id)
	{
		free_vars(vars);
		error("Malloc error.");
	}
	vars->win = mlx_new_window(vars->mlx, vars->id->width, vars->id->height, "delaunay");
	srandom(time(0));
	scramble_points(vars);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_loop_hook(vars->mlx, loop_handler, vars);
	mlx_loop(vars->mlx);
}

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
