NAME = a 

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c utils.c init.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

e: re clean

.PHONY: all clean fclean re e