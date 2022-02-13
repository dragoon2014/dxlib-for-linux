#include "DxLib.h"

int main(){
    //ChangeWindowMode(1);
    if(DxLib_Init() == -1){
        return -1;
    }
    printfDx("should not show it");
    clsDx();
    printfDx("abcあいうdef012");
    WaitKey();
    DxLib_End();
    return 0;
}

