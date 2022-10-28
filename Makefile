NAME			=	delaunay

SRCS			=	src/delaunay.c			\
					src/struct_inits.c		\
					src/hook_funcs.c		\
					src/img_funcs.c			\
					src/list_funcs.c		\
					src/loop_funcs.c		\
					src/physics_funcs.c		\
					src/utils.c				\
					src/errors.c

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra

MLXFLAGS		=	-Lmlx-linux -L/usr/lib -Imlx-linux -lXext -lX11 -lm -lz

MAKEFLAGS		+=	--silent

GREEN		=	\033[1;32m
PINK		=	\033[1;35m
BLUE		=	\033[1;36m
RESET		=	\033[1;0m

%.o				:	%.c
					$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

$(NAME)			:	$(OBJS)
					echo "$(BLUE)Compiling...$(RESET)"
					make -C minilibx-linux/ --silent
					echo "$(PINK)minilibX compiled!$(RESET)"
					$(CC) $(OBJS) minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a $(MLXFLAGS) -o $(NAME)
					echo "$(GREEN)delaunay compiled!$(RESET)"

all				:	$(NAME)

clean			:
					rm -f $(OBJS)
					echo "$(BLUE)delaunay objs cleaned!$(RESET)"

fclean			:	clean
					make -C minilibx-linux/ clean --silent
					echo "$(BLUE)minilibX objs cleaned!$(RESET)"
					rm -f $(NAME)
					echo "$(BLUE)delaunay removed!$(RESET)"

re				:	fclean all

.PHONY			:	all clean fclean re
