#pragma once
#include "SGWindow.h"
#include "SGMath.h";
#include <vector>

class SGEngine 
{
public:
	SGEngine(std::string title, int width, int height);
	~SGEngine();

	void addMesh(std::vector<Triangle> mesh);

	int startLoop();

private:
	void initialize(std::string title);
	void drawEmptyTriangle(Uint32* pixels, Vector3 p0, Vector3 p1, Vector3 p2);
	void drawLine(Uint32* pixels, Vector3 p0, Vector3 p1);
	void drawPoint(Uint32* pixels, Vector3 p);

	SGWindow *window = nullptr;

	std::vector<std::vector<Triangle>> meshes;
	
	int _width;
	int _height;
};
