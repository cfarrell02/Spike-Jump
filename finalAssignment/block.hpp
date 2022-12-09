//
//  block.hpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>

using namespace::sf;
class Block {
private:
    Sprite m_Sprite;
    IntRect m_Position;
    
public:
    const bool m_IsWalkable;
    Block(Texture& texture, IntRect pos, bool isWalkable = true);
    IntRect getPosition();
    Sprite getSprite();
};

#endif /* block_hpp */
