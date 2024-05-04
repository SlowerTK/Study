#include <windows.h>
#include <gl/gl.h>
#include <math.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void drow1task(HDC& hDC) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(-2.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-2.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-0.9f, 0.9f);
	glVertex2f(-0.3f, 0.9f);
	glVertex2f(-0.3f, 0.3f);
	glVertex2f(-0.9f, 0.3f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0.9f, -0.8f);
	glVertex2f(0.1f, -0.8f);
	glVertex2f(0.1f, -0.2f);
	glVertex2f(0.9f, -0.2f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	for(float i = 0; i < 360; i += 1) {
		glVertex2f((float)0.6 + (float)0.2 * (float)cos(i), (float)0.6 + (float)0.2 * (float)sin(i));
	}
	glEnd();
	SwapBuffers(hDC);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	WNDCLASSEX wcex{};
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;

	float theta = 0.0f;

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if(!RegisterClassEx(&wcex))
		return 0;

	hwnd = CreateWindowEx(0, L"GLSample", L"OpenGL Sample", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 680, 680, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);

	EnableOpenGL(hwnd, &hDC, &hRC);

	MSG msg;
	BOOL bQuit = FALSE;
	while(!bQuit) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) {
				bQuit = TRUE;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			drow1task(hDC);
			Sleep(1);
		}
	}


	DisableOpenGL(hwnd, hDC, hRC);
	DestroyWindow(hwnd);
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch(wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC) {
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	*hDC = GetDC(hwnd);

	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}
void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}

