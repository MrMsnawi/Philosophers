SRC = 	main.c \
		error.c \
		inits.c \
		monitor.c \
		parser.c \
		philos_op.c \
		philosophers.c \
		strings.c \
		utils.c

OBJ = $(SRC:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror #-pthread -fsanitize=thread
NAME = philo

all : $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean
