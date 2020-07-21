#pragma once
/*
 * Class structure
 * Stores the internal vertex information, and does the necessary computations for it.
 * This is the place where the user can utilize there own rasterization algorithm or ray tracing or whatever.
 * Does not use DirectX or OpenGL. Experimental setup for learning rendering and such.
 * Can eventually be used for physics engine stuff too :D
 */
#include "SGWindow.h"

class SGEngine 
{
public:
	SGEngine(int width, int height);
	~SGEngine();
	void setSize(int height, int width);
private:
	int w;
	int h;
	SGWindow window;
	void StartRenderingLoop();

};