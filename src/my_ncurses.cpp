/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** my_ncurses.cpp
*/

#include "my_ncurses.hpp"

My_ncurses::My_ncurses()
{
    if (initscr() == 0)
        printError("Erreur ncurses initscr :");
}

My_ncurses::~My_ncurses()
{
    endwin();
}

void My_ncurses::create_window(int sx, int sy, std::string title)
{
    title = title;
    _window = newwin(100, 100, sx, sy);
    _isOpen = 1;
}

void My_ncurses::destroy_window()
{
    delwin(_window);
    _isOpen = 0;
}

void My_ncurses::update_window()
{
    wrefresh(_window);
}

void My_ncurses::clear()
{
    clear();
    display_sprite("bg", mPos(0, 0), 0);
}

void My_ncurses::set_title(std::string title)
{
    title = title;
}

int My_ncurses::isOpen()
{
    if (_isOpen)
        return (1);
    return (0);
}

char My_ncurses::get_event()
{
    _window = _window;
    return (0);
}

int My_ncurses::set_bg(std::string path)
{
    path = path;
    return (0);
}

int My_ncurses::set_sprite(std::string name, std::string path)
{
    std::string buffer;
    std::string full_path = "./img/ncurses/" + path;
    std::ifstream stream(full_path);

    while (std::getline(stream, buffer))
    {
        for (int i = 0; buffer[i]; i++)
            _textures[name] = buffer;
    }
    return 1;
    return 0;
}

void My_ncurses::display_sprite(std::string name, mPos pos, int d)
{
    if (_textures.find(name) != _textures.end())
    {
        mvwprintw(_window, pos.x, pos.y, _textures[name].c_str());
    }
    d = d;
}

void My_ncurses::display_button(std::string &msg, int &x, int &y)
{
    msg = msg;
    x = x;
    y = y;
}
const std::string My_ncurses::get_name()
{
    return 0;
}

char My_ncurses::get_key()
{
    int ch;

    ch = getch();
    switch (ch)
    {
    case 27:
        destroy_window();
        return 1;
    case KEY_UP:
        return 2;
    case KEY_DOWN:
        return 3;
    case KEY_LEFT:
        return 4;
    case KEY_RIGHT:
        return 5;
    default:
        return 0;
    }
}

extern "C" IDisplay *create()
{
    return new My_ncurses();
}

extern "C" void destroy(IDisplay *ncurses)
{
    delete ncurses;
}
