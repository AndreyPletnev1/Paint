#pragma once
#include <SFML/Graphics.hpp>
#include "ToolType.h"

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, ToolType toolType);

    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2i& point) const;

    ToolType getToolType() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

private:
    sf::Vector2f position;
    sf::Vector2f size;
    ToolType toolType;
    sf::RectangleShape shape;
};