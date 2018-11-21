//
// EPITECH PROJECT, 2018
// arcade
// File description:
// my_sfml.cpp
//

#include "my_sfml.hpp"
#include <iostream>

My_sfml::My_sfml()
{
	_window = new sf::RenderWindow;
	for (int i = 0 ; i < 10 ; i++)
		set_sprite(std::to_string(i),
		        std::string("nb/") + std::to_string(i) + ".png");
}

My_sfml::~My_sfml()
{
}

void	My_sfml::create_window(int sx, int sy, std::string title)
{
	_window->create(sf::VideoMode(sx, sy), title);
}

void	My_sfml::destroy_window()
{
	_window->close();
}

void	My_sfml::update_window()
{
	
	_window->display();
}

void	My_sfml::clear()
{
	_window->clear();
	display_sprite("bg", mPos(0, 0), -2);
}

void	My_sfml::set_title(std::string title)
{
	_window->setTitle(title);
}

int	My_sfml::isOpen()
{
	if (_window->isOpen())
		return 1;
	return 0;
}

char	My_sfml::get_event()
{
	sf::Event	event;
	
	if (_window->pollEvent(event)){
		switch (event.type)
		{
		case sf::Event::Closed:
			_window->close();
			return 1;
		case sf::Event::KeyPressed:
			return (get_key(event));
		default:
			break;
		}
	}
	return 0;
}

char	My_sfml::get_key(sf::Event event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Escape:
		_window->close();
		return 1;
	case sf::Keyboard::PageUp:
		return 2;
	case sf::Keyboard::PageDown:
		return 3;
	case sf::Keyboard::Up:
		return 4;
	case sf::Keyboard::Down:
		return 5;
	case sf::Keyboard::Left:
		return 6;
	case sf::Keyboard::Right:
		return 7;
	default:
		return get_key2(event);
	}
}

char	My_sfml::get_key2(sf::Event event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::RShift:
		return 8;
	case sf::Keyboard::LShift:
		return 9;
	case sf::Keyboard::R:
		return 10;
	default:
		return 0;
	}
}

int	My_sfml::set_bg(std::string path)
{
	std::string	full_path = "./img/sfml/" + path;

	if (_textures["bg"]->loadFromFile(full_path))
		return 1;
	return 0;
}

int	My_sfml::set_sprite(std::string name, std::string path)
{
	std::string	full_path = "./img/sfml/" + path;

	_textures[name] = new sf::Texture;
	if (_textures[name]->loadFromFile(full_path))
		return 1;
	return 0;
}

void	My_sfml::display_sprite(std::string name, mPos pos, int d)
{
	sf::Sprite*	sprite = new sf::Sprite;
	sf::Vector2u	size;

	d = d;
	if (_textures.find(name) != _textures.end()){
		sprite->setTexture(*_textures[name]);
		size = _textures[name]->getSize();
		sprite->setOrigin(size.x / 2, size.y / 2);
		sprite->setPosition(pos.x + size.x / 2, pos.y + size.y / 2);
		if (d != -2)
			sprite->setRotation(d * 90);
		_window->draw(*sprite);
	}
}

void	My_sfml::display_button(std::string& msg, int& x, int& y)
{
	(void) msg;
	int	a = x;
	int	b = y;
	b = a * y;
	a = b * x;
}

void		My_sfml::display_text(std::string msg, int x, int y)
{
	int	nb;

	try{
		nb = std::stoi(msg);
		display_nb(nb, x, y);
	} catch(const std::invalid_argument& ia){
	}
}

void		My_sfml::display_nb(int nb, int x, int y)
{
	int	tmp = nb;
	int	size = 1;
	int	tmp_size;

	while (tmp >= 10){
		size++;
		tmp = tmp / 10;
	}
	tmp = nb;
	tmp_size = size;
	while (tmp_size > 0){
		display_sprite(std::to_string(tmp % 10),
			       mPos(x - (size - tmp_size) * 40, y), -2);
		tmp = tmp / 10;
		tmp_size--;
	}
}

const std::string	My_sfml::get_name()
{
	return std::string("lib_arcade_sfml.so");
}

extern "C" IDisplay*	create()
{
	return new My_sfml();
}

extern "C" void		destroy(IDisplay* sfml)
{
	delete sfml;
}
