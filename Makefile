SRC			=	$(wildcard src/*.c)

OBJS		=	$(SRC:.c=.o)

CC 			=	cc
RM			=	rm -f
FLAGS		=	-Wall -Wextra -Werror

NAME		= 	philosophers

all:		$(NAME)
$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re