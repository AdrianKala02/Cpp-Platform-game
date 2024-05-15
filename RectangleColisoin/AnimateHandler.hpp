//
//  AnimateHandler.hpp
//  MagicKnight
//
//  Created by Adrian Kala on 07/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef AnimateHandler_hpp
#define AnimateHandler_hpp
#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ObjCreator.hpp"
#include "Hero.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
class AnimateHandler{
public:
    void hand(Hero&,sf::Clock&, float const&);
    void handV2(ObjCreator& , sf::Clock& , float const&);
    void runAnimation(std::vector<Item>&,sf::Clock&,float const&);
    void runAnimation(std::vector<Enemy>&,sf::Clock&,float const&);

};
#endif /* AnimateHandler_hpp */
