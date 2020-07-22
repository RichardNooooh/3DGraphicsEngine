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

		Uint32 *pixels = new Uint32[_width * _height];

		unsigned color = 0xFF01AAA5, blank = 0xFFFFFF, duplicate = 0xFFAA55;
		for (int x = 0; x < _width; x++)
		{
			for (int y = 0; y < _height; y++)
			{
				/*int a = 255 << 24;
				int r = (rand() % 255) << 16;
				int g = (rand() % 255) << 12;
				int b = (rand() % 255);*/
				pixels[x + y * _width] = color;
			}
		}
		window->updateFrame(pixels);
		window->wait(100);
		delete[] pixels;
	}
	return 0;
}

void SGEngine::initialize(std::string title)
{
	window = new SGWindow(title, _width, _height);
}
