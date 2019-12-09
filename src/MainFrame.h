#pragma once
#include "CObject.h"
#include "AdditionalCalculations.h"
#include <vector>
using namespace std;
class MainFrame
{
private:
	vector<CObject*> m_objList;
	vector<AdditionalCalculation*>  m_adpList;
	HINSTANCE hInst;
	HWND hWnd;
	HDC hdc;
	LPCSTR lpszClass = "Simulator";
	RECT rc{ 0,0, WND_SIZE_X, WND_SIZE_Y };

public:
	MainFrame();
	~MainFrame();

	void Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow);
	void Run();

	void Update(const _m_d_float& dt);
	void Render();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);