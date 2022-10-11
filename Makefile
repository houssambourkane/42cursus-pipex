# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 10:03:21 by hbourkan          #+#    #+#              #
#    Updated: 2021/12/23 10:24:09 by hbourkan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color
BLACK = \e[30m
RED = \e[31;52m
RED_BOLD = \e[1;31m

GREEN = \e[32m
GREEN_BOLD = \e[1;32m
YELLOW = \e[33m
YELLOW_UNDERLINE = \e[4;33m
BLUE = \e[34m
BLUE_BOLD = \e[1;34m
MAGENTI = \e[35m
MAGENTI_BOLD = \e[1;35m
CYAN = \e[36m
WHITE = \e[37m
RESET= \e[0m

NAME = mandatory/pipex

NAME_BONUS = bonus/pipex

FLAGS = -Wall -Wextra -Werror

CFILES = mandatory/pipex.c \
		mandatory/check.c \
		mandatory/ft_split.c \
		mandatory/pipex_utils.c \
		mandatory/childs.c

BFILES = bonus/pipex_bonus.c \
		bonus/pipex_utils_bonus.c \
		bonus/check_bonus.c \
		bonus/pipex_utils2_bonus.c \
		bonus/pipes_mng_bonus.c \
		bonus/ft_split_bonus.c \
		bonus/get_next_line_bonus.c \
		bonus/pipex_heredoc_bonus.c \
		bonus/free_all_bonus.c \
		bonus/pipex_heredocpross_bonus.c

OFILES = $(CFILES:%.c=%.o)

OBFILES = $(BFILES:%.c=%.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OFILES)
	@cc $(FLAGS) $(OFILES) -o $(NAME)
	@printf "🚀 $(GREEN)Mandatory compilation done $(RESET)\n"

$(NAME_BONUS): $(OBFILES)
	@cc $(FLAGS) $(BFILES) -o $(NAME_BONUS)
	@printf "🚀 $(MAGENTI)Bonus compilation done $(RESET)\n"

%.o : %.c
	@cc $(FLAGS) -c  $< -o $@
	@printf "🚀 $(CYAN)Generating $(YELLOW_UNDERLINE)$@ $(RESET)$(CYAN)from $(YELLOW_UNDERLINE)$<$(RESET) 🔥\n"

clean:
	@rm -f $(OFILES)
	@rm -f $(OBFILES)
	@printf "🚀 $(RED)Objects files cleaned $(RESET)\n"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@printf "🚀 $(RED_BOLD)Binary file cleaned $(RESET)\n"


re : fclean all
	@printf "🚀 $(BLACK)Recompilation... $(RESET)\n"
