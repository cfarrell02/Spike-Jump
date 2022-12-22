//
//  block.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 07/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#include "block.hpp"
#include <cmath>

// Constructor for the Block class
// Initializes the sprite using the specified texture and position, and sets the other member variables based on the input arguments
Block::Block(Texture& texture, FloatRect pos, bool isWalkable, int timeOut, bool levelExit, bool hazard, bool isCoin) :
    m_IsWalkable(isWalkable), m_Position(pos), m_isHazard(hazard), m_LevelExit(levelExit), m_FadeTimeout(timeOut), m_isCoin(isCoin)
{
    // Set the texture of the sprite
    m_Sprite.setTexture(texture);

    // Set the position of the sprite
    m_Sprite.setPosition(m_Position.left, m_Position.top);

    // Restart the hitClock
    hitClock.restart();
}

// Function to start the countdown for a block
void Block::startCountdown()
{
    // If the countdown is already started or the fade timeout is 0 or less, return
    if (!m_CountDown || m_FadeTimeout <= 0)
        return;

    // Restart the hitClock
    hitClock.restart();

    // Set m_CountDown to false
    m_CountDown = false;
}

// Function to remove a block
void Block::remove()
{
    // Set m_IsWalkable to false
    m_IsWalkable = false;

    // Set m_isCoin to false
    m_isCoin = false;

    // Set the sprite to an empty sprite
    m_Sprite = Sprite(TextureHolder::GetTexture(""));
}

// Function to check if a block is a coin
bool Block::isCoin()
{
    return m_isCoin;
}

// Function to update a block
void Block::update()
{
    // If the fade timeout is greater than 0 and the countdown has not started
    if (m_FadeTimeout > 0 && !m_CountDown)
    {
        // Calculate the regen time as twice the fade timeout
        int regenTime = m_FadeTimeout * 2;
        
        // If the elapsed time is less than or equal to the fade timeout
        if (hitClock.getElapsedTime().asSeconds() <= m_FadeTimeout)
        {
            // Set the sprite to the blue block sprite
            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/Images/blueBlock1.png"));
        }
        // If the elapsed time is greater than the fade timeout and less than or equal to the fade timeout plus the regen time
        else if (hitClock.getElapsedTime().asSeconds() >= m_FadeTimeout && hitClock.getElapsedTime().asSeconds() <= m_FadeTimeout + regenTime)
        {
            // Set the sprite to an empty sprite
            m_Sprite = Sprite(TextureHolder::GetTexture(""));
            
            // Set m_IsWalkable to false
            m_IsWalkable = false;
        }
        // If the elapsed time is greater than the fade timeout plus the regen time
        else if (hitClock.getElapsedTime().asSeconds() >= m_FadeTimeout + regenTime)
        {
            // Set m_IsWalkable to true
            m_IsWalkable = true;
            
            // Set m_CountDown to true
            m_CountDown = true;
            
            // Set the sprite to the red block sprite
            m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/Images/redBlock1.png"));
        }
        
        // Set the position of the sprite
        m_Sprite.setPosition(m_Position.left, m_Position.top);
    }
}

// Function to check if a block is walkable
bool Block::isWalkable()
{
    return m_IsWalkable;
}

// Function to get the position of a block
FloatRect Block::getPosition()
{
    return m_Position;
}

// Function to get the sprite of a block
Sprite Block::getSprite()
{
    return m_Sprite;
}



