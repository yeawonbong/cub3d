
CFLAGS = -Wall -Wextra -Werror
OUT = cub3d
LIB = cub3d.a
SRC = testmain.c \
		map.c \
		moving.c \
		pixel_put.c \
		pixel_put_wall.c \
		find_wall.c \
		draw.c \
		follow_quard.c \
		setting.c

OBJ = $(SRC:.c=.o)

# gcc -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework Appkit -g3 -fsanitize=address $(CFLAGS) $(MAIN) $(FILE) -o $(OUT) -L. -lgnl -I.
# gcc -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework Appkit $(CFLAGS) $(MAIN) $(FILE) -o $(OUT) -L. -lgnl -L. -lft -I.

all : $(OUT)

$(OUT) : $(OBJ)
	gcc -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework Appkit $(CFLAGS) $(OBJ) -o $(OUT) -L./get_next_line -lgnl -L./libft -lft -I.

$(OBJ) : $(SRC)
	gcc $(CFLAGES) -c $(SRC)

clean :
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean : clean
	rm -rf $(OUT) $(SILHANG_BONUS)

re : fclean all

.PHONY : all clean fclean bonus