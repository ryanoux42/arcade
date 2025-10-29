##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## task01
##

SRC = Pacman.cpp

OBJ = $(SRC:.cpp=.o)

NAME = arcade_pacman.so

all : $(NAME)

$(NAME) : $(OBJ)
	g++ -o Pacman.o -c -fPIC Pacman.cpp
	g++ -shared -o $(NAME) Pacman.o
	cp $(NAME) ../../../lib/$(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re : fclean all
