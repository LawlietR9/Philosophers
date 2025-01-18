NAME = philo

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC = 	src/main.c\
		src/init.c\
		src/routine.c\
		src/utils.c\

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	gcc $(CFLAGS) $(SRC) -o $(NAME)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJ)

re : fclean all
