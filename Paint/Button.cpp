#include "Button.h"
#include <SFML/Graphics.hpp>

Button::Button(sf::Vector2f position, sf::Vector2f size, ToolType toolType)
    : position(position), size(size), toolType(toolType) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(200, 200, 200));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
}

void Button::draw(sf::RenderWindow& window) const {
    // Draw button background
    window.draw(shape);

    // Draw icon based on tool type
    switch (toolType) {
    case ToolType::PENCIL: {
        sf::CircleShape circle(size.x / 4);
        circle.setPosition(position.x + size.x / 4, position.y + size.y / 4);
        circle.setFillColor(sf::Color::Black);
        window.draw(circle);
        break;
    }
    case ToolType::LINE: {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(position.x + 5, position.y + size.y / 2), sf::Color::Black),
            sf::Vertex(sf::Vector2f(position.x + size.x - 5, position.y + size.y / 2), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        break;
    }
    case ToolType::RECTANGLE: {
        sf::RectangleShape rect(sf::Vector2f(size.x - 10, size.y - 10));
        rect.setPosition(position.x + 5, position.y + 5);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2);
        window.draw(rect);
        break;
    }
    case ToolType::CIRCLE: {
        sf::CircleShape circle(size.x / 2 - 5);
        circle.setPosition(position.x + 5, position.y + 5);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        window.draw(circle);
        break;
    }
    case ToolType::FILL: {
        sf::RectangleShape rect(sf::Vector2f(size.x - 10, size.y - 10));
        rect.setPosition(position.x + 5, position.y + 5);
        rect.setFillColor(sf::Color(100, 100, 100));
        window.draw(rect);
        break;
    }
    case ToolType::ERASER: {
        sf::RectangleShape rect(sf::Vector2f(size.x - 10, size.y - 10));
        rect.setPosition(position.x + 5, position.y + 5);
        rect.setFillColor(sf::Color::White);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1);
        window.draw(rect);

        // Red cross
        sf::Vertex cross[] = {
            sf::Vertex(sf::Vector2f(position.x + 8, position.y + 8), sf::Color::Red),
            sf::Vertex(sf::Vector2f(position.x + size.x - 8, position.y + size.y - 8), sf::Color::Red),
            sf::Vertex(sf::Vector2f(position.x + size.x - 8, position.y + 8), sf::Color::Red),
            sf::Vertex(sf::Vector2f(position.x + 8, position.y + size.y - 8), sf::Color::Red)
        };
        window.draw(cross, 4, sf::Lines);
        break;
    }
    }
}

bool Button::contains(const sf::Vector2i& point) const {
    return shape.getGlobalBounds().contains(static_cast<float>(point.x), static_cast<float>(point.y));
}

ToolType Button::getToolType() const {
    return toolType;
}

sf::Vector2f Button::getPosition() const {
    return position;
}

sf::Vector2f Button::getSize() const {
    return size;
}   