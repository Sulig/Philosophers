# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 11:51:06 by sadoming          #+#    #+#              #
#    Updated: 2024/02/02 17:35:23 by sadoming         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Default arguments for make run
DEF = 1 400 200 200
DEF = 2 400 200 200
DEF = 100 800 200 200 #No Philo should die!
DEF = 10 800 200 100 2 #Stop when all eaten 2 times
# ------------------ #
# Flags:

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -pthread
CFLAGSF = -Wall -Wextra -Werror -fsanitize=thread -g
# ------------------ #
# Sources:

MAK = Makefile

LIB = philo.h

SRC = philo_main.c ft_check_errors.c ft_man_structs.c ft_actions.c\
	  ft_print_stat.c ft_pthreads.c ft_monitoring.c ft_utils.c

OBJ = $(SRC:%.c=%.o)
# ******************************************************************************* #
#-------------------------------------------------------------#
all: $(NAME)
#-------------------------------------------------------------#
#-------------------------------------------------------------#
norm:
	@echo "\n\033[1;93m\n~ Norminette:\n"
	@norminette
	@echo "\n~~~~~~~~~~~~~~~~~~~~~~\n"
	@norminette -R CheckForbiddenSourceHeader
	@echo "\033[1;32m\n ~ Norminette:\t~ OK\n"
	@echo "~~~~~~~~~~~~~~~~~~~~~~\n"
#-------------------------------------------------------------#
#-------------------------------------------------------------#
run: $(NAME)
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo " ~ Running ./$(NAME) $(DEF)"
	@echo "\n~ **************************************** ~ \033[1;37m\n"
	@./$(NAME) $(DEF)

#-------------------------------------------------------------#
# ******************************************************************************* #
# Compiling Region:

$%.o: %.c $(LIB) $(MAK)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB) $(MAK)
	@echo "\033[1;37m\n~ **************************************** ~\n"
	@echo "\033[1;93m * Making $(NAME) -->\033[1;97m\n"
	@$(CC) $(OBJ) -o $(NAME)
	@echo "\033[1;35m\n~ **************************************** ~\n"
	@echo "  ~\t    Philosophers is ready!\t       ~\n"
	@echo "~ **************************************** ~\n"
#-------------------------------------------------------------#
# ******************************************************************************* #
# Debuging region:

debug: $(NAME)
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo " ~ Running ./$(NAME) $(DEF)"
	@echo "\n~ **************************************** ~\n"
	@lldb $(NAME) $(DEF)

# ------------------

fsanitize:
	$(CC) $(CFLAGSF) $(SRC) $(LIB)
	@./a.out $(DEF)
	
# ------------------

leaks: $(NAME)
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo " ~ Running ./$(NAME) $(DEF)"
	@echo "\n~ **************************************** ~\n"
	@leaks -atExit -- ./$(NAME) $(DEF)

# ------------------

val: $(NAME)
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo " ~ Running ./$(NAME) $(DEF)"
	@echo "\n~ **************************************** ~\n"
	@valgrind --leak-check=full -s ./$(NAME) $(DEF)

val_fsn:
	$(CC) $(CFLAGSF) $(SRC) $(LIB)
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo " ~ Running ./a.out $(DEF)"
	@echo "\n~ **************************************** ~\n"
	@./a.out $(DEF)
	@valgrind --leak-check=full -s ./a.out $(DEF)

# ********************************************************************************* #
# Clean region

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[1;34m\n All obj removed\033[1;97m\n"


fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out
	@/bin/rm -f $(LIB).gch
	@/bin/rm -frd $(NAME).dSYM
	@/bin/rm -frd a.out.dSYM
	@find ../ -name ".DS_Store" -type f -delete
	@echo "\033[1;34m All cleaned succesfully\033[1;97m\n"

clear: fclean
	@clear

re: fclean all
# -------------------- #
.PHONY: all clean clear fclean fsanitize
.PHONY: debug leaks norm re run val val_fsn trueall
# ********************************************************************************** #
