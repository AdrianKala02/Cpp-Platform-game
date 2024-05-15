//
//  Bullet.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 02/01/2024.
//  Copyright © 2024 Adrian Kala. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp
#pragma once
#include <stdio.h>
#include "ObjCreator.hpp"
class Bullet: public ObjCreator{
public:
    bool colidet;
    int damage;
    float lifeSpan;
    float kat;
    void draw(sf::RenderWindow& window, bool debug);
    Bullet(sf::Texture& texture,int const& dmg);
};
#endif /* Bullet_hpp */
