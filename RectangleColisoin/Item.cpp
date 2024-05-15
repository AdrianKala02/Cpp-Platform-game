//
//  Item.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 26/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "Item.hpp"
Item::Item(sf::Texture& tekstura,int const& id): ObjCreator(tekstura,id),point(1),value('a'),colected(false){
}
Item::Item(sf::Texture& tekstura,int const& id,int const & point,char const & value):ObjCreator(tekstura,id),point(point),value(value),colected(false){}

void Item::draw(sf::RenderWindow& window,bool const& debug){
    window.draw(sprite);
    if(debug){
        window.draw(shape);
    }
}
