# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: wbarendr <wbarendr@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/08 14:53:04 by wbarendr      #+#    #+#                  #
#    Updated: 2020/12/09 16:32:15 by wester        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
END = "\033[0m"

SRCS =	main output_functions utilities initialize sleep_functions \
		extra_functions

CFILES  = $(SRCS:%=%.c)

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -o $(NAME) $(CFILES)
	@echo $(GREEN) COMPILED PHILO_THREE $(END)

clean:
	@rm -f $(NAME)
	@echo $(YELLOW) CLEANED $(END)

fclean: clean

re: fclean all
