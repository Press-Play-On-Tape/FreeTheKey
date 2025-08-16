#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/utils/SpritesU.hpp"


void title_Init() {

    gameState = GameState::Title_OptPlay;
    titleCounter = 0;
    game.resetFrameCount();

}

void title_Update() {

    game.incFrameCount();

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    switch (gameState) {

        case GameState::Title_OptPlay:

            if ((titleCounter == 24) && (justPressed & A_BUTTON)) {

                a.initRandomSeed(); 
                gameState = GameState::Play_Init;

            }

            if (titleCounter < 24) titleCounter++;

            break;

    }

}

void title(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) title_Update();

    uint8_t currentPlane = a.currentPlane();

    switch (gameState) {

        case GameState::Title_OptPlay:
            {
                SpritesU::drawOverwriteFX(0, 0, Images::FreeTheKey, currentPlane);
            }

            break;

    }            

}
