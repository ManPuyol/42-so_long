NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = main.c map.c game.c utils.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLXFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
