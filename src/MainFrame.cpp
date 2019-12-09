#include "MainFrame.h"

MainFrame::MainFrame()
{
}


MainFrame::~MainFrame()
{
	for (auto obj : m_objList) {
		delete obj;
	}
	for (auto obj : m_adpList) {
		delete obj;
	}

	ReleaseDC(hWnd ,hdc);
}

Atom* BuildAtom(const Vector2& position, const Vector2& velocity, _m_d_float mass, _m_d_int radius, _m_d_float charge = 0) {
	Atom* at = new Atom(radius);
	at->position = position;
	at->velocity = velocity;
	at->charge = charge;
	at->mass = mass;
	return at;
}

void MainFrame::Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//Init wnd
	WNDCLASS WndClass;
	hInst = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WND_SIZE_X, WND_SIZE_Y,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	hdc = GetDC(hWnd);

	//Init objs	
	m_objList.push_back(BuildAtom(Vector2(350, 300), Vector2(_m_sqrt(20.f), 0), 4, 4));
	m_objList.push_back(new KineticObject(Vector2(350, 350), 10));

	m_adpList.push_back(new GravityMovement());
}

void MainFrame::Run()
{
	MSG msg;
	DWORD time=GetTickCount();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DWORD ct = GetTickCount();
		if (ct > time)
		{
			const _m_d_float dt = (ct - time) / 50.0f;
			time = ct + 50;
			Update(dt);
			Render();
		}
	}
}

void MainFrame::Update(const _m_d_float& dt)
{
	for (auto adaptor : m_adpList) {
		adaptor->Perform(&m_objList, dt);
	}
	for (auto obj : m_objList) {
		obj->Update(dt);
	}
}

void MainFrame::Render()
{
	FillRect(hdc, &rc, NULL);
	for (auto obj : m_objList) {
		obj->Render(hdc);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
