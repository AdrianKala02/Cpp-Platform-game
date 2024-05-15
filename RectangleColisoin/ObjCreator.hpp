//
//  ObjCreator.hpp
//  TechnoMagic
//
//  Created by Adrian Kala on 07/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef ObjCreator_hpp
#define ObjCreator_hpp
#pragma once
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class ObjCreator{
public:
     int id;
    sf::Color mapIdColor;
    sf::Sprite sprite;
    sf::IntRect spritesSheetPos;
    sf::RectangleShape shape;
    
    void draw(sf::RenderWindow& window);
    
    ObjCreator(sf::Texture& tekstura);
    ObjCreator(sf::Texture& tekstura,int const& id);
    ObjCreator(sf::Texture& tekstura,unsigned int const& x,unsigned int const& y);
    ObjCreator(sf::Texture& tekstura,int const& id,unsigned int const& x,unsigned int const& y);
};
#endif /* ObjCreator_hpp */
