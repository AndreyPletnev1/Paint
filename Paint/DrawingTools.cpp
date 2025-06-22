#include "DrawingTools.h"
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>

void drawLine(sf::Image& img, sf::Vector2i p1, sf::Vector2i p2, const sf::Color& color) {
    // Реализация алгоритма Брезенхема
    int dx = std::abs(p2.x - p1.x);
    int dy = -std::abs(p2.y - p1.y);
    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;
    int err = dx + dy;

    while (true) {
        if (p1.x >= 0 && p1.x < static_cast<int>(img.getSize().x) &&
            p1.y >= 0 && p1.y < static_cast<int>(img.getSize().y)) {
            img.setPixel(p1.x, p1.y, color);
        }

        if (p1.x == p2.x && p1.y == p2.y) break;
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            p1.x += sx;
        }
        if (e2 <= dx) {
            err += dx;
            p1.y += sy;
        }
    }
}

void drawRectangle(sf::Image& img, sf::Vector2i p1, sf::Vector2i p2, const sf::Color& color) {
    int minX = std::min(p1.x, p2.x);
    int maxX = std::max(p1.x, p2.x);
    int minY = std::min(p1.y, p2.y);
    int maxY = std::max(p1.y, p2.y);

    // Верхняя и нижняя линии
    for (int x = minX; x <= maxX; x++) {
        if (x >= 0 && x < static_cast<int>(img.getSize().x)) {
            if (minY >= 0 && minY < static_cast<int>(img.getSize().y))
                img.setPixel(x, minY, color);
            if (maxY >= 0 && maxY < static_cast<int>(img.getSize().y))
                img.setPixel(x, maxY, color);
        }
    }

    // Левая и правая линии
    for (int y = minY; y <= maxY; y++) {
        if (y >= 0 && y < static_cast<int>(img.getSize().y)) {
            if (minX >= 0 && minX < static_cast<int>(img.getSize().x))
                img.setPixel(minX, y, color);
            if (maxX >= 0 && maxX < static_cast<int>(img.getSize().x))
                img.setPixel(maxX, y, color);
        }
    }
}

void drawCircle(sf::Image& img, sf::Vector2i center, sf::Vector2i edge, const sf::Color& color) {
    int dx = edge.x - center.x;
    int dy = edge.y - center.y;
    int radius = static_cast<int>(std::sqrt(dx * dx + dy * dy));

    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    auto setPixel = [&](int cx, int cy) {
        if (cx >= 0 && cx < static_cast<int>(img.getSize().x) &&
            cy >= 0 && cy < static_cast<int>(img.getSize().y)) {
            img.setPixel(cx, cy, color);
        }
        };

    while (y >= x) {
        setPixel(center.x + x, center.y + y);
        setPixel(center.x - x, center.y + y);
        setPixel(center.x + x, center.y - y);
        setPixel(center.x - x, center.y - y);
        setPixel(center.x + y, center.y + x);
        setPixel(center.x - y, center.y + x);
        setPixel(center.x + y, center.y - x);
        setPixel(center.x - y, center.y - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        }
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void floodFill(sf::Image& img, sf::Vector2i start, sf::Color targetColor, sf::Color fillColor) {
    if (targetColor == fillColor) return;

    std::stack<sf::Vector2i> pixels;
    pixels.push(start);

    sf::Vector2u size = img.getSize();

    while (!pixels.empty()) {
        sf::Vector2i p = pixels.top();
        pixels.pop();

        if (p.x < 0 || p.y < 0 ||
            p.x >= static_cast<int>(size.x) ||
            p.y >= static_cast<int>(size.y) ||
            img.getPixel(p.x, p.y) != targetColor) {
            continue;
        }

        img.setPixel(p.x, p.y, fillColor);

        pixels.push(sf::Vector2i(p.x + 1, p.y));
        pixels.push(sf::Vector2i(p.x - 1, p.y));
        pixels.push(sf::Vector2i(p.x, p.y + 1));
        pixels.push(sf::Vector2i(p.x, p.y - 1));
    }
}