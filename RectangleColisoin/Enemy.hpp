//
//  Enemy.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 30/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp
#pragma once
#include <stdio.h>
#include "ObjCreator.hpp"
#include "InfoBlok.hpp"
#include <sstream>

class Enemy: public ObjCreator{
public:
    int HeroesHealth;
    sf::Vector2f heroPos;
    float jumpPower;
    int ability;
    int numFrames;
    std::string nazwaRodzaju;
    InfoBlok enemyBar;
    sf::Clock timeChargeAttack;
    int timeBetweenAttacks;
    int health;
    int damage;
    int moveDirection;
    /**/ float movementspeed;
    /**/ sf::Vector2f velocity;
    sf::FloatRect nextPos;
    sf::Clock jumptimer;
    bool canJump;    //info czy postać może skoczyć
    void tekstUpdate();
    void smellLowHp(float& dt);
    void movmentLeftRight(float& dt);
    void jumping();
    void smartJumping();
    void following(float& dt);
    void runingOf(float& dt);
    void wardening(float& dt);
    void update();  //łączy wszystko co ma być sprawdzane w każdym frame, np move()
    
    void moveMe(float&); //poruszenie shape z danymi z move2
    
    void draw(sf::RenderWindow& window,bool const& debug,bool const& metaData);
    std::string getAddressString();
    ///CONSTRUKTOR
    Enemy(sf::Texture&,int const &, int const &,int const &);
    
    Enemy(sf::Texture& tekstura,int const& hp, int const& dmg,int const& frames,int  const& mvSpeed,int  const& attacTime,int  const& mvStartDirection,std::string const& nazwaRodz,int const& whatItCan);
    
    Enemy(sf::Texture& tekstura,int const& hp, int const& dmg,int const& frames,int  const& mvSpeed,int  const& attacTime,int  const& mvStartDirection,std::string const& nazwaRodz,int const& whatItCan,unsigned int const& x,unsigned int const& y);
    
};
#endif /* Enemy_hpp */
