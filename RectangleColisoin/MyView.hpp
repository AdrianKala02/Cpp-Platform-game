//
//  MyView.hpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 28/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#ifndef MyView_hpp
#define MyView_hpp
#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
class MyView{
public:
    float scrollSpeed;
    sf::View view;
    float zoomFactor = 1.0f;
    
    void moveView(sf::Shape const& hero);
    void zoomView(sf::Event& event,sf::RenderWindow& window);
    
    
    ///construktor
    MyView(sf::RenderWindow&,float const&);
};
#endif /* MyView_hpp */
