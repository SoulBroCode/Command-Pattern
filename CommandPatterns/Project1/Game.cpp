#include "Game.h"
#include <iostream>
#include <thread>
#include "ConcreteCommand.h"

using namespace std;

Game::Game() : m_running(false)
{
}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_p_Window != 0)
		{
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
			{
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);

				mActor = new Actor();
				mInputHandler = new InputHandler();
				mMacroCommand = new MacroCommand();

				Command* fireCommand = new FireCommand(mActor);
				Command* walkCommand = new WalkCommand(mActor);
				Command* jumpCommand = new JumpCommand(mActor);
				Command* moveCommand = new MoveCommand(mActor);
				
				//binding the commands to a map
				mInputHandler->bindKeyCommand(SDLK_a, new FireCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_d, new WalkCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_w, new JumpCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_s, new MoveCommand(mActor));

				mInputHandler->bindKeyCommand(SDLK_LEFT, new FireCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_RIGHT, new WalkCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_UP, new JumpCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_DOWN, new MoveCommand(mActor));
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	m_running = true;

	return true;
}



void Game::LoadContent()
{
	m_p_Surface = SDL_LoadBMP("assets/sprite.bmp");
	m_p_Texture = SDL_CreateTextureFromSurface(m_p_Renderer, m_p_Surface);
	SDL_FreeSurface(m_p_Surface);

	if(SDL_QueryTexture(m_p_Texture, NULL, NULL, &m_Source.w, &m_Destination.h)==0)
	{
		m_Destination.x = m_Source.x = 0;
		m_Destination.y = m_Source.y = 0;
		m_Destination.w = m_Source.w;
		m_Destination.h = m_Source.h;
	}
	else
	{
		m_running = false;
	}
}

void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{

}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		case SDL_KEYDOWN:
		{
			SDL_Keycode key = event.key.keysym.sym;
			Command* command = mInputHandler->handleInput(key);
			if (command != nullptr)
			{
				mMacroCommand->add(command);
				mMacroCommand->execute();
			}
			else if (key == SDLK_RETURN)
			{
				mMacroCommand->redo();
			}
			else if (key == SDLK_BACKSPACE)
			{
				mMacroCommand->undo();
			}			
		}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::UnloadContent()
{

}

void Game::CleanUp()
{
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}
