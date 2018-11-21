//
// EPITECH PROJECT, 2018
// arcade
// File description:
// IDisplay.hpp
//

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

class mPos
{
public:
	mPos(int nx, int ny) : x(nx), y(ny){};
	~mPos() = default;
	int	x;
	int	y;
};

class IDisplay
{
public:
	virtual	~IDisplay() = default;
	virtual void	create_window(int sx, int sy, std::string title) = 0;
	virtual void	destroy_window() = 0;
	virtual void	update_window() = 0;
	virtual	void	clear() = 0;
	virtual void	set_title(std::string title) = 0;
	virtual int	isOpen() = 0;
	virtual char	get_event() = 0;
	virtual int	set_bg(std::string path) = 0;
	virtual int	set_sprite(std::string name, std::string path) = 0;
	virtual void	display_sprite(std::string name, mPos pos, int d) = 0;
	virtual void	display_button(std::string& msg, int& x, int& y) = 0;
	virtual void	display_text(std::string msg, int x, int y) = 0;
	virtual const std::string	get_name() = 0;
};

#endif
