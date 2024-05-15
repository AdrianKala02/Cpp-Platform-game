//
//  Map.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 23/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp
#pragma once
#include <stdio.h>
#include "ObjCreator.hpp"
#include "Blok.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "Hero.hpp"
#include "SpecialBlok.hpp"
#endif /* Map_hpp */
class Map{
public:
    void imgTEST(std::string const&);
    void loadMap2(
                  std::vector<Blok>&,std::vector<Blok>&,
                  std::vector<Item>&,std::vector<Item>&,
                  std::vector<Enemy>&,std::vector<Enemy>&,
                  std::string const&,float const&);
    
    void advancedMapLoader(
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
                           float const& gridSize);
};
