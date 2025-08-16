#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

struct Block {

    private:

        uint8_t x = 0;
        uint8_t y = 0;
        BlockType blockType = BlockType::None;

    public:


        uint8_t getX()                                  { return this->x; }
        uint8_t getY()                                  { return this->y; }
        BlockType getBlockType()                        { return this->blockType; }

        void setX(uint8_t val)                          { this->x = val; }
        void setY(uint8_t val)                          { this->y = val; }
        void setBlockType(BlockType val)                { this->blockType = val; }

        void decX()                                     { x--; }
        void incX()                                     { x++; }
        void decY()                                     { y--; }
        void incY()                                     { y++; }

};