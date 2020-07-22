
//#include <Windows.h>

#include "SGEngine.h"
#undef main

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//}

int main() 
{
    SGEngine engine("test ", 640 / 4, 480 / 4);
    engine.startLoop();
    return 0;
}