#pragma once
#include "SGWindow.h"
#include <string>
#include "SGMath.h";

class SGEngine 
{
public:
	SGEngine(std::string title, int width, int height);
	~SGEngine();

	int startLoop();

private:
	void initialize(std::string title);
	//void drawTriangle(Uint32* pixels, Vector3 p0, Vector3 p1, Vector3 p2);
	void drawPoint(Uint32* pixels, Vector3 p);

	SGWindow *window = nullptr;
	
	int _width;
	int _height;
};
