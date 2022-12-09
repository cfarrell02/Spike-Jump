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
    Vector2i m_Coords, m_Size;
    
public:
    const bool m_IsWalkable;
    const int Id;
    Block(Texture& texture, Vector2i coords,Vector2i size, bool isWalkable = true);
    Vector2i getCoords() , getSize();
    Sprite getSprite();
};

#endif /* block_hpp */
