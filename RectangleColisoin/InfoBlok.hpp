//
//  InfoBlok.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 26/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef InfoBlok_hpp
#define InfoBlok_hpp
#pragma once
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ObjCreator.hpp"
#include "MyView.hpp"
#endif /* InfoBlok_hpp */


enum class XPos {
    Left,
    Center,
    Right
};

enum class YPos {
    Top,
    Middle,
    Bottom
};

class InfoBlok{
public:
    sf::Text text;
    sf::RectangleShape rectangle;
    float proporiton;
    void draw(sf::RenderWindow&);
    void setSizeAll();
    void setSizeAll(float const& zoomFactor);
    void setPosAuto(sf::View const& view, XPos const& posx,YPos const& posy);
    
    void setPositionManual(sf::Shape const& shape);
    void setPositionManual(sf::Vector2f const& punkt);

    void update(ObjCreator const&);
    void update(MyView const&, XPos const& posx,YPos const& posy);
    void update(ObjCreator const&, XPos const& posx,YPos const& posy);

    //====
    ///Konstruktory
    InfoBlok();
    InfoBlok(sf::Font const&);
    InfoBlok(sf::Font const& font,int const& wielkoscTekstu,float const&skala,float const& originX,float const& originY,sf::Vector2f const& wielkoscPros,sf::Color const& kolor,sf::Color const& kolorRamki,int const& gruposcRamki);
};
