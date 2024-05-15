//
//  Item.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 26/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp
#pragma once
#include <stdio.h>
#include "ObjCreator.hpp"
class Item:public ObjCreator{
public:
    bool colected;
    int point;
    char value;
    Item(sf::Texture& tekstura,int const& id);
    Item(sf::Texture& tekstura,int const& id,int const & point,char const & value);
    void draw(sf::RenderWindow& window,bool const& debug);
};
#endif /* Item_hpp */
