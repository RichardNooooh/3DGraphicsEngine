
//#include <Windows.h>

#include "SGEngine.h"
#undef main

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//}

int main() 
{
	//unit cube creation, TODO move this to main and add a "add mesh" thing
	Vector3 point000(0.0f, 0.0f, 0.0f);
	Vector3 point001(0.0f, 0.0f, 1.0f);
	Vector3 point010(0.0f, 1.0f, 0.0f);
	Vector3 point011(0.0f, 1.0f, 1.0f);
	Vector3 point100(1.0f, 0.0f, 0.0f);
	Vector3 point101(1.0f, 0.0f, 1.0f);
	Vector3 point110(1.0f, 1.0f, 0.0f);
	Vector3 point111(1.0f, 1.0f, 1.0f);

	Triangle front1(point000, point010, point110);
	Triangle front2(point000, point110, point100);
	Triangle right1(point100, point110, point111);
	Triangle right2(point100, point111, point101);
	Triangle top1(point010, point011, point111);
	Triangle top2(point010, point111, point110);
	Triangle left1(point001, point011, point010);
	Triangle left2(point001, point010, point000);
	Triangle back1(point101, point111, point011);
	Triangle back2(point101, point011, point001);
	Triangle bottom1(point101, point001, point000);
	Triangle bottom2(point101, point000, point100);

	std::vector<Triangle> cube{ front1, front2, right1, right2, top1, top2,
								left1, left2, back1, back2, bottom1, bottom2 };


    SGEngine engine("Cube Drawing Test", 800, 600);
	engine.addMesh(cube);
    engine.startLoop();
    return 0;
}