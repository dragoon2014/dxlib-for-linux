#define DX_MAKE

#include "DxWindowLinux.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE


extern int NS_GetWindowSize(int *Width, int *Height){
    *Width = GLINUX.Device.Screen.Width;
    *Height = GLINUX.Device.Screen.Height;
    return 0;
}

extern int NS_SetMainWindowText(const TCHAR *WindowText){
    Display* d = GLINUX.Device.Screen.XDisplay;
    Window w = GLINUX.Device.Screen.XWindow;
    Xutf8SetWMProperties(d, w, WindowText, NULL, NULL, 0, NULL, NULL, NULL);
    return 0;
}


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

