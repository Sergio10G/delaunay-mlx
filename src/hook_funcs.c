#include "../includes/delaunay.h"

int	loop_handler(t_vars *vars)
{
	// loop funcs
	update(vars);
	render(vars);
	return 0;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == K_ESC)
	{
		free_vars(vars);
		exit(0);
	}
	return 0;
}
