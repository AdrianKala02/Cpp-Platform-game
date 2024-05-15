//
//  MyView.cpp
//  RectangleColisoin
//
//  Created by Adrian Kala on 28/12/2023.
//  Copyright © 2023 Adrian Kala. All rights reserved.
//

#include "MyView.hpp"
MyView::MyView(sf::RenderWindow& window,float const& scrSpeed):scrollSpeed(scrSpeed){
    view.setSize(window.getSize().x, window.getSize().y);
}

void MyView::moveView(sf::Shape const& hero){
sf::Vector2f direction = hero.getGlobalBounds().getPosition() - view.getCenter();
sf::Vector2f offset = direction * scrollSpeed;

// Sprawdzenie czy osiągnięto docelowe położenie
if (std::abs(direction.x) > std::abs(offset.x) || std::abs(direction.y) > std::abs(offset.y)) {
    view.move(offset);
} else {
    view.setCenter(hero.getGlobalBounds().getPosition());
}
}
void MyView::zoomView(sf::Event& event,sf::RenderWindow& window){

         if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            // Zdarzenie przewijania myszy (pinch)
            if (event.mouseWheelScroll.delta > 0) {zoomFactor /= 1.1f;} else {zoomFactor *= 1.1f;}

            //zakres zooma
            zoomFactor = std::max(0.1f, std::min(zoomFactor, 5.0f));

            view.setSize(window.getDefaultView().getSize() * zoomFactor);
            window.setView(view);
        }
        }
}
