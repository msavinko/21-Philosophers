NAME_PH = philosophers
NAME_PHB = philosophers_bonus

INCLUDES_SL	=	includes/
HEADER_PH	=	includes/philosophers.h
HEADER_PHB	=	includes/philosophers_bonus.h

DIR_PH		=	src/
DIR_PHB		=	bonus/

FILES_PH	=	

FILES_PHB	=	

SRCS_PH		=	$(addprefix $(DIR_PH), $(FILES_PH))
SRCS_PHB	=	$(addprefix $(DIR_PHB), $(FILES_PHB))

OBJS_PH		=	$(SRCS_PH:%.c=%.o)
OBJS_PHB	=	$(SRCS_SPB:%.c=%.o)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

.PHONY		:	all clean fclean re libft bonus

all			:	libft $(NAME_SL)

libft		:
			@make -C libft/

bonus		:
			@make NAME_SL="$(NAME_SLB)" \
			HEADER_SL="$(HEADER_SLB)" \
			OBJS_SL="$(OBJS_SLB)" all

$(NAME_SL)	:	$(OBJS_SL)
			$(CC) $(OBJS_SL) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $@

%.o			:	%.c $(LIBFT) $(HEADER_SL) Makefile
			$(CC) $(CFLAGS) -I $(INCLUDES_SL) -c $< -o $@

clean		:
			$(RM) $(OBJS_SL) $(OBJS_SLB)
			make -C libft/ clean

fclean		:	clean
			$(RM) $(NAME_SL) $(NAME_SLB)
			make -C libft/ fclean

re			:	fclean all