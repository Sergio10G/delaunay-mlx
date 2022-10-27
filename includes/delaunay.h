#ifndef DELAUNAY_H
# define DELAUNAY_H

// External libs

# include "../minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

// Consts and macros

# define	MAX_POINTS	20
# define	DEF_WIDTH	1024
# define	DEF_HEIGHT	768
# define	DEF_RADIUS	5
# define	DEF_COLOR	0x00FFFFFF
# define	DEF_BG		0x00000000

//  Key macros

# define	K_ESC		65307

// Struct and type defs

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
} t_imgdata;

typedef struct s_point
{
	int	    x;
	int	    y;
	double	vel_x;
	double	vel_y;
	int		radius;
	int	    color;
}	t_point;

typedef struct s_line
{
	t_point*	p1;
	t_point*	p2;
	int			length;
}	t_line;

typedef struct s_vars
{
	void*			mlx;
	void*			win;
	double			scale;
	double			offset_x;
	double			offset_y;
	t_point*		points[MAX_POINTS];
	int				point_count;
	t_line**		lines;
	int				line_count;
	t_imgdata*		id;
}	t_vars;

// Function defs

// delaunay.c
void	free_vars(t_vars* vars);

// img_funcs.c
void	img_pixel_put(t_imgdata* id, int x, int y, int color);
void	clear_img(t_imgdata* id);
void	draw_point(t_imgdata* id, t_point* point);
void	draw_line(t_imgdata* id, t_point* start, t_point* end);

// struct_inits.c
t_vars*		init_vars(void);
t_imgdata*	init_imgdata(t_vars* vars);
t_point*	init_point(void);
t_line*		init_line(t_point* p1, t_point* p2);

// hook_funcs.c
int	loop_handler(t_vars *vars);
int	key_hook(int keycode, t_vars *vars);

// loop_funcs.c
void	update(t_vars* vars);
void	render(t_vars* vars);

// utils.c
double	normrand(void);
void	scramble_points(t_vars* vars);
int	    calc_line_count(int point_count);
void	gen_line_array(t_vars* vars);
void	swap_lines(t_line** l1, t_line** l2);
int	    line_is_in_array(t_line** arr, int size, t_line* line);
void	pop_line_from_array(t_vars* vars, t_line* line);

// list_funcs.c
t_list	*lstnew(void *content);
void	lstadd_front(t_list **lst, t_list *new);
int		lstsize(t_list *lst);
t_list	*lstlast(t_list *lst);
void	lstadd_back(t_list **lst, t_list *new);
void	lstdelone(t_list *lst, void (*del)(void *));
void	lstclear(t_list **lst, void (*del)(void *));
void	lstiter(t_list *lst, void (*f)(void *));
t_list	*lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// errors.c
void	error(char* msg);
void	error_quiet(void);

#endif
