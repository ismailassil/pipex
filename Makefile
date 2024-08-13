# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassil <iassil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 09:48:55 by iassil            #+#    #+#              #
#    Updated: 2024/01/13 16:38:49 by iassil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## SOURCE FILES
SRC=			pipex.c					./_utils/ft_split.c			./_utils/ft_strjoin.c		./_utils/ft_strnstr.c	\
				./_utils/ft_strtrim.c	./_utils/_process_utils.c	./_utils/_child_process_.c	
SRC_BONUS=		pipex_bonus.c			./_utils_bonus/ft_split_bonus.c		./_utils_bonus/ft_strjoin_bonus.c		\
				./_utils_bonus/ft_strnstr_bonus.c	./_utils_bonus/ft_strtrim_bonus.c		./_utils_bonus/_child_process_bonus.c	\
				./_utils_bonus/_child_utils_bonus.c	./_utils_bonus/get_next_line/get_next_line_bonus.c	\
				./_utils_bonus/get_next_line/get_next_line_utils_bonus.c

########## HEADER FILE
HEADER=			./_header/pipex.h
HEADER_BONUS=	./_header/pipex_bonus.h	./_utils_bonus/get_next_line/get_next_line_bonus.h

########## VARIABLES
CC=				cc
CC+=			-Wall -Wextra -Werror -g
#CC+=			-fsanitize=address
NAME=			pipex
NAME_BONUS=		pipex_bonus
RM=				rm
RM+=			-f
OBJ=			$(SRC:.c=.o)
OBJ_BONUS=		$(SRC_BONUS:.c=.o)

########## DEFAULT GOAL
all: $(NAME)

### BONUS PART
bonus: $(NAME_BONUS)

########## BUILD FUNCTIONS
%.o: %.c
	@$(CC) -c -o $@ $<

$(NAME): $(OBJ) $(HEADER)
	@echo "$(YELLOW)Compilation of the Objects files...$(RESET)"
	@$(CC) -o $@ $(OBJ)
	@echo "$(GREEN)[====Executable file Compiled Successfully!====]$(RESET)"

$(NAME_BONUS): $(OBJ_BONUS) $(HEADER_BONUS)
	@echo "$(YELLOW)Compilation of the Objects files...$(RESET)"
	@$(CC) -o $@ $(OBJ_BONUS)
	@echo "$(GREEN)[====Executable file Compiled Successfully!====]$(RESET)"

######## OTHER 
re: clean all

clean:
	@echo "$(YELLOW)Removing Object files...$(RESET)"
	@$(RM) $(OBJ) $(UT_OBJ) $(OBJ_BONUS) $(UT_BONUS_OBJ)
	@echo "$(GREEN)[====Object files removed successfully!====]$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing Executable files...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)[====Executable files removed successfully!====]$(RESET)"

.PHONY: re all clean fclean

########## Define ANSI escape codes for colors
GREEN=	\033[32m
RED=	\033[31m
YELLOW=	\033[0;33m
RESET=	\033[0m # No Color
