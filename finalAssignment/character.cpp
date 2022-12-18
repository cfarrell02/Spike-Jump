//
//  character.cpp
//  finalAssignment
//
//  Created by Cian Farrell on 09/12/2022.
//  Copyright © 2022 Cian Farrell. All rights reserved.
//
#include "textureHolder.hpp"
#include "character.hpp"

Character::Character(int lives, int speed):
m_Lives(lives), MAX_LIVES(lives),m_Speed(speed){
    clock.restart();
    m_Sprite = Sprite(TextureHolder::GetTexture("../Resources/Images/Character.png"));
    m_Coins = 0;
    
    
  //  m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2.f, m_Sprite.getLocalBounds().height / 2.f);
    
}
    
void Character::spawn(Vector2i spawnLocation,  int tileSize){
    m_Position.x = spawnLocation.x;
    m_Position.y = spawnLocation.y;
    
    m_TileSize = tileSize;
        
//        m_Resolution.x = resolution.x;
//        m_Resolution.y = resolution.y;
    }

void Character::resetLives(){
    m_Lives = MAX_LIVES;
}
void Character::resetScore(){
    m_Coins = 0;
}

void Character::addCoin(){
    m_Coins++;
}

int Character::getCoinCount(){
    return m_Coins;
}
int Character::getLives(){
    return m_Lives;
}

void Character::removeLife(){
    m_Lives--;
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




void Character::update(float elapsedTime, bool groundContact){
//    std::cout<<clock.getElapsedTime().asSeconds()<<std::endl;
    float change = m_Speed*elapsedTime;
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
    }else if(m_VerticalVelocity>0){
        m_VerticalVelocity = 0;
    }
    m_Position.y += m_VerticalVelocity; 
    m_Sprite.setPosition(m_Position);

}



void Character::jump(float power, bool isGrounded) {
  // Get the elapsed time since the last jump
  if(!isGrounded) return;

  // Check if the jump cooldown has elapsed
  if (clock.getElapsedTime().asSeconds() >= m_JumpCoolDown) {

    // Jump if the cooldown has elapsed
    m_VerticalVelocity = -power;
 //   m_Position.y += m_VerticalVelocity;

    // Update the last jump time
    clock.restart();
  }
}
