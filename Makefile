NAME	:= ft_nm

CFLAGS	:= -Werror -Wall -Wextra

INC 	:= includes

FILES	:=	main.c \
			char_symbol.c \
			print_data_64.c \
			print_data_32.c \
			cmp.c \
			utils.c \
			list.c \

LIB_NAME	:= ftprintf
LIB_DIR		:= ./ft_printf

$(LIB_NAME):
	@ make -C ./ft_printf
	@ echo "\033[0;32m [DONE] \033[0m"


CC		:= cc
OBJDIR	:= objs
SRCDIR  := srcs
SRCS	:= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))


all: $(NAME) 

$(NAME): $(OBJDIR) $(OBJS) $(LIB_NAME)
	@ $(CC) -o $(NAME) $(OBJS) -I $(INC) -L $(LIB_DIR) -l $(LIB_NAME)
	@ echo "\033[0;32m [DONE] \033[0m"
	

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ $(CC) $(CFLAGS) -I $(INC) -I $(LIB_DIR) -c $< -o $@
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