#pragma once
#include "Command.h"
#include "SDL.h"
#include <iostream>
#include <map>


class InputHandler
{
public:
	InputHandler();

	Command* handleInput(SDL_Keycode key);
	void bindKeyCommand(SDL_Keycode, Command*);
private:
	typedef std::map<SDL_Keycode, Command*>::iterator map_iterator;
	std::map<SDL_Keycode, Command*> mKeyCommand;

};
