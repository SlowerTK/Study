#include <windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void SetColor(HWND, int, COLORREF);
void Save();

HWND hButton1, hButton2;
HWND hStatic1, hStatic2;
HINSTANCE hInst;
CHOOSECOLOR cc2, cc1;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS w{};

	hInst = hInstance;

	w.lpszClassName = L"My Class";
	w.hInstance = hInstance;
	w.lpfnWndProc = WndProc;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	if (!RegisterClass(&w))
		return 0;

	hWnd = CreateWindow(L"My Class", L"My Window", WS_OVERLAPPEDWINDOW, 200, 200, 350, 215, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	SendMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment");
	return (int)msg.wParam;
}

void AddControls(HWND hWnd)
{
	hButton1 = CreateWindow(L"button", L"Выбрать", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 10, 100, 30, hWnd, (HMENU)1, hInst, NULL);
	hButton2 = CreateWindow(L"button", L"Выбрать", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 50, 100, 30, hWnd, (HMENU)2, hInst, NULL);

	hStatic1 = CreateWindow(L"static", L"Hilight Color", WS_CHILD | WS_VISIBLE | SS_CENTER, 120, 10, 200, 30, hWnd, NULL, hInst, NULL);
	hStatic2 = CreateWindow(L"static", L"Hot Tracking Color", WS_CHILD | WS_VISIBLE | SS_CENTER, 120, 50, 200, 30, hWnd, NULL, hInst, NULL);

	CreateWindow(L"button", L"Стандартные", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 170, 90, 150, 30, hWnd, (HMENU)5, hInst, NULL);
	CreateWindow(L"button", L"Сохранить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 130, 100, 30, hWnd, (HMENU)3, hInst, NULL);
	CreateWindow(L"button", L"Отмена", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 220, 130, 100, 30, hWnd, (HMENU)4, hInst, NULL);
}

void SetColor(HWND hWnd, int id, COLORREF color)
{
	HDC hdc = GetDC(hWnd);
	HBRUSH hBrush = CreateSolidBrush(color);
	RECT rect;
	GetClientRect(hWnd, &rect);
	rect.left = 120;
	rect.top = id == 1 ? 10 : 50;
	rect.right = 320;
	rect.bottom = id == 1 ? 40 : 80;
	FillRect(hdc, &rect, hBrush);
	ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLongPtr(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SIZEBOX);
		AddControls(hWnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1:
		{
			static COLORREF acrCustClr[16];
			ZeroMemory(&cc1, sizeof(cc1));
			cc1.lStructSize = sizeof(cc1);
			cc1.hwndOwner = hWnd;
			cc1.lpCustColors = (LPDWORD)acrCustClr;
			cc1.rgbResult = RGB(0, 0, 0);
			cc1.Flags = CC_FULLOPEN | CC_RGBINIT;
			if (ChooseColor(&cc1) == TRUE)
			{
				SetColor(hWnd, 1, cc1.rgbResult);
			}
		}
		break;
		case 2:
		{
			static COLORREF acrCustClr[16];
			ZeroMemory(&cc2, sizeof(cc2));
			cc2.lStructSize = sizeof(cc2);
			cc2.hwndOwner = hWnd;
			cc2.lpCustColors = (LPDWORD)acrCustClr;
			cc2.rgbResult = RGB(0, 0, 0);
			cc2.Flags = CC_FULLOPEN | CC_RGBINIT;
			if (ChooseColor(&cc2) == TRUE)
			{
				SetColor(hWnd, 2, cc2.rgbResult);
			}
		}
		break;
		case 3: {
			Save();
			DestroyWindow(hWnd);
			MessageBox(NULL, L"Не забудь перезагрузить пк(если сейчас ничего не произошло)", L"Успех", MB_ICONINFORMATION);
			PostQuitMessage(0);
			break;
		}
		case 4: {
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			break;
		}
		case 5: {
			SetColor(hWnd, 1, RGB(0, 120, 215));
			cc1.rgbResult = RGB(0, 120, 215);
			SetColor(hWnd, 2, RGB(0, 102, 204));
			cc2.rgbResult = RGB(0, 102, 204);
			break;
		}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void Save()
{
	int R1 = GetRValue(cc1.rgbResult);
	int G1 = GetGValue(cc1.rgbResult);
	int B1 = GetBValue(cc1.rgbResult);
	int R2 = GetRValue(cc2.rgbResult);
	int G2 = GetGValue(cc2.rgbResult);
	int B2 = GetBValue(cc2.rgbResult);

	wstring str1 = to_wstring(R1) + L" " + to_wstring(G1) + L" " + to_wstring(B1);
	wstring str2 = to_wstring(R2) + L" " + to_wstring(G2) + L" " + to_wstring(B2);


	HKEY hKey;
	RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\\Colors", 0, KEY_ALL_ACCESS, &hKey);
	RegSetValueExW(hKey, L"Hilight", 0, REG_SZ, (LPBYTE)str1.c_str(), (DWORD)str1.length() * sizeof(wchar_t));
	RegSetValueExW(hKey, L"HotTrackingColor", 0, REG_SZ, (LPBYTE)str2.c_str(), (DWORD)str2.length() * sizeof(wchar_t));
	RegCloseKey(hKey);
}