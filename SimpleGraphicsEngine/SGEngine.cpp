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
		
		std::vector<Uint32> pixels(Uint64(_width) * _height, 0);
		Uint32* pixelData = pixels.data();
		int pitch = 0;

		window->lockFrame(&pixelData, &pitch);
		for (int x = 0; x < pitch; x++)
		{
			for (int y = 0; y < _height; y++)
			{
				/*int a = 255 << 24;
				int r = (rand() % 255) << 16;
				int g = (rand() % 255) << 12;
				int b = (rand() % 255);*/
				pixels[Uint64(x)+ Uint64(y) * pitch] = 0xFFAAAAAA;
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
