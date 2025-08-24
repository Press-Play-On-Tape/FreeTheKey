#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/utils/SpritesU.hpp"



uint8_t getJustPressedButtons() {

    a.pollButtons();

    return a.justPressedButtons();

}


uint8_t getPressedButtons() {

    return a.pressedButtons();

}


uint8_t getJustReleasedButtons(uint8_t button) {

    return a.justReleasedButtons(button);

}

void saveCookie() {

    FX::saveGameState(cookie);

}

void cookieReset() {

    for (uint8_t i = 0; i < 40; i++) {

        if (i == 0) {
            game.getPuzzle(i).setStatus(PuzzleStatus::InProgress);
            game.getPuzzle(i).setNumberOfMoves(0);
        }
        else {
            game.getPuzzle(i).setStatus(PuzzleStatus::Locked);
            game.getPuzzle(i).setNumberOfMoves(0);
        }

    }
    
    levelSelect.x = 0;
    levelSelect.y = 0;

}