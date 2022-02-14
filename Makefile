##
## EPITECH PROJECT, 2022
## malloc
## File description:
## Makefile
##

NAME	=	libmy_malloc.so

SOURCE	=	lib/malloc.c 		\
			lib/my_putnbr.c 	\

OBJECT	=	$(SOURCE:.c=.o)

CC		=	gcc

RM		=	rm -rf

CFLAGS	=	-fPIC -I include

$(NAME):	$(OBJECT)
	$(CC) -o $(NAME) $(OBJECT) $(CFLAGS) -shared

all:	$(NAME)

clean:
	$(RM) $(OBJECT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:re fclean clean all