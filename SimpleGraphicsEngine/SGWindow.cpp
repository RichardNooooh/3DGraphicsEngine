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
}

void SGWindow::SetPixelImage(int x, int y)
{
    HDC mydc = GetDC(consoleHandle);

    ReleaseDC(consoleHandle, mydc);
    cin.ignore();
}

void SGWindow::SetTitle(char title[])
{
}
