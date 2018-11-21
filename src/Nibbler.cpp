//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Nibbler.cpp
//

#include "Nibbler.hpp"

Nibbler::Nibbler(int sx, int sy) : player(pos_sprite(5 * 52, 17 * 52, 1))
{
	size.first = sx - sx / 5;
	size.second = sy;
	score = 0;
	level = 1;
	init_map();
	init_target();
}

Nibbler::~Nibbler()
{
}

void	Nibbler::restart()
{
	player = Player(pos_sprite(5 * 52, 17 * 52, 1));
	score = 0;
	level = 1;
	init_map();
	init_target();
}

std::string	Nibbler::get_name() const
{
	return std::string("lib_arcade_nibbler.so");
}

int		Nibbler::get_score() const
{
	return score;
}

int		Nibbler::get_level() const
{
	return level;
}

std::map<std::string, std::string>	Nibbler::get_sprites()
{
	std::map<std::string, std::string>	res;

	res["playerH"] = "nibbler/playerH.png";
	res["playerC"] = "nibbler/playerC.png";
	res["playerQ"] = "nibbler/playerQ.png";
	res["target"] = "nibbler/target.png";
	res["bg"] = "nibbler/bg.png";
	res["bg_wall"] = "nibbler/wall.png";
	res["bg_wall_c"] = "nibbler/wall_corner.png";
	res["loose"] = "nibbler/loose.png";
	res["win"] = "nibbler/win.png";
	return res;
}

int	Nibbler::get_life_player()
{
	return player.get_life();
}

std::map<std::string, std::vector<pos_sprite>>	Nibbler::get_all_pos()
{
	std::map<std::string, std::vector<pos_sprite>>	res;
	std::vector<pos_sprite>	tmp;

	if (is_end())
	        return get_end_game();
	res["playerH"] = std::vector<pos_sprite>{player.pos[0]};
	for (size_t i = 1 ; i < player.pos.size() - 1 ; i++)
		tmp.push_back(player.pos[i]);
	res["playerC"] = tmp;
	res["playerQ"] = std::vector<pos_sprite>{
		player.pos[player.pos.size() - 1]};
	tmp.clear();
	for (size_t i = 0 ; i < target.size(); i++)
		tmp.push_back(target[i]);
	res["target"] = tmp;
	res["bg_wall"] = pos_wall(0);
	res["bg_wall_c"] = pos_wall(1);
	return res;
}

std::vector<pos_sprite>	Nibbler::pos_wall(int corner)
{
	std::vector<pos_sprite>	res;
	int	dir;

	for (unsigned int j = 0 ; j < map.size() ; j++){
		for (unsigned int i = 0 ; i < map[j].size() ; i++){
			if (corner)
				dir = get_dir_wall_c(i, j);
			else
				dir = get_dir_wall(i, j);
			if (dir != 0)
				res.push_back(pos_sprite(i * 52, j * 52, dir));
		}
	}
	return res;
}

int	Nibbler::get_dir_wall(int i, int j)
{
	int	m_size = map.size() - 1;
	int	l_size = map[j].size() - 1;
	
	if (map[j][i] == 1 && get_dir_wall_c(i, j) == 0){
		if ((j > 0 && map[j - 1][i] == 1) ||
			 (j < m_size && map[j + 1][i] == 1))
			return -2;
		else if ((i > 0  && map[j][i - 1] == 1) ||
			(i < l_size && map[j][i + 1] == 1))
			return 1;
	}
	return 0;
}

int	Nibbler::get_dir_wall_c(int i, int j)
{
	int	m_size = map.size() - 1;
	int	l_size = map[j].size() - 1;
	
	if (map[j][i] == 1){
		if (i > 0 && j > 0 && map[j - 1][i] != 0 && map[j][i - 1] != 0)
			return -1;
		else if (j > 0 && i < l_size && map[j - 1][i] != 0 &&
			 map[j][i + 1] != 0)
			return -2;
		else if (i > 0 && j < m_size && map[j][i - 1] != 0 &&
			 map[j + 1][i] != 0)
			return 2;
		else if (i < l_size && j < m_size && map[j][i + 1] != 0 &&
			 map[j + 1][i] != 0)
			return 1;
	}
	return 0;
}

void	Nibbler::move_player(int mov)
{
	if (mov > 3 && mov < 8)
		player.set_dir(mov);
}

void	Nibbler::move_all()
{
	player.move(map);
	check_target_eat();
}

int	Nibbler::is_end()
{
	if (player.get_life() == 0)
		return 1;
	else if (level > 2)
		return 2;
	return 0;
}

std::map<std::string, std::vector<pos_sprite>>	Nibbler::get_end_game()
{
	std::map<std::string, std::vector<pos_sprite>>	res;
	std::vector<pos_sprite>		tmp;
	int		end = is_end();

	tmp.push_back(pos_sprite(0, 0, -2));
	if (end == 1)
		res["loose"] = tmp;
	else if (end == 2)
		res["win"] = tmp;	
	return res;
}

void    Nibbler::check_target_eat()
{
        int     save = -1;

        for (unsigned int i = 0 ; i < target.size() ; i++) {
		if (target[i].x == player.pos[0].x &&
		    target[i].y == player.pos[0].y) {
                        save = i;
		}
	}
        if (save != -1){
                target.erase(target.begin() + save);
		player.eat();
		score += 10 * level;
	}
	if (target.size() == 0){
		level++;
		init_map();
		init_target();
		player.init_pos();
	}
}

void	Nibbler::init_map()
{
	std::string	f_name(std::string("./map/nibbler/map") +
			       std::to_string(level) + ".conf");
	std::ifstream	file(f_name);
	std::string	buf;
	std::vector<int>	tmp;

	map.clear();
	while (std::getline(file, buf)){
		for (int i = 0 ; buf[i] ; i++)
			tmp.push_back(buf[i] - '0');
		map.push_back(tmp);
		tmp.clear();
	}
}

void	Nibbler::init_target()
{
	target.push_back(pos_sprite(9 * 52, 5 * 52, -2));
	target.push_back(pos_sprite(1 * 52, 7 * 52, -2));
	target.push_back(pos_sprite(17 * 52, 7 * 52, -2));
	target.push_back(pos_sprite(1 * 52, 9 * 52, -2));
	target.push_back(pos_sprite(17 * 52, 9 * 52, -2));
	target.push_back(pos_sprite(7 * 52, 11 * 52, -2));
	target.push_back(pos_sprite(11 * 52, 11 * 52, -2));
	target.push_back(pos_sprite(5 * 52, 15 * 52, -2));
	target.push_back(pos_sprite(13 * 52, 15 * 52, -2));
}

extern "C" IGame*	create()
{
	return new Nibbler(WIN_X, WIN_Y);
}

extern "C" void		destroy(IGame* nibbler)
{
	delete nibbler;
}
