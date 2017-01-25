#pragma once
#include "Command.h"
#include "Actor.h"
class JumpCommand : public Command
{
public:
	JumpCommand(Actor* actor) : Command(),mActor(actor) { }
	virtual void execute() 
	{ 
		mActor->jump();
	}
	virtual void undo() {};
private:
	Actor* mActor;
};

class FireCommand : public Command
{
public:
	FireCommand(Actor* actor) : Command(), mActor(actor) {}
	virtual void execute() 
	{ 
		mActor->fireGun();
	}
	virtual void undo() {};
private:
	Actor* mActor;
};
