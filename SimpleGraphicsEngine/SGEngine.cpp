#include "SGEngine.h"


SGEngine::SGEngine(int height, int width)
{
	w = width;
	h = height;
	window = SGWindow();
	StartRenderingLoop();
}

SGEngine::~SGEngine()
{

}

void SGEngine::setSize(int length, int width)
{

}

void SGEngine::StartRenderingLoop()
{
	bool isRendering = true;
	while (isRendering) 
	{
		//start frame




		//end frame
	}
}
