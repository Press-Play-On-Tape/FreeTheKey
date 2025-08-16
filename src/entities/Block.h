#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "Base.h"

struct Block : public Base {

    private:

        BlockType blockType = BlockType::None;

    public:

        BlockType getBlockType()                        { return this->blockType; }

        void setBlockType(BlockType val)                { this->blockType = val; }

        void reset() {
        
            this->setX(0);
            this->setY(0);
            this->blockType = BlockType::None;
            Base::reset();

        }

};