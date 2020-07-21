#include "SGWindow.h"
#include <iostream>
#include <cmath>

using namespace std;

SGWindow::SGWindow(int width, int height)
{
    consoleHandle = GetConsoleWindow();

    RECT r = { 0 };
    GetWindowRect(consoleHandle, &r); //stores the console's current dimensions
    MoveWindow(consoleHandle, r.left, r.top, width, height, TRUE);

    currentDeviceContext = nullptr;
}

SGWindow::~SGWindow()
{
    EndFrame();
}

void SGWindow::StartFrame()
{
    currentDeviceContext = GetDC(consoleHandle);
}

void SGWindow::EndFrame()
{

}

void SGWindow::SetFramePixel(int x, int y, COLORREF color)
{
    currentDeviceContext = GetDC(consoleHandle);
    SetPixel(currentDeviceContext, x, y, color);
    ReleaseDC(consoleHandle, currentDeviceContext);
}

void SGWindow::SetTitle(char title[])
{
}
