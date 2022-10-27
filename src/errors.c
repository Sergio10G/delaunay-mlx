#include "../includes/delaunay.h"

void	error(char* msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	error_quiet(void)
{
	exit(1);
}