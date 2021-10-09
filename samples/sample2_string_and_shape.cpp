#include "DxLib.h"

int main(){
    //ChangeWindowMode(1);
    if(DxLib_Init() == -1){
        return -1;
    }
    DrawFormatString(0, 0, 0xabcdef, "abcあいうdef012");
    DrawLine(20, 100, 100, 20, 0xabcdef);
    DrawCircle(50, 50, 30, 0xabcdef, 0);
    WaitKey();
    DxLib_End();
    return 0;
}
