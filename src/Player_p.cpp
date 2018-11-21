//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Player.cpp
//

#include "Player_p.hpp"

Player::Player(pos_sprite new_pos)
{
	pos.push_back(new_pos);
	next_dir = new_pos.dir;
	life = 3;
	v = 1;
	state = 0;
}

Player::~Player()
{
}

int		Player::get_life() const
{
	return life;
}

int		Player::get_speed() const
{
	return v;
}

int		Player::get_state() const
{
	return state;
}

void		Player::set_life(int value)
{
	life = value;
}

void		Player::set_speed(int speed)
{
	v = speed;
}

void		Player::set_state(int new_state)
{
	state = new_state;
}

void		Player::loose_life()
{
	life--;
	pos.clear();
	pos.push_back(pos_sprite(1 * 52, 1 * 52, 1)); //
	next_dir = 1;
}

std::vector<pos_sprite>	Player::get_pos() const
{
	return pos;
}

void		Player::init_pos()
{
	pos.clear();
	pos.push_back(pos_sprite(1 * 52, 1 * 52, 1));
	next_dir = 1;
}

void		Player::set_dir(int mov)
{
	switch (mov)
	{
	case 4 :
		next_dir = -2;
		break;
	case 5 :
		next_dir = 2;
		break;
	case 6 :
		next_dir = -1;
		break;
	case 7 :
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

	if (dir != 0){
        	position = calc_move(pos[0].dir);
		pos[0].x += position.first;
		pos[0].y += position.second;
        }
}

int	Player::check_dir(std::vector<std::vector<int>>& map)
{
	if (check_move(map, next_dir) == 1){
		pos[0].dir = next_dir;
		return next_dir;
	} else if (check_move(map, pos[0].dir) == 1) {
		return pos[0].dir;
	}
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
