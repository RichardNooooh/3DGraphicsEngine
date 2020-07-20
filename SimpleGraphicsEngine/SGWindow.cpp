#include "SGWindow.h"
#include <iostream>
#include <cmath>

using namespace std;

SGWindow::SGWindow()
{
    consoleHandle = GetConsoleWindow();

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
    ReleaseDC(consoleHandle, currentDeviceContext);
}

void SGWindow::SetFramePixel(int x, int y, COLORREF color)
{
    SetPixel(currentDeviceContext, x, y, color);
    cin.ignore();
}

void SGWindow::SetTitle(char title[])
{
}
