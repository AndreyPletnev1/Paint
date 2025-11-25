#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
using namespace std;
using namespace sf;
class Canvas {
private:
    RenderTexture m_texture;
    Sprite m_sprite;

public:
    Canvas(unsigned int width, unsigned int height);

    //Припечатывание к канвасу рисунка
    void stamp(const Drawable& drawable);
    void draw(RenderWindow& window);
    void clear();
    void floodFill(int x, int y, Color newColor);
};