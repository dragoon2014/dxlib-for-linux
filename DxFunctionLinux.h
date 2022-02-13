
#ifndef DX_FUNCTIONLINUX_H
#define DX_FUNCTIONLINUX_H

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

#define DX_FUNCTION_START


// DxWindow.cpp関数プロトタイプ宣言

//// ウインドウ関係情報取得関数
extern  int         GetWindowSize(                  int *Width, int *Height ) ;                             // メインウインドウのクライアント領域のサイズを取得する

//// 設定系関数
extern  int         SetMainWindowText(                      const TCHAR *WindowText                          ) ;                                // SetWindowText の別名関数

#undef DX_FUNCTION_START
#define DX_FUNCTION_END
#undef DX_FUNCTION_END


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_FUNCTIONLINUX_H

