##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

CCPP		=	g++

RM		=	rm -f

CPPFLAGS	=	-W -Wall -Werror -Wextra -Iinclude -fPIC

LDFLG		=       -ldl

FLG_sfml	=	-lsfml-graphics -lsfml-window -lsfml-system

FLG_sdl		=	-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf

FLG_ncurses	=	-lncurses

NAME_core	=	arcade

NAME_sfml	=	lib/lib_arcade_sfml.so

NAME_sdl	=	lib/lib_arcade_sdl.so

NAME_ncurses	=	lib/lib_arcade_ncurses.so

NAME_nibbler	=	games/lib_arcade_nibbler.so

NAME_pacman	=	games/lib_arcade_pacman.so

SRC_core	=	src/main.cpp		\
			src/Arcade.cpp

SRC_sfml	=	src/my_sfml.cpp

SRC_sdl		=	src/my_sdl.cpp

SRC_ncurses	=	src/my_ncurses.cpp

SRC_nibbler	=	src/Nibbler.cpp	\
			src/Player.cpp

SRC_pacman	=	src/Pacman.cpp \
			src/Player_p.cpp \
			src/Ennemy_p.cpp

OBJS_core	=	$(SRC_core:.cpp=.o)

OBJS_sfml	=	$(SRC_sfml:.cpp=.o)

OBJS_sdl	=	$(SRC_sdl:.cpp=.o)

OBJS_ncurses	=	$(SRC_ncurses:.cpp=.o)

OBJS_nibbler	=	$(SRC_nibbler:.cpp=.o)

OBJS_pacman	=	$(SRC_pacman:.cpp=.o)

all		:	graphicals games core

graphicals	:	$(OBJS_sdl) $(OBJS_sfml)
			$(CCPP) -shared $(OBJS_sdl) -o $(NAME_sdl) $(FLG_sdl)
			$(CCPP) -shared $(OBJS_sfml) -o $(NAME_sfml) $(FLG_sfml)

games		:	$(OBJS_nibbler) $(OBJS_pacman)
			$(CCPP) -shared $(OBJS_nibbler) -o $(NAME_nibbler)
			$(CCPP) -shared $(OBJS_pacman) -o $(NAME_pacman)

core		:	$(OBJS_core)
			$(CCPP) -o $(NAME_core) $(OBJS_core) $(CPPFLAGS) $(LDFLG)

clean		:	clean_graphicals clean_games clean_core

clean_graphicals	:
				$(RM) $(OBJS_sdl) $(OBJS_sfml) $(OBJS_ncurses)

clean_games	:
			$(RM) $(OBJS_nibbler)
			$(RM) $(OBJS_pacman)

clean_core	:
			$(RM) $(OBJS_core)

fclean		:	fclean_graphicals fclean_games fclean_core

fclean_graphicals	:	clean_graphicals
				$(RM) $(NAME_sfml) $(NAME_sdl) $(NAME_ncurses)

fclean_games	:	clean_games
			$(RM) $(NAME_nibbler) $(NAME_pacman)

fclean_core	:	clean_core
			$(RM) $(NAME_core)

re		:	fclean all

.PHONY		:	all fclean re
