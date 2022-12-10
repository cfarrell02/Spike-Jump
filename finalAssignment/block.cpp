//
//  block.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#include "block.hpp"

Block::Block(Texture& texture,FloatRect pos, bool isWalkable):
m_IsWalkable(isWalkable), m_Position(pos)
{
    m_Sprite.setTexture(texture);
    //m_Sprite.setOrigin(size.x/2, size.y/2);
    m_Sprite.setPosition(m_Position.left, m_Position.top);
}



FloatRect Block::getPosition(){
    return m_Position;
}

Sprite Block::getSprite(){
    return m_Sprite;
}

//Block& Block::operator=(const Block& b){
//    if (this != &b) {
//        m_Sprite = b.m_Sprite;
//        m_Position = b.m_Position;
//        m_IsWalkable = b.m_IsWalkable;
//        
//    }
//    return *this;
//}
