#pragma once
#include "../../fxdata/fxdata.h"
#include "../../fxdata/images/Images.h"

#define _DEBUG_PRINT    Serial.print
#define _DEBUG_PRINTLN  Serial.println
#define DEBUG_BREAK    asm volatile("break\n");

#define _DEBUG
#define _DEBUG_RAND


namespace Constants {

    constexpr uint8_t levelSelect_Offset[] = { 0, 2, 6, 21, 36, 42, 54, 55};

    constexpr uint8_t Level_Count = 40;
    constexpr uint8_t Block_Count = 25;
    constexpr uint8_t Undo_Count = 30;
    constexpr uint8_t NoBlock = Block_Count - 1;

    constexpr uint8_t Grid_Size = 10;
    constexpr uint8_t Grid_Left = 6;
    constexpr uint8_t Grid_Top = 1;

};
