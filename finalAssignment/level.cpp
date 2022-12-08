//
//  level.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#include "level.hpp"
#include <map>

Level::Level(map<Vector2i,Block> blocks)
{
    map<Vector2i,Block>::iterator iter;
    for(iter = blocks.begin();iter!=blocks.end();++iter){
        m_Map.insert(*iter);
    }
}

map<Vector2i,Block>* Level::getBlocks(){
    return &m_Map;
}
