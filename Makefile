SHELL = bash
GREEN = "\033[32m"
YELLOW = "\033[33m"
RESET = "\033[0m"

CFLAGS = -Wall -Wextra -Werror
OUT = cub3d
SRC = cub3d.c \
		map.c \
		map_util.c \
		moving.c \
		stopping.c \
		pixel_put.c \
		pixel_put_wall.c \
		find_wall.c \
		draw.c \
		follow_quard.c \
		follow_while.c \
		setting.c

OBJ = $(SRC:.c=.o)

LIBS = libft/libft.a \
		get_next_line/libgnl.a

# gcc -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework Appkit -g3 -fsanitize=address $(CFLAGS) $(MAIN) $(FILE) -o $(OUT) -L. -lgnl -I.
# gcc -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework Appkit $(CFLAGS) $(MAIN) $(FILE) -o $(OUT) -L. -lgnl -L. -lft -I.

all : $(OUT)

$(OUT) : $(OBJ) $(LIBS)
	@echo -en 'Assembling ['$(YELLOW)'$@'$(RESET)']... '
	@gcc -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework Appkit $(CFLAGS) $(OBJ) -o $(OUT) -L./get_next_line -lgnl -L./libft -lft -I.
	@echo -e $(GREEN)✔$(RESET)

$(OBJ) : $(SRC)
	@echo -n "Compiling... "
	@gcc $(CFLAGES) -c $(SRC)
	@echo -e $(GREEN)✔$(RESET)

$(LIBS) : ./libft ./get_next_line
	@echo -en 'Archiving ['$(YELLOW)'libft.a libgnl.a'$(RESET)']... '
	@make -C libft
	@make -C get_next_line
	@echo -e $(GREEN)✔$(RESET)

clean :
	@echo -n "Cleaning obj files... "
	@rm -f $(OBJ)
	@make clean -C libft
	@make clean -C get_next_line
	@echo -e $(GREEN)✔$(RESET)

fclean : clean
	@echo -n "Cleaning all... "
	@rm -f $(OUT)
	@make fclean -C libft
	@make fclean -C get_next_line
	@echo -e $(GREEN)✔$(RESET)

re : fclean all

.PHONY : all clean fclean bonus