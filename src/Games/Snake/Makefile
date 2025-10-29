##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## task01
##

SRC = Snake.cpp

OBJ = $(SRC:.cpp=.o)

NAME = arcade_snake.so

all : $(NAME)

$(NAME) : $(OBJ)
	g++ -o Snake.o -c -fPIC Snake.cpp
	g++ -shared -o $(NAME) Snake.o
	cp $(NAME) ../../../lib/$(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re : fclean all
