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
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void SGWindow::clear() const
{
	SDL_RenderClear(_renderer);
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
		case SDL_MOUSEMOTION:
			std::cout << event.motion.x << ", " << event.motion.y << "\n";
			break;
		}

	}
}

//int SGWindow::lockFrame(FrameInfo frameInfo)
//{
//	if (SDL_LockTexture(_texture, NULL, &frameInfo.pixels, &frameInfo.pitch) != 0)
//	{
//		std::cerr << "Unable to LockTexture";
//		return -1;
//	}
//	return 0;
//}
//
//void SGWindow::unlockFrame(FrameInfo frameInfo)
//{
//	SDL_UnlockTexture(_texture);
//	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
//	SDL_RenderPresent(_renderer);
//}

int SGWindow::updateFrame(Uint32 *pixels)
{
	SDL_UpdateTexture(_texture, NULL, pixels, _width * 4);
	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
	SDL_RenderPresent(_renderer);
	return 0;
}

void SGWindow::wait(Uint32 milliseconds)
{
	SDL_Delay(milliseconds);
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

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer";
		return false;
	}

	//I think the width/height is divided by 4 because of the size of the pixel (UINT32), need to experiment
	_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, _width, _height); 
	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create texture";
		return false;
	}
	
	return true;
}
