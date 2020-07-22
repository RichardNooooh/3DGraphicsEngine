#include "SGWindow.h"
#include <Windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SGWindow window("Test", 640, 480);
    while (!window.isClosed()) 
    {
        window.pollEvents();
    }

    return 0;
}