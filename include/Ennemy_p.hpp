//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Player.hpp
//

#ifndef ENNEMY_HPP_
#define ENNEMY_HPP_

#include "Arcade.hpp"
#include "Player_p.hpp"

class Ennemy
{
public:
	Ennemy(pos_sprite new_pos);
	~Ennemy();
	int	get_life() const;
	void	set_life(int new_life);
	void	set_pos_ennemy(std::pair<int, int> new_pos);
	std::pair<int, int>	find_vect_dir(Player player, std::vector<std::vector<int>> map);
	
	
	std::vector<pos_sprite>	pos;
private:
	std::pair<int, int>	move_ennemy_next_pos();
	std::pair<int, int>	find_vect_dir2(std::vector<std::vector<int>> map, int dir);

	std::vector<pos_sprite>	next_pos;
	int		life;
	int		v;
};

#endif
