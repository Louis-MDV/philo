# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 13:23:42 by lmerveil          #+#    #+#              #
#    Updated: 2024/09/05 13:45:14 by louismdv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	philo

CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror -g3 -pthread

RED			= 	$(shell tput setaf 1)
GREEN		= 	$(shell tput setaf 2)
YELLOW		= 	$(shell tput setaf 3)
NC			= 	$(shell tput sgr0)

SRCS		 = 	$(addsuffix .c,				\
				$(addprefix srcs/, 			\
					monitoring				\
					init					\
					routine					\
					threads					\
					utils					\
					utils2					\
				)							\
					main					\
				)							\

OFILES		= 	$(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "$(GREEN)[$(CC)]$(NC) compilation: $(YELLOW)$<$(NC)\r\c"

all: 	$(NAME)

$(NAME): $(OFILES)
	@$(CC) $(OFILES) -o $(NAME) 
	@echo "$(GREEN)[EXECUTABLE]$(NC) created successfully: $(YELLOW)$(NAME)$(NC)"

clean:
	@rm -f $(OFILES)
	@echo "$(RED)[clean]$(NC) deleting OFILES: $(YELLOW)$(OFILES)$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[fclean]$(NC) deleting libraries: $(YELLOW)$(NAME)$(NC)"

re: fclean all
	@echo "$(GREEN)[re]$(NC) rebuilding project: $(YELLOW)$(NAME)$(NC)"

.PHONY: all clean fclean re
