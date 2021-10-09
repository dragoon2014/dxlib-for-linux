#include "DxLib.h"

int main(){
    //ChangeWindowMode(1);
    if(DxLib_Init() == -1){
        return -1;
    }
    PlaySoundFile("assets/noise.ogg", DX_PLAYTYPE_LOOP);
    WaitKey();
    DxLib_End();
    return 0;
}
