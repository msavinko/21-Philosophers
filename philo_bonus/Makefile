NAME_PHB 	=	philo_bonus
HEADER_PHB	=	philo_bonus.h

SRCS_PHB		=	philo_bonus.c 
OBJS_PHB		=	$(SRCS_PHB:%.c=%.o)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=thread #DONT FORGET TO REMOVE THIS FLAG
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

# 21 290 100 100
# 50 210 100 100
# 199 2000 600 60
# 7 190 60 60
# 8 130 60 60

# not necessarily  
# 5 260 100 100  

# CHECKLIST
# DIE
# 1 800 200 200 
# 4 310 200 100 

# DONT DIE
# 4 410 200 200 
# 5 800 200 200 
# 5 800 200 200 7 

# death delayed by more than 10 ms is unacceptable!!!


# ◦ timestamp_in_ms X has taken a fork
# ◦ timestamp_in_ms X is eating
# ◦ timestamp_in_ms X is sleeping
# ◦ timestamp_in_ms X is thinking
# ◦ timestamp_in_ms X died

# valgrind ./philo 7 190 60 60 --leak-check=full
# ps - check ongoing process
# leaks PID - check leaks of ongoing process