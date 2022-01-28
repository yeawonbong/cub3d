SRCS = get_next_line.c\
get_next_line_utils.c

CC = gcc
CFLAGES = -Wall -Wextra -Werror
AR = ar rcs
NAME = get_next_line.a
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $(OBJS)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGES) -c $(SRCS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	fclean all

.PHONY : all clean fclean re