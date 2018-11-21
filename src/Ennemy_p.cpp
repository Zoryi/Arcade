//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Ennemy_p.cpp
//

#include "Ennemy_p.hpp"

Ennemy::Ennemy(pos_sprite new_pos)
{
	v = 1;
	life = 1;
	next_pos.push_back(pos_sprite(-1, -1, 1));
	pos.push_back(new_pos);
}

Ennemy::~Ennemy()
{
}

int	Ennemy::get_life() const
{
	return life;
}

void	Ennemy::set_life(int new_life)
{
	life = new_life;
}

void	Ennemy::set_pos_ennemy(std::pair<int, int> new_pos)
{
        pos[0].x = new_pos.first;
	pos[0].y = new_pos.second;
}

std::pair<int, int>	Ennemy::find_vect_dir(Player player,
					      std::vector<std::vector<int>> map)
{
	std::pair<int, int>	ret;
	
	if (next_pos[0].x != -1 && next_pos[0].y != -1)
		return (move_ennemy_next_pos());
	else if (pos[0].x <= player.pos[0].x && pos[0].y > player.pos[0].y)
		ret = find_vect_dir2(map, 1);
	else if (pos[0].x <= player.pos[0].x && pos[0].y <= player.pos[0].y)
		ret = find_vect_dir2(map, 2);
	else if (pos[0].x > player.pos[0].x && pos[0].y <= player.pos[0].y)
		ret = find_vect_dir2(map, 3);
	else if (pos[0].x > player.pos[0].x && pos[0].y > player.pos[0].y)
		ret = find_vect_dir2(map, 4);
        next_pos[0].x = ret.first;
	next_pos[0].y = ret.second;
	return std::pair<int, int>(pos[0].x, pos[0].y);
}

std::pair<int, int>	Ennemy::move_ennemy_next_pos()
{	
        if (pos[0].x != next_pos[0].x){
		if (pos[0].x < next_pos[0].x)
			return std::pair<int,int>(pos[0].x + 1, pos[0].y);
		else if (pos[0].x > next_pos[0].x)
			return std::pair<int,int>(pos[0].x - 1, pos[0].y);
	} else if (pos[0].y != next_pos[0].y) {
		if (pos[0].y < next_pos[0].y)
			return std::pair<int,int>(pos[0].x, pos[0].y + 1);
		else if (pos[0].y > next_pos[0].y)
			return std::pair<int,int>(pos[0].x, pos[0].y - 1);
	} else if (pos[0].x == next_pos[0].x &&
		   pos[0].y == next_pos[0].y){
		next_pos[0].x = -1;
		next_pos[0].y = -1;
	}
        return std::pair<int, int>(pos[0].x, pos[0].y);	
}

std::pair<int, int>	Ennemy::find_vect_dir2(std::vector<std::vector<int>> map, int dir)
{
        if ((dir == 1 || dir == 4) && map[pos[0].y / 52 - 1][pos[0].x / 52] == 0)
		return std::pair<int, int>(pos[0].x, pos[0].y - 52);
	else if ((dir == 1 || dir == 2) && map[pos[0].y / 52][pos[0].x / 52 + 1] == 0)
		return std::pair<int, int>(pos[0].x + 52, pos[0].y);
	else if ((dir == 2 || dir == 3) && map[pos[0].y / 52 + 1][pos[0].x / 52] == 0)
		return std::pair<int, int>(pos[0].x, pos[0].y + 52);
	else if ((dir == 3 || dir == 4) && map[pos[0].y / 52][pos[0].x / 52 - 1] == 0)
		return std::pair<int, int>(pos[0].x - 52, pos[0].y);
	return std::pair<int, int>(pos[0].x, pos[0].y);
}
