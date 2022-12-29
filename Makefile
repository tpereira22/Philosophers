NAME		= philo

SRCS		= srcs/philo.c srcs/handle_philo.c srcs/handle_threads.c

OBJS		= $(SRCS:.c=.o)

LIBFTA		= ./libft/libft.a

RM		= rm -f

CC		= cc -Wall -Wextra -Werror -pthread #-g -fsanitize=address

.c.o:
			@$(CC) -c $< -o $@

all:		$(NAME)

$(NAME): 	$(LIBFTA) $(OBJS)
			$(CC) $(OBJS) $(LIBFTA) -o $(NAME)

$(LIBFTA):
			@make -C libft

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			make -C libft fclean

re:			fclean all

.PHONY:		all clean re fclean