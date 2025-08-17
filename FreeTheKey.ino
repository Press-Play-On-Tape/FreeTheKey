#define ABG_IMPLEMENTATION
#define ABG_TIMER1
#define ABG_SYNC_PARK_ROW
#define SPRITESU_IMPLEMENTATION

#include <ArduboyFX.h>  
#include <FixedPointsCommon.h>
#include "src/utils/ArduboyG.h"
#include "src/utils/Enums.h"
#include "src/utils/Constants.h"
#include "src/utils/Utils.h"
#include "src/entities/Game.h"
#include "src/entities/SoundSettings.h"
#include "src/entities/Cookie.h"
#include "fxdata/fxdata.h"
#include "fxdata/images/Images.h"
#include "src/utils/Random.h"

#define SPRITESU_OVERWRITE
#define SPRITESU_PLUSMASK
#define SPRITESU_RECT
#define SPRITESU_FX

#include "src/utils/SpritesU.hpp"

extern ArduboyGBase_Config<ABG_Mode::L4_Triplane> a;
decltype(a) a;

#include <stdio.h>
#include <stdlib.h>
#include "time.h"

Cookie cookie;
Game &game = cookie.game;
SoundSettings &soundSettings = cookie.soundSettings;

#if not defined(DEBUG) && not defined(DEBUG_BASIC)
GameState gameState = GameState::SplashScreen_Start;
#else
GameState gameState = GameState::Title_Init;
#endif

uint8_t titleCounter = 0;


void setup() {

    a.boot();
    abg_detail::send_cmds_prog<0xDB, 0x20>();
    a.startGray();
    
    FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);
    // FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));

    game.setFrameCount(0);

    // game.getPuzzle(0).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(1).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(2).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(3).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(4).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(5).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(6).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(7).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(8).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(9).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(10).setStatus(PuzzleStatus::Complete);
    // game.getPuzzle(11).setStatus(PuzzleStatus::InProgress);

    game.getPuzzle(0).setStatus(PuzzleStatus::InProgress);

    for (uint8_t i = 0; i < 40; i++) {
    game.getPuzzle(i).setStatus(PuzzleStatus::Complete);
    }

}

void loop() {

    FX::enableOLED();
    a.waitForNextPlane(BLACK);
    FX::disableOLED();

    switch (gameState) {

        #if not defined(DEBUG) && not defined(DEBUG_BASIC)
            case GameState::SplashScreen_Start ... GameState::SplashScreen_End:
                splashScreen(a);
                break;
        #endif

        case GameState::Title_Init:
            title_Init();
            [[fallthrough]];

        case GameState::Title_Start ... GameState::Title_End:
            title(a);
            break;

        case GameState::Play_Init:
            play_Init();
            [[fallthrough]];

        case GameState::Play_Start ... GameState::Play_End:
            play(a);
            break;


    }

}

