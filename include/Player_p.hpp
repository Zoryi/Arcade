//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Player.hpp
//

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Arcade.hpp"

class Player
{
public:
	Player(pos_sprite new_pos);
	~Player();

	void	move(std::vector<std::vector<int>>& map);
	int	check_dir(std::vector<std::vector<int>>& map);
	std::pair<int, int>	calc_move(int dir);
	int	check_move(std::vector<std::vector<int>>& map, int direction);
	
	std::vector<pos_sprite>	get_pos() const;
	void	init_pos();
	void	loose_life();
	int	get_life() const;
	int	get_speed() const;
	int	get_state() const;	
	void	set_life(int life);
	void	set_dir(int mov);
	void	set_speed(int speed);
	void	set_state(int new_state);
	
	std::vector<pos_sprite>	pos;
private:
	int		life;
	int		next_dir;
	int		v;
	int		state;
};

#endif
