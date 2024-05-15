//
//  Gun.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 01/01/2024.
//  Copyright © 2024 Adrian Kala. All rights reserved.
//

#ifndef Gun_hpp
#define Gun_hpp
#pragma once
#include <stdio.h>
#include "ObjCreator.hpp"
#include "MyView.hpp"
#include "Bullet.hpp"
#include <cmath>
#include <algorithm>
#include <math.h>
class Gun :public ObjCreator{
public:
    int wymaganePunkty;
    sf::Clock shootClock;
    float ShootTime;
    sf::Clock reloadClock;
    float reloadTime;
    int ammoCap;
    int ammoMag;
    int speedBullet;
    Bullet naboj;
    std::vector<Bullet> magazine;
    
    std::string nazwaBroni;
    float katMiedzyBroniaAMyszyka;
    float katMiedzyBroniaAMyszykaRadiany;
    
    bool uzywana;

    bool automatycznePrzeladowanie;
    void shoot();
    void reload();
    void autoReload();
    
    
    void setToHeroPos(sf::Shape const& hero);
    
    void setPos(sf::Vector2f const& polozenie);
    void setRot(float const& stopnie);
    void setHeroToMouseRotation(sf::RenderWindow& window,sf::Mouse& mouse,sf::Shape const& hero,MyView const& myview);
    
    void update(sf::RenderWindow& window,sf::Mouse& mouse,sf::Shape const& hero,MyView const& myview);
    
    void draw(sf::RenderWindow& window,bool const& debug);
    ///CONSTRUCTOR
    Gun(sf::Texture& texture,Bullet& bull,unsigned int const& x,unsigned int const& y,unsigned int const& capacity,float const& timeBWshoots,float const& timeBWreloads, int const& speedBullet,int const& wymaganePunkty,bool const& automatycznePrzeladowanie);
};
#endif /* Gun_hpp */
