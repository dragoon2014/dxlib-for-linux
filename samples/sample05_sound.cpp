#include "DxLib.h"

int main(){
#ifdef WINDOWS_DESKTOP_OS
    ChangeWindowMode(1);
#endif
    if(DxLib_Init() == -1){
        return -1;
    }
    DrawString(0, 0, "Playing sound...", 0xffffff);
    PlaySoundFile("assets/noise.ogg", DX_PLAYTYPE_LOOP);
    WaitKey();
    DxLib_End();
    return 0;
}
