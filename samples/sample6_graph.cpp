#include "DxLib.h"

int main(){
    //ChangeWindowMode(1);
    if(DxLib_Init() == -1){
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    auto p1 = "assets/bbball.png";
    auto p2 = "assets/bbball_tiled.png";
    const auto g2n = 20;
    auto g1 = LoadGraph(p1);
    int g2s[g2n];
    LoadDivGraph(p2, 20, 5, 4, 100, 100, g2s);
    auto g3 = DerivationGraph(25, 25, 50, 50, g1);
    int t=0;
    while(ProcessMessage() != -1){
        t++;
        ClearDrawScreen();
        DrawBox(50, 50, 600, 150, 0x00ff00, 1);
        DrawGraph(0, 0, g1, 1);
        DrawGraph(100, 0, g1, 0);
        DrawGraph(200, 0, g2s[t%g2n], 1);
        DrawTurnGraph(0, 100, g1, 1);
        DrawExtendGraph(0, 50, 300, 250, g1, 1);
        DrawRotaGraph(300, 150, 1.5, t*0.01, g1, 1, 0);
        DrawRotaGraph2(400, 150, 40, 40, 1.5, t*0.01, g1, 1, 0);
        DrawRotaGraph3(500, 150, 40, 40, 1.4, 0.8, t*0.01, g1, 1, 0);
        DrawModiGraph(350, 0, 450, 0, 350, 100, 250, 100, g1, 1);
        DrawRectGraph(400, 10, 0, 0, 50, 50, g1, 1, 0);
        DrawGraph(475, 25, g3, 1);
        GetDrawScreenGraph(0, 0, 20, 20, g1);
        ScreenFlip();
    }
    DxLib_End();
    return 0;
}
