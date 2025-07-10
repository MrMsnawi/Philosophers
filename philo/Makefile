OBJ_DIR = build

SRC = main.c error.c parser.c strings.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

HEADS = philo.h

NAME = philo

all : $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean