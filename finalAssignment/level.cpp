//
//  level.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#include "level.hpp"
#include <iostream>

Level::Level(vector<vector<Block>> blocks)
{
    m_Map = new vector<vector<Block>>(blocks);

}

vector<vector<Block>>* Level::getBlocks(){
    return m_Map;
}

bool Level::isTouchingBlock(FloatRect object)
{
    int width = object.width, height = object.height;
    // Calculate the coordinates of the nearest block to the rectangle
    float x = object.left, y = object.top;
    


    int blockX = std::ceil(x / 64);
    int blockY = std::ceil(y / 64);

    Block* nearestBlock = nullptr;

    // Check if the block is within the bounds of the map
    if (blockX < m_Map->size() && blockY >= 0 && blockY < m_Map->at(blockX).size())
    {
        nearestBlock = &m_Map->at(blockX).at(blockY);

        // Check if the rectangle is intersecting with the block's Position
        if (nearestBlock->getPosition().intersects(object))
        {
            // Check if the block is walkable
            if (nearestBlock->m_IsWalkable)
            {
                // Return true if the block is walkable
                return true;
            }
        }
    }

    // Return false if the block is not within the bounds of the map or if the rectangle is not intersecting with the block
    return false;

}
