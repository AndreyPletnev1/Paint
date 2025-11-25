#include "Canvas.h"

Canvas::Canvas(unsigned int width, unsigned int height) {
    m_texture.create(width, height);
    clear();
    m_sprite.setTexture(m_texture.getTexture());
}

void Canvas::stamp(const Drawable& drawable) {
    m_texture.draw(drawable);
        
}

void Canvas::draw(RenderWindow& window) {
    window.draw(m_sprite);
}

void Canvas::clear() {
    m_texture.clear(Color::White);
    m_texture.display();
}

void Canvas::floodFill(int x, int y, Color newColor) {
    Image image = m_texture.getTexture().copyToImage();//Копируем содержимое, чтобы изменить
    unsigned int w = image.getSize().x;
    unsigned int h = image.getSize().y;

    if (x < 0 || x >= (int)w || y < 0 || y >= (int)h) return;//Если x,y за пределами холста, завершаем

    Color targetColor = image.getPixel(x, y);
    if (targetColor == newColor) return;

    stack<Vector2i> stack;//Стек, чтобы без рекурсии идти по пикселям
    stack.push({ x, y });

    while (!stack.empty()) {
        Vector2i p = stack.top();
        stack.pop();

        if (p.x < 0 || p.x >= (int)w || p.y < 0 || p.y >= (int)h) continue; 
        if (image.getPixel(p.x, p.y) != targetColor) continue;

        image.setPixel(p.x, p.y, newColor);

        stack.push({ p.x + 1, p.y });
        stack.push({ p.x - 1, p.y });
        stack.push({ p.x, p.y + 1 });
        stack.push({ p.x, p.y - 1 });
    }

    // Обновляем текстуру
    Texture tempTex;
    tempTex.loadFromImage(image);
    Sprite tempSprite(tempTex);
    m_texture.draw(tempSprite);
    m_texture.display();
}