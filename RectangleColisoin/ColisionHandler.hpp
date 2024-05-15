//
//  ColisionHandler.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 13/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef ColisionHandler_hpp
#define ColisionHandler_hpp

#include <stdio.h>

#pragma once
#include <SFML/Graphics.hpp>
#include "ObjCreator.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
class ColisionHandler{
public:
    void objToscreen(ObjCreator&);
    
    void objToboj(Hero&, ObjCreator const&);
    void enemyToObj(Enemy&, ObjCreator const&);

    void forJump(Hero&,ObjCreator const&);
    
    void forJumpEnemy(Enemy&,ObjCreator const&);
};
#endif /* ColisionHandler_hpp */
