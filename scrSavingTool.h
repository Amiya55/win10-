#ifndef SCRSAVINGTOOL_H
#define SCESAVINGTOOL_H

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
// 这里的Python.h你需要自己利用Vs2022或者cmakeLists.txt链接
#include <Python.h>

// 调用python脚本将生成的bmp文件转化为png并写到指定的目录
void callPython();

// 利用windows api读取剪切板中的DIB图片生成bmp文件
static bool create_pic();

// windowPrco函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


#endif