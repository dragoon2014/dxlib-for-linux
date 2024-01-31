#include "DxLib.h"

// for debugging
#ifdef __linux__
#include "Linux/DxGraphicsLinux.h"
#endif

void clearLog(){
    clsDx();
    printfDx("\
keys:\n\
  C: clear\n\
  1: SetClipboardText(\"Hello world!\")\n\
  2: SetClipboardText(\"あいうえお\")  // aiueo of hiragana\n\
  3: SetClipboardTextWithStrLen(\"Hello world!\", 5)\n\
  4: SetClipboardText(\"\")  // blank\n\
  5: GetClipboardText(NULL)\n\
  6: DxRealloc(str, len)\n\
  7: GetClipboardText(str, len)\n\
  8: [str(s)]\n\
  9: str(02x)\n\
");
}

int main(){
#ifdef WINDOWS_DESKTOP_OS
    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
    SetWindowSizeChangeEnableFlag(1, 0);
    ChangeWindowMode(1);
    SetAlwaysRunFlag(1);
    SetWindowMaximizeButtonBehavior(1);
#endif
    SetGraphMode(800, 600, 32);
    if(DxLib_Init() == -1){
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    auto c = GetColor(0xab, 0xcd, 0xef);
    int currKey, prevKey;
    clearLog();
    int len = 1;
    char* str = (char*)DxAlloc(len);
    while(ProcessMessage() != -1){
        ClearDrawScreen();

        currKey = CheckHitKeyAll();
        switch(currKey & (~prevKey)){
        case KEY_INPUT_C: clearLog(); break;
        case KEY_INPUT_1: printfDx("1: %d\n", SetClipboardText("Hello world!")); break;
        case KEY_INPUT_2: printfDx("2: %d\n", SetClipboardText("あいうえお")); break;
        case KEY_INPUT_3: printfDx("3: %d\n", SetClipboardTextWithStrLen("Hello world!", 5)); break;
        case KEY_INPUT_4: printfDx("4: %d\n", SetClipboardText("")); break;
        case KEY_INPUT_5: printfDx("5: %d\n", len = GetClipboardText(NULL, 0)); break;
        case KEY_INPUT_6: printfDx("6: %p\n", str = (char*)DxRealloc(str, len)); break;
        case KEY_INPUT_7: printfDx("7: %d\n", GetClipboardText(str, len)); break;
        case KEY_INPUT_8: printfDx("8: [%s]\n", str); break;
        case KEY_INPUT_9: printfDx("9: "); for(int i=0; i<len; i++){ printfDx("%02x ", (unsigned char)str[i]); } printfDx("\n", str); break;
        default: break;
        }
        prevKey = currKey;
        {
            // for debugging
            int l=0;
            #ifdef __linux__
            DrawFormatString(400, 20*l++, 0xabcdef, "ptr:%p", GLINUX.Device.Screen._clipboard_bufPtr);
            DrawFormatString(400, 20*l++, 0xabcdef, "len:%d", GLINUX.Device.Screen._clipboard_bufLen);
            DrawFormatString(400, 20*l++, 0xabcdef, "get ptr:%p", GLINUX.Device.Screen._clipboard_get_bufPtr);
            DrawFormatString(400, 20*l++, 0xabcdef, "get len:%d", GLINUX.Device.Screen._clipboard_get_bufLen);
            #endif
        }
        ScreenFlip();
    }
    DxLib_End();
    return 0;
}
