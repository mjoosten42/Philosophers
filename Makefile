NAME = philo
FLAGS = -Wall -Werror -Wextra

SRC = 	main.c		\
		libft.c		\
		time.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $^ -o $@

%.o: %.c
	gcc $(FLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME) 3 400 100 200

.PHONY = clean fclean re