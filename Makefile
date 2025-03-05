NAME = philosophers
SRC = main.c instructions.c utils.c utils2.c init.c launcher.c arguments.c
CFLAGS = -Wall -Wextra -Werror -g
OBJ = $(SRC:.c=.o)

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

.c.o:
	@cc $(CFLAGS) -c $< -o $@

clean: 
	@rm -f $(OBJ)
	@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re: fclean
	@make all

.PHONY: clean fclean re all