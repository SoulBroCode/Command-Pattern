#include "MacroCommand.h"
MacroCommand::MacroCommand() : commands(std::list<Command*>()), mIndex(0){};
MacroCommand::~MacroCommand() {};

void MacroCommand::execute() 
{
	if (!commands.empty())
	{
		if (commands.size() > mIndex)
		{
			std::list<Command*>::iterator it = commands.begin();
			std::advance(it, mIndex);
			(*it)->execute();
			mIndex++;
			// 'it' points to the element at index 'N'
		}
	}
}

void MacroCommand::add(Command *c) {
	commands.push_back(c);
	if (commands.size() > mMaxSize)
	{
		commands.erase(commands.begin());
		if (mIndex > 0)
		{
			mIndex--;
		}
	}
}
void MacroCommand::remove(Command *c) {
	commands.remove(c);
}

void MacroCommand::undo() {
	
	if (!commands.empty())
	{
		if (mIndex > 0)
		{
			mIndex--;
		}
		std::list<Command*>::iterator it = commands.begin();
		std::advance(it, mIndex);
		(*it)->undo();
	}
}