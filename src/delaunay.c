#include "../inc/delaunay.h"

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
