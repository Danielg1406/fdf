NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

HEADER = fdf.h

SRCS = main.c

OBJS = $(SRCS:%.c=%.o)

RM = rm -f

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) -I . -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
