#include "SGEngine.h"

#include <vector>
#include <iostream>

SGEngine::SGEngine(std::string title, int width, int height) 
	: _width(width), _height(height)
{
	Initialize(title);

}

SGEngine::~SGEngine()
{
	delete window;
}

void SGEngine::addMesh(std::vector<Triangle> mesh)
{
	meshes.push_back(mesh);
}

int SGEngine::startLoop()
{
	//Perspective Matrix
	float fovAngle = 90.0f / 180 * 3.14159f;
	float zFarPlane = 1000.0f;
	float zNearPlane = 0.1f;
	static Matrix44 perspectiveMatrix = {};
	perspectiveMatrix.m[0][0] = (float)_height / (float)_width / tanf(fovAngle / 2);
	perspectiveMatrix.m[1][1] = 1 / tanf(fovAngle / 2);
	perspectiveMatrix.m[2][2] = (zFarPlane + zNearPlane) / (zFarPlane - zNearPlane);
	perspectiveMatrix.m[3][2] = (2 * zFarPlane * zNearPlane) / (zFarPlane - zNearPlane);
	perspectiveMatrix.m[2][3] = -1;
	perspectiveMatrix.m[3][3] = 0;

	//for rotating the cube;
	float theta = 0.0f;

	//perspectiveMatrix.m[0][0] = (float)_height / (float)_width / tanf(fovAngle / 2.0f);
	//perspectiveMatrix.m[1][1] = 1.0f / tanf(fovAngle / 2.0f);
	//perspectiveMatrix.m[2][2] = (zFarPlane) / (zFarPlane - zNearPlane);
	//perspectiveMatrix.m[3][2] = (-zFarPlane * zNearPlane) / (zFarPlane - zNearPlane);
	//perspectiveMatrix.m[2][3] = 1;
	//perspectiveMatrix.m[3][3] = 0;
	

	//main loop
	while (!window->isClosed())
	{
		window->PollEvents();
		//window->clear();

		//Rotation Matrices
		Matrix44 rotateMatrixZ = {};
		rotateMatrixZ.m[0][0] = cosf(theta);
		rotateMatrixZ.m[0][1] = -sinf(theta);
		rotateMatrixZ.m[1][0] = sinf(theta);
		rotateMatrixZ.m[1][1] = cosf(theta);
		rotateMatrixZ.m[2][2] = 1.0f;
		rotateMatrixZ.m[3][3] = 1.0f;

		Matrix44 rotateMatrixX = {};
		rotateMatrixX.m[0][0] = 1.0f;
		rotateMatrixX.m[1][1] = cosf(theta * 0.5f);
		rotateMatrixX.m[1][2] = -sinf(theta * 0.5f);
		rotateMatrixX.m[2][1] = sinf(theta * 0.5f);
		rotateMatrixX.m[2][2] = cosf(theta * 0.5f);
		rotateMatrixX.m[3][3] = 1.0f;

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

		theta += 0.0125f;

		window->LockFrame(&pixels, &pitch);
		std::fill_n(pixels, _width * _height, 0); // clears the screen to black

		Vector3 camera(0.0f, 0.0f, 0.0f);

		for (std::vector<Triangle> mesh : meshes)
		{
			for (Triangle tri : mesh)
			{
				Triangle rotatedTriangle = tri;
				rotatedTriangle._points[0] = rotatedTriangle._points[0].Matrix44Multiply(generalRotateMatrix);
				rotatedTriangle._points[1] = rotatedTriangle._points[1].Matrix44Multiply(generalRotateMatrix);
				rotatedTriangle._points[2] = rotatedTriangle._points[2].Matrix44Multiply(generalRotateMatrix);
				//rotatedTriangle._normal = &rotatedTriangle._normal->Matrix44Multiply(generalRotateMatrix);

				Triangle triangleTranslated = rotatedTriangle;
				//move object forward a tiny bit
				triangleTranslated._points[0].z -= 2.5f;
				triangleTranslated._points[1].z -= 2.5f;
				triangleTranslated._points[2].z -= 2.5f;
				//triangleTranslated._normal->z -= 2.5f;

				//check if visible
				//Vector3 triangleMidpoint = (triangleTranslated._points[0] + triangleTranslated._points[1] + triangleTranslated._points[2]).Scale(1.0f / 3.0f);
				Vector3 cameraToTriangle = triangleTranslated._points[1] - camera;
				Vector3 normal = Vector3::Normal(triangleTranslated._points[1] - triangleTranslated._points[0], 
												triangleTranslated._points[2] - triangleTranslated._points[0]);
				float alignmentValue = cameraToTriangle.DotProduct(normal);
				if (alignmentValue < 0)
				{
					//draw projected triangles
					Vector3 projectedPoint0 = triangleTranslated._points[0].Matrix44Multiply(perspectiveMatrix);
					Vector3 projectedPoint1 = triangleTranslated._points[1].Matrix44Multiply(perspectiveMatrix);
					Vector3 projectedPoint2 = triangleTranslated._points[2].Matrix44Multiply(perspectiveMatrix);

					//move and scale to screen
					projectedPoint0 = projectedPoint0.Scale(200);
					projectedPoint1 = projectedPoint1.Scale(200);
					projectedPoint2 = projectedPoint2.Scale(200);

					float translateScreenX = _width / 2;
					float translateScreenY = _height / 2;

					projectedPoint0 = projectedPoint0 + Vector3(translateScreenX, translateScreenY, 0);
					projectedPoint1 = projectedPoint1 + Vector3(translateScreenX, translateScreenY, 0);
					projectedPoint2 = projectedPoint2 + Vector3(translateScreenX, translateScreenY, 0);


					drawEmptyTriangle(pixels, projectedPoint0, projectedPoint1, projectedPoint2);
					//drawPoint(pixels, projectedPoint0);
					//drawPoint(pixels, projectedPoint1);
					//drawPoint(pixels, projectedPoint2);
				}
			}
		}

		window->UnlockFrame();
		window->Wait(16); //60fps
	}
	return 0;
}

void SGEngine::Initialize(std::string title)
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
	drawLine(pixels, p0, p1);
	drawLine(pixels, p1, p2);
	drawLine(pixels, p2, p0);
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
