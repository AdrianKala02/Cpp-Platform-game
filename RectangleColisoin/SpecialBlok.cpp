//
//  SpecialBlok.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 04/01/2024.
//  Copyright © 2024 Adrian Kala. All rights reserved.
//

#include "SpecialBlok.hpp"



void SpecialBlok::draw(sf::RenderWindow& window,bool const& debug){
    window.draw(sprite);
    if(debug){
    window.draw(shape);
    }
}


SpecialBlok::SpecialBlok(sf::Texture& tekstura,int const& id):ObjCreator(tekstura,id){}
SpecialBlok::SpecialBlok(sf::Texture& tekstura,int const& id, unsigned int const& x,unsigned int const& y):ObjCreator(tekstura,id, x, y){}
