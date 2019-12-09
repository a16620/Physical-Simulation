#include "MainFrame.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MainFrame mf;
	mf.Initialize(hInstance, hPrevInstance, lpszCmdParam, nCmdShow);
	mf.Run();
	return 0;
}
