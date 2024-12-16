#include "scrSavingTool.h"


int main()
{
	const WCHAR* class_name = L"ClipboardMonitorClass";

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = class_name;  // 窗口名

	if (!RegisterClass(&wc))
	{
		fprintf(stderr, "failed to register window class");
		return 1;
	}

	HWND hwnd = CreateWindowEx(
		0,
		class_name,
		L"clipboard monitor",
		0,
		0, 0, 0, 0,
		NULL,
		NULL,
		wc.hInstance,
		NULL
	);

	if (!hwnd)
	{
		fprintf(stderr, "failed to create window");
		return 1;
	}

	/*SetClipboardViewer(hwnd);*/
	if (!AddClipboardFormatListener(hwnd))
	{
		fprintf(stderr, "failed to add clipboard listener");
		return 1;
	}

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}