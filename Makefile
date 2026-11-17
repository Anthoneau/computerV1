#BASE

NAME		=	computerv1
CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -MMD -MP -g -I${INCL_DIR}
RM			=	rm -rf
SRCS_DIR	=	srcs/
INCL_DIR	=	includes/
OBJS_DIR	=	objs/

#SOURCES

SRCS_FILES	=	main polynomial

SRCS 		= 	${addprefix ${SRCS_DIR}, ${addsuffix .cpp, ${SRCS_FILES}}}
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

${NAME}:	${OBJS}
			@${CXX} ${OBJS} -o ${NAME}
			@printf "${BGREEN}ComputerV1 compiled!${COLOR_END}\n"

${OBJS_DIR}%.o :	${SRCS_DIR}%.cpp | ${OBJSF}
			@mkdir -p $(dir $@)
			@${CXX} ${CXXFLAGS} -c $< -o $@

${OBJSF}:
			@mkdir -p ${OBJS_DIR}

clean:
			@${RM} ${OBJS_DIR}
			@${RM} ${OBJSF}
			@printf "${BCYAN}ComputerV1 .o files cleaned!${COLOR_END}\n"

fclean:		clean
			@${RM} ${NAME}
			@printf "${BBLUE}ComputerV1 files cleaned!${COLOR_END}\n"

re:			fclean all

.PHONY:		all clean fclean re

-include ${DEPS}