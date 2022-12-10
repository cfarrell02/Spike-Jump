//
//  character.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 09/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//
#include "textureHolder.hpp"
#include "character.hpp"

Character::Character(){
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
    clock.restart();
    m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/Images/Character.png"));
    
    
  //  m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2.f, m_Sprite.getLocalBounds().height / 2.f);
    
}
    
void Character::spawn(Vector2i spawnLocation,  int tileSize, Vector2f resolution){
        m_Position.x = spawnLocation.x;
        m_Position.y = spawnLocation.y;
        
        m_TileSize = tileSize;
        
        m_Resolution.x = resolution.x;
        m_Resolution.y = resolution.y;
    }

void Character::resetCharacterStats(){
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

Time Character::getLastHitTime(){
    return m_LastHit;
}

bool Character::hit(Time timeHit){
    if(timeHit.asMilliseconds() - m_LastHit.asMilliseconds() >200){
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }
    return false;
}

FloatRect Character::getPosition(){
    return m_Sprite.getGlobalBounds();
}

Vector2f Character::getCenter(){
    return m_Position;
}

float Character::getRotation(){
    return m_Sprite.getRotation();
}
Sprite Character::getSprite(){
    return m_Sprite;
}
int Character::getHealth(){
    return m_Health;
}
void Character::moveLeft(){
    m_LeftPressed=true;
}
void Character::moveRight(){
    m_RightPressed=true;
}

void Character::stopLeft(){
    m_LeftPressed = false;
}
void Character::stopRight(){
    m_RightPressed = false;
}

void Character::update(float elapsedTime, Vector2i mousePosition,bool groundContact){
   // std::cout<<clock.getElapsedTime().asSeconds()<<"  -  "<<m_LastJump.asSeconds()<<std::endl;
    float change = m_Speed*elapsedTime;
    float angle = 0;
    if(m_RightPressed){
        m_Position.x += change;
      //  m_Sprite.rotate(ROTATION_SPEED);
    }
    if(m_LeftPressed){
        m_Position.x -= change;
      //  m_Sprite.rotate(-ROTATION_SPEED);
    }
    
    if(!groundContact){
        m_VerticalVelocity += GRAVITY * elapsedTime;
    }else{
        m_VerticalVelocity = 0;
    }
    m_Position.y += m_VerticalVelocity;
    m_Sprite.setPosition(m_Position);

}

void Character::upgradeSpeed(){
    m_Speed += START_SPEED*.2;
}
void Character::upgradeHealth(){
    m_Health += START_HEALTH*.2;
}
void Character::increaseHealthLevel(int amount){
    m_Health += amount;
    
    if(m_Health > m_MaxHealth){
        m_Health = m_MaxHealth;
    }
}


//TODO Fix this method
void Character::jump(float power, sf::Clock& clock, bool isGrounded) {
  // Get the elapsed time since the last jump
    if(!isGrounded) return;

  // Check if the jump cooldown has elapsed
  if (clock.getElapsedTime().asSeconds() >= m_JumpCoolDown) {
    // Jump if the cooldown has elapsed
    m_Position.y -= power;

    // Update the last jump time
    clock.restart();
  }
}
