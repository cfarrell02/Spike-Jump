//
//  level.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#include "level.hpp"
#include <map>
#include <iostream>

Level::Level(vector<vector<Block>> blocks)
{
    m_Map = new vector<vector<Block>>(blocks);

}

vector<vector<Block>>* Level::getBlocks(){
    return m_Map;
}
