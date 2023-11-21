#include "../inc/delaunay.h"

int	loop_handler(t_vars* vars)
{
	// TODO: Implement deltaTime
	// loop funcs
	update(vars);
	render(vars);
	exec_commands(vars);
	return 0;
}

int	key_hook(int keycode, t_vars* vars)
{
	//printf("%d\n", keycode);
	//srandom(time(0));
	if (keycode == K_ESC || keycode == K_M)
	{
		free_vars(vars);
		exit(0);
	}
	if (keycode == K_NUMPAD_DOT && vars->point_count < MAX_POINTS) {
		// ADD POINT
		pthread_mutex_lock(vars->command_lst_mtx);
		lstadd_back(&(vars->command_lst), lstnew(init_command(com_add_point)));
		pthread_mutex_unlock(vars->command_lst_mtx);
	}
	if (keycode == K_NUMPAD_0 && vars->point_count > 1) {
		// POP POINT
		pthread_mutex_lock(vars->command_lst_mtx);
		lstadd_back(&(vars->command_lst), lstnew(init_command(com_pop_point)));
		pthread_mutex_unlock(vars->command_lst_mtx);
	}
	printf("%d\n", vars->point_count);
	return 0;

}
