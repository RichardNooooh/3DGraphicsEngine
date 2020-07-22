
//#include <Windows.h>

#include "SGEngine.h"
#undef main

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//}

int main() 
{
    SGEngine engine("test ", 640, 480);
    engine.startLoop();
    return 0;
}