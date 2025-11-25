#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Canvas.h"
#include "UI.h"
#include "Tools.h"
using namespace std;
using namespace sf;
    class Application {
    private:
        RenderWindow m_window;
        Canvas m_canvas;
        ToolSelector m_toolSelector;

        Slider sliderR, sliderG, sliderB;
        RectangleShape colorPreview;
        //unique - сам выделяет память, сам освобождает, только он может владеть обьектом.
        unique_ptr<RectTool> t_rect;
        unique_ptr<CircleTool> t_circle;
        unique_ptr<LineTool> t_line;
        unique_ptr<PencilTool> t_pencil;

        bool m_isDrawing;

public:
    Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

    Color getCurrentColor();
    ToolLogic* getCurrentTool();
};