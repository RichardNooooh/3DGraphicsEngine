
//#include <Windows.h>

#include "SGEngine.h"
#undef main

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//}

int main() 
{
    SGEngine engine("Cube Drawing Test", 800, 600);
    engine.startLoop();
    return 0;
}