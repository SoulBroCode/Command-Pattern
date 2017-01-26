#pragma once
#include "Command.h"
#include <vector>
#include <iostream>
class MacroCommand : public Command {
public:
	MacroCommand();
	virtual ~MacroCommand();
	virtual void add(Command*);
	virtual void remove(Command*);
	virtual void execute();
	virtual void undo();
	virtual void redo();
private:
	int	mIndex;
	std::vector<Command*> commands;
};
