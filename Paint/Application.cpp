#include "Application.h"

Application::Application()
    : m_window(sf::VideoMode(900, 700), "SFML Paint"),
    m_canvas(900, 700),
    sliderR(600, 10, 150, sf::Color::Red),
    sliderG(600, 40, 150, sf::Color::Green),
    sliderB(600, 70, 150, sf::Color::Blue),
    m_isDrawing(false)
{
    m_window.setFramerateLimit(60);

    t_rect = std::make_unique<RectTool>();
    t_circle = std::make_unique<CircleTool>();
    t_line = std::make_unique<LineTool>();
    t_pencil = std::make_unique<PencilTool>();

    colorPreview.setSize(sf::Vector2f(50, 50));
    colorPreview.setPosition(770, 25);
    colorPreview.setOutlineThickness(2);
    colorPreview.setOutlineColor(sf::Color::Black);
}

sf::Color Application::getCurrentColor() {
    return sf::Color(sliderR.getValue(), sliderG.getValue(), sliderB.getValue());
}

ToolLogic* Application::getCurrentTool() {
    switch (m_toolSelector.getSelected()) {
    case ToolType::Rectangle: return t_rect.get();
    case ToolType::Circle:    return t_circle.get();
    case ToolType::Line:      return t_line.get();
    case ToolType::Pencil:    return t_pencil.get();
    default: return nullptr;
    }
}

void Application::run() {
    while (m_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();

        sliderR.handleInput(event, m_window);
        sliderG.handleInput(event, m_window);
        sliderB.handleInput(event, m_window);

        sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        bool isMouseInUI = (mousePos.y < 80);

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseInUI) {
                m_toolSelector.handleInput(mousePos);
            }
            else {
                ToolType type = m_toolSelector.getSelected();
                sf::Color col = getCurrentColor();

                if (type == ToolType::Bucket) {
                    m_canvas.floodFill((int)mousePos.x, (int)mousePos.y, col);
                }
                else {
                    m_isDrawing = true;
                    getCurrentTool()->onMousePress(mousePos, col);
                }
            }
        }

        if (event.type == sf::Event::MouseMoved && m_isDrawing) {
            getCurrentTool()->onMouseMove(mousePos);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (m_isDrawing) {
                m_isDrawing = false;
                sf::Drawable* d = getCurrentTool()->getDrawable();
                if (d) m_canvas.stamp(*d);
            }
        }
    }
}

void Application::update() {
    colorPreview.setFillColor(getCurrentColor());
}

void Application::render() {
    m_window.clear(sf::Color(50, 50, 50));

    m_canvas.draw(m_window);

    if (m_isDrawing) {
        ToolLogic* tool = getCurrentTool();
        if (tool && tool->getDrawable()) {
            m_window.draw(*tool->getDrawable());
        }
    }

    // ‘ÓÌ UI
    sf::RectangleShape uiBg(sf::Vector2f(900, 80));
    uiBg.setFillColor(sf::Color(240, 240, 240));
    m_window.draw(uiBg);

    m_toolSelector.draw(m_window);

    sliderR.draw(m_window);
    sliderG.draw(m_window);
    sliderB.draw(m_window);
    m_window.draw(colorPreview);

    m_window.display();
}