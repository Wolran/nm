NAME := libftprintf.a

CFLAGS	:= -Werror -Wall -Wextra

INC 	:= includes

FILES :=	ft_printf.c \
		ft_%%.c \
		ft_%c.c \
		ft_%s.c \
		ft_%di.c \
		ft_%u.c \
		ft_%x.c \
		ft_%p.c \
		ft_putnbr_base.c

CC		:= cc
AR		:= ar rcs
OBJDIR	:= objs
SRCDIR  := srcs
SRCS	:= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@ $(AR) $(NAME) $(OBJS)
	@ echo "\033[0;32m [PRINTF DONE] \033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ $(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@ echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling: \033[0m  $<"

$(OBJDIR):
	@ mkdir -p $@
	@ echo "\033[0;32m [OK] \033[0m       \033[0;33m Creating: \033[0m   $(OBJDIR) folder"

clean:
	@ $(RM) -r $(OBJDIR)
	@ echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleting: \033[0m   $(OBJDIR)"

fclean: clean
	@ $(RM) $(NAME)
	@ echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleting: \033[0m   $(NAME)"

re: fclean all

.PHONY: all clean fclean re
