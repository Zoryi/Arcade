//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Arcade.hpp
//

#ifndef MY_SDL_HPP_
#define MY_SDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <map>
#include "IDisplay.hpp"

class My_sdl : public IDisplay
{
public:
	My_sdl();
	~My_sdl();
	void	create_window(int sx, int sy, std::string title) override;
	void	destroy_window() override;
	void	update_window() override;
	void	clear() override;
	void	set_title(std::string title) override;
	int	isOpen() override;
	char	get_event() override;
        int	set_bg(std::string path) override;
	int	set_sprite(std::string name, std::string path) override;
	void	display_sprite(std::string name, mPos pos, int d) override;
	void	display_button(std::string& msg, int& x, int& y) override;
	void	display_text(std::string msg, int x, int y) override;	
	const std::string	get_name() override;

private:
	char		get_key(SDL_Event event);
	char		get_key2(SDL_Event event);
	SDL_Surface*	set_rotation(SDL_Surface* sprite, int rotation);
	void		printError(std::string error);
	SDL_Window*	_window;
	SDL_Renderer*	_renderer;
	SDL_Surface*	_bg;
	TTF_Font*	_font;
	int		_isOpen;
	std::map<std::string, SDL_Surface*>	_sprites;
};

extern "C" IDisplay*	create();
extern "C" void		destroy(IDisplay* SDL);

#endif
