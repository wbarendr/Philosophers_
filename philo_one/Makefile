# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: wbarendr <wbarendr@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/08 14:53:04 by wbarendr      #+#    #+#                  #
#    Updated: 2020/12/07 18:18:03 by wester        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
END = "\033[0m"

SRCS =	main output_functions utilities initialize sleep_functions \
		error_functions

CFILES  = $(SRCS:%=%.c)

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -o $(NAME) $(CFILES)
	@echo $(GREEN) COMPILED PHILO_ONE $(END)

clean:
	@rm -f $(NAME)
	@echo $(YELLOW) CLEANED $(END)

fclean: clean

re: fclean all
