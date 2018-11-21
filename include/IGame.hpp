//
// EPITECH PROJECT, 2018
// arcade
// File description:
// IGame.hpp
//

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>

class pos_sprite
{
public:
	pos_sprite(int nx, int ny, int nd) : x(nx), y(ny), dir(nd){};
	~pos_sprite() = default;
	int	x;
	int	y;
	int	dir;
};

class IGame
{
public:
	virtual ~IGame() = default;
	virtual	void			restart() = 0;
	virtual std::string		get_name() const = 0;
	virtual int			get_score() const = 0;
	virtual int			get_level() const = 0;
	virtual std::map<std::string, std::string>	get_sprites() = 0;
	virtual std::map<std::string, std::vector<pos_sprite>>	get_all_pos() = 0;
	virtual int			get_life_player() = 0;
	virtual void			move_player(int mov) = 0;
	virtual void			move_all() = 0;
	virtual int			is_end() = 0;
};

#endif
