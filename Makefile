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

NAME = mandatory/pipex

NAME_BONUS = bonus/pipex

FLAGS = -Wall -Wextra -Werror

CFILES = mandatory/pipex.c mandatory/check.c mandatory/ft_split.c mandatory/pipex_utils.c mandatory/childs.c

BFILES = bonus/pipex_bonus.c bonus/pipex_utils_bonus.c bonus/check_bonus.c bonus/pipex_utils2_bonus.c bonus/pipes_mng_bonus.c \
			bonus/ft_split_bonus.c bonus/get_next_line_bonus.c bonus/pipex_heredoc_bonus.c bonus/free_all_bonus.c bonus/pipex_heredocpross_bonus.c

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(CFILES)
	cc $(FLAGS) $(CFILES) -o $(NAME)

$(NAME_BONUS): $(BFILES)
	cc $(FLAGS) $(BFILES) -o $(NAME_BONUS)
	

clean:
	rm -f $(NAME) $(NAME_BONUS)
	
fclean: clean

re : fclean all