//
//  block.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#include "block.hpp"
#include <cmath>

Block::Block(Texture& texture,FloatRect pos, bool isWalkable,int timeOut , bool levelExit, int damageAmount):
m_IsWalkable(isWalkable), m_Position(pos), m_DamageAmount(damageAmount), m_LevelExit(levelExit), m_FadeTimeout(timeOut)
{
    m_Sprite.setTexture(texture);

    m_Sprite.setPosition(m_Position.left, m_Position.top);
    hitClock.restart();
}

void Block::startCountdown(){
    if(!m_CountDown || m_FadeTimeout <= 0) return;
    hitClock.restart();
    m_CountDown = false;
}

void Block::update(){
    int regenTime = m_FadeTimeout*2;
    if(m_FadeTimeout > 0 && !m_CountDown){
        if(hitClock.getElapsedTime().asSeconds()<=m_FadeTimeout){
            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/Images/blueBlock1.png"));
        }
        else if(hitClock.getElapsedTime().asSeconds()>=m_FadeTimeout && hitClock.getElapsedTime().asSeconds()<=m_FadeTimeout+regenTime){
            m_Sprite = Sprite(TextureHolder::GetTexture(""));
            m_IsWalkable = false;
        }else if(hitClock.getElapsedTime().asSeconds()>=m_FadeTimeout+regenTime){
            m_IsWalkable = true;
            m_CountDown = true;
            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/Images/redBlock1.png"));
        }
        m_Sprite.setPosition(m_Position.left, m_Position.top);
    }
}



bool Block::isWalkable(){
    return m_IsWalkable;
}

FloatRect Block::getPosition(){
    return m_Position;
}

Sprite Block::getSprite(){
        return m_Sprite;
}

