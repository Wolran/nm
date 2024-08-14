NAME = libftprintf.a

SRCS		=		ft_printf.c ft_%%.c ft_%c.c ft_%s.c ft_%di.c \
				ft_%u.c ft_%x.c ft_%p.c ft_putnbr_base.c


OBJ = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g3

COMPILE = gcc $(CFLAGS) -c

LIB = ar rcs $(NAME)

REMOVE = rm -f

all: $(NAME)

$(NAME):	$(OBJ)
	@$(LIB) $(OBJ)
clean:
	@$(REMOVE) $(OBJ)

fclean: clean
	@$(REMOVE) $(NAME)

re: fclean all

.PHONY: all clean fclean re 
