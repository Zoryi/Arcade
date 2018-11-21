/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** my_ncurses.hpp
*/

#ifndef MY_NCURSES_HPP_
#define MY_NCURSES_HPP_

#include <ncurses.h>
#include <string>
#include <map>
#include <fstream>
#include "IDisplay.hpp"

class My_ncurses : public IDisplay
{
public:
	My_ncurses();
	~My_ncurses();
	void create_window(int sy, int sx, std::string title) override;
	void destroy_window() override;
	void update_window() override;
	void clear() override;
	void set_title(std::string title) override;
	int isOpen() override;
	char get_event() override;
	int	set_bg(std::string path) override;
	int	set_sprite(std::string name, std::string path) override;
	void	display_sprite(std::string name, mPos pos, int d) override;
	void	display_button(std::string& msg, int &x, int& y) override;
	const std::string get_name() override;
private:
	char get_key();
	void	printError(std::string error);
	WINDOW*	_window;
	int	_isOpen;
	std::map<std::string, std::string>	_textures;
};

extern "C" IDisplay *create();
extern "C" void destroy(IDisplay *SDL);

#endif
