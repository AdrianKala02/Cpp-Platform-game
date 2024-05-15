//
//  SpecialBlok.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 04/01/2024.
//  Copyright © 2024 Adrian Kala. All rights reserved.
//

#ifndef SpecialBlok_hpp
#define SpecialBlok_hpp
#pragma once
#include <stdio.h>
#include "ObjCreator.hpp"



class SpecialBlok:public ObjCreator{
public:
    void draw(sf::RenderWindow& window,bool const& debug);
    SpecialBlok(sf::Texture& tekstura,int const& id);
    SpecialBlok(sf::Texture& tekstura,int const& id, unsigned int const& x,unsigned int const& y);
};
#endif /* SpecialBlok_hpp */
