//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		Linux用入力情報プログラム
// 
//  	Ver 3.22c
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_INPUT

// インクルード----------------------------------------------------------------
#include "DxInputLinux.h"
#include "DxSystemLinux.h"
#include "../DxLog.h"
#include "../DxInput.h"
#include "../DxSystem.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義------------------------------------------------------------------

// 型定義----------------------------------------------------------------------

// 定数定義 ----------------------------------------------------------------------

// データ宣言------------------------------------------------------------------

// 関数プロトタイプ宣言 -------------------------------------------------------

// プログラム------------------------------------------------------------------

// 入力システムを初期化する処理の環境依存処理
extern int InitializeInputSystem_PF_Timing0( void )
{
	static int NowInitialize = FALSE ;
//	int i, j ;

	// 既に初期化処理が開始されている場合も何もせずに終了
	if( NowInitialize )
	{
		return 0 ;
	}

	// 初期化中フラグを立てる
	NowInitialize = TRUE ;


	// ジョイパッドの数を増やす
	InputSysData.PadNum = 1 ;

	// 初期化中フラグを倒す
	NowInitialize = FALSE ;

	// 正常終了
	return 0 ;
}

// 入力システムの後始末をする処理の環境依存処理
extern int TerminateInputSystem_PF_Timing0( void )
{
	// 正常終了
	return 0 ;
}

// 自動初期化を行う環境依存処理
extern int AutoInitialize_PF( void )
{
	return 0 ;
}

// ジョイパッドのセットアップの環境依存処理
extern int SetupJoypad_PF( void )
{
	// 正常終了
	return 0 ;
}

// ジョイパッドの後始末を行う処理の環境依存処理
extern int TerminateJoypad_PF( void )
{
	// 正常終了
	return 0 ;
}

// 入力状態の更新の環境依存処理
extern int UpdateKeyboardInputState_PF( int UseProcessMessage )
{
	_MEMSET( &InputSysData.KeyInputBuf, 0, sizeof( InputSysData.KeyInputBuf ) ) ;
//	if( InputSysData.PF.SourceNum[ LINUX_INPUT_SOURCE_KEYBOARD ] > 0 )
//	{
//		int i, j ;
//
//		for( j = 0 ; j < InputSysData.PF.SourceNum[ LINUX_INPUT_SOURCE_KEYBOARD ] ; j ++ )
//		{
//			INPUT_LINUX_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ LINUX_INPUT_SOURCE_KEYBOARD ][ j ] ] ;
//
//			for( i = 0 ; g_LinuxKeyToDXInputKey[i][0] != 0xffff ; i ++ )
//			{
//				InputSysData.KeyInputBuf[ g_LinuxKeyToDXInputKey[ i ][ 1 ] ] |= Info->KeyState[ g_LinuxKeyToDXInputKey[ i ][ 0 ] ] ? 0x80 : 0x00 ;
//			}
//		}
//	}

	return 0 ;
}

// パッドの入力状態の更新の環境依存処理
extern int UpdateJoypadInputState_PF( int PadNo )
{

	// 終了
	return 0 ;
}

// パッドエフェクトの再生状態を更新する関数の環境依存処理
extern int RefreshEffectPlayState_PF( void )
{
	// 終了
	return 0 ;
}

// 指定のパッドが振動に対応しているかどうかを取得する( TRUE:対応している  FALSE:対応していない )
extern int CheckJoypadVibrationEnable_PF( INPUTPADDATA *pad, int EffectIndex )
{
	return FALSE ;
}

// 指定の入力デバイスが XInput に対応しているかどうかを取得する処理の環境依存処理( 戻り値  TRUE:XInput対応の入力デバイス  FALSE:XInput非対応の入力デバイス   -1:エラー )( DX_INPUT_KEY や DX_INPUT_KEY_PAD1 など、キーボードが絡むタイプを InputType に渡すとエラーとなり -1 を返す )の環境依存処理
extern int CheckJoypadXInput_PF( int InputType )
{
	return FALSE ;
}

// マウスのボタンの状態を得る処理の環境依存処理
extern int GetMouseInput_PF( void )
{
	int res = 0 ;

	return res ;
}

// 垂直マウスホイールの回転量を取得する
extern int GetMouseWheelRotVol_PF( int CounterReset )
{
	int Vol ;

	Vol = InputSysData.MouseMoveZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveZ -= Vol ;
	}

	return Vol ;
}

// 水平マウスホイールの回転量を取得する
extern int GetMouseHWheelRotVol_PF( int CounterReset )
{
	int Vol ;

	Vol = InputSysData.MouseMoveHZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveHZ -= Vol ;
	}

	return Vol ;
}

// 垂直マウスホイールの回転量を取得する( 戻り値が float 型 )
extern float GetMouseWheelRotVolF_PF( int CounterReset )
{
	float Vol ;

	Vol = ( float )InputSysData.MouseMoveZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveZ = 0 ;
	}

	return Vol ;
}

// 水平マウスホイールの回転量を取得する( 戻り値が float 型 )
extern float GetMouseHWheelRotVolF_PF( int CounterReset )
{
	float Vol ;

	Vol = ( float )InputSysData.MouseMoveHZ ;
	if( CounterReset )
	{
		InputSysData.MouseMoveHZ = 0 ;
	}

	return Vol ;
}

// マウスの位置を取得する
extern int GetMousePoint_PF( int *XBuf, int *YBuf )
{
	if( XBuf != NULL )
	{
		*XBuf = 0 ;
	}

	if( YBuf != NULL )
	{
		*YBuf = 0 ;
	}

//	if( InputSysData.PF.SourceNum[ LINUX_INPUT_SOURCE_MOUSE ] > 0 )
//	{
//		int ScreenX, ScreenY ;
//		INPUT_LINUX_DEVICE_INFO *Info = &InputSysData.PF.InputInfo[ InputSysData.PF.SourceNoToInputInfoTable[ LINUX_INPUT_SOURCE_MOUSE ][ 0 ] ] ;
//
//		ScreenX = ( int )Info->AxisX ;
//		ScreenY = ( int )Info->AxisY ;
//		ConvScreenPositionToDxScreenPosition( ScreenX, ScreenY, XBuf, YBuf ) ;
//	}

	return 0 ;
}

// マウスの位置をセットする
extern int SetMousePoint_PF( int PointX , int PointY )
{
	return 0 ;
}

// ジョイパッドの無効ゾーンの設定を行う関数の環境依存処理
extern int SetJoypadDeadZone_PF( INPUTPADDATA *pad )
{
	// 正常終了
	return 0 ;
}

// デバイスＩＤから値を代入すべき入力情報番号を取得する
extern int GetLinuxDeviceIdToInputInfoNo( int32_t Source, int32_t DeviceId )
{
	return 0 ;
}


// ゲームパッドの番号と入力情報との対応テーブルを更新する
extern int RefreshLinuxGamePadSourceNoToInputInfoTable( void )
{
	// 終了
	return 0 ;
}



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_INPUT


