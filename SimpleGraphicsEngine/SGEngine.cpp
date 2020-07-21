#include "SGEngine.h"


SGEngine::SGEngine(int width, int height) : w(width), h(height), window(width, height) 
{
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
		//window.StartFrame();

		//vertically drawn
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++) 
			{
				window.SetFramePixel(x, y, RGB(255, 25, 252));
			}
		}




		//end frame
		//window.EndFrame();
	}
}
