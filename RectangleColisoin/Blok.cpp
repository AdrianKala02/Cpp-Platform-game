//
//  Blok.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 26/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "Blok.hpp"


void Blok::draw(sf::RenderWindow& window,bool const& debug){
    window.draw(sprite);
    if(debug){
    window.draw(shape);
    }
}

Blok::Blok(sf::Texture& tekstura,int const& id):ObjCreator(tekstura,id){
}
Blok::Blok(sf::Texture& tekstura,int const& id,unsigned int const& x,unsigned int const& y):ObjCreator(tekstura,id,x,y){
}
