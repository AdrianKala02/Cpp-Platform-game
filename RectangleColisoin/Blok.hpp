//
//  Blok.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 26/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef Blok_hpp
#define Blok_hpp
#pragma once
#include <stdio.h>
#include "ObjCreator.hpp"
class Blok: public ObjCreator{
public:
   bool canColide;

    
    
    void draw(sf::RenderWindow& window,bool const& debug);
    Blok(sf::Texture&,int const& id);
    Blok(sf::Texture& tekstura,int const& id,unsigned int const& x,unsigned int const& y);
};
#endif /* Blok_hpp */
