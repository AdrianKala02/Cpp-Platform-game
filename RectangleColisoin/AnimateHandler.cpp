//
//  AnimateHandler.cpp
//  MagicKnight
//
//  Created by Adrian Kala on 07/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "AnimateHandler.hpp"

void AnimateHandler::hand(Hero& hero, sf::Clock& c, float const& tps) {

    if (c.getElapsedTime().asSeconds() < 1.f/tps) {
        return;
    }

    if (hero.spritesSheetPos.left == 96) {
        hero.spritesSheetPos.left = 0;
    } else {
        hero.spritesSheetPos.left += 32;
    }

    c.restart();
    hero.sprite.setTextureRect(hero.spritesSheetPos);
}
void AnimateHandler::handV2(ObjCreator& obj, sf::Clock& c, float const& tps) {

    float czasMiedzyZmianami = 1.0f / tps;

    if (c.getElapsedTime().asSeconds() < czasMiedzyZmianami) {
        return;
    }

        if (obj.spritesSheetPos.left == obj.sprite.getTexture()->getSize().x - obj.sprite.getGlobalBounds().getSize().x) {
            obj.spritesSheetPos.left = 0;
        } else {
            obj.spritesSheetPos.left += obj.sprite.getGlobalBounds().getSize().x;
        }
    obj.sprite.setTextureRect(obj.spritesSheetPos);

    c.restart();
}


//sprawdzone
void AnimateHandler::runAnimation(std::vector<Enemy>& objects, sf::Clock& c, float const& tps) {
    float czasMiedzyZmianami = 1.0f / tps;

    if (c.getElapsedTime().asSeconds() < czasMiedzyZmianami) {
        return;
    }

    for (auto& obj : objects) {
        const float frameWidth = obj.sprite.getTexture()->getSize().x / obj.numFrames;

        if (obj.spritesSheetPos.left + frameWidth >= obj.sprite.getTexture()->getSize().x) {
            obj.spritesSheetPos.left = 0;
        } else {
            obj.spritesSheetPos.left += static_cast<int>(frameWidth);
        }

        obj.sprite.setTextureRect(obj.spritesSheetPos);
    }

    c.restart();
}

void AnimateHandler::runAnimation(std::vector<Item>& objects, sf::Clock& c, float const& tps) {
    float czasMiedzyZmianami = 1.0f / tps;

    if (c.getElapsedTime().asSeconds() < czasMiedzyZmianami) {
        return;
    }

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].spritesSheetPos.left == objects[i].sprite.getTexture()->getSize().x - objects[i].sprite.getGlobalBounds().getSize().x) {
            objects[i].spritesSheetPos.left = 0;
        } else {
            objects[i].spritesSheetPos.left += objects[i].sprite.getGlobalBounds().getSize().x;
        }
        objects[i].sprite.setTextureRect(objects[i].spritesSheetPos);
    }

    c.restart();
}
