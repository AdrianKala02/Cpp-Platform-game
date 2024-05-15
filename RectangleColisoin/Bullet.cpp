//
//  Bullet.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 02/01/2024.
//  Copyright © 2024 Adrian Kala. All rights reserved.
//

#include "Bullet.hpp"
void Bullet::draw(sf::RenderWindow& window, bool debug){
    window.draw(sprite);
    if(debug){
        window.draw(shape);
    }
}
Bullet::Bullet(sf::Texture& texture,int const& dmg):ObjCreator(texture),damage(dmg),colidet(false){}
