#pragma once
#include "../../fxdata/fxdata.h"
#include "../../fxdata/images/Images.h"

#define _DEBUG_PRINT    Serial.print
#define _DEBUG_PRINTLN  Serial.println
#define _DEBUG_BREAK    asm volatile("break\n");

#define _DEBUG
#define _DEBUG_SKIP_DEAL
#define _DEBUG_BASIC
#define _DEBUG_RAND


// Bidding

#define _DEBUG_EVALUATE
#define _DEBUG_EVALUATE_SUIT
#define _DEBUG_EVALUATE_NOTRUMPS
#define _DEBUG_EVALUATE_MISERE

#define _DEBUG_PREPARE_SUIT_PILES
#define _DEBUG_CALC_MISERE_SCORE
#define _DEBUG_ELEVPART_EVALUATE

#ifdef OPEN_MISERE
#define _DEBUG_EVALUATE_OPEN_MISERE
#endif

//Kitty

#define _DEBUG_HANDLEKITTY_TRUMPS
#define _DEBUG_HANDLEKITTY_MISERE

//Play

#define _DEBUG_PLAYER_WINNING_HAND
#define _DEBUG_PLAYNOTRUMPS_LEAD
#define _DEBUG_PLAYNOTRUMPS_FOLLOW
#define _DEBUG_PLAYSUIT_LEAD;
#define _DEBUG_PLAYSUIT_FOLLOW;
#define _DEBUG_PLAYMISERE_LEAD
#define _DEBUG_PLAYMISERE_FOLLOW
#define _DEBUG_MARKCARDPLAYED
#define _DEBUG_HASCARDBEENPLAYED
#define _DEBUG_GETTOP_INSUIT
#define _DEBUG_SORT
#define _DEBUG_SORT_DETAIL
#define _DEBUG_PLAY_ADDCARD
#define _DEBUG_DISCARDALL_INSUIT
#define _DEBUG_DISCARDCARD
#define _DEBUG_GETBOTTOM_INSUIT
#define _DEBUG_GETNEXTLOWEST_INSUIT
#define _DEBUG_NUMBER_OF_UNPLAYED_CARDS


namespace Constants {

    constexpr uint8_t BlockCount = 12;
    constexpr uint8_t NoBlock = 255;

};
