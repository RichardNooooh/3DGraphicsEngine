#include "SGWindow.h"
#include <iostream>

//From ArchieG on Youtube: https://www.youtube.com/channel/UCn8h9ivAVGou9dkn0H9aVDw
SGWindow::SGWindow(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	_closed = !initialize();
}

SGWindow::~SGWindow()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void SGWindow::pollEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) 
	{
		switch (event.type) {
		case SDL_QUIT:
			_closed = true;
			break;
		}
	}
}

bool SGWindow::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initialize SDL\n";
		return false;
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
	if (_window == nullptr) 
	{
		std::cerr << "Failed to create window";
		return false;
	}

	return true;
}
