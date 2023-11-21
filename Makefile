# VARS	--------------------------------------------------------------

NAME		:=	delaunay

SRC_DIR		:=	src

INC_DIR		:=	inc

OBJ_DIR		:=	obj

SRCS		:=	$(shell find $(SRC_DIR) -type f -name *.c)

OBJS		:=	$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,${SRCS:.c=.o})

INC			:=	-I$(INC_DIR)

CC			:=	gcc

CFLAGS		:=	-Wall -Werror -Wextra

MLXFLAGS		=	-Lmlx-linux -L/usr/lib -Imlx-linux -lXext -lX11 -lm

RM			:=	rm -f

RED			:=	\033[1;31m
GREEN		:=	\033[1;32m
PINK		:=	\033[1;35m
BLUE		:=	\033[1;36m
GRAY		:=	\033[90m
RESET		:=	\033[1;0m

MAKEFLAGS	+=	--silent

vpath	%.c	$(SRC_DIR)

# RULES	--------------------------------------------------------------

all				:	$(NAME)

$(OBJ_DIR)/%.o	:	%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME)			:	$(OBJS)
					echo "$(BLUE)Compiling...$(RESET)"
					make -C minilibx-linux/ --silent
					echo "$(PINK)minilibX compiled!$(RESET)"
					$(CC) $(OBJS) minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a $(MLXFLAGS) -o $(NAME)
					echo "$(GREEN)delaunay compiled!$(RESET)"

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
