SRCS = cub3d.c map.c

CC = gcc
CFLAGES = -Wall -Wextra -Werror
AR = ar rcs
NAME = so_long.a
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
OUT = so_long
BONUS_OUT = so_long_bonus

GNL = get_next_line.a
GNL_DIR = ./get_next_line
MLX = libmlx.dylib
MLX_DIR = ./minilibx_mms_20200219


all : $(NAME)

$(NAME) : $(OBJS)
	make all -C $(GNL_DIR)
	make all -C $(MLX_DIR)
	@cp $(GNL_DIR)/$(GNL) $(NAME)
	@cp $(MLX_DIR)/$(MLX) .
	$(AR) $@ $(OBJS)
	$(CC) $(CFLAGES) $(NAME) $(MLX) -o $(OUT)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGES) -c $(SRCS) -I $(GNL_DIR)

clean : 
	make clean -C $(GNL_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	make fclean -C $(GNL_DIR)
	rm -rf $(NAME) $(OUT) $(BONUS) $(BONUS_OUT)
	rm -f $(MLX)

re : fclean all

bonus : $(BONUS)

$(BONUS) : $(BONUS_OBJS)
	make all -C $(GNL_DIR)
	make all -C $(MLX_DIR)
	@cp $(GNL_DIR)/$(GNL) $(BONUS)
	@cp $(MLX_DIR)/$(MLX) .
	$(AR) $@ $(BONUS_OBJS)
	$(CC) $(CFLAGES) $(BONUS) $(MLX) -o $(BONUS_OUT)

$(BONUS_OBJS) : $(BONUS_SRCS)
	$(CC) $(CFLAGES) -c $(BONUS_SRCS) -I $(GNL_DIR)

.PHONY : all clean fclean re bonus