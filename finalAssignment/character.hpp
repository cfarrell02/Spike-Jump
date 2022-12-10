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

using namespace sf;

class Character{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    Vector2f m_Position, m_Resolution;
    Sprite m_Sprite;
    Texture m_Texture;
    int m_TileSize, m_Health, m_MaxHealth;
    bool m_LeftPressed, m_RightPressed;
    Clock clock;
    Time m_LastHit;
    float m_JumpCoolDown = .1;
    float m_Speed, m_VerticalVelocity = 0;
    const int GRAVITY = 1, ROTATION_SPEED = 1;
public:
    Character();
    void spawn(Vector2i spawnLocation,  int tileSize, Vector2f resolution);
    void resetCharacterStats();
    bool hit(Time timeHit);
    Time getLastHitTime();
    FloatRect getPosition();
    Vector2f getCenter();
    float getRotation();
    Sprite getSprite();
    int getHealth();
    void moveLeft(), moveRight();
    void stopLeft(), stopRight();
    void jump(float power, Clock& clock, bool isGrounded);
    void update(float elapsedTime, Vector2i mousePosition, bool groundContact);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);
    
};


#endif /* character_hpp */
