#include "InputHandler.h"

InputHandler::InputHandler() :
	mKeyCommand(std::map<SDL_Keycode, Command*>())
{
	int i = 0;
}

void InputHandler::bindKeyCommand(SDL_Keycode key, Command* command)
{
	mKeyCommand.insert(std::make_pair(key, command));

}


Command* InputHandler::handleInput(SDL_Keycode key)
{			
	for (map_iterator iterator = mKeyCommand.begin(); iterator != mKeyCommand.end(); iterator++) {
		if (key == iterator->first)
		{
			std::cout << "Command Added" << std::endl;
			return  iterator->second;
		}
	}

	return nullptr;	
}