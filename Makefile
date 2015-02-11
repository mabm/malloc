##
## Makefile for Makefile in /home/barnea_v/Downloads
## 
## Made by Viveka BARNEAUD
## Login   <barnea_v@epitech.net>
## 
## Started on  Wed Feb 11 14:41:51 2015 Viveka BARNEAUD
## Last update Wed Feb 11 14:57:46 2015 Viveka BARNEAUD
##

NAME=		libmy_malloc_$(HOSTTYPE).so

SRC=		malloc.c

OBJ=		$(SRC:.c=.o)

CFLAGS+=	-W -Wall -Wextra -Werror

all:		$(OBJ)
		gcc -shared -fPIC $(SRC) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
