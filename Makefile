NAME = cub3D

SRCS = ./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		ft_error.c \
		ft_main.c  \
		ft_map_check2.c \
		ft_parser.c  \
		ft_raycast.c  \
		ft_screenshot.c \
		ft_sprites2.c \
		ft_init.c   \
		ft_map_check.c \
		ft_move.c \
		ft_parser2.c \
		ft_raycast2.c \
		ft_sprites.c \
		ft_utils.c \
		./libft/ft_lstadd_back.c \
		./libft/ft_lstclear.c \
		./libft/ft_lstnew.c \
		./libft/ft_lstsize.c \
		./libft/ft_lstlast.c



CFLAGS 	= -Wall -Wextra -Werror
CC = gcc
MLX =  -Lminilibx -lmlx -framework OpenGL -framework AppKit

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) bonus -C ./libft
	$(MAKE) -C ./minilibx
	cp ./minilibx/libmlx.dylib ./
	 $(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -I ./includes $(MLX)  -o $(NAME)



clean:
	rm -f $(OBJS)
	rm libmlx.dylib
	make -C libft/ clean
	make -C minilibx/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx/ clean

re: fclean all