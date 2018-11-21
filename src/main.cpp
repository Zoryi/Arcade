/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** main.c
*/

#include "Arcade.hpp"

#include <unistd.h>

void	loop_game(Arcade* arc, IGame* game)
{
	arc = arc;
	game->move_all();
}

void	loop_lib(Arcade* arc, IDisplay* lib)
{
	lib->clear();
	arc->display_all();
	if (!arc->get_game()->is_end()){
		lib->display_text(std::to_string(arc->get_game()->get_score()),
				1200, 100);
		lib->display_text(
			std::to_string(arc->get_game()->get_life_player()),
				1140, 330);
		lib->display_text(std::to_string(arc->get_game()->get_level()),
				1140, 570);
	}
	lib->update_window();
}

void	loop(Arcade* arc)
{
	IDisplay*	lib = arc->get_lib();
	IGame*		game = arc->get_game();

	lib->create_window(WIN_X, WIN_Y, "Arcade");
	arc->init_lib();
	while (lib->isOpen()){
		if (!game->is_end())
			loop_game(arc, game);
		loop_lib(arc, lib);
		arc->exec_events();
		game = arc->get_game();
		lib = arc->get_lib();
	}
}

int	main(int ac, char** av)
{
	Arcade*		arc = NULL;

	if (ac == 2)
		arc = new Arcade(av[1]);
	if (!arc || arc->get_game() == NULL || arc->get_lib() == NULL){
		std::cerr << "Erreur lors de l'initalisation des libraries ";
		std::cerr << "partagées" << std::endl;
		return 84;
	}else{
		loop(arc);
		delete arc;
	}
	return 0;
}
