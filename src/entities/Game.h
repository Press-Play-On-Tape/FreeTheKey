#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "Player.h"
#include "Block.h"

struct Game {

    private:

        Player player;
        Block blocks[Constants::BlockCount];
        uint16_t frameCount = 0;

    public:

        
        uint16_t getFrameCount()                        { return this->frameCount; }
        uint16_t getFrameCount(uint8_t half)            { return (this->frameCount % half) < (half / 2); }
        Player &getPlayer()                             { return this->player; }
        Block &getBlock(uint8_t idx)                    { return this->blocks[idx]; }

        void setFrameCount(uint16_t val)                { this->frameCount = val; }

        void incFrameCount() {

            this->frameCount++;

        }

        void resetFrameCount() {

            this->frameCount = 0;
            
        }

        void setBlock(uint8_t idx, uint8_t x, uint8_t y, BlockType blockType) {
        
            Block &block = this->blocks[idx];
            block.setX(x);
            block.setY(y);
            block.setBlockType(blockType);
            
        }


        uint8_t getBlock_Idx(uint8_t x, uint8_t y) {
        
            for (uint8_t i = 0; i < Constants::BlockCount; i++) {
            
                Block &block = this->blocks[i];

                switch ( block.getBlockType()) {
                
                    case BlockType::None:
                        continue;

                    case BlockType::Block_12:

                        if (block.getX() == x && (block.getY() == y || block.getY() + 1 == y)) {
                            return i;
                        }
                        
                        break;

                    case BlockType::Block_13:

                        if (block.getX() == x && (block.getY() == y || block.getY() + 1 == y || block.getY() + 2 == y)) {
                            return i;
                        }

                        break;

                    case BlockType::Block_21:
                    case BlockType::Key:

                        if ((block.getX() == x || block.getX() + 1 == x) && block.getY() == y) {
                            return i;
                        }
                        
                        break;                        

                    case BlockType::Block_31:

                        if ((block.getX() == x || block.getX() + 1 == x || block.getX() + 2 == x) && block.getY() == y) {
                            return i;
                        }
                        
                        break;                        
                
                }

            }

            return Constants::NoBlock;

        }

};