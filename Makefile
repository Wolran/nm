NAME	:= ft_nm

CFLAGS	:= -Werror -Wall -Wextra

INC 	:= includes

FILES	:= main.c \
		   elf32.c \
		   elf64.c \
		   print.c \
		
CC		:= cc
OBJDIR	:= objs
SRCDIR  := srcs
SRCS	:= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))


all: $(NAME) 

$(NAME): $(OBJDIR) $(OBJS)
	@ $(CC) -o $(NAME) $(OBJS) -L $(INC)
	@ echo "\033[0;32m [DONE] \033[0m"
	

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ $(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling: \033[0m  " $(<)

$(OBJDIR):
	@ mkdir -p $@
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Creating: \033[0m   " $(OBJDIR) folder

clean:
	@ $(RM) -r $(OBJDIR)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleting: \033[0m   " $(OBJDIR)

fclean: clean
	@ ${RM} ${NAME}
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleting: \033[0m   " $(NAME)
	

re: fclean all
	
.PHONY: all clean fclean re