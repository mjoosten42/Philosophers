NAME = philo_bonus
FLAGS = -Wall -Werror -Wextra

SRC = 	main.c	\
		philo.c	\
		utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): philo_bonus.h $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $@

%.o: %.c
	gcc $(FLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME) 3 180 600 600

.PHONY = clean fclean re