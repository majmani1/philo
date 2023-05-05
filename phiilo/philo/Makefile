NAME=	philo
cc=	cc
CFLAGS=	-Wall -Wextra -Werror  #-fsanitize=thread -g

AF=    philo.c   \
ft_atoi.c	\
utils_philo.c	\
utils_philo2.c	\

OBJ=    $(AF:.c=.o)

all:    $(NAME)

$(NAME):    $(OBJ)
	$(cc) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re: fclean all
