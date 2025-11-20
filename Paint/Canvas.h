#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class Canvas {
private:
    sf::RenderTexture m_texture;
    sf::Sprite m_sprite;

public:
    Canvas(unsigned int width, unsigned int height);

    //Припечатывание к канвасу рисунка
    void stamp(const sf::Drawable& drawable);
    void draw(sf::RenderWindow& window);
    void clear();
    void floodFill(int x, int y, sf::Color newColor);
};