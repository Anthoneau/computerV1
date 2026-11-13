#BASE

NAME		=	computer
LIBFT		=	libft/libft.a
CC			=	g++
CFLAGS		=	-Wall -Wextra -Werror
SRCS		=	main.c
RM			=	rm -rf
SRCS_DIR	=	src/
INCL_DIR	=	includes/
OBJS_DIR	=	objs/

#SOURCES

SRCS_FILES	=	main
INCL_FILES	=	

SRCS 		= 	${addprefix ${SRCS_DIR}, ${addsuffix .c, ${SRCS_FILES}}}
OBJS 		= 	${addprefix ${OBJS_DIR}, ${addsuffix .o, ${SRCS_FILES}}}

#COLORS

BGREEN		=	\033[1;32m
BBLUE		=	\033[1;34m
BCYAN		=	\033[1;36m
COLOR_END	=	\033[0m

# ---------------------------------------------------------------------------- #

MAKEFLAGS	+=	--no-print-directory
OBJSF		=	.cache_exists
DEPS		=	${OBJS:.o=.d}

all:		${NAME}

${NAME}:	${LIBFT} ${OBJS}
			@${CC} ${LDFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
			@printf "${BGREEN}Malloc compiled!${COLOR_END}\n"

${OBJS_DIR}%.o :	${SRCS_DIR}%.c | ${OBJSF}
			@mkdir -p $(dir $@)
			@${CC} ${CFLAGS} -g -c $< -o $@

${OBJSF}:
			@mkdir -p ${OBJS_DIR}

${LIBFT}:
			@make -C libft/
			@make clean -C libft/

clean:
			@${RM} ${OBJS_DIR}
			@${RM} ${OBJSF}
			@printf "${BCYAN}Malloc .o files cleaned!${COLOR_END}\n"

fclean:		clean
			@${RM} ${SYMB}
			@${RM} ${NAME}
			@${RM} ${EXEC}
			@make fclean -C libft/
			@printf "${BBLUE}Malloc files cleaned!${COLOR_END}\n"

re:			fclean all

run:		all
			@cc main.c ${LIBFT} -o ${EXEC} -g -L. -l${LNNAME}
			@LD_LIBRARY_PATH=. ./${EXEC}

stress:		all
			@cc stress_test.c ${LIBFT} -o stress -g -L. -l${LNNAME}
			@LD_LIBRARY_PATH=. ./stress

.PHONY:		all clean fclean re run

-include ${DEPS}