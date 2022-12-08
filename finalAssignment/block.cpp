//
//  block.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#include "block.hpp"

Block::Block(Texture& texture,Vector2i coords,Vector2i size, bool isWalkable):
m_IsWalkable(isWalkable), m_Coords(coords), m_Size(size)
{
    m_Sprite.setTexture(texture);
    //m_Sprite.setOrigin(size.x/2, size.y/2);
    m_Sprite.setPosition(m_Coords.x, m_Coords.y);
}

Vector2i Block::getCoords(){
    return m_Coords;
}

Vector2i Block::getSize(){
    return m_Size;
}

Sprite Block::getSprite(){
    return m_Sprite;
}
