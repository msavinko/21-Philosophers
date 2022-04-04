NAME_PH = philosophers
HEADER_PH	=	philosophers.h

SRCS_PH	=	philo.c philo_utils.c
OBJS_PH		=	$(SRCS_PH:%.c=%.o)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

.PHONY		:	all clean fclean re

all			:	$(NAME_PH)

$(NAME_PH)	:	$(OBJS_PH)
			$(CC) $(OBJS_PH) -o $@

%.o			:	%.c $(HEADER_PH) Makefile
			$(CC) $(CFLAGS) -I $(HEADER_PH) -c $< -o $@

clean		:
			$(RM) $(OBJS_PH) $(OBJS_PHB)

fclean		:	clean
			$(RM) $(NAME_PH) $(NAME_PHB)

re			:	fclean all