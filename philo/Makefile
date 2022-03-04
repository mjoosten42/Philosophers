NAME = philo
FLAGS = -Wall -Werror -Wextra

SRC = 	main.c		\
		philo.c		\
		state.c		\
		utils.c		

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): philo.h $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $@

%.o: %.c
	gcc $(FLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME) 4 403 200 200 5

.PHONY = clean fclean re test