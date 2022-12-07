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
    Vector2<int> m_levelDimensions;
    map<Vector2<int>,Block> m_Map;
public:
    Level(map<Vector2<int>,Block> map);
    Block getBlock(Vector2<int> coords);
    bool isValidLocation(Vector2<int> coords);
    
    
};

#endif /* level_hpp */
