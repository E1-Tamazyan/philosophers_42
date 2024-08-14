CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS =  main.c checks.c libft_utils.c regimen.c utils.c

INCS = philo.h

NAME = philo

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c Makefile $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

.PHONY: all re clean fclean