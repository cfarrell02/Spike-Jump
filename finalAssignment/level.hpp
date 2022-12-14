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
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

class Level {
private:
    Vector2i m_levelDimensions;
    vector<vector<Block*>> m_Map;
public:
    Level(vector<vector<Block*>> blocks);
    ~Level();
    Block getBlock(Vector2i coords);
    vector<vector<Block*>> getBlocks();
    Block* getIntersectingBlock(FloatRect object);
    Block* getIntersectingBlockBelow(FloatRect object);
    Block* getIntersectingBlockAbove(FloatRect object);
    bool canMoveRight(FloatRect object), canMoveLeft(FloatRect object);
};

#endif /* level_hpp */
