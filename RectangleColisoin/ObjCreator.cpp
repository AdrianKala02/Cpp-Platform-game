//
//  ObjCreator.cpp
//  TechnoMagic
//
//  Created by Adrian Kala on 07/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "ObjCreator.hpp"
void ObjCreator::draw(sf::RenderWindow& window){
    
    ///ważne, shape zużywa diametralnie więcej zasobów niż sprite
    window.draw(sprite);
    ///usunąć
//    window.draw(shape);
};
ObjCreator::ObjCreator(sf::Texture& tekstura):id(0){
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(-1);

    spritesSheetPos=sf::IntRect(0,0,32,32);
    sprite.setTexture(tekstura);
    shape.setSize(sf::Vector2f(32,32));
    sprite.setTextureRect(spritesSheetPos);
}
ObjCreator::ObjCreator(sf::Texture& tekstura,int const& id):id(id){
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(-1);

    spritesSheetPos=sf::IntRect(0,0,32,32);
    sprite.setTexture(tekstura);
    shape.setSize(sf::Vector2f(32,32));
    sprite.setTextureRect(spritesSheetPos);
}

ObjCreator::ObjCreator(sf::Texture& tekstura,unsigned int const& x,unsigned int const& y):id(0){
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(-1);
    sprite.setTexture(tekstura);
    shape.setSize(sf::Vector2f(x,y));
}
//dla broni bo nie mają stałej wielkości
ObjCreator::ObjCreator(sf::Texture& tekstura,int const& id,unsigned int const& x,unsigned int const& y):id(id){
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(-1);
    sprite.setTexture(tekstura);
    shape.setSize(sf::Vector2f(x,y));
    spritesSheetPos=sf::IntRect(0,0,x,y);
    sprite.setTextureRect(spritesSheetPos);

}

