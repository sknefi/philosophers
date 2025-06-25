NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = .
OBJDIR = obj

SRCS = 	main.c \
		init.c \
		philo.c \
		utils.c \
		clean.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

e: re clean

.PHONY: all clean fclean re e