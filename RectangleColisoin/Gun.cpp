//
//  Gun.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 01/01/2024.
//  Copyright © 2024 Adrian Kala. All rights reserved.
//

#include "Gun.hpp"
void Gun::shoot(){
    if(ammoMag>0){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&shootClock.getElapsedTime().asSeconds()>ShootTime){
        ammoMag-=1;
        std::cout<<"Shoot! "<<ammoMag<<"/"<<ammoCap<<"\n";
        

        naboj.shape.setPosition(shape.getPosition());
        naboj.sprite.setPosition(naboj.shape.getPosition());
        naboj.shape.setRotation(katMiedzyBroniaAMyszyka);
        naboj.sprite.setRotation(naboj.shape.getRotation());
        naboj.kat=katMiedzyBroniaAMyszykaRadiany;
        magazine.push_back(naboj);
        shootClock.restart();}}
    
    else if(automatycznePrzeladowanie){
        autoReload();
    }
}
void Gun::reload(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)&&reloadClock.getElapsedTime().asSeconds()>reloadTime){
        std::cout<<"Reload!"<<"\n";
        reloadClock.restart();
        ammoMag=ammoCap;
    }
}
void Gun::autoReload(){
    if(reloadClock.getElapsedTime().asSeconds()>reloadTime){
        std::cout<<"Reload!"<<"\n";
        reloadClock.restart();
        ammoMag=ammoCap;
    }
}
void Gun::setToHeroPos(sf::Shape const& hero){
    shape.setPosition(hero.getPosition().x+hero.getGlobalBounds().width/2,
                      hero.getPosition().y+hero.getGlobalBounds().height/2);
    sprite.setPosition(shape.getPosition());
}
void Gun::setPos(sf::Vector2f const& polozenie){
    shape.setPosition(polozenie);
    sprite.setPosition(shape.getPosition());
}
void Gun::setRot(float const& stopnie){
    shape.setRotation(stopnie);
    sprite.setRotation(shape.getRotation());
}

void Gun::setHeroToMouseRotation(sf::RenderWindow& window,sf::Mouse& mouse,sf::Shape const& hero,MyView const& myview){

    float mousePosX = myview.view.getCenter().x+mouse.getPosition(window).x*myview.zoomFactor-myview.view.getSize().x/2;
    float mousePosY = myview.view.getCenter().y+mouse.getPosition(window).y*myview.zoomFactor-myview.view.getSize().y/2;
    
    float deltaX=mousePosX-shape.getPosition().x;
    float deltaY=mousePosY-shape.getPosition().y;

    
    float angleRadius =  atan2(deltaY, deltaX);
    float angleDegrees =  atan2(deltaY, deltaX) * (180.0 / M_PI);
//    std::cout<<": | "<<deltaX<<" | "<<deltaY<<" | angDeg: "<<angleDegrees<<"\n";
    katMiedzyBroniaAMyszyka=angleDegrees;
    katMiedzyBroniaAMyszykaRadiany=angleRadius;
    shape.setRotation(angleDegrees);
    sprite.setRotation(shape.getRotation());
    
}

void Gun::update(sf::RenderWindow& window,sf::Mouse& mouse,sf::Shape const& hero,MyView const& myview){
    setToHeroPos(hero);
    setHeroToMouseRotation(window,mouse,hero,myview);
    shoot();
    reload();



}

void Gun::draw(sf::RenderWindow& window,bool const& debug){

    for(auto &naboj :magazine){
        naboj.shape.move(speedBullet*cos(naboj.kat),speedBullet*sin(naboj.kat));
        naboj.sprite.setPosition(naboj.shape.getPosition());

    }
    for(auto &naboj :magazine){
        naboj.draw(window, debug);
    }
    window.draw(sprite);
    if(debug){
        window.draw(shape);
    }
}

///CONSTRUCTOR
Gun::Gun(sf::Texture& texture,Bullet& bull,unsigned int const& x,unsigned int const& y,unsigned int const& capacity,float const& timeBWshoots,float const& timeBWreloads, int const& speedBullet,int const& wymaganePunkty,bool const& automatycznePrzeladowanie)
:ObjCreator(texture,x,y),ammoCap(capacity),ammoMag(capacity),ShootTime(timeBWshoots),reloadTime(timeBWreloads),naboj(bull),nazwaBroni("???"),speedBullet(speedBullet),wymaganePunkty(wymaganePunkty),uzywana(false),automatycznePrzeladowanie(automatycznePrzeladowanie){

}
