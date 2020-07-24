#include "SGEngine.h"

#include "SGMath.h" //should move this to the header, maybe.

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
	//Perspective Matrix
	float fovAngle = 45;
	float zFarPlane = -10;
	float zNearPlane = 5;
	static Matrix44 PerspectiveMatrix = { { {1 / tan(45 / 2), 0, 0, 0},
											{0, 1 / tan(45 / 2), 0, 0},
											{0, 0, (zFarPlane + zNearPlane) / (zFarPlane - zNearPlane), -1},
											{0, 0, (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane), 0} } };

	//unit cube creation, TODO move this to main and add a "add mesh" thing
	Vector3 point000(0, 0, 0);
	Vector3 point001(0, 0, 1);
	Vector3 point010(0, 1, 0);
	Vector3 point011(0, 1, 1);
	Vector3 point100(1, 0, 0);
	Vector3 point101(1, 0, 1);
	Vector3 point110(1, 1, 0);
	Vector3 point111(1, 1, 1);

	Triangle front1 = { {point000, point010, point110} };
	Triangle front2 = { {point000, point110, point100} };
	Triangle right1 = { {point100, point110, point111} };
	Triangle right2 = { {point100, point111, point101} };
	Triangle top1 = { {point010, point011, point111} };
	Triangle top2 = { {point010, point111, point110} };
	Triangle left1 = { {point001, point011, point010} };
	Triangle left2 = { {point001, point010, point000} };
	Triangle back1 = { {point101, point111, point011} };
	Triangle back2 = { {point101, point011, point001} };
	Triangle bottom1 = { {point001, point000, point100} };
	Triangle bottom2 = { {point001, point100, point101} };
	
	std::vector<Triangle> cube{ front1, front2, right1, right2, top1, top2,
								left1, left2, back1, back2, bottom1, bottom2 };
	

	//main loop
	while (!window->isClosed())
	{
		window->pollEvents();

		Uint32* pixels = { 0 };
		int pitch = 0;

		window->lockFrame(&pixels, &pitch);
		for (Triangle tri : cube) 
		{
			//draw projected triangles
			Vector3 projectedPoint0 = tri.points[0].Matrix44Multiply(PerspectiveMatrix);
			Vector3 projectedPoint1 = tri.points[1].Matrix44Multiply(PerspectiveMatrix);
			Vector3 projectedPoint2 = tri.points[2].Matrix44Multiply(PerspectiveMatrix);
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
