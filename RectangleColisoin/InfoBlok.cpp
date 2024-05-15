//
//  InfoBlok.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 26/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "InfoBlok.hpp"

    
    void InfoBlok::draw(sf::RenderWindow& window){
        window.draw(rectangle);
        window.draw(text);
    }

void InfoBlok::setPositionManual(sf::Shape const& shape){
    rectangle.setPosition(shape.getPosition().x+shape.getGlobalBounds().width,shape.getPosition().y-rectangle.getGlobalBounds().height);
    text.setPosition(rectangle.getPosition()+sf::Vector2f(6,6));
}
void InfoBlok::setPositionManual(sf::Vector2f const& punkt){
    rectangle.setPosition(punkt);
    text.setPosition(rectangle.getPosition());
}

void InfoBlok::setPosAuto(sf::View const& view,  XPos const& posx,YPos const& posy) {
        float xNewPos;
        float yNewPos;

        switch (posx) {
            case XPos::Left:
                xNewPos = view.getCenter().x - view.getSize().x / 2;
                break;
            case XPos::Center:
                xNewPos = view.getCenter().x - rectangle.getGlobalBounds().width / 2;
                break;
            case XPos::Right:
                xNewPos = view.getCenter().x + view.getSize().x / 2 - rectangle.getGlobalBounds().width;
                break;
        }

        switch (posy) {
            case YPos::Top:
                yNewPos = view.getCenter().y - view.getSize().y / 2;
                break;
            case YPos::Middle:
                yNewPos = view.getCenter().y - rectangle.getGlobalBounds().height / 2;
                break;
            case YPos::Bottom:
                yNewPos = view.getCenter().y + view.getSize().y / 2 - rectangle.getGlobalBounds().height;
                break;
        }

        rectangle.setPosition(xNewPos, yNewPos);
    text.setPosition(rectangle.getPosition().x+8*proporiton,rectangle.getPosition().y+16*proporiton);
}

void InfoBlok::setSizeAll(){
    rectangle.setScale(proporiton,proporiton);
    text.setScale(proporiton,proporiton);
};
void InfoBlok::setSizeAll(float const& zoomFactor){
    rectangle.setScale(zoomFactor,zoomFactor);
    text.setScale(zoomFactor,zoomFactor);
};

void InfoBlok::update(ObjCreator const& hero){
        rectangle.setPosition(hero.shape.getPosition().x-rectangle.getGlobalBounds().width,hero.shape.getPosition().y-rectangle.getGlobalBounds().height);
}

void InfoBlok::update(MyView const& Myview, XPos const& posx,YPos const& posy){
    proporiton=Myview.zoomFactor;
    setPosAuto(Myview.view,posx,posy);
    setSizeAll();
}
///CONSTRUKTOR
InfoBlok::InfoBlok(){};
InfoBlok::InfoBlok(sf::Font const& font){
        text.setFont(font);
        text.setCharacterSize(16);
        rectangle.setSize(sf::Vector2f(400,200));
        rectangle.setFillColor(sf::Color(0,0,0,160));
        rectangle.setOutlineColor(sf::Color(0,0,0,255));
        rectangle.setOutlineThickness(-2);
    }

InfoBlok::InfoBlok(sf::Font const& font,int const& wielkoscTekstu,float const&skala,float const& originX,float const& originY,sf::Vector2f const& wielkoscPros,sf::Color const& kolor,sf::Color const& kolorRamki,int const& gruposcRamki){
        text.setFont(font);
        text.setCharacterSize(wielkoscTekstu);
        text.scale(skala, skala);
        text.setOrigin(originX, originY);
        rectangle.setSize(wielkoscPros);
        rectangle.setFillColor(kolor);
        rectangle.setOutlineColor(kolorRamki);
        rectangle.setOutlineThickness(gruposcRamki);
    }
