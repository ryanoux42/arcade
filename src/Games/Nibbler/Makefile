##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Nibbler
##

SRC = Nibbler.cpp

OBJ = $(SRC:.cpp=.o)

NAME = arcade_nibbler.so

all : $(NAME)

$(NAME) : $(OBJ)
	g++ -o Nibbler.o -c -fPIC Nibbler.cpp
	g++ -shared -o $(NAME) Nibbler.o
	cp $(NAME) ../../../lib/$(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re : fclean all
