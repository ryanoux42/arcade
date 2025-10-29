##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## task01
##

SRC = Ncurses.cpp

OBJ = $(SRC:.cpp=.o)

NAME = arcade_ncurses.so

NCURSES 	= 	-lncurses

all : $(NAME)

$(NAME) : $(OBJ)
	g++ -o Ncurses.o -c -fPIC Ncurses.cpp $(NCURSES)
	g++ -shared -o $(NAME) Ncurses.o $(NCURSES)
	cp $(NAME)  ../../../lib/$(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	rm -f ../../../lib/$(NAME)

re : fclean all
