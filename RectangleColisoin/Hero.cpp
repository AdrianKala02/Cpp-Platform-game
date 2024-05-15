//
//  Hero.cpp
//  MagicKnight
//
//  Created by Adrian Kala on 07/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "Hero.hpp"



void Hero::tankTracks(float& dt){
    velocity.x=0.f;
    //gravity
    if(velocity.y<10.f){
    velocity.y += movementspeed*dt/20;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&canJump){
        velocity.y += -movementspeed/40;
            canJump=false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        velocity.x += -movementspeed*dt;
        spritesSheetPos.top=32;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        velocity.x += movementspeed*dt;
        spritesSheetPos.top=0;
    }
}
void Hero::wheels(float& dt){
    velocity.x=0.f;
    //gravity
    if(velocity.y<10.f){
    velocity.y += movementspeed*dt/35;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&canJump){
        velocity.y += -movementspeed/80;
            canJump=false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        velocity.x += -movementspeed*dt*2;
        spritesSheetPos.top=96;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        velocity.x += movementspeed*dt*2;
        spritesSheetPos.top=64;
    }
}


void Hero::moveMe(float& dt){
    switch (rodzajZawieszenia) {
        case 1:
            tankTracks(dt);
            break;
        case 2:
            wheels(dt);
            break;
        default:
            break;
    }
    nextPos= shape.getGlobalBounds();
    nextPos.left+=velocity.x;
    nextPos.top+=velocity.y;
}
void Hero::wyborBroni(unsigned int const& nrBroni, sf::RenderWindow& window, sf::Mouse& mouse, MyView& heroView) {
    if (nrBroni < bronie.size()) {
        for(auto &d:bronie){
            d.uzywana=false;
        }
        wybranaBron = &bronie[nrBroni];
        wybranaBron->update(window, mouse, shape, heroView);
        wybranaBron->uzywana=true;

    }
}


void Hero::addToEQ(Gun& nowaBron){
    bronie.push_back(nowaBron);
}

void Hero::chooser(sf::RenderWindow& window, sf::Mouse& mouse, MyView& heroView){
    for(int i =0;i<bronie.size();i++){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(27+i))&&points>=bronie[i].wymaganePunkty){
            wybor=i+1;
            
        }
    }
        wyborBroni(wybor-1,window,mouse,heroView);
}


void Hero::update(sf::RenderWindow& window,sf::Mouse& mouse,MyView& heroView){
    shape.move(velocity);
    sprite.setPosition(shape.getGlobalBounds().getPosition());

}



void Hero::draw(sf::RenderWindow& window,bool const& debug){
    window.draw(sprite);
    if(debug){
        window.draw(shape);
    }
}
///CONSTRUKTOR
Hero::Hero(sf::Texture& tekstura,int const& hp, int const& ar,Gun& gun) :ObjCreator(tekstura),health(hp),maxhealth(hp),armor(ar),wybor(1),rodzajZawieszenia(1){}
Hero::Hero(sf::Texture& tekstura,Gun& gun): ObjCreator(tekstura),health(50),maxhealth(health),armor(4),points(0),movementspeed(300.f),maxmovementspeed(movementspeed),canJump(true),wybor(1),rodzajZawieszenia(1){
    shape.setOutlineColor(sf::Color::Black);

}

