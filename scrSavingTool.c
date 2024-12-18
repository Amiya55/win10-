#include "scrSavingTool.h"

void callPython()
{
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		fprintf(stderr, "failed to load python module");
		return;
	}
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	PyObject* pModule = PyImport_ImportModule("bmp2png");
	if (!pModule)
	{
		fprintf(stderr, "failed to load python module");
		return;
	}

	PyObject* pFunc = PyObject_GetAttrString(pModule, "bmp2png");
	if (!pFunc)
	{
		Py_DECREF(pModule);
		fprintf(stderr, "failed to load python module");
		return;
	}

	PyObject_CallObject(pFunc, 0);
	Py_DECREF(pModule);
	Py_DECREF(pFunc);


}

static bool create_pic()
{
	if (OpenClipboard(NULL))
	{
		if (IsClipboardFormatAvailable(CF_DIB))
		{
			// 获取剪切板内存空间句柄
			HANDLE hDib = GetClipboardData(CF_DIB);
			if (!hDib)
			{
				CloseClipboard();
				fprintf(stderr, "failed to creat handle");
				return false;
			}
			// 获得剪切板中的DIB数据大小
			size_t clipboardSize = GlobalSize(hDib);

			// 返回char*指针(GlobalLock()函数返回的是无类型指针，我们这里用了强制类型转换)
			char* data = (char*)GlobalLock(hDib);
			if (!data)
			{
				CloseClipboard();
				fprintf(stderr, "failed to get pionter");
			}

			// 构建文件头
			BITMAPFILEHEADER fileHeader;
			fileHeader.bfType = 0x4d42;
			fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + clipboardSize;
			fileHeader.bfReserved1 = 0;
			fileHeader.bfReserved2 = 0;
			fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


			FILE* pf = fopen("temp.bmp", "wb");
			if (!pf)
			{
				GlobalUnlock(hDib);
				CloseClipboard();
				fprintf(stderr, "failed to creat a bmp file");
				return false;
			}

			// 将文件头，信息头，图片数据原封不动写到文件中
			fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pf);
			fwrite(data, sizeof(char), sizeof(BITMAPINFOHEADER), pf);
			fwrite(data + sizeof(BITMAPINFOHEADER), sizeof(char), clipboardSize - sizeof(BITMAPINFOHEADER), pf);

			fclose(pf);

			GlobalUnlock(hDib);
		}
		CloseClipboard();
	}

	callPython();
	return true;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLIPBOARDUPDATE:
		if (OpenClipboard(NULL))
		{
			if (IsClipboardFormatAvailable(CF_DIB))
			{
				if(!create_pic())
				{
					time_t now_time;
					time(&now_time);

					FILE* pf = fopen("./failure.log", "a");
					fprintf(pf, "%s", ctime(&now_time));
					fprintf(pf, "%s", "bmp文件生成失败\n");
					fclose(pf);	
				}
			}
			CloseClipboard();
		}
		break;

	case WM_DESTROY:
		Py_Finalize();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}