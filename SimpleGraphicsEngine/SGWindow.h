#pragma once
/*
 * Disables unused features of Windows.h and clears up namespace.
 * From user "Cat Plus Plus" on StackOverFlow: 
 * https://stackoverflow.com/questions/1394910/how-to-tame-the-windows-headers-useful-defines
 */

#define NOGDICAPMASKS
//#define NOVIRTUALKEYCODES
//#define NOWINMESSAGES
//#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
//#define NOSHOWWINDOW
//#define OEMRESOURCE
//#define NOATOM
//#define NOCLIPBOARD
//#define NOCTLMGR
//#define NOKERNEL
//#define NOUSER
//#define NONLS
//#define NOMB
//#define NOMEMMGR
//#define NOMETAFILE
//#define NOMINMAX
//#define NOMSG
//#define NOOPENFILE
#define NOSCROLL
//#define NOSERVICE
//#define NOSOUND
//#define NOTEXTMETRIC
//#define NOWH
//#define NOWINOFFSETS
//#define NOCOMM
//#define NOKANJI
//#define NOHELP
//#define NOPROFILER
//#define NODEFERWINDOWPOS
//#define NOMCX

#include <Windows.h>
#include <string>

class SGWindow
{
public:
	SGWindow();
	~SGWindow();
	void StartFrame();
	void EndFrame();
	void SetFramePixel(int x, int y, COLORREF color);
	void SetTitle(char title[]);
private:
	HWND consoleHandle;
	HDC currentDeviceContext;
};

