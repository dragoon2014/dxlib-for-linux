#ifndef DX_WINDOW_LINUX_H
#define DX_WINDOW_LINUX_H

#include "DxGraphicsLinux.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE


#define NS_GetWindowSize                        GetWindowSize
#define NS_SetMainWindowText                    SetMainWindowText


extern int GetWindowSize(int *Width, int *Height);
extern int SetMainWindowText(const TCHAR *WindowText);


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_WINDOW_LINUX_H
