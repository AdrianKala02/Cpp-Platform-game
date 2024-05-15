//
//  Hero.hpp
//  MagicKnight
//
//  Created by Adrian Kala on 07/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef Hero_hpp
#define Hero_hpp
#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ObjCreator.hpp"
#include "Gun.hpp"
#include "MyView.hpp"
class Hero:public ObjCreator{
public:
    ///A
    
    
    int points;
    float mass;
    /**/ float movementspeed;
    float maxmovementspeed;
    /**/ sf::Vector2f velocity;
    sf::FloatRect nextPos;
    sf::Clock jumptimer;
    bool canJump;    //info czy postać może skoczyć
    int health;   //ile ma zdrowia postać
    int maxhealth;
    
    int rodzajZawieszenia;
    
    
    
    unsigned int wybor;
    int armor;   //dodatkowy mnożnik przy otrzymaniu obrażeń
    Gun* wybranaBron;  // Zmieniamy na wskaźnik
    std::vector<Gun> bronie;
    ///FUNKCJE

    void chooser(sf::RenderWindow& window, sf::Mouse& mouse, MyView& heroView);

    void wyborBroni(unsigned int const& nrBroni,sf::RenderWindow& window,sf::Mouse& mouse,MyView& heroView);
    void addToEQ(Gun& nowaBron);
    void update(sf::RenderWindow& window,sf::Mouse& mouse,MyView& heroView);  //łączy wszystko co ma być sprawdzane w każdym frame, np move()
    
    
    void tankTracks(float& dt);
    void wheels(float& dt);
    void moveMe(float&); //poruszenie shape z danymi z move2
    
    void draw(sf::RenderWindow& window,bool const& debug);
    ///KONSSTRUKTORY
    Hero(sf::Texture&,int const&, int const&,Gun& gun);
    Hero(sf::Texture&,Gun& gun);
};
#endif /* Hero_hpp */
