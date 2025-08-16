#pragma once

enum class GameState : uint8_t {

    SplashScreen_Start,
        SplashScreen_00 = SplashScreen_Start,
        SplashScreen_01,
        SplashScreen_02,
        SplashScreen_03,
    SplashScreen_End,

    Title_Init,
    Title_Start,
        Title_Main = Title_Start,
        Title_Select,
    Title_End,

    Play_Init,
    Play_Start,
        Play = Play_Start,
        Play_Menu_Undo,
        Play_Menu_ResetLevel,
        Play_Menu_MainMenu,
    Play_End = Play_Menu_MainMenu,
    
};

inline GameState &operator++(GameState &c) {
    c = static_cast<GameState>( static_cast<uint8_t>(c) + 1 );
    return c;
}

inline GameState operator++(GameState &c, int) {
    GameState result = c;
    ++c;
    return result;
}

inline GameState &operator--(GameState &c) {
    c = static_cast<GameState>( static_cast<uint8_t>(c) - 1 );
    return c;
}

inline GameState operator--(GameState &c, int) {
    GameState result = c;
    --c;
    return result;
}

enum BlockType : uint8_t { 
    None,
    Key,
    Block_12,
    Block_13,
    Block_21,
    Block_31,
};
