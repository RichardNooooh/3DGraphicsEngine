#include "SGEngine.h"
#include <vector>
#include <iostream>

SGEngine::SGEngine(std::string title, int width, int height) 
	: _width(width), _height(height)
{
	initialize(title);

}

SGEngine::~SGEngine()
{
	delete window;
}

int SGEngine::startLoop()
{
	while (!window->isClosed())
	{
		window->pollEvents();

		Uint32* pixels = { 0 };
		int pitch = 0;

		window->lockFrame(&pixels, &pitch);
		for (int x = 0; x < _width; x++)
		{
			for (int y = 0; y < _height; y++)
			{
				int a = 255 << 24;
				int r = (rand() % 255) << 16;
				int g = (rand() % 255) << 12;
				int b = (rand() % 255);
				pixels[x + y * _width] = a | r | g | b;
			}
		}
		window->unlockFrame();
		window->wait(100);
	}
	return 0;
}

void SGEngine::initialize(std::string title)
{
	window = new SGWindow(title, _width, _height);
}
