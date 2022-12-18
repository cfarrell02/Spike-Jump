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
#include "textureHolder.hpp"

using namespace::sf;
class Block {
private:
    Sprite m_Sprite;
    FloatRect m_Position;
//    Vector2f m_StartPos,m_EndPos;
    bool m_IsWalkable, m_CountDown = true,  m_isCoin;
    Clock hitClock;
public:
    const bool m_LevelExit, m_isHazard;
    const int m_FadeTimeout;
//    float m_MoveDirection;
    void remove();
    bool isWalkable(), isCoin();
    Block(Texture& texture, FloatRect pos, bool isWalkable = true ,int timeOut = -1, bool levelExit = false, bool hazard = false, bool isCoin = false);
    FloatRect getPosition();
    Sprite getSprite();
    void update();
    void startCountdown();
    Block& operator=(const Block& b);
};


#endif /* block_hpp */
