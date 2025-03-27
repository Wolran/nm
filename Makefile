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

CC		:= cc
OBJDIR	:= objs
SRCDIR  := srcs
SRCS	:= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	:= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))


all: $(NAME) 

$(NAME): $(OBJDIR) $(LIB_NAME) $(OBJS)
	@ $(CC) -o $(NAME) $(OBJS) -I $(INC) -L $(LIB_DIR) -l $(LIB_NAME)
	@ echo "\033[0;32m [DONE] \033[0m"

$(LIB_NAME):
	@ make -C $(LIB_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ $(CC) $(CFLAGS) -I $(INC) -I $(LIB_DIR) -c $< -o $@
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling: \033[0m  " $(<)

$(OBJDIR):
	@ mkdir -p $@
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Creating: \033[0m   " $(OBJDIR) folder

clean:
	@ make clean -C $(LIB_DIR)
	@ $(RM) -r $(OBJDIR)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleting: \033[0m   " $(OBJDIR)

fclean: clean
	@ make fclean -C $(LIB_DIR)
	@ ${RM} ${NAME}
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Deleting: \033[0m   " $(NAME)
	

re: fclean all
	
.PHONY: all clean fclean re
