NAME		= philo

SRCS		= srcs/philo.c srcs/philo_utils.c srcs/handle_philo.c srcs/handle_threads.c srcs/handle_actions.c srcs/handle_mutex.c srcs/close_sim.c

OBJS		= $(SRCS:.c=.o)

RM		= rm -f

CC		= cc -Wall -Wextra -Werror -pthread #-g -fsanitize=address

.c.o:
			@$(CC) -c $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean re fclean