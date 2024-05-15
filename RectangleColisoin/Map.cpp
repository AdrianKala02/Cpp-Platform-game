//
//  Map.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 23/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "Map.hpp"
void Map::imgTEST(std::string const& url){
    sf::Image img;
    if(!img.loadFromFile(url)){
        std::cout<<"\nbłąd! nie można wczytać pliku\n";
    }
    std::cout<<"RENDER MAPY W TERMINALU\nROZMIAR MAPY: "<<img.getSize().x<<"x"<<img.getSize().y<<"\n"<<"===========================\n";
    for(int i=0;i<img.getSize().y;i++){
        for(int j=0;j<img.getSize().x;j++){
            if(img.getPixel(j, i)==sf::Color::Black) std::cout<<"1 ";
            else if(img.getPixel(j, i)==sf::Color::Red) std::cout<<"2 ";
            else if(img.getPixel(j, i)==sf::Color::Green) std::cout<<"3 ";
            else if(img.getPixel(j, i)==sf::Color::Blue) std::cout<<"4 ";
            else if(img.getPixel(j, i)==sf::Color::Cyan) std::cout<<"5 ";
            else if(img.getPixel(j, i)==sf::Color::Magenta) std::cout<<"6 ";
            else if(img.getPixel(j, i)==sf::Color::Yellow) std::cout<<"7 ";
            else std::cout<<"  ";
        }
        std::cout<<"\n";
    }
}



void Map::advancedMapLoader(
                            std::vector<Blok>& blokiNO1,
                            std::vector<Item>& itemNO1,
                            std::vector<Enemy>& enemyNO1,
                            std::vector<SpecialBlok>& specialneBlokiNO1,
//=======================================================
                            std::vector<Blok>& blokiMapy,
                            std::vector<Item>& itemyMapy,
                            std::vector<Enemy>& enemyMapy,
                            std::vector<SpecialBlok>& specialneBlokiMapy,
//=======================================================
                            Hero& hero,
                            std::string const& url,
                            float const& gridSize){
        sf::Image img;
        if(!img.loadFromFile(url)){std::cout<<"\nbłąd! nie można wczytać pliku\n";}
    
        for(int j=0;j<img.getSize().x;j++){
            for(int i=0;i<img.getSize().y;i++){
                
                if(img.getPixel(j, i)==hero.mapIdColor){
                    hero.shape.setPosition(j*gridSize, i*gridSize);
                }
                for(auto& blok: blokiMapy){
                    if(img.getPixel(j, i)==blok.mapIdColor){
                        blok.shape.setPosition(j*gridSize, i*gridSize);
                        blok.sprite.setPosition(blok.shape.getPosition());
                        blokiNO1.push_back(blok);
                    }
                }
                for(auto& item: itemyMapy){
                    if(img.getPixel(j, i)==item.mapIdColor){
                        item.shape.setPosition(j*gridSize, i*gridSize);
                        item.sprite.setPosition(item.shape.getPosition());
                        itemNO1.push_back(item);
                    }
                }
                for(auto& enemy: enemyMapy){
                    if(img.getPixel(j, i)==enemy.mapIdColor){
                        enemy.shape.setPosition(j*gridSize, i*gridSize);
                        enemy.sprite.setPosition(enemy.shape.getPosition());
                        enemyNO1.push_back(enemy);
                    }
                }
                for(auto& spb: specialneBlokiMapy){
                    if(img.getPixel(j, i)==spb.mapIdColor){
                        spb.shape.setPosition(j*gridSize, i*gridSize);
                        spb.sprite.setPosition(spb.shape.getPosition());
                        specialneBlokiNO1.push_back(spb);
                    }
                }
                }}
}
