SRCS = philo.c ft_atoi.c utils.c main.c table.c

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

%.o: %.c
			@${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re