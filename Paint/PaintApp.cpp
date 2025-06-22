#include "PaintApp.h"
#include "DrawingTools.h"
#include <iostream>

const int TOOLBAR_HEIGHT = 50;
const int COLOR_SLIDER_WIDTH = 200;
const int COLOR_SLIDER_HEIGHT = 20;

PaintApp::PaintApp(int width, int height)
    : window(sf::VideoMode(width, height), "Simple Paint"),
    currentColor(sf::Color::Black),
    currentTool(ToolType::PENCIL), showColorSliders(false),
    drawing(false), isDragging(false) {

    canvas.create(width, height, sf::Color::White);
    tempCanvas.create(width, height, sf::Color::Transparent);
    canvasTexture.loadFromImage(canvas);
    canvasSprite.setTexture(canvasTexture);

    setupUI();
}

void PaintApp::setupUI() {
    toolButtons.clear();
    int btnSize = 40;
    int margin = 10;

    // Create buttons for each tool type
    toolButtons.emplace_back(sf::Vector2f(margin, margin), sf::Vector2f(btnSize, btnSize), ToolType::PENCIL);
    toolButtons.emplace_back(sf::Vector2f(margin * 2 + btnSize, margin), sf::Vector2f(btnSize, btnSize), ToolType::LINE);
    toolButtons.emplace_back(sf::Vector2f(margin * 3 + btnSize * 2, margin), sf::Vector2f(btnSize, btnSize), ToolType::RECTANGLE);
    toolButtons.emplace_back(sf::Vector2f(margin * 4 + btnSize * 3, margin), sf::Vector2f(btnSize, btnSize), ToolType::CIRCLE);
    toolButtons.emplace_back(sf::Vector2f(margin * 5 + btnSize * 4, margin), sf::Vector2f(btnSize, btnSize), ToolType::FILL);
    toolButtons.emplace_back(sf::Vector2f(margin * 6 + btnSize * 5, margin), sf::Vector2f(btnSize, btnSize), ToolType::ERASER);

    // Color display button
    colorDisplay.setSize(sf::Vector2f(btnSize, btnSize));
    colorDisplay.setPosition(margin * 7 + btnSize * 6, margin);
    colorDisplay.setFillColor(currentColor);
    colorDisplay.setOutlineColor(sf::Color::Black);
    colorDisplay.setOutlineThickness(1);

    // Color sliders
    rSlider.setSize(sf::Vector2f(COLOR_SLIDER_WIDTH, COLOR_SLIDER_HEIGHT));
    gSlider.setSize(sf::Vector2f(COLOR_SLIDER_WIDTH, COLOR_SLIDER_HEIGHT));
    bSlider.setSize(sf::Vector2f(COLOR_SLIDER_WIDTH, COLOR_SLIDER_HEIGHT));

    rSlider.setFillColor(sf::Color(150, 0, 0));
    gSlider.setFillColor(sf::Color(0, 150, 0));
    bSlider.setFillColor(sf::Color(0, 0, 150));

    rSlider.setPosition(10, TOOLBAR_HEIGHT + 40);
    gSlider.setPosition(10, TOOLBAR_HEIGHT + 70);
    bSlider.setPosition(10, TOOLBAR_HEIGHT + 100);

    rThumb.setRadius(10);
    gThumb.setRadius(10);
    bThumb.setRadius(10);

    rThumb.setFillColor(sf::Color::Red);
    gThumb.setFillColor(sf::Color::Green);
    bThumb.setFillColor(sf::Color::Blue);

    updateColorDisplay();
}


void PaintApp::updateColorDisplay() {
    colorDisplay.setFillColor(currentColor);

    rThumb.setPosition(rSlider.getPosition().x +
        currentColor.r * (COLOR_SLIDER_WIDTH - 20) / 255.0f,
        rSlider.getPosition().y - 5);

    gThumb.setPosition(gSlider.getPosition().x +
        currentColor.g * (COLOR_SLIDER_WIDTH - 20) / 255.0f,
        gSlider.getPosition().y - 5);

    bThumb.setPosition(bSlider.getPosition().x +
        currentColor.b * (COLOR_SLIDER_WIDTH - 20) / 255.0f,
        bSlider.getPosition().y - 5);
}

void PaintApp::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

void PaintApp::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool inCanvas = mousePos.y > TOOLBAR_HEIGHT;

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Check tool buttons
                for (auto& btn : toolButtons) {
                    if (btn.contains(mousePos)) {
                        currentTool = btn.getToolType();
                        showColorSliders = false;
                        break;
                    }
                }

                // Check color button
                if (colorDisplay.getGlobalBounds().contains(
                    static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y))) {

                    showColorSliders = !showColorSliders;
                }
                // Handle color sliders
                else if (showColorSliders) {
                    if (rSlider.getGlobalBounds().contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y))) {

                        float value = (mousePos.x - rSlider.getPosition().x) * 255.0f / COLOR_SLIDER_WIDTH;
                        value = std::max(0.0f, std::min(255.0f, value));
                        currentColor.r = static_cast<sf::Uint8>(value);
                        updateColorDisplay();
                    }
                    else if (gSlider.getGlobalBounds().contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y))) {

                        float value = (mousePos.x - gSlider.getPosition().x) * 255.0f / COLOR_SLIDER_WIDTH;
                        value = std::max(0.0f, std::min(255.0f, value));
                        currentColor.g = static_cast<sf::Uint8>(value);
                        updateColorDisplay();
                    }
                    else if (bSlider.getGlobalBounds().contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y))) {

                        float value = (mousePos.x - bSlider.getPosition().x) * 255.0f / COLOR_SLIDER_WIDTH;
                        value = std::max(0.0f, std::min(255.0f, value));
                        currentColor.b = static_cast<sf::Uint8>(value);
                        updateColorDisplay();
                    }
                }
                // Handle canvas tools
                else if (inCanvas) {
                    drawing = true;
                    isDragging = true;
                    startPos = mousePos;
                    currentPos = mousePos;

                    if (currentTool == ToolType::FILL) {
                        floodFill(canvas, mousePos, canvas.getPixel(mousePos.x, mousePos.y),
                            (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
                        canvasTexture.loadFromImage(canvas);
                    }
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && drawing) {
                drawing = false;
                isDragging = false;

                if (currentTool != ToolType::PENCIL &&
                    currentTool != ToolType::ERASER &&
                    currentTool != ToolType::FILL) {

                    // Apply final shape to canvas
                    switch (currentTool) {
                    case ToolType::LINE:
                        drawLine(canvas, startPos, currentPos,
                            (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
                        break;
                    case ToolType::RECTANGLE:
                        drawRectangle(canvas, startPos, currentPos,
                            (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
                        break;
                    case ToolType::CIRCLE:
                        drawCircle(canvas, startPos, currentPos,
                            (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
                        break;
                    default: break;
                    }

                    canvasTexture.loadFromImage(canvas);
                }
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            currentPos = mousePos;
            if (drawing && inCanvas) {
                if (currentTool == ToolType::PENCIL || currentTool == ToolType::ERASER) {
                    drawLine(canvas, startPos, currentPos,
                        (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
                    startPos = currentPos;
                    canvasTexture.loadFromImage(canvas);
                }
            }
        }
    }
}

void PaintApp::render() {
    window.clear(sf::Color(220, 220, 220));

    // Draw canvas
    window.draw(canvasSprite);

    // Draw preview if dragging
    if (isDragging && currentTool != ToolType::PENCIL &&
        currentTool != ToolType::ERASER && currentTool != ToolType::FILL) {

        tempCanvas.create(window.getSize().x, window.getSize().y, sf::Color::Transparent);

        switch (currentTool) {
        case ToolType::LINE:
            drawLine(tempCanvas, startPos, currentPos,
                (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
            break;
        case ToolType::RECTANGLE:
            drawRectangle(tempCanvas, startPos, currentPos,
                (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
            break;
        case ToolType::CIRCLE:
            drawCircle(tempCanvas, startPos, currentPos,
                (currentTool == ToolType::ERASER) ? sf::Color::White : currentColor);
            break;
        default: break;
        }

        sf::Texture tempTexture;
        tempTexture.loadFromImage(tempCanvas);
        sf::Sprite tempSprite(tempTexture);
        window.draw(tempSprite);
    }

    // Draw toolbar background
    sf::RectangleShape toolbar(sf::Vector2f(window.getSize().x, TOOLBAR_HEIGHT));
    toolbar.setFillColor(sf::Color(180, 180, 180));
    window.draw(toolbar);

    // Draw tool buttons
    for (auto& btn : toolButtons) {
        btn.draw(window);
        if (btn.getToolType() == currentTool) {
            sf::RectangleShape highlight(btn.getSize() + sf::Vector2f(4, 4));
            highlight.setPosition(btn.getPosition() - sf::Vector2f(2, 2));
            highlight.setFillColor(sf::Color::Transparent);
            highlight.setOutlineColor(sf::Color::Blue);
            highlight.setOutlineThickness(2);
            window.draw(highlight);
        }
    }

    // Draw color button
    window.draw(colorDisplay);

    // Draw color sliders if visible
    if (showColorSliders) {
        window.draw(rSlider);
        window.draw(gSlider);
        window.draw(bSlider);
        window.draw(rThumb);
        window.draw(gThumb);
        window.draw(bThumb);
    }

    window.display();
}