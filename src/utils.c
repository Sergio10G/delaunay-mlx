#include "../includes/delaunay.h"

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

int	calc_line_count(int point_count)
{
	int	sum;

	sum = 0;
	for (int i = point_count - 1; i >= 1; i--)
	{
		sum += i;
	}
	return sum;
}

void	gen_line_array(t_vars* vars)
{
	int	l_ind;

	if (vars->lines)
	{
		for (int i = 0; i < vars->line_count; i++)
			free(vars->lines[i]);
		free(vars->lines);
	}
	vars->line_count = calc_line_count(vars->point_count);
	vars->lines = (t_line**)calloc(sizeof(t_line*), vars->line_count);
	if (!vars->lines)
	{
		free_vars(vars);
		error("Malloc error.");
	}
	// Generate all possible lines
	l_ind = 0;
	for (int i = 0; i < vars->point_count - 1; i++)
	{
		for (int j = i + 1; j < vars->point_count; j++)
		{
			//TODO: Uncontrolled Malloc
			vars->lines[l_ind++] = init_line(vars->points[i], vars->points[j]);
		}
	}
	// Order the lines by length
	// Bubble sort ftw
	/*
	for (int i = 0; i < vars->line_count - 1; i++)
	{
		for (int j = i + 1; j < vars->line_count; j++)
		{
			if (vars->lines[j]->length < vars->lines[i]->length)
				swap_lines(vars->lines + j, vars->lines + i);
			
		}
		
	}
	*/
	// Filter the lines
	// TODO: this
}

void	swap_lines(t_line** l1, t_line** l2)
{
	t_line* temp;
	temp = *l1;
	*l1 = *l2;
	*l2 = temp;
}

int	line_is_in_array(t_line** arr, int size, t_line* line)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == line)
			return 1;
		if (arr[i] == 0)
			break;
	}
	return(0);
}

void	pop_line_from_array(t_vars* vars, t_line* line)
{
	t_line**	new_arr;
	int			new_ind;

	new_arr = (t_line**)calloc(sizeof(t_line*), vars->line_count - 1);
	if (!new_arr)
	{
		free_vars(vars);
		error("Malloc error.");
	}
	new_ind = 0;
	for (int i = 0; i < vars->line_count - 1; i++)
		if (vars->lines[i] != line)
			new_arr[new_ind++] = vars->lines[i];
	free(line);
	free(vars->lines);
	vars->lines = new_arr;
	vars->line_count -= 1;
}