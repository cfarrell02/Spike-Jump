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
    FloatRect m_Position;
    
public:
    const bool m_IsWalkable, m_LevelExit;
    const int m_DamageAmount;
    Block(Texture& texture, FloatRect pos, bool isWalkable = true, bool levelExit = false, int damageAmount = 0);
    FloatRect getPosition();
    Sprite getSprite();
    Block& operator=(const Block& b);
};

//class Hazard : public Block {
//private:
//    int damageAmount;
//public:
//    Hazard(Texture& texture, FloatRect pos, int damageAmount, bool isWalkable = true);
//    
//    
//};
#endif /* block_hpp */
