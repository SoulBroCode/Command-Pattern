#include "InputHandler.h"

InputHandler::InputHandler() :
	mKeyCommand(std::map<SDL_Keycode, Command*>())
{
}

void InputHandler::bindKeyCommand(SDL_Keycode key, Command* command)
{
	//bind a key to a command
	mKeyCommand.insert(std::make_pair(key, command));
}


Command* InputHandler::handleInput(SDL_Keycode key)
{			
	//loop throught map of key and return command if there is one.
	for (map_iterator iterator = mKeyCommand.begin(); iterator != mKeyCommand.end(); iterator++) {
		if (key == iterator->first)
		{
			return  iterator->second;
		}
	}

	return nullptr;	
}