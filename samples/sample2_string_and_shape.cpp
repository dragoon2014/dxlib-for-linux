#include "DxLib.h"

int main(){
    //ChangeWindowMode(1);
    if(DxLib_Init() == -1){
        return -1;
    }
    auto c = GetColor(0xab, 0xcd, 0xef);
    DrawFormatString(0, 0, c, "abcあいうdef012");
    DrawLine(20, 100, 100, 20, c);
    DrawLineAA(30.0f, 100.0f, 110.0f, 20.0f, c);
    DrawBox(30, 130, 110, 210, c, 1);
    DrawBox(20, 120, 120, 200, c, 0);
    DrawBoxAA(150.4, 130.3, 230.2, 210.1, c, 1);
    DrawBoxAA(140.8, 120.7, 240.6, 200.5, c, 0);
    DrawCircle(50, 50, 30, c, 0);
    DrawCircle(40, 50, 12, c, 1);
    DrawCircleAA(60, 50, 30, 32, c, 0);
    DrawCircleAA(80, 50, 15, 32, c, 1);
    DrawOval(120, 50, 20, 30, c, 0);
    DrawOval(120, 50, 10, 15, c, 1);
    DrawOvalAA(160, 50, 20, 30, 32, c, 0);
    DrawOvalAA(160, 50, 10, 15, 32, c, 1);
    DrawTriangle(320, 100, 240, 220, 380, 210, c, 0);
    DrawTriangle(320, 120, 260, 210, 360, 200, c, 1);
    DrawTriangleAA(420, 100, 340, 220, 480, 210, c, 0);
    DrawTriangleAA(420, 120, 360, 210, 460, 200, c, 1);
    DrawPixel(55, 30, c);
    DrawFormatString(100, 0, c, "%x", GetPixel(10, 50));
    DrawFormatString(200, 0, c, "%x", GetPixel(50, 50));
    DrawFormatString(300, 0, c, "%x", GetPixel(81, 30));
    WaitKey();
    DxLib_End();
    return 0;
}
