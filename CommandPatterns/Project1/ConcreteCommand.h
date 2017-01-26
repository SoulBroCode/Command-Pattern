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
	virtual void undo() 
	{
		std::cout << "undo jump command" << std::endl;
	}
	virtual void redo()
	{
		std::cout << "redo jump command" << std::endl;
	}
private:
	Actor* mActor;
};

class FireCommand : public Command
{
public:
	FireCommand(Actor* actor) : Command(), mActor(actor) {}
	virtual void execute() 
	{ 
		mActor->fire();
	}
	virtual void undo() 
	{
		std::cout << "undo fire command" << std::endl;
	}
	virtual void redo()
	{
		std::cout << "redo fire command" << std::endl;
	}
private:
	Actor* mActor;
};

class MoveCommand : public Command
{
public:
	MoveCommand(Actor* actor) : Command(), mActor(actor) {}
	virtual void execute()
	{
		mActor->move();
	}
	virtual void undo() 
	{
		std::cout << "undo move command" << std::endl;
	}
	virtual void redo()
	{
		std::cout << "redo move command" << std::endl;
	}
private:
	Actor* mActor;
};

class WalkCommand : public Command
{
public:
	WalkCommand(Actor* actor) : Command(), mActor(actor) {}
	virtual void execute()
	{
		mActor->walk();
	}
	virtual void undo() 
	{
		std::cout << "undo walk command" << std::endl;
	}
	virtual void redo()
	{
		std::cout << "redo walk command" << std::endl;
	}
private:
	Actor* mActor;
};