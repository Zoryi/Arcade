//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Pacman.hpp
//

#include <fstream>
#include <map>
#include <string>
#include "IGame.hpp"
#include "Arcade.hpp"
#include "Player_p.hpp"
#include "Ennemy_p.hpp"

#define NB_LEVEL 2

typedef struct s_target
{
        std::vector<pos_sprite>	pos;
	int		type;
}t_target;

class Pacman : public IGame
{
public:
	Pacman(int sx, int sy);
	~Pacman();
        void		restart() override;
	std::string	get_name() const override;
	int		get_score() const override;
	int		get_level() const override;
	std::map<std::string, std::string>	get_sprites() override;
	int		get_life_player() override;
	std::map<std::string, std::vector<pos_sprite>>	get_all_pos() override;
	std::map<std::string, std::vector<pos_sprite>>	get_end_game();
	void		move_player(int mov) override;
	void		move_all() override;
	int		is_end() override;
private:
	std::pair<int, int>	calc_move_player(int dir);
	int		check_move_player(int direction);
	void		make_move_player();
	std::vector<pos_sprite>	pos_wall(int corner);
	int		get_dir_wall(int i, int j);
	int		get_dir_wall_c(int i, int j);
	void		init_map();
	void		init_player();
	void		init_ennemy();
	void		init_target();
	int		check_pos_ennemy(int x, int y);
	void		place_target(int nb, int x, int y);
	void		check_target_eat();
	void		eat_target(int save);
	void		print_map();
	void		move_ennemy();
	void		new_level();
	void		get_ennemy_pos(std::map<std::string, std::vector<pos_sprite>>& res);
	
	int		score;
	int		level;
	int		ennemy_nb;
	std::pair<int, int>	size;
	Player			player;
	std::vector<s_target>	target;
	std::vector<Ennemy>	ennemy;
	std::vector<std::vector<int>>	map;
};

extern "C" IGame*	create();
extern "C" void		destroy(IGame* pacman);
