NAME_PH 	=	philo
HEADER_PH	=	philo.h

SRCS_PH		=	philo.c \
				philo_init.c \
				philo_utils.c\
				action.c

OBJS_PH		=	$(SRCS_PH:%.c=%.o)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

.PHONY		:	all clean fclean re

all			:	$(NAME_PH)

$(NAME_PH)	:	$(OBJS_PH)
			$(CC) $(CFLAGS) $(OBJS_PH) -o $@

%.o			:	%.c $(HEADER_PH) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

clean		:
			$(RM) $(OBJS_PH)

fclean		:	clean
			$(RM) $(NAME_PH)

re			:	fclean all