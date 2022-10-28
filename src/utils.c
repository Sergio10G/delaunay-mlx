#include "../includes/delaunay.h"
#include <stdlib.h>

double	normrand(void)
{
	return (double)random() / (double)RAND_MAX;
}

void	scramble_points(t_vars* vars)
{
	for (int i = 0; i < vars->point_count; i++)
	{
		//	Randomize position
		vars->points[i]->x = (int)(normrand() * vars->id->width);
		vars->points[i]->y = (int)(normrand() * vars->id->height);
		//	Randomize velocity
		vars->points[i]->vel_x = (normrand() * 2) - 1.0;
		vars->points[i]->vel_y = (normrand() * 2) - 1.0;
		//	Randomize color
		vars->points[i]->color = 0;
		vars->points[i]->color += (int)(normrand() * 255.0);		//	Blue
		vars->points[i]->color += (int)(normrand() * 255.0) << 8;	//	Green
		vars->points[i]->color += (int)(normrand() * 255.0) << 16;//	Red
		//printf("[%d]\t{%d, %d}\n", i, (vars->points[i])->x, (vars->points[i])->y);
	}
}

void	free_line(void* content)
{
	free((t_line*)content);
}

void	gen_line_array(t_vars* vars)
{
	if (vars->line_lst)
		lstclear(&vars->line_lst, &free_line);
	for (int i = 0; i < vars->point_count - 1; i++)
	{
		for (int j = i + 1; j < vars->point_count; j++)
		{
			t_line*	line_new = init_line(vars->points[i], vars->points[j]);
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
		}
	}
}
