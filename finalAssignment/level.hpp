//
//  level.hpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#ifndef level_hpp
#define level_hpp

#include <stdio.h>
#include "block.hpp"
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class Level {
private:
    Vector2i m_levelDimensions;
    map<Vector2i,Block> m_Map;
public:
    Level(map<Vector2i,Block> blocks);
    Block getBlock(Vector2i coords);
    map<Vector2i,Block>* getBlocks();
    bool isValidLocation(Vector2i coords);
};

#endif /* level_hpp */
