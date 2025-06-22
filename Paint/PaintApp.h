#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ToolType.h"
#include "Button.h"

class PaintApp {
public:
    PaintApp(int width, int height);
    void run();

private:
    void handleEvents();
    void render();
    void setupUI();
    void updateColorDisplay();
    void applyTool(const sf::Vector2i& pos);
    void drawPreview();

    sf::RenderWindow window;
    sf::Image canvas;
    sf::Texture canvasTexture;
    sf::Sprite canvasSprite;
    sf::Color currentColor;
    ToolType currentTool;

    // UI Elements
    std::vector<Button> toolButtons;
    sf::RectangleShape colorDisplay;
    bool showColorSliders;
    sf::RectangleShape rSlider, gSlider, bSlider;
    sf::CircleShape rThumb, gThumb, bThumb;

    bool drawing;
    bool isDragging;
    sf::Vector2i startPos;
    sf::Vector2i currentPos;
    sf::Image tempCanvas;
};