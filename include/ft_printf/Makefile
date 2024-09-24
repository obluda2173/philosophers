NAME = libftprintf.a

SRC = ft_printf.c ft_printf_util.c
OBJS = $(SRC:.c=.o)

LIBFTDIR = ../Libft/
LIBFT = $(LIBFTDIR)libft.a

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

libft_build:
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re
