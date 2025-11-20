#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Canvas.h"
#include "UI.h"
#include "Tools.h"

class Application {
private:
    sf::RenderWindow m_window;
    Canvas m_canvas;
    ToolSelector m_toolSelector;

    Slider sliderR, sliderG, sliderB;
    sf::RectangleShape colorPreview;

    std::unique_ptr<RectTool> t_rect;
    std::unique_ptr<CircleTool> t_circle;
    std::unique_ptr<LineTool> t_line;
    std::unique_ptr<PencilTool> t_pencil;

    bool m_isDrawing;

public:
    Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::Color getCurrentColor();
    ToolLogic* getCurrentTool();
};