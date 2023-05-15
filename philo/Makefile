# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:22:49 by javiersa          #+#    #+#              #
#    Updated: 2023/05/12 18:01:13 by javiersa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers.a
PROGRAM = philo
CFLAGS = -Wall -Werror -Wextra -pthread
SANITIZE = -fsanitize=thread -g
PERSONALNAME = Philosophers
CC = gcc
CLEAN = rm -Rf
SRC = main.c philo_utils.c philo_threads.c check_thread.c parse.c
PARAMS = 5 500 200 200 3
DATETIME := $(shell date +%Y-%m-%d' '%H:%M:%S)

OBJS := $(SRC:.c=.o)

all: $(PROGRAM)

$(PROGRAM): $(NAME)
	@$(CC) $(CFLAGS) $(NAME) -o $(PROGRAM)
	@echo "$(MAGENTA)Program $(PERSONALNAME) created successfully.$(DEFAULT)"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@echo "$(GREEN)Compiling:$(DEFAULT) $(notdir $<)"
	
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(MAGENTA)Library $(NAME) created successfully.$(DEFAULT)"
clean:
	@$(CLEAN) ./$(OBJS)
	@echo "$(RED)Removing:$(DEFAULT) All objects from $(PERSONALNAME)."
fclean: clean
	@$(CLEAN) ./$(NAME) ./$(PROGRAM)
	@echo "$(RED)Removing:$(DEFAULT) Library $(NAME)."
	@echo "$(RED)Removing:$(DEFAULT) Program $(PROGRAM)."
re: fclean all

#Personal use
git: fclean gitignore
	@git add *
	@echo "$(BOLD)$(YELLOW)Git:$(WHITE) Adding all archives.$(DEFAULT)"
	@git commit -m "Little changes $(DATETIME)"
	@echo "$(BOLD)$(CYAN)Git:$(WHITE) Commit this changes with "Little changes $(DATETIME)".$(DEFAULT)"
	@git push
	@echo "$(BOLD)$(GREEN)Git:$(WHITE) Pushing all changes.$(DEFAULT)"
gitignore:
	@echo ".*\n*.out\n*.o\n*.a">.gitignore
	@echo "$(GREEN)Creating:$(DEFAULT) Gitignore."
42prepare: submodules
	@rm -rf $(LIBFT)/.git
	@rm -rf $(NEXTILE)/.git
	@rm -rf $(PRINTF)/.git
	@rm -rf .git .gitmodules
	@echo "$(GREEN)All .git removed.$(DEFAULT)"
valgrind_datarace:
	valgrind --tool="helgrind" ./$(PROGRAM) $(PARAMS)
valgrind_leaks:
	valgrind --leak-check=full ./$(PROGRAM) $(PARAMS)

#COLORS
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
DEFAULT	:= \033[0m

.PHONY : all clean fclean re bonus git gitignore submodules 42prepare .c.o
