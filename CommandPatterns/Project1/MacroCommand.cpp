#include "MacroCommand.h"
MacroCommand::MacroCommand() : commands(std::vector<Command*>()), mIndex(0){};
MacroCommand::~MacroCommand() {};

void MacroCommand::execute() 
{
	if (!commands.empty())
	{	
		commands[mIndex]->execute();
		mIndex++;
	}
}

void MacroCommand::add(Command *c) {
	std::vector<Command*>::iterator it = commands.begin();
	
	commands.insert(it + mIndex, c);
	//delete any command after insert to a index
	while (commands.size() != mIndex + 1)
	{
		commands.pop_back();
	}
}

void MacroCommand::remove(Command *c) {

}

void MacroCommand::undo() {
	if (!commands.empty())
	{
		if (mIndex > 0)
		{
			mIndex--;	
			commands[mIndex]->undo();	
		}
		else
		{
			std::cout << "undo fail - reach limit" << std::endl;
		}
	}
}

void MacroCommand::redo()
{
	if (!commands.empty())
	{
		if (mIndex < commands.size() )
		{	
			commands[mIndex]->redo();
			mIndex++;
		}
		else
		{
			std::cout << "redo fail - reach limit" << std::endl;
		}
	}
}