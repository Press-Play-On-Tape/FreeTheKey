#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/utils/SpritesU.hpp"


uint8_t selectedPuzzle = 0;
uint8_t selectedPuzzleX = 0;
uint8_t selectedPuzzleY = 0;

void title_Init() {

    gameState = GameState::Title_Main;
    titleCounter = 0;
    game.resetFrameCount();

}

void title_Update() {

    game.incFrameCount();

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    selectedPuzzle = (selectedPuzzleY * 5) + selectedPuzzleX;

    switch (gameState) {

        case GameState::Title_Main:

            if ((titleCounter == 24) && (justPressed & A_BUTTON)) {

                a.initRandomSeed(); 
                gameState = GameState::Title_Select;

            }

            if (titleCounter < 24) titleCounter++;

            break;

        case GameState::Title_Select:

            if (justPressed & A_BUTTON) {
                game.setLevel(selectedPuzzle);
                gameState = GameState::Play_Init;
            }

            if (justPressed & LEFT_BUTTON && selectedPuzzleX > 0) {

                selectedPuzzleX--;

            }

            if (justPressed & RIGHT_BUTTON && selectedPuzzleX < 4 && game.getPuzzle(selectedPuzzle + 1).getStatus() != PuzzleStatus::Locked) {

                selectedPuzzleX++;

            }

            if (justPressed & DOWN_BUTTON && selectedPuzzleY < 7 && game.getPuzzle(selectedPuzzle + 5).getStatus() != PuzzleStatus::Locked) {

                selectedPuzzleY++;

            }

            if (justPressed & UP_BUTTON && selectedPuzzleY > 0) {

                selectedPuzzleY--;

            }

            break;

    }

}

void title(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) title_Update();

    uint8_t currentPlane = a.currentPlane();
    uint8_t yOffset = Constants::levelSelect_Offset[selectedPuzzleY];

    switch (gameState) {

        case GameState::Title_Main:
            
            SpritesU::drawOverwriteFX(0, 0, Images::FreeTheKey, currentPlane);
            break;

        case GameState::Title_Select:

            for (uint8_t y = 0; y < 8; y++) {

                for (uint8_t x = 0; x < 5; x++) {

                    Puzzle &puzzle = game.getPuzzle((y * 5) + x);

                    if (puzzle.getStatus() == PuzzleStatus::Complete) {

                        SpritesU::drawOverwriteFX(x * 15, (y * 15) - yOffset, Images::Levels, ((((y * 5) + x) + 1) * 3) + currentPlane);

                    }
                    else if (puzzle.getStatus() == PuzzleStatus::InProgress) {

                        SpritesU::drawOverwriteFX(x * 15, (y * 15) - yOffset, Images::Levels, ((((y * 5) + x) + 51) * 3) + currentPlane);

                    }                        
                    else {

                        SpritesU::drawOverwriteFX(x * 15, (y * 15) - yOffset, Images::Levels, (41 * 3) + currentPlane);

                    }

                    if (((y * 5) + x) == selectedPuzzle) {

                        if (game.getFrameCount(48)) {
                            SpritesU::drawPlusMaskFX(x * 15, (y * 15) - yOffset, Images::Levels_Cursor, currentPlane);
                        }

                    }

                }
                
            }

            break;

    }            

}
