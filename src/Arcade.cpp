//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Arcade.cpp
//

#include "Arcade.hpp"

Arcade::Arcade(std::string path)
{
	dl_lib = load_lds("./lib/", path);
	dl_game = load_lds("./games/", "");
	init_lds();
	if (lib_list.find(path) != lib_list.end())
		cur_lib = lib_list[path];
	if (game_list.size() > 0)
		cur_game = game_list.begin()->second;
}

Arcade::~Arcade()
{
	delete_lds();
}

std::pair<std::string, void*>	Arcade::load_one_ld(std::string path)
{
	std::pair<std::string, void*>	to_insert;

	to_insert.first = path;
	to_insert.second = dlopen(path.c_str(), RTLD_LAZY);
	if (!to_insert.second)
		std::cerr << "Cannot load library: " << dlerror() << '\n';
	dlerror();
	return to_insert;
}

std::map<std::string, void*>	Arcade::load_lds(std::string folder,
						std::string user)
{
	std::string	path = folder;
	DIR		*dir = opendir(path.c_str());
	std::map<std::string, void*>	res;
	std::pair<std::string, void*>   tmp;

	(void) user;
	// uncomment for append "user lib" at ./lib/
	if (!dir /* || (!load_one_ld(user).second && folder == "./lib/"*/)
		return res;
	// else if (folder == "./lib/")
	// 	res.insert(load_one_ld(user));
	for (struct dirent *e = readdir(dir) ; e ; e = readdir(dir))
		if (e->d_type == 0x8){
			path = folder + std::string(e->d_name);
			if (path.find(".so", path.size() - 3) != std::string::npos){
				tmp = load_one_ld(path);
				if (tmp.second)
					res.insert(tmp);
			}
		}
	return res;
}

void	Arcade::delete_lds()
{
	t_destroy*	destroyer;
	
	for (const auto& ld : dl_lib){
		destroyer = (t_destroy*) dlsym(ld.second, "destroy");
		destroyer(lib_list[ld.first]);
		dlclose(ld.second);
	}
	for (const auto& ld : dl_game){
		destroyer = (t_destroy*) dlsym(ld.second, "destroy");
		destroyer(game_list[ld.first]);
		dlclose(ld.second);
	}
}

void	Arcade::init_lds()
{
	std::pair<std::string, IDisplay*>	to_insert_lib;
	std::pair<std::string, IGame*>		to_insert_game;
	t_create_lib*	creator_l;
	t_create_game*	creator_g;
	
	for (const auto& ld : dl_lib){
		creator_l = (t_create_lib*) dlsym(ld.second, "create");
		to_insert_lib.first = ld.first;
		to_insert_lib.second = creator_l();
	        lib_list.insert(to_insert_lib);
	}
	for (const auto& ld : dl_game){
		creator_g = (t_create_game*) dlsym(ld.second, "create");
		to_insert_game.first = ld.first;
		to_insert_game.second = creator_g();
	        game_list.insert(to_insert_game);
	}
}

void	Arcade::exec_events()
{
	static int	timer = 0;
	int	event = cur_lib->get_event();

	if (timer == 0 && event != 0){
		if (event >= 2 && event <= 3)
			change_ld((event + 1) % 2);
		else if (event >= 4 && event <= 7)
			cur_game->move_player(event);
		else if (event >= 8 && event <= 9)
			change_game((event + 1) % 2);
		if (event == 10)
			cur_game->restart();
		timer++;
	}
	if (timer > 10)
		timer = 0;
	else if (timer > 0)
		timer++;
}

IDisplay*	Arcade::get_lib() const
{
	return cur_lib;
}

IGame*		Arcade::get_game() const
{
	return cur_game;
}

void	Arcade::change_ld(int dir)
{
	std::string	cur_name = "./lib/" + cur_lib->get_name();
	std::map<std::string, IDisplay*>::iterator	it;

	it = lib_list.find(cur_name);
	if (dir > 0 && std::distance(it, lib_list.end()) > 1)
	        it++;
	else if (dir == 0 && it != lib_list.begin())
		it--;
	if (it != lib_list.find(cur_name)){
		cur_lib->destroy_window();
		cur_lib = it->second;
		init_lib();
	}
}

void	Arcade::init_lib()
{
	std::map<std::string, std::string>	tmp = cur_game->get_sprites();

	cur_lib->create_window(WIN_X, WIN_Y, "Arcade");
	for (const auto& a : tmp)
		cur_lib->set_sprite(a.first, a.second);
}

void	Arcade::display_all()
{
	std::map<std::string, std::vector<pos_sprite>>	tmp;
	std::vector<pos_sprite>		pos;

	tmp = cur_game->get_all_pos();
	for (const auto& a : tmp){
		pos = a.second;
		for (const auto& b : pos)
			cur_lib->display_sprite(a.first, mPos(b.x, b.y),
						b.dir);
	}
}

void	Arcade::change_game(int dir)
{
	std::string	cur_name = "./games/" + cur_game->get_name();
	std::map<std::string, IGame*>::iterator	it;
	std::map<std::string, std::string>	tmp;

	it = game_list.find(cur_name);
	if (dir > 0 && std::distance(it, game_list.end()) > 1)
		it++;
	else if (dir == 0 && it != game_list.begin())
		it--;
	if (it != game_list.find(cur_name)){
		cur_game = it->second;
		tmp = cur_game->get_sprites();
		for (const auto& a : tmp)
			cur_lib->set_sprite(a.first, a.second);
	}
}
