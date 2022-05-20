NAME_PHB 	=	philo_bonus
HEADER_PHB	=	philo_bonus.h

SRCS_PHB		=	philo_bonus.c \
					init_bonus.c \
					child_bonus.c

OBJS_PHB		=	$(SRCS_PHB:%.c=%.o)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=thread
RM			=	rm -f

.PHONY		:	all clean fclean re

all			:	$(NAME_PHB)

$(NAME_PHB)	:	$(OBJS_PHB)
			$(CC) $(CFLAGS) $(OBJS_PHB) -o $@

%.o			:	%.c $(HEADER_PHB) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

clean		:
			$(RM) $(OBJS_PHB)

fclean		:	clean
			$(RM) $(NAME_PHB)

re			:	fclean all