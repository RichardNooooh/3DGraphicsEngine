#pragma once
#include "SGWindow.h"
#include <string>

class SGEngine 
{
public:
	SGEngine(std::string title, int width, int height);
	~SGEngine();

	int startLoop();

private:
	void initialize(std::string title);

	SGWindow *window = nullptr;
	
	int _width;
	int _height;
};
