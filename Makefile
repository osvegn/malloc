##
## EPITECH PROJECT, 2022
## malloc
## File description:
## Makefile
##

NAME	=	libmy_malloc.so

SOURCE	=	lib/malloc.c 				\
			lib/first_and_end_block.c 	\
			lib/calloc.c 				\
			lib/create_block.c 			\
			lib/find_free_space.c 		\
			lib/free.c 					\
			lib/realloc.c 				\
			lib/set_free_block.c 		\
			lib/my_putnbr.c 			\

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