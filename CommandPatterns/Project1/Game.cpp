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
				count = 0;
				mActor = new Actor();
				mInputHandler = new InputHandler();
				mMacroCommand = new MacroCommand();



				mInputHandler->bindKeyCommand(SDLK_a, new JumpCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_d, new JumpCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_w, new JumpCommand(mActor));
				mInputHandler->bindKeyCommand(SDLK_s, new JumpCommand(mActor));

				//mInputHandler->bindKeyCommand(SDLK_RETURN, mMacroCommand);
				//mInputHandler->bindKeyCommand(SDLK_BACKSPACE, new JumpCommand(mActor));

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

		//DEBUG_MSG("Destination X:" + m_Destination.x);
		/*DEBUG_MSG("Destination Y:" + m_Destination.y);
		DEBUG_MSG("Destination W:" + m_Destination.w);
		DEBUG_MSG("Destination H:" + m_Destination.h);*/
	}
	else
	{
		m_running = false;
	}
}

void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);

	/*
	if(m_p_Renderer != nullptr && m_p_Texture != nullptr)
		SDL_RenderCopy(m_p_Renderer, m_p_Texture, NULL, NULL);*/
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	//mMacroCommand->execute();
	//count++;
	//std::cout << "output : " << count << std::endl;
	//DEBUG_MSG("Updating....");
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
			}
			else if (key == SDLK_RETURN)
			{
				mMacroCommand->execute();
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
