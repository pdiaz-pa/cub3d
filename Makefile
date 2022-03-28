SRC =	cub3d.c \
				ft_premap.c \
				ft_atoi_utils.c \
				ft_parsing_map.c \
				ft_emptyline.c \
				ft_utils.c \
				ft_error.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_raycasting_utils.c \
				ft_raycasting_init.c \
				ft_init.c \
				ft_raycasting_move.c \
				ft_raycasting.c \
				ft_keys.c \
				ft_mlx.c \
				ft_sprite.c \
				ft_save.c \
				ft_walls.c
				
NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/

HEADER = cube3d.h

LXFLAGS = -lmlx -framework OpenGL -framework AppKit -lm

MLX = libmlx.dylib

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C mlx/
	cp mlx/$(MLX) .
	$(CC) $(OBJ) -o $(NAME) $(LXFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(MLX) $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME) /mapas/validos/peque.cub

norm:
	norminette $(SRC) $(HEADER)

.PHONY: all re clean fclean test norm
