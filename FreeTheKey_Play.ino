#include <ArduboyFX.h>  

void play_Init() { 

    game.reset();

    game.setBlock(0, 1, 2, BlockType::Key);
    game.setBlock(1, 0, 0, BlockType::Block_21);
    game.setBlock(2, 5, 0, BlockType::Block_13);
    game.setBlock(3, 0, 1, BlockType::Block_13);
    game.setBlock(4, 3, 1, BlockType::Block_13);
    game.setBlock(5, 0, 4, BlockType::Block_12);
    game.setBlock(6, 4, 4, BlockType::Block_21);
    game.setBlock(7, 2, 5, BlockType::Block_31);
    game.setBlock(8, 0, 0, BlockType::None);

    gameState = GameState::Play;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void play_Update() { 

    uint8_t pressed = getPressedButtons();
    uint8_t justPressed = getJustPressedButtons();
    uint8_t selectedBlock_Idx = game.getBlock_Idx(game.getPlayer().getX(), game.getPlayer().getY());

    Block &block = game.getBlock(selectedBlock_Idx);


    game.incFrameCount();


    // Toggle between menu and game ..

    if (justPressed & B_BUTTON) {

        switch (gameState) {

            case GameState::Play:   

                if (game.getUndoCount() == 0) {
                    gameState = GameState::Play_Menu_ResetLevel;
                }
                else {
                    gameState = GameState::Play_Menu_Undo;
                }
                break;

            case GameState::Play_Menu_Undo:
            case GameState::Play_Menu_ResetLevel:
            case GameState::Play_Menu_MainMenu:
                gameState = GameState::Play;
                break;

        }

    }


    if (pressed & A_BUTTON) {

        switch (gameState) {

            case GameState::Play:

                if (block.getBlockType() == BlockType::None) return;
            
                if (justPressed & LEFT_BUTTON) {

                    switch (block.getBlockType()) {

                        case BlockType::Block_12:
                        case BlockType::Block_13:
                            break;

                        case BlockType::Key:
                        case BlockType::Block_21:
                        case BlockType::Block_31:

                            if (block.getX() > 0 && game.getBlock_Idx(block.getX() - 1, block.getY()) == Constants::NoBlock) {

                                game.captureMove();
                                block.decX();
                                game.getPlayer().decX();

                            }
                            break;

                    }

                }
            
                else if (justPressed & RIGHT_BUTTON) {

                    switch (block.getBlockType()) {

                        case BlockType::Block_12:
                        case BlockType::Block_13:
                            break;

                        case BlockType::Key:

                            if (block.getY() == 2 && game.getBlock_Idx(block.getX() + 2, block.getY()) == Constants::NoBlock) {

                                game.captureMove();
                                block.incX();
                                game.getPlayer().incX();

                            }

                            else if (block.getX() < 4 && game.getBlock_Idx(block.getX() + 2, block.getY()) == Constants::NoBlock) {

                                game.captureMove();
                                block.incX();
                                game.getPlayer().incX();

                            }
                            break;

                        case BlockType::Block_21:

                            if (block.getX() < 4 && game.getBlock_Idx(block.getX() + 2, block.getY()) == Constants::NoBlock) {

                                game.captureMove();
                                block.incX();
                                game.getPlayer().incX();

                            }
                            break;

                        case BlockType::Block_31:

                            if (block.getX() < 3 && game.getBlock_Idx(block.getX() + 3, block.getY()) == Constants::NoBlock) {

                                game.captureMove();
                                block.incX();
                                game.getPlayer().incX();

                            }
                            break;

                    }

                }

                else if (justPressed & UP_BUTTON) {

                    switch (block.getBlockType()) {

                        case BlockType::Key:
                        case BlockType::Block_21:
                        case BlockType::Block_31:
                            break;

                        case BlockType::Block_12:
                        case BlockType::Block_13:

                            if (block.getY() > 0 && game.getBlock_Idx(block.getX(), block.getY() - 1) == Constants::NoBlock) {

                                game.captureMove();
                                block.decY();
                                game.getPlayer().decY();

                            }
                            break;

                    }

                }
            
                else if (justPressed & DOWN_BUTTON) {

                    switch (block.getBlockType()) {

                        case BlockType::Key:
                        case BlockType::Block_21:
                        case BlockType::Block_31:
                            break;

                        case BlockType::Block_12:

                            if (block.getY() < 4 && game.getBlock_Idx(block.getX(), block.getY() + 2) == Constants::NoBlock) {

                                game.captureMove();
                                block.incY();
                                game.getPlayer().incY();

                            }
                            break;

                        case BlockType::Block_13:

                            if (block.getY() < 3 && game.getBlock_Idx(block.getX(), block.getY() + 3) == Constants::NoBlock) {

                                game.captureMove();
                                block.incY();
                                game.getPlayer().incY();

                            }
                            break;

                    }

                }

                break;

            default:
                break;

        }

    }
    else if (justPressed & A_BUTTON) {

        switch (gameState) {

            case GameState::Play:
                break;

            case GameState::Play_Menu_Undo:
                game.revertMove();
                if (game.getUndoCount() == 0) {
                    gameState = GameState::Play;
                }
                break;

            case GameState::Play_Menu_ResetLevel:
                gameState = GameState::Play_Init;
                break;

            case GameState::Play_Menu_MainMenu:
                gameState = GameState::Title_Init;
                break;

        }

    }
    else {

        switch (gameState) {

            case GameState::Play:
                    
                if (justPressed & LEFT_BUTTON) {

                    switch (block.getBlockType()) {
                                
                        case BlockType::None:
                        case BlockType::Block_12:
                        case BlockType::Block_13:

                            if (game.getPlayer().getX() > 0) game.getPlayer().decX();
                            break;
                                
                        case BlockType::Key:
                        case BlockType::Block_21:
                        case BlockType::Block_31:

                            if (block.getX() > 0) {
                                game.getPlayer().setX(block.getX() - 1);
                            }
                            else {
                                game.getPlayer().setX(0);
                            }
                            break;

                    }
                    
                }

                else if (justPressed & RIGHT_BUTTON) {

                    switch (block.getBlockType()) {
                                
                        case BlockType::None:
                        case BlockType::Block_12:
                        case BlockType::Block_13:

                            if (game.getPlayer().getX() < 5) game.getPlayer().incX();
                            break;
                                
                        case BlockType::Key:
                        case BlockType::Block_21:

                            if (block.getX() < 4) {
                                game.getPlayer().setX(block.getX() + 2);
                            }
                            else {
                                game.getPlayer().setX(5);
                            }
                            break;
                                
                        case BlockType::Block_31:

                            if (block.getX() < 3) {
                                game.getPlayer().setX(block.getX() + 3);
                            }
                            else {
                                game.getPlayer().setX(5);
                            }
                            break;

                    }
                    
                }

                else if (justPressed & UP_BUTTON) {

                    switch (block.getBlockType()) {
                                
                        case BlockType::None:
                        case BlockType::Key:
                        case BlockType::Block_21:
                        case BlockType::Block_31:

                            if (game.getPlayer().getY() > 0) game.getPlayer().decY();
                            break;
                                
                        case BlockType::Block_12:
                        case BlockType::Block_13:

                            if (block.getY() > 0) {
                                game.getPlayer().setY(block.getY() - 1);
                            }
                            else {
                                game.getPlayer().setY(0);
                            }
                            break;

                    }
                    
                }

                else if (justPressed & DOWN_BUTTON) {

                    switch (block.getBlockType()) {
                                
                        case BlockType::None:
                        case BlockType::Key:
                        case BlockType::Block_21:
                        case BlockType::Block_31:

                            if (game.getPlayer().getY() < 5) game.getPlayer().incY();
                            break;
                                
                        case BlockType::Block_12:

                            if (block.getY() < 4) {
                                game.getPlayer().setY(block.getY() + 2);
                            }
                            else {
                                game.getPlayer().setY(5);
                            }
                            break;
                                
                        case BlockType::Block_13:

                            if (block.getY() < 3) {
                                game.getPlayer().setY(block.getY() + 3);
                            }
                            else {
                                game.getPlayer().setY(5);
                            }
                            break;

                    }
                    
                }

                break;

            case GameState::Play_Menu_Undo:

                if (justPressed & DOWN_BUTTON) {
                    gameState = GameState::Play_Menu_ResetLevel;
                }

                break;

            case GameState::Play_Menu_ResetLevel:

                if (justPressed & UP_BUTTON && game.getUndoCount() > 0) {
                    gameState = GameState::Play_Menu_Undo;
                }
                else if (justPressed & DOWN_BUTTON) {
                    gameState = GameState::Play_Menu_MainMenu;
                }

                break;

            case GameState::Play_Menu_MainMenu:

                if (justPressed & UP_BUTTON) {
                    gameState = GameState::Play_Menu_ResetLevel;
                }

                break;

        }

    }

}


void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t currentPlane = a.currentPlane();
    if (a.needsUpdate()) play_Update();

    SpritesU::drawOverwriteFX(0, 0, Images::Background, currentPlane);

    uint8_t menu_Idx = gameState == GameState::Play_Init ? 0 : static_cast<uint8_t>(gameState) - static_cast<uint8_t>(GameState::Play);
    if (game.getUndoCount() > 0) menu_Idx = menu_Idx + 4;
    SpritesU::drawOverwriteFX(83, 38, Images::Menu, (menu_Idx * 3) + currentPlane);


    // Level ..

    SpritesU::drawOverwriteFX(113, 0, Images::Numbers_5x3_2D_MB, ((game.getLevel() + 1) * 3) + currentPlane);


    // Moves ..

    SpritesU::drawOverwriteFX(109, 8, Images::Numbers_5x3_1D_MB, ((game.getMoveCount() / 100) * 3) + currentPlane);
    SpritesU::drawOverwriteFX(113, 8, Images::Numbers_5x3_2D_MB, ((game.getMoveCount() % 100) * 3) + currentPlane);



    uint8_t selectedBlock = game.getBlock_Idx(game.getPlayer().getX(), game.getPlayer().getY());


    for (uint8_t i = 0; i < Constants::Block_Count; i++) {

        uint8_t idx = (i == selectedBlock ? game.getFrameCount(48) * 3 : 0);

        Block &block = game.getBlock(i);

        switch (block.getBlockType()) {
        
            case BlockType::None:   
                break;

            case BlockType::Key:
                SpritesU::drawPlusMaskFX(Constants::Grid_Left +  (Constants::Grid_Size * block.getX()),  Constants::Grid_Top + (Constants::Grid_Size * block.getY()), Images::Key, idx + currentPlane);
                break;

            case BlockType::Block_21:
                SpritesU::drawPlusMaskFX(Constants::Grid_Left +  (Constants::Grid_Size * block.getX()),  Constants::Grid_Top + (Constants::Grid_Size * block.getY()), Images::Block_21, idx + currentPlane);
                break;

            case BlockType::Block_31:
                SpritesU::drawPlusMaskFX(Constants::Grid_Left +  (Constants::Grid_Size * block.getX()),  Constants::Grid_Top + (Constants::Grid_Size * block.getY()), Images::Block_31, idx + currentPlane);
                break;

            case BlockType::Block_12:
                SpritesU::drawPlusMaskFX(Constants::Grid_Left +  (Constants::Grid_Size * block.getX()),  Constants::Grid_Top + (Constants::Grid_Size * block.getY()), Images::Block_12, idx + currentPlane);
                break;

            case BlockType::Block_13:
                SpritesU::drawPlusMaskFX(Constants::Grid_Left +  (Constants::Grid_Size * block.getX()),  Constants::Grid_Top + (Constants::Grid_Size * block.getY()), Images::Block_13, idx + currentPlane);
                break;
                
        }


        if (selectedBlock == Constants::NoBlock) {

            idx = game.getFrameCount(48) * 3;
            SpritesU::drawPlusMaskFX(Constants::Grid_Left +  (Constants::Grid_Size * game.getPlayer().getX()),  Constants::Grid_Top + (Constants::Grid_Size * game.getPlayer().getY()), Images::Cursor, idx + currentPlane);

        }

    }

}
