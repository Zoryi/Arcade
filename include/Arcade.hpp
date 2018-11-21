//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Arcade.hpp
//

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <map>
#include "IDisplay.hpp"
#include "IGame.hpp"


#define WIN_X 1300
#define WIN_Y 1200

typedef IDisplay*	t_create_lib();
typedef IGame*	t_create_game();
typedef void	t_destroy(void*);

class Arcade
{
public:
	Arcade(std::string path);
	~Arcade();
	IDisplay*	get_lib() const;
	IGame*		get_game() const;
	void		display_all();
	void		change_ld(int dir);
	void		change_game(int dir);
	void		init_lib();
	void		exec_events();

private:
	std::pair<std::string, void*>	load_one_ld(std::string path);
	std::map<std::string, void*>	load_lds(std::string folder,
						std::string user);
	void	init_lds();
	void	delete_lds();

	std::map<std::string, void*>	dl_game;
	std::map<std::string, IGame*>	game_list;
	IGame*		cur_game;
	std::map<std::string, void*>	dl_lib;
	std::map<std::string, IDisplay*>	lib_list;
	IDisplay*	cur_lib;
};

#endif
