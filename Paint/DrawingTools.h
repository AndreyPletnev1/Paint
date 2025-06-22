#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <queue>
#include <stack>

void drawLine(sf::Image& img, sf::Vector2i p1, sf::Vector2i p2, const sf::Color& color);
void drawRectangle(sf::Image& img, sf::Vector2i p1, sf::Vector2i p2, const sf::Color& color);
void drawCircle(sf::Image& img, sf::Vector2i center, sf::Vector2i edge, const sf::Color& color);
void floodFill(sf::Image& img, sf::Vector2i start, sf::Color targetColor, sf::Color fillColor);