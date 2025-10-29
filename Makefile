##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## root
##

SRC	        =	src/main.cpp 	\
				src/LibLoad.cpp 	\
				src/Core.cpp 		\
				src/SafeDirectoryLister.cpp 	\
				src/Menu.cpp 	\

OBJ	        =	$(SRC:.cpp=.o)

NAME	    =	arcade

CC 		    =	g++

CPPFLAGS	=	-I ./src

# CFLAGS      =   -Wall -Wextra
CXXFLAGS      =   -std=c++20 -Wall -Wextra -Werror -fno-gnu-unique -g3

all : $(NAME)

$(NAME) :	$(OBJ) core games graphicals

core :	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

games :
	make -C src/Games

graphicals :
	make -C src/Graphicals

clean :
	rm -f $(OBJ)
	make clean -C src/Games
	make clean -C src/Graphicals

fclean : clean
	rm -f $(NAME)
	make fclean -C src/Games
	make fclean -C src/Graphicals

re : fclean all

tests_run:
	$(CC) $(OBJ) $(TSRC) --coverage -lcriterion -I ./includes/ -o unit_tests

coverage:
	gcovr --exclude tests/

.PHONY: re clean fclean all tests_run coverage core games graphicals
