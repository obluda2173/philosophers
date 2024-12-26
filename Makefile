# **************************************************************************** #
# CONFIG                                                                       #
# **************************************************************************** #
NAME		=	philo

# Compiler and flags
CC 			=	@cc
RM			=	@rm -f
FLAGS		=	-Wall -Wextra -Werror 

# Directories and source files
SRC_DIR		=	src
SRC			=	$(SRC_DIR)/philosophers.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/launcher.c

OBJS		=	$(SRC:.c=.o)

# **************************************************************************** #
# COLORS                                                                       #
# **************************************************************************** #
BLUE        =   \033[0;94m
RED         =   \033[0;91m
GREEN       =   \033[0;92m
YELLOW      =   \033[0;33m
CYAN        =   \033[0;96m
COLOR       =   \033[0m

# Messages
SUCCESS     =   @echo "$(GREEN)Philosophers compiled successfully$(COLOR)"
S_OBJS      =   @echo "$(BLUE)Cleaning of objects completed$(COLOR)"
S_NAME      =   @echo "$(BLUE)Full clean completed$(COLOR)"

# **************************************************************************** #
# RULES                                                                        #
# **************************************************************************** #
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)
			$(SUCCESS)

clean:
			$(RM) $(OBJS)
			$(S_OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(S_NAME)

re: 		fclean all

# **************************************************************************** #
# PHONY                                                                        #
# **************************************************************************** #
.PHONY:		all clean fclean re