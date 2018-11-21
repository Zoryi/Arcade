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
	int	check_hit();
	void	eat();
	void	expand();
	
	std::vector<pos_sprite>	get_pos() const;
	void	init_pos();
	void	loose_life();
	int	get_life() const;
	void	set_life(int life);
	void	set_dir(int mov);
	
	std::vector<pos_sprite>	pos;
private:
	int		life;
	int		next_dir;
	int		v;
};

#endif
