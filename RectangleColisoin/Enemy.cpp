//
//  Enemy.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 30/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "Enemy.hpp"



void Enemy::movmentLeftRight(float& dt){
    velocity.x += movementspeed*dt*moveDirection;
}
void Enemy::jumping(){
    if(canJump){
        velocity.y += -movementspeed/jumpPower;
            canJump=false;}
}
void Enemy::smellLowHp(float& dt){
    if(HeroesHealth<30){
        following(dt);
        jumping();
    }
    else{
        runingOf(dt);
        smartJumping();
    }
}
void Enemy::smartJumping(){
//      ^
//      |                   ||
//      |                   ||
//      |                   ||
//      |    H[]            ||
//      |   ##              ||              E[not jump]
//      |                   ||              ######
//      |          E[jump]  ||      H[]
//      ###########################################
    if(heroPos.y<shape.getPosition().y){
        jumping();
    }
}

void Enemy::following(float& dt){
    if(heroPos.x>shape.getPosition().x){
        velocity.x+= movementspeed*dt;
    }else if(heroPos.x<shape.getPosition().x){
        velocity.x-= movementspeed*dt;
    }
}
void Enemy::runingOf(float& dt){
    if(heroPos.x<shape.getPosition().x){
            velocity.x+= movementspeed*dt;
    }
    else if(heroPos.x>shape.getPosition().x){
            velocity.x-= movementspeed*dt;
    }
}
void Enemy::wardening(float& dt){
    //          E[go]->     |     [not go]      |[go]->         H[]
    //----------------------------------------------------------->
                if(heroPos.x>shape.getPosition().x){
                    if(( abs(heroPos.x-shape.getPosition().x)<1000
                       &&abs(heroPos.x-shape.getPosition().x)>600)||
                         abs(heroPos.x-shape.getPosition().x)<300){
                        velocity.x+= movementspeed*dt;
                    }
                }
    //          H[]         <-[go]|    [not go]        |    <-E[go]
    //----------------------------------------------------------->
                else if(heroPos.x<shape.getPosition().x){
                    if(( abs(heroPos.x-shape.getPosition().x)<1000
                       &&abs(heroPos.x-shape.getPosition().x)>600)||
                         abs(heroPos.x-shape.getPosition().x)<300){
                        velocity.x-= movementspeed*dt;
                    }
                }
}
void Enemy::moveMe(float& dt){
    velocity.x=0.f;
    //gravity
    if(velocity.y<10.f){
    velocity.y += movementspeed*dt/20;
    }
    switch (ability) {
 //może poruszać się lewo prawo
        case 1:
            movmentLeftRight(dt);
            break;
//może skakać
        case 2:
            jumping();
            break;
//może case 1 i 2
        case 3:
            movmentLeftRight(dt);
            jumping();
            break;
//próbuje podążać za graczem
        case 4:
            following(dt);
            break;
        case 5:
            following(dt);
            jumping();
        case 6:
            smellLowHp(dt);
        case 7:
            wardening(dt);
        default:
            break;
    }
        

    if(velocity.x>=0){
        spritesSheetPos.top=0;
    }
    else{
        spritesSheetPos.top=shape.getSize().x;
    }
    
    nextPos= shape.getGlobalBounds();
    nextPos.left+=velocity.x;
    nextPos.top+=velocity.y;
}
void Enemy::tekstUpdate(){

    enemyBar.text.setString("ID: "+getAddressString()+"\n"+
                            "Nazwa: "+nazwaRodzaju+"\n"+
                            "Dmg: "+std::to_string(damage)+"\n"+
                            "Hp: "+std::to_string(health));
}
//Adres obiektu enemy
std::string Enemy::getAddressString() {
    std::stringstream ss;
    ss << this;
    return ss.str();
}
void Enemy::update(){
    shape.move(velocity);
    sprite.setPosition(shape.getGlobalBounds().getPosition());
    enemyBar.setPositionManual(shape);
    tekstUpdate();
}

void Enemy::draw(sf::RenderWindow& window,bool const& debug,bool const& metaData){
    window.draw(sprite);
    if(debug){
       window.draw(shape);
    }
    if(metaData){
        window.draw(enemyBar.rectangle);
        window.draw(enemyBar.text);
    }
}

///CONSTRUKTOR
Enemy::Enemy(sf::Texture& tekstura,int const& hp, int const& ar,int const& frames) :ObjCreator(tekstura),health(hp),damage(ar),movementspeed(100),moveDirection(-1),timeBetweenAttacks(2),canJump(true),numFrames(frames),ability(1){
    nazwaRodzaju="???";
    enemyBar.text.setCharacterSize(24);
    enemyBar.text.setScale(0.3, 0.3);
    enemyBar.text.setOrigin(3, -6);
    enemyBar.rectangle.setSize(sf::Vector2f(80,45));
    enemyBar.rectangle.setFillColor(sf::Color(120,0,0,160));
    enemyBar.rectangle.setOutlineColor(sf::Color(160,0,0,255));
    enemyBar.rectangle.setOutlineThickness(-2);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(-1);
}
Enemy::Enemy(sf::Texture& tekstura,int const& hp, int const& dmg,int const& frames,int  const& mvSpeed,int  const& attacTime,int  const& mvStartDirection,std::string const& nazwaRodz,int const& whatItCan) :ObjCreator(tekstura),health(hp),damage(dmg),movementspeed(mvSpeed),moveDirection(mvStartDirection),timeBetweenAttacks(attacTime),canJump(true),numFrames(frames),nazwaRodzaju(nazwaRodz),ability(whatItCan){
    enemyBar.text.setCharacterSize(24);
    enemyBar.text.setScale(0.3, 0.3);
    enemyBar.text.setOrigin(3, -6);
    enemyBar.rectangle.setSize(sf::Vector2f(80,45));
    enemyBar.rectangle.setFillColor(sf::Color(120,0,0,160));
    enemyBar.rectangle.setOutlineColor(sf::Color(160,0,0,255));
    enemyBar.rectangle.setOutlineThickness(-2);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(-1);
}
Enemy::Enemy(sf::Texture& tekstura,int const& hp, int const& dmg,int const& frames,int  const& mvSpeed,int  const& attacTime,int  const& mvStartDirection,std::string const& nazwaRodz,int const& whatItCan,unsigned int const& x,unsigned int const& y) :ObjCreator(tekstura,x,y),health(hp),damage(dmg),movementspeed(mvSpeed),moveDirection(mvStartDirection),timeBetweenAttacks(attacTime),canJump(true),numFrames(frames),nazwaRodzaju(nazwaRodz),ability(whatItCan){
    enemyBar.text.setCharacterSize(24);
    enemyBar.text.setScale(0.3, 0.3);
    enemyBar.text.setOrigin(3, -6);
    enemyBar.rectangle.setSize(sf::Vector2f(80,45));
    enemyBar.rectangle.setFillColor(sf::Color(120,0,0,160));
    enemyBar.rectangle.setOutlineColor(sf::Color(160,0,0,255));
    enemyBar.rectangle.setOutlineThickness(-2);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(-1);
}
