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
	static Matrix44 perspectiveMatrix = {};
	perspectiveMatrix.m[0][0] = 1 / tanf(fovAngle / 2);
	perspectiveMatrix.m[1][1] = 1 / tanf(fovAngle / 2);
	perspectiveMatrix.m[2][2] = (zFarPlane + zNearPlane) / (zFarPlane - zNearPlane);
	perspectiveMatrix.m[3][2] = (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane);
	perspectiveMatrix.m[2][3] = -1;
	perspectiveMatrix.m[3][3] = 0;

	//for rotating the cube;
	float theta = 0.0f;

	//perspectiveMatrix.m[0][0] = _height / _width / tan(fovAngle / 2.0f);
	//perspectiveMatrix.m[1][1] = 1.0f / tan(fovAngle / 2.0f);
	//perspectiveMatrix.m[2][2] = (zFarPlane) / (zFarPlane - zNearPlane);
	//perspectiveMatrix.m[3][2] = (-zFarPlane * zNearPlane) / (zFarPlane - zNearPlane);
	//perspectiveMatrix.m[2][3] = 1;
	//perspectiveMatrix.m[3][3] = 0;

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
		//window->clear();

		//Rotation Matrices
		Matrix44 rotateMatrixZ = {};
		rotateMatrixZ.m[0][0] = cosf(theta);
		rotateMatrixZ.m[0][1] = -sinf(theta);
		rotateMatrixZ.m[1][0] = sinf(theta);
		rotateMatrixZ.m[1][1] = cosf(theta);
		rotateMatrixZ.m[2][2] = 1;
		rotateMatrixZ.m[3][3] = 1;

		Matrix44 rotateMatrixX = {};
		rotateMatrixX.m[0][0] = 1;
		rotateMatrixX.m[1][1] = cosf(theta * 0.5f);
		rotateMatrixX.m[1][2] = -sinf(theta * 0.5f);
		rotateMatrixX.m[2][1] = sinf(theta * 0.5f);
		rotateMatrixX.m[2][2] = cosf(theta * 0.5f);
		rotateMatrixX.m[3][3] = 1;

		Matrix44 generalRotateMatrix = rotateMatrixZ * rotateMatrixX;

		//std::cout << "Matrix is: ";
		//for (int i = 0; i < 4; i++)
		//{
		//	std::cout << "[ ";
		//	for (int j = 0; j < 4; j++)
		//		std::cout << generalRotateMatrix.m[i][j] << " ";
		//	std::cout << "]\n";
		//}
		//std::cout << "\n";

		Uint32* pixels = { 0 };
		int pitch = 0;

		theta += 0.05f;

		window->lockFrame(&pixels, &pitch);
		std::fill_n(pixels, _width * _height, 0);
		for (Triangle tri : cube) 
		{
			Triangle rotatedTriangle = tri;
			rotatedTriangle.points[0] = rotatedTriangle.points[0].Matrix44Multiply(generalRotateMatrix);
			rotatedTriangle.points[1] = rotatedTriangle.points[1].Matrix44Multiply(generalRotateMatrix);
			rotatedTriangle.points[2] = rotatedTriangle.points[2].Matrix44Multiply(generalRotateMatrix);


			Triangle triangleTranslated = rotatedTriangle;
			//move object forward a tiny bit
			triangleTranslated.points[0].z -= 2.5f;
			triangleTranslated.points[1].z -= 2.5f;
			triangleTranslated.points[2].z -= 2.5f;

			//draw projected triangles
			Vector3 projectedPoint0 = triangleTranslated.points[0].Matrix44Multiply(perspectiveMatrix);
			Vector3 projectedPoint1 = triangleTranslated.points[1].Matrix44Multiply(perspectiveMatrix);
			Vector3 projectedPoint2 = triangleTranslated.points[2].Matrix44Multiply(perspectiveMatrix);

			//move and scale to screen
			projectedPoint0 = projectedPoint0 + Vector3(1.5, 1.5, 0);
			projectedPoint1 = projectedPoint1 + Vector3(1.5, 1.5, 0);
			projectedPoint2 = projectedPoint2 + Vector3(1.5, 1.5, 0);

			projectedPoint0 = projectedPoint0.Scale(200);
			projectedPoint1 = projectedPoint1.Scale(200);
			projectedPoint2 = projectedPoint2.Scale(200);

			drawEmptyTriangle(pixels, projectedPoint0, projectedPoint1, projectedPoint2);
			//drawPoint(pixels, projectedPoint0);
			//drawPoint(pixels, projectedPoint1);
			//drawPoint(pixels, projectedPoint2);
		}

		window->unlockFrame();
		window->wait(16);
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
		pixels[(int)p.x + _width * (int)p.y] = 0xFFFF0000;
}


void SGEngine::drawEmptyTriangle(Uint32* pixels, Vector3 p0, Vector3 p1, Vector3 p2)
{
	//window->lockFrame(&pixels, &pitch);
	drawLine(pixels, p0, p1);
	//window->unlockFrame();
	//window->lockFrame(&pixels, &pitch);
	drawLine(pixels, p1, p2);
	//window->unlockFrame();
	//window->lockFrame(&pixels, &pitch);
	drawLine(pixels, p2, p0);
	//window->unlockFrame();
}

//Bresenham's Algoirthm from Wikipedia
void SGEngine::drawLine(Uint32* pixels, Vector3 p0, Vector3 p1)
{
	int x0 = p0.x; int x1 = p1.x;
	int y0 = p0.y; int y1 = p1.y;

	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);

	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while (x0 != x1 || y0 != y1)
	{
		if (x0 < _width && x0 >= 0 && y0 < _height && y0 >= 0)
			pixels[x0 + _width * y0] = 0xFFFFFFFF;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
