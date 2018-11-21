//
// EPITECH PROJECT, 2018
// arcade
// File description:
// my_sfml.hpp
//

#ifndef MY_SFML_HPP_
#define MY_SFML_HPP_

#include <SFML/System.hpp>
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include "IDisplay.hpp"

class My_sfml : public IDisplay
{
public:
	My_sfml();
	~My_sfml();
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
	void	display_nb(int nb, int x, int y);
	char	get_key(sf::Event event);
	char	get_key2(sf::Event event);
	sf::RenderWindow*	_window;
	sf::Texture		_bg;
	std::map<std::string, sf::Texture*>	_textures;
};

extern "C" IDisplay*	create();
extern "C" void		destroy(IDisplay* sfml);

#endif
