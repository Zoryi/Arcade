//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Player.cpp
//

#include "Player.hpp"

Player::Player(pos_sprite new_pos)
{
	pos.push_back(new_pos);
	next_dir = new_pos.dir;
	life = 3;
	v = 1;
	for (int i = 0 ; i < 3 ; i++)
		expand();
}

Player::~Player()
{
	pos.clear();
}

int		Player::get_life() const
{
	return life;
}

void		Player::set_life(int value)
{
	life = value;
}

void		Player::loose_life()
{
	life--;
	pos.clear();
	pos.push_back(pos_sprite(5 * 52, 17 * 52, 1));
	next_dir = 1;
	for (int i = 0 ; i < 3 ; i++)
		expand();
}

std::vector<pos_sprite>	Player::get_pos() const
{
	return pos;
}

void		Player::init_pos()
{
	unsigned int	size = pos.size();

	pos.clear();
	pos.push_back(pos_sprite(10 * 52, 17 * 52, 1));
	next_dir = 1;
	for (unsigned int i = 1 ; i < size ; i++)
		expand();
}

void		Player::set_dir(int mov)
{
	switch (mov)
	{
	case 4 :
		if (pos[0].dir != 2 && pos[1].dir != 2)
	                next_dir = -2;
		break;
	case 5 :
		if (pos[0].dir != -2 && pos[1].dir != -2)
			next_dir = 2;
		break;
	case 6 :
		if (pos[0].dir != 1 && pos[1].dir != 1)
			next_dir = -1;
		break;
	case 7 :
		if (pos[0].dir != -1 && pos[1].dir != -1)
			next_dir = 1;
		break;
	}
}

std::pair<int, int>	Player::calc_move(int dir)
{
	switch (dir)
	{
	case -1:
		return std::pair<int, int>(-1 * v, 0);
	case -2:
		return std::pair<int, int>(0, -1 * v);
	case 1:
		return std::pair<int, int>(1 * v, 0);
	case 2:
		return std::pair<int, int>(0, 1 * v);
	default:
		return std::pair<int, int>(0, 0);
	}
}

void	Player::move(std::vector<std::vector<int>>& map)
{
	std::pair<int, int>	position;
	int			dir = check_dir(map);
	pos_sprite		old = pos[0];

	if (dir != 0){
		for (auto& p : pos){
			if (old.dir != 0 && old.dir != p.dir &&
			    (old.x == p.x || old.y == p.y)){
				p.dir = old.dir;
			}
			position = calc_move(p.dir);
			p.x += position.first;
			p.y += position.second;
			old = p;
		}
	}
	if (check_hit())
		loose_life();
}

int	Player::check_dir(std::vector<std::vector<int>>& map)
{
	if (check_move(map, next_dir) == 1){
		pos[0].dir = next_dir;
		return next_dir;
	}else if (check_move(map, pos[0].dir) == 1)
		return pos[0].dir;
	else
		return 0;
}

int	Player::check_move(std::vector<std::vector<int>>& map, int direction)
{
	std::pair<int, int>	dir = calc_move(direction);
	std::pair<int, int>	dest(pos[0].x + dir.first,
				     pos[0].y + dir.second);

	for (int i = dest.first ; i < dest.first + 52 ; i++)
		for (int j = dest.second ; j < dest.second + 52 ; j++)
			if (map[j / 52][i / 52] != 0)
				return 0;
	return 1;
}

int	Player::check_hit()
{
	for (unsigned int i = 2 ; i < pos.size() ; i++){
		if (pos[0].x > pos[i].x && pos[0].x < pos[i].x + 51)
			if (pos[0].y > pos[i].y - 51 &&
			    pos[0].y < pos[i].y + 51)
				return 1;
	}
	return 0;
}

void	Player::eat()
{
	if (pos.size() > 1)
		expand();
}

void	Player::expand()
{
	pos_sprite	new_pos = pos[pos.size() - 1];
	std::pair<int, int>	move;

	new_pos.x = pos[pos.size() - 1].x;
	new_pos.y = pos[pos.size() - 1].y;
	new_pos.dir = pos[pos.size() - 1].dir;
	move = calc_move(-new_pos.dir);
	move.first = move.first / v * 52;
	move.second = move.second / v * 52;
	new_pos.x += move.first;
	new_pos.y += move.second;
	pos.push_back(new_pos);
}
