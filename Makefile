NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

INCLUDES = -I/usr/include -Imlx

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = main.c map.c game.c utils.c ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(MLX_LIB) $(NAME)


$(NAME): $(OBJ)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
