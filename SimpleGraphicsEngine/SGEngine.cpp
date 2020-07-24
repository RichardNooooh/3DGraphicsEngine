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
	//Perspective Matrix
	float fovAngle = 90.0f / 180 * 3.14159f;
	float zFarPlane = 1000;
	float zNearPlane = 0.1;
	static Matrix44 PerspectiveMatrix = {};
	PerspectiveMatrix.m[0][0] = 1 / tan(fovAngle / 2);
	PerspectiveMatrix.m[1][1] = 1 / tan(fovAngle / 2);
	PerspectiveMatrix.m[2][2] = (zFarPlane + zNearPlane) / (zFarPlane - zNearPlane);
	PerspectiveMatrix.m[3][2] = (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane);
	PerspectiveMatrix.m[2][3] = -1;
	PerspectiveMatrix.m[3][3] = 0;

	//PerspectiveMatrix.m[0][0] = _height / _width / tan(fovAngle / 2);
	//PerspectiveMatrix.m[1][1] = 1 / tan(fovAngle / 2);
	//PerspectiveMatrix.m[2][2] = (zFarPlane) / (zFarPlane - zNearPlane);
	//PerspectiveMatrix.m[3][2] = (-zFarPlane * zNearPlane) / (zFarPlane - zNearPlane);
	//PerspectiveMatrix.m[2][3] = 1;
	//PerspectiveMatrix.m[3][3] = 0;

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
		window->clear();

		Uint32* pixels = { 0 };
		int pitch = 0;


		window->lockFrame(&pixels, &pitch);
		for (Triangle tri : cube) 
		{
			//move object forward a tiny bit
			tri.points[0].z += 3;
			tri.points[1].z += 3;
			tri.points[2].z += 3;

			//draw projected triangles
			Vector3 projectedPoint0 = tri.points[0].Matrix44Multiply(PerspectiveMatrix);
			Vector3 projectedPoint1 = tri.points[1].Matrix44Multiply(PerspectiveMatrix);
			Vector3 projectedPoint2 = tri.points[2].Matrix44Multiply(PerspectiveMatrix);

			//move and scale to screen
			projectedPoint0 = projectedPoint0 + Vector3(1, 1, 0);
			projectedPoint1 = projectedPoint1 + Vector3(1, 1, 0);
			projectedPoint2 = projectedPoint2 + Vector3(1, 1, 0);

			projectedPoint0 = projectedPoint0.Scale(200);
			projectedPoint1 = projectedPoint1.Scale(200);
			projectedPoint2 = projectedPoint2.Scale(200);

			drawPoint(pixels, projectedPoint0);
			drawPoint(pixels, projectedPoint1);
			drawPoint(pixels, projectedPoint2);
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

void SGEngine::drawPoint(Uint32 *pixels, Vector3 p)
{
	if (p.x < _width && p.x >= 0 && p.y < _height && p.y >= 0)
		pixels[(int)p.x + _width * (int)p.y] = 0xFFFFFFFF;
}

//void SGEngine::drawTriangle(Uint32* pixels, Vector3 p0, Vector3 p1, Vector3 p2)
//{
//	
//}
