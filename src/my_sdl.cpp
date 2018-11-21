//
// EPITECH PROJECT, 2018
// arcade
// File description:
// my_sdl.cpp
//

#include "my_sdl.hpp"

My_sdl::My_sdl()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		printError("Erreur SDL_Init :");
}

My_sdl::~My_sdl()
{
	for (auto& sprite : _sprites)
		SDL_FreeSurface(sprite.second);
	SDL_FreeSurface(_bg);
	SDL_Quit();
}

void	My_sdl::create_window(int sx, int sy, std::string title)
{
        _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, sx, sy, SDL_WINDOW_SHOWN);
	if (_window == NULL)
		printError("Erreur SDL_CreateWindow : ");
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (_renderer == NULL)
		printError("Erreur SDL_CreateRenderer : ");
	if (TTF_Init() == -1)
		printError("Erreur TTF_Init :");
	_isOpen = 1;
        _font = TTF_OpenFont("./font/Font.ttf", 15);
}

void	My_sdl::destroy_window()
{
	TTF_Quit();
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	_isOpen = 0;
}

void	My_sdl::update_window()
{
	SDL_RenderPresent(_renderer);
}

void	My_sdl::clear()
{	
	SDL_RenderClear(_renderer);
	display_sprite("bg", mPos(0, 0), 0);
}

void	My_sdl::set_title(std::string title)
{
	SDL_SetWindowTitle(_window, title.c_str());
}

int	My_sdl::isOpen()
{
	if (_isOpen)
		return 1;
	return (0);
}

char	My_sdl::get_event()
{
	SDL_Event	event;

	if (SDL_PollEvent(&event)){
		switch(event.type) {
		case SDL_QUIT:
			destroy_window();
			return 1;
		case SDL_KEYDOWN:
			return get_key(event);
	        default:
			break;
		}
	}	
	return 0;
}

char	My_sdl::get_key(SDL_Event event)
{
	switch (event.key.keysym.sym) {
	case SDLK_ESCAPE:
		destroy_window();
		return 1;
	case SDLK_PAGEUP:
		return 2;
	case SDLK_PAGEDOWN:
		return 3;
	case SDLK_UP:
		return 4;
	case SDLK_DOWN:
		return 5;
	case SDLK_LEFT:
		return 6;
	case SDLK_RIGHT:
		return 7;
	default:
		return get_key2(event);
	}
}

char	My_sdl::get_key2(SDL_Event event)
{
        switch (event.key.keysym.sym) {
	case SDLK_RSHIFT:
		return 8;
	case SDLK_LSHIFT:
		return 9;
	case SDLK_r:
		return 10;
	default:
		return 0;
	}
}

int	My_sdl::set_bg(std::string path)
{
	return (set_sprite("bg", path));
}

void		My_sdl::display_sprite(std::string name, mPos pos, int d)
{
        SDL_Texture*	texture;
	SDL_Rect	dest;
	SDL_Surface*	rotate;
	
	if (_sprites[name]) {
		dest = {pos.x, pos.y, _sprites[name]->w, _sprites[name]->h};
        	rotate = set_rotation(_sprites[name], d);
	        texture = SDL_CreateTextureFromSurface(_renderer, rotate);
	        if (texture) {
			SDL_RenderCopy(_renderer, texture, NULL, &dest);
			SDL_DestroyTexture(texture);
        	} else
			printError("Erreur SDL_CreateTextureFromSurface :");
        } else
		printError("Erreur : Sprite pas set");
}

SDL_Surface*	My_sdl::set_rotation(SDL_Surface* sprite, int rotation)
{
	SDL_Surface*	ret = sprite;
	
        if (rotation >= 0)
		ret = rotateSurface90Degrees(ret, rotation);
	// else if (rotation == -1){
	// 	ret = rotateSurface90Degrees(ret, 3);
	// }
	return ret;
}

void		My_sdl::display_button(std::string& msg, int& x, int& y)
{
	msg = msg;
	x = x;
	y = y;
}

void		My_sdl::display_text(std::string msg, int x, int y)
{
	SDL_Color my_color = {255, 255, 0, 1};	
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, msg.c_str(), my_color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
	SDL_Rect	Message_rect;
	
	Message_rect.x = x - msg.size() * 15;
	Message_rect.y = y;
	Message_rect.w = 100;
	Message_rect.h = 100;
	SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

int		My_sdl::set_sprite(std::string name, std::string path)
{
	std::string	full_path = "./img/sdl/" + path;
	
	_sprites[name] = IMG_Load(full_path.c_str());
	if (_sprites[name])
		return 1;
        return 0;
}

const std::string	My_sdl::get_name()
{
	return std::string("lib_arcade_sdl.so");
}

void	My_sdl::printError(std::string error)
{
	std::cerr << error << SDL_GetError() << std::endl;
}

extern "C" IDisplay*	create()
{
	return new My_sdl();
}

extern "C" void		destroy(IDisplay* SDL)
{
	delete SDL;
}
