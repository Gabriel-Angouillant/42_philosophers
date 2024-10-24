NAME = philo
CC = cc
SRCS = routines.c \
		forks.c \
		lst_utils.c \
		philo_utils.c \
		init.c \
		main.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ -o $(NAME)
	@echo "\033[1;32m -= Sources compiled =-"
	
%.o: %.c
	@$(CC) $(FLAGS) $< -c -o $@

clean:
	@rm -f $(OBJS)
	@echo "\033[1;31m -= Sources removed =-"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31m -= Executable removed =-"

re: fclean all
