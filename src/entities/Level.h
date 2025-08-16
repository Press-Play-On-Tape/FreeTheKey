#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

struct Level {

    private:

        bool complete = false;
        uint16_t numberOfMoves;

    public:

        uint16_t getNumberOfMoves() const               { return this->numberOfMoves; }
        bool isComplete() const                         { return this->complete; }

        void setNumberOfMoves(uint16_t val)             { this->numberOfMoves = val; }
        void setComplete(bool val)                      { this->complete = val; }

};