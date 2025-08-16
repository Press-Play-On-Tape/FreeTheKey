#include <ArduboyFX.h>  



void renderHUD_Top(uint8_t currentPlane, uint8_t backgroundIdx, bool showTeam0, bool showTeam1) {

    // backgroundIdx = backgroundIdx + (backgroundIdx >= 6 ? gameRound.getFirstPlayer_Idx() * 9 : 0);
    // SpritesU::drawOverwriteFX(105, 0, Images::HUD_Top, backgroundIdx + currentPlane);
    // if (showTeam0)    SpritesU::drawOverwriteFX(118,  8, Images::HUD_Trick_Score, (gameRound.getTeam_TrickCount(1) * 3) + currentPlane);
    // if (showTeam1)    SpritesU::drawOverwriteFX(118, 15, Images::HUD_Trick_Score, (gameRound.getTeam_TrickCount(0) * 3) + currentPlane);

}

