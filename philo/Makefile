# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 15:34:38 by thsembel          #+#    #+#              #
#    Updated: 2021/08/04 11:27:08 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[0;92m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m

SRCS		=	./main.c \
				./utils.c \
				./start.c \

INCLUDES	=	philosopher.h \

HEAD		= ./

NAME		= philo

CC			= clang

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

#linux
#CFLAGS		= -Wall -Wextra -Werror -lpthread

.c.o:
		@${CC} ${CFLAGS} -I${HEAD} -c $< -o ${<:.c=.o}
		@echo "${GREEN}[ OK ]	${ORANGE}${<:.s=.o}${NC}"


all:		${NAME} ${NAME2}

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} -I${HEAD} -o ${NAME} $(OBJS)
			@echo "${GREEN}\nphilo  program	has been created${NC}"

clean:
			@${RM} ${OBJS}
			@echo "${GREEN}[ OK ]${RED}	*.o files	deleted${NC}"

fclean:		clean
			@${RM} ${NAME}
			@echo "${GREEN}[ OK ]${RED}	philo program	deleted${NC}"

re :		fclean all

.PHONY:		all	clean	fclean re bonus2 bonus

