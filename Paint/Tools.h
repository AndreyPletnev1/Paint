#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

enum class ToolType {
    Rectangle,
    Circle,
    Line,
    Pencil,
    Bucket,
    EraserTool
};


class ToolLogic {
public:
    virtual ~ToolLogic() = default;
    virtual void onMousePress(sf::Vector2f pos, sf::Color color) = 0;
    virtual void onMouseMove(sf::Vector2f pos) = 0;
    virtual sf::Drawable* getDrawable() = 0;
};

// --- Реализации ---

class RectTool : public ToolLogic {
    sf::RectangleShape m_rect;
    sf::Vector2f m_startPos;//Начальная позиция клика мыши.
public:
    void onMousePress(sf::Vector2f pos, sf::Color color) override;
    void onMouseMove(sf::Vector2f pos) override;
    sf::Drawable* getDrawable() override;
};

class CircleTool : public ToolLogic {
    sf::CircleShape m_circle;
    sf::Vector2f m_startPos;
public:
    void onMousePress(sf::Vector2f pos, sf::Color color) override;
    void onMouseMove(sf::Vector2f pos) override;
    sf::Drawable* getDrawable() override;
};

class LineTool : public ToolLogic {
    sf::VertexArray m_line;
public:
    LineTool();
    void onMousePress(sf::Vector2f pos, sf::Color color) override;
    void onMouseMove(sf::Vector2f pos) override;
    sf::Drawable* getDrawable() override;
};

class PencilTool : public ToolLogic {
    sf::VertexArray m_points;
    sf::Color m_color;
public:
    PencilTool();
    void onMousePress(sf::Vector2f pos, sf::Color color) override;
    void onMouseMove(sf::Vector2f pos) override;
    void addPoint(sf::Vector2f pos);
    sf::Drawable* getDrawable() override;
};