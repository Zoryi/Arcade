//
// EPITECH PROJECT, 2018
// arcade
// File description:
// nibbler.hpp
//

#include <fstream>
#include <map>
#include "IGame.hpp"
#include "Arcade.hpp"
#include "Player.hpp"

class Nibbler : public IGame
{
public:
	Nibbler(int sx, int sy);
	~Nibbler();
        void		restart() override;
	std::string	get_name() const override;
	int		get_score() const override;
	int		get_level() const override;
	std::map<std::string, std::string>	get_sprites() override;
	std::map<std::string, std::vector<pos_sprite>>	get_all_pos() override;
	int		get_life_player() override;
	void		move_player(int mov) override;
	void		move_all() override;
	int		is_end() override;
	
private:
	void		check_target_eat();
	std::map<std::string, std::vector<pos_sprite>>	get_end_game();
	std::vector<pos_sprite>		pos_wall(int corner);
	int		get_dir_wall_c(int i, int j);
	int		get_dir_wall(int i, int j);
	void		init_map();
	void		init_target();

	int		score;
	int		level;
	std::pair<int, int>	size;
	Player			player;
	std::vector<pos_sprite>	target;
	std::vector<std::vector<int>>		map;
	
};

extern "C" IGame*	create();
extern "C" void		destroy(IGame* nibbler);
