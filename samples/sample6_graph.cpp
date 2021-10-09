#include "DxLib.h"

int main(){
    //ChangeWindowMode(1);
    if(DxLib_Init() == -1){
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    int gr = LoadGraph("assets/bbball.png");
    while(ProcessMessage() != -1){
        ClearDrawScreen();
        DrawBox(50, 50, 150, 150, 0x00ff00, 1);
        DrawGraph(0, 0, gr, 1);
        ScreenFlip();
    }
    DxLib_End();
    return 0;
}
