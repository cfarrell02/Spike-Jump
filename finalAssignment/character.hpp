//
//  character.hpp
//  finalAssignment
//
//  Created by Cian Farrell on 09/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//

#ifndef character_hpp
#define character_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "block.hpp"

using namespace sf;

class Character{
private:
    Vector2f m_Position, m_Resolution;
    Sprite m_Sprite;
    Texture m_Texture;
    int m_TileSize, m_Lives, m_Coins;
    bool m_LeftPressed, m_RightPressed;
    Clock clock;
    Time m_LastHit;
    float m_JumpCoolDown = .1;
    float m_Speed, m_VerticalVelocity = 0;
    const int GRAVITY = 15, MAX_LIVES;
public:
    Character(int lives, int speed);
    void spawn(Vector2i spawnLocation,  int tileSize);
    void resetScore();
    void resetLives();
    FloatRect getPosition();
    Vector2f getCenter();
    float getRotation();
    Sprite getSprite();
    void moveLeft(), moveRight();
    void stopLeft(), stopRight();
    void jump(float power, bool isGrounded);
    void update(float elapsedTime, bool groundContact, bool canMoveUp);
    void addCoin();
    void removeLife();
    int getCoinCount(), getLives();
    
};


#endif /* character_hpp */
