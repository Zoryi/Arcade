//
// EPITECH PROJECT, 2018
// arcade
// File description:
// pacman.cpp
//

#include "Pacman.hpp"

Pacman::Pacman(int sx, int sy) : player(pos_sprite(52 * 1, 52 * 1, 1))
{
	size.first = sx - sx / 5;
	size.second = sy;	
	level = 1;
	init_map();
	init_target();
	init_ennemy();
	score = 0;
	ennemy_nb = 2;
}

Pacman::~Pacman()
{
}

void	Pacman::restart()
{
	map.clear();
	init_map();
	ennemy.clear();
	init_ennemy();
	target.clear();
	init_target();
	player = Player(pos_sprite(1 * 52, 1 * 52, 1));
	score = 0;
	level = 1;
	ennemy_nb = 2;
}

std::string	Pacman::get_name() const
{
	return std::string("lib_arcade_pacman.so");
}

int		Pacman::get_score() const
{
	return score;
}

int		Pacman::get_level() const
{
	return level;
}

std::map<std::string, std::string>	Pacman::get_sprites()
{
	std::map<std::string, std::string>	res;

	res["player1"] = "pacman/player.png";
	res["player2"] = "pacman/player_full.png";
	res["ennemyR"] = "pacman/ennemyR.png";
	res["ennemyP"] = "pacman/ennemyP.png";
	res["ennemyB"] = "pacman/ennemyB.png";
	res["ennemyY"] = "pacman/ennemyY.png";
	res["target1"] = "pacman/target1.png";
	res["target2"] = "pacman/target2.png";
	res["bg_wall"] = "pacman/wall_t.png";
	res["bg_wall2"] = "pacman/wall_corner_t.png";
	res["bg"] = "pacman/bg.png";
	res["win"] = "pacman/win.png";
	res["loose"] = "pacman/loose.png";
	return res;
}

int		Pacman::get_life_player()
{
	return player.get_life();
}

std::map<std::string, std::vector<pos_sprite>>	Pacman::get_all_pos()
{
	std::map<std::string, std::vector<pos_sprite>>	res;
	std::vector<pos_sprite>		tmp;
	std::vector<pos_sprite>		tmp2;
	static int			save = 0;
        
	if (is_end())
		return get_end_game();
        if (save < 50)
		res["player1"] = std::vector<pos_sprite>{player.pos[0]};
	else
		res["player2"] = std::vector<pos_sprite>{player.pos[0]};
        save = (save < 100) ? save + 1 : 0;
	get_ennemy_pos(res);
	for (auto& p : target)
	        p.type == 1 ? tmp.push_back(p.pos[0]) : tmp2.push_back(p.pos[0]);
	res["target1"] = tmp;
	res["target2"] = tmp2;
	res["bg_wall"] = pos_wall(0);
	res["bg_wall2"] = pos_wall(2);
	return res;
}

void	Pacman::get_ennemy_pos(std::map<std::string, std::vector<pos_sprite>>& res)
{
	if (ennemy[0].get_life() > 0)
		res["ennemyR"] = std::vector<pos_sprite>{ennemy[0].pos[0]};
        if (ennemy[1].get_life() > 0)
		res["ennemyP"] = std::vector<pos_sprite>{ennemy[1].pos[0]};
        if (ennemy[2].get_life() > 0)
		res["ennemyB"] = std::vector<pos_sprite>{ennemy[2].pos[0]};
        if (ennemy[3].get_life() > 0)
		res["ennemyY"] = std::vector<pos_sprite>{ennemy[3].pos[0]};
}

void	Pacman::move_player(int mov)
{
	if (mov > 3 && mov < 8)
		player.set_dir(mov);
}

void	Pacman::move_all()
{
	player.move(map);
	move_ennemy();
	check_target_eat();
	(player.get_state() == 1) ? player.set_speed(2) : player.set_speed(1);
}

int	Pacman::is_end()
{
	if (player.get_life() == 0)
		return 1;
	else if (level > NB_LEVEL)
		return 2;
	return 0;
}

std::vector<pos_sprite>	Pacman::pos_wall(int corner)
{
	std::vector<pos_sprite> res;
	int	dir;

	for (unsigned int j = 0; j < map.size(); j++) {
		for (unsigned int i = 0; i < map[j].size(); i++) {
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

int	Pacman::get_dir_wall(int i, int j)
{
	int	m_size = map.size() - 1;
	int	l_size = map[j].size() - 1;

	if (map[j][i] == 1 && get_dir_wall_c(i, j) == 0) {
		if ((j > 0 && map[j - 1][i] == 1) ||
		    (j < m_size && map[j + 1][i] == 1))
			return -2;
		else if ((i > 0 && map[j][i - 1] == 1) || (i < l_size && map[j][i + 1] == 1))
			return 1;
	}
	return 0;
}

int	Pacman::get_dir_wall_c(int i, int j)
{
	int	m_size = map.size() - 1;
	int	l_size = map[j].size() - 1;

	if (map[j][i] == 1) {
		if (i > 0 && j > 0 && map[j - 1][i] != 0 && map[j][i - 1] != 0)
			return -1;
		else if (j > 0 && i < l_size && map[j - 1][i] != 0 && map[j][i + 1] != 0)
			return -2;
		else if (i > 0 && j < m_size && map[j][i - 1] != 0 && map[j + 1][i] != 0)
			return 2;
		else if (i < l_size && j < m_size && map[j][i + 1] != 0 && map[j + 1][i] != 0)
			return 1;
	}
	return 0;
}

void	Pacman::make_move_player()
{
	std::pair<int, int> pos;

	pos = calc_move_player(player.pos[0].dir);
	player.pos[0].x += pos.first;
	player.pos[0].y += pos.second;
}

void	Pacman::move_ennemy()
{
	std::pair<int, int>	new_pos;

	for (int i = 0; i < ennemy_nb; i++) {
		
		if (player.pos[0].x / 52 == ennemy[i].pos[0].x / 52 &&
		    player.pos[0].y / 52 == ennemy[i].pos[0].y / 52 &&
		    ennemy[i].get_life() > 0) {
			if (player.get_state() == 1)
				ennemy[i].set_life(ennemy[i].get_life() - 1);
			else if (player.get_life() > 0)
				player.loose_life();
	        } else {
			new_pos = ennemy[i].find_vect_dir(player, map);
			ennemy[i].set_pos_ennemy(new_pos);
		}
	}
}

std::map<std::string, std::vector<pos_sprite>>	Pacman::get_end_game()
{
	std::map<std::string, std::vector<pos_sprite>>	res;
	std::vector<pos_sprite>		tmp;
	int	end = is_end();

	tmp.push_back(pos_sprite(0, 0, -2));
	if (end == 1)
		res["loose"] = tmp;
	else if (end == 2)
		res["win"] = tmp;
	return res;
}

void	Pacman::init_map()
{
	std::string	f_name(std::string("./map/pacman/map") +
			       std::to_string(level) + ".conf");
	std::ifstream	file(f_name);
	std::string	buf;
	std::vector<int>	tmp;

        map.clear();
        while (std::getline(file, buf)) {
		for (int i = 0; buf[i]; i++)
			tmp.push_back(buf[i] - '0');
		map.push_back(tmp);
		tmp.clear();
	}
}

void	Pacman::print_map()
{	
	for (auto& p : map) {
		for (auto& a : p)
			std::cout << a;
		std::cout << std::endl;
	}
}

void	Pacman::init_ennemy()
{	
	for (int i = 0; i < 4; i++) {
		Ennemy tmp(pos_sprite(((8 * 52) + (i * 52)), 5*52, 1));
		ennemy.push_back(tmp);
	}
}

void	Pacman::init_target()
{
	int	x = 0;
	int	y = 0;
	
	for (auto& p : map) {
		for (auto& b : p){
			place_target(b, x, y);
			x += 52;
		}
		x = 0;
		y += 52;
	}
}

int	Pacman::check_pos_ennemy(int x, int y)
{
	for (auto& e : ennemy) {
		if (x == e.pos[0].x && y == e.pos[0].y)
			return 0;
	}
	return 1;
}

void	Pacman::place_target(int nb, int x, int y)
{
	t_target	tmp;

	if (nb == 0) {
		if (x != player.pos[0].x || y != player.pos[0].y) {
			if (check_pos_ennemy(x, y)) {
				tmp.pos.push_back(pos_sprite(x, y, 1));
				tmp.type = (x / 52 == 1 || x / 52 == 18) ? 2 : 1;
				tmp.type = (tmp.type == 2 &&
					    (y / 52 == 1 || y / 52 == 9)) ? 2 : 1;
				target.push_back(tmp);
			}
		}
	}
}

void	Pacman::check_target_eat()
{
	int	i = 0;
	int	save = -1;

        for (auto& p : target) {
		if (p.pos[0].x == player.pos[0].x && p.pos[0].y == player.pos[0].y)
			save = i;
		i++;
	}
	eat_target(save);
	if (target.size() == 0) {
		level++;
		new_level();
	}
}

void	Pacman::new_level()
{
	map.clear();
	init_map();
	ennemy.clear();
	init_ennemy();
	player.init_pos();
	init_target();
}

void	Pacman::eat_target(int save)
{
	static int state_save = 0;

	if (state_save > 0)
		state_save--;
	else if (player.get_state() == 1)
		player.set_state(0);
	if (save != -1) {
		if (target[save].type == 2){
			player.set_state(1);
			state_save = 2000;
			score += 90;
		}
		target.erase(target.begin() + save);
		score += 10;
	}
	ennemy_nb = ((score >= 350 && ennemy_nb < 3) || (score >= 700 && ennemy_nb < 4))
		? ennemy_nb + 1 : ennemy_nb;
}

extern "C" IGame*	create()
{
	return new Pacman(WIN_X, WIN_Y);
}

extern "C" void		destroy(IGame*	pacman)
{
	delete pacman;
}
