# Colors
DEF_COLOR   = "\033[0;39m"
GRAY        = "\033[0;90m"
YELLOW      = "\033[0;93m"
GREEN       = "\033[0;92m"
RED         = "\033[0;91m"
BLUE        = "\033[0;94m"
MAGENTA     = "\033[0;95m"
CYAN        = "\033[0;96m"
WHITE       = "\033[0;97m"
ORANGE      = "\033[38;5;222m"
GREEN_BR    = "\033[38;5;118m"
YELLOW_BR   = "\033[38;5;227m"
PINK_BR     = "\033[38;5;206m"
BLUE_BR     = "\033[38;5;051m"
PINK_BRR    = "\033[38;5;219m"

# Text styles
BOLD        = "\033[1m"
UNDERLINE   = "\033[4m"
BLINK       = "\033[5m"

NAME = sat

CC = c++
CPP_FLAGS = -Wall -Werror -Wextra

RM = rm -rf

FILES = ex07

SRCS = $(addsuffix .cpp, $(FILES))

HDRS = $(wildcard *.hpp)

OBJS_DIR = obj
OBJ_DIRS = $(OBJS_DIR)
OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

$(OBJS_DIR)/%.o: %.cpp
	@printf $(GRAY)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CPP_FLAGS) -c -o $@ $<

all: $(NAME)
	@printf $(BOLD)$(GREEN_BR)"\n"
	@printf $(BOLD)$(GREEN_BR)"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣶⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf $(BOLD)$(GREEN_BR)"⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣦⣄⣀⡀⣠⣾⡇⠀⠀⠀⠀\n"
	@printf $(BOLD)$(GREEN_BR)"⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀\n"
	@printf $(BOLD)$(GREEN_BR)"⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⢿⣿⣿⡇⠀⠀⠀⠀\n"
	@printf $(BOLD)$(GREEN_BR)"⠀⣶⣿⣦⣜⣿⣿⣿⡟⠻⣿⣿⣿⣿⣿⣿⣿⡿⢿⡏⣴⣺⣦⣙⣿⣷⣄⠀⠀⠀\n"
	@printf $(BOLD)$(GREEN_BR)"⠀⣯⡇⣻⣿⣿⣿⣿⣷⣾⣿⣬⣥⣭⣽⣿⣿⣧⣼⡇⣯⣇⣹⣿⣿⣿⣿⣧⠀⠀\n"
	@printf $(BOLD)$(GREEN_BR)"⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⣿⣿⣿⣿⣿⣿⣿⣷⠀\n\n"
	@printf $(BOLD)$(ORANGE)"💥 SAT 💥\n\n"

$(NAME): $(OBJS)
	@printf $(GRAY)
	$(CC) $(CPP_FLAGS) -o $(NAME) $(OBJS)
	@printf $(DEF_COLOR)

clean:
	@printf $(YELLOW)
	$(RM) $(OBJS_DIR) $(NAME)
	@printf $(DEF_COLOR)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
