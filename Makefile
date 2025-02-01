NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

HEADER = fdf.h

SRCS = main.c map.c rendering.c $(GNL_SRCS) \
       utils.c handler.c map_utils.c rendering_utils.c

OBJS = $(SRCS:%.c=%.o)

RM = rm -f

all: submodules $(LIBFT) $(MLX) $(NAME)

submodules:
	@git submodule update --init --recursive get_next_line
	@git submodule update --init --recursive minilibx-linux

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) -I $(GNL_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re submodules
