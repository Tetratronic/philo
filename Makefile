SRCS = main.c cleaning.c utils.c initialization.c monitoring.c p_routine.c parsing.c
NAME = philo
OBJS = $(SRCS:%.c=%.o)
CC = cc
HEADER = philo.h
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS)  -I. -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	make clean;

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
