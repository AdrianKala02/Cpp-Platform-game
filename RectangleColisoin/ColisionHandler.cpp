//
//  ColisionHandler.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 13/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "ColisionHandler.hpp"
 void ColisionHandler::objToscreen(ObjCreator& hero){
    if(hero.shape.getPosition().x<0){
        hero.shape.setPosition(0, hero.shape.getPosition().y);
    }
    if(hero.shape.getPosition().y<0){
        hero.shape.setPosition(hero.shape.getPosition().x,0);
    }
    if(hero.shape.getPosition().x+hero.shape.getGlobalBounds().width>800){
        hero.shape.setPosition(800-hero.shape.getGlobalBounds().width,hero.shape.getPosition().y);
    }
    if(hero.shape.getPosition().y+hero.shape.getGlobalBounds().height>600){
        hero.shape.setPosition(hero.shape.getPosition().x,600-hero.shape.getGlobalBounds().height);
    }
}
void ColisionHandler::forJump(Hero& hero,ObjCreator const& wall){
    sf::FloatRect playerBounds= hero.shape.getGlobalBounds();
    sf::FloatRect wallBounds= wall.shape.getGlobalBounds();
    //bottom
    if(playerBounds.top<wallBounds.top
       &&playerBounds.top+playerBounds.height<wallBounds.top+wallBounds.height
       && playerBounds.left<wallBounds.left+wallBounds.width
       &&playerBounds.left+playerBounds.width>wallBounds.left){
        hero.canJump=true;
    }
}
//https://www.youtube.com/watch?v=A04MPkBL5H4
void ColisionHandler::objToboj(Hero& hero, ObjCreator const& wall){
    sf::FloatRect playerBounds= hero.shape.getGlobalBounds();
    sf::FloatRect wallBounds= wall.shape.getGlobalBounds();
    //bottom
    if(playerBounds.top<wallBounds.top
       &&playerBounds.top+playerBounds.height<wallBounds.top+wallBounds.height
       && playerBounds.left<wallBounds.left+wallBounds.width
       &&playerBounds.left+playerBounds.width>wallBounds.left){
        hero.velocity.y=0.f;
        hero.shape.setPosition(playerBounds.left,wallBounds.top-playerBounds.height);
    }
else if(playerBounds.top>wallBounds.top
       &&playerBounds.top+playerBounds.height>wallBounds.top+wallBounds.height
       && playerBounds.left<wallBounds.left+wallBounds.width
       &&playerBounds.left+playerBounds.width>wallBounds.left){
        hero.velocity.y=0.f;
        hero.shape.setPosition(playerBounds.left,wallBounds.top+wallBounds.height);
}
    if(playerBounds.left<wallBounds.left
       &&playerBounds.left+playerBounds.width<wallBounds.left+wallBounds.width
       && playerBounds.top<wallBounds.top+wallBounds.height
       &&playerBounds.top+playerBounds.height>wallBounds.top){
        hero.velocity.x=0.f;
        hero.shape.setPosition(wallBounds.left-playerBounds.width, playerBounds.top);
    }
    //left
   else if(playerBounds.left>wallBounds.left
       &&playerBounds.left+playerBounds.width>wallBounds.left+wallBounds.width
       && playerBounds.top<wallBounds.top+wallBounds.height
       &&playerBounds.top+playerBounds.height>wallBounds.top){
        hero.velocity.x=0.f;
       hero.shape.setPosition(wallBounds.left+wallBounds.width, playerBounds.top);
    }
}
///!!!!!
void ColisionHandler::enemyToObj(Enemy& hero, ObjCreator const& wall){
    sf::FloatRect playerBounds= hero.shape.getGlobalBounds();
    sf::FloatRect wallBounds= wall.shape.getGlobalBounds();
    //bottom
    if(playerBounds.top<wallBounds.top
       &&playerBounds.top+playerBounds.height<wallBounds.top+wallBounds.height
       && playerBounds.left<wallBounds.left+wallBounds.width
       &&playerBounds.left+playerBounds.width>wallBounds.left){
        hero.velocity.y=0.f;
        hero.shape.setPosition(playerBounds.left,wallBounds.top-playerBounds.height);
    }
else if(playerBounds.top>wallBounds.top
       &&playerBounds.top+playerBounds.height>wallBounds.top+wallBounds.height
       && playerBounds.left<wallBounds.left+wallBounds.width
       &&playerBounds.left+playerBounds.width>wallBounds.left){
    hero.velocity.y=0.f;
        hero.shape.setPosition(playerBounds.left,wallBounds.top+wallBounds.height);
}
    //right
    if(playerBounds.left<wallBounds.left
       &&playerBounds.left+playerBounds.width<wallBounds.left+wallBounds.width
       && playerBounds.top<wallBounds.top+wallBounds.height
       &&playerBounds.top+playerBounds.height>wallBounds.top){
        hero.velocity.x=0.f;
        hero.shape.setPosition(wallBounds.left-playerBounds.width, playerBounds.top);
        hero.moveDirection=-hero.moveDirection;

    }
    //left
   else if(playerBounds.left>wallBounds.left
       &&playerBounds.left+playerBounds.width>wallBounds.left+wallBounds.width
       && playerBounds.top<wallBounds.top+wallBounds.height
       &&playerBounds.top+playerBounds.height>wallBounds.top){
       hero.velocity.x=0.f;
       hero.shape.setPosition(wallBounds.left+wallBounds.width, playerBounds.top);
       hero.moveDirection=-hero.moveDirection;

    }
}
void ColisionHandler::forJumpEnemy(Enemy& hero,ObjCreator const& wall){
    sf::FloatRect playerBounds= hero.shape.getGlobalBounds();
    sf::FloatRect wallBounds= wall.shape.getGlobalBounds();
    //bottom
    if(playerBounds.top<wallBounds.top
       &&playerBounds.top+playerBounds.height<wallBounds.top+wallBounds.height
       && playerBounds.left<wallBounds.left+wallBounds.width
       &&playerBounds.left+playerBounds.width>wallBounds.left){
        hero.canJump=true;
    }
}
