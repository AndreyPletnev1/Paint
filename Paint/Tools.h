#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;
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
    virtual void onMousePress(Vector2f pos, Color color) = 0;
    virtual void onMouseMove(Vector2f pos) = 0;
    virtual Drawable* getDrawable() = 0;
};

// --- Реализации ---

class RectTool : public ToolLogic {
    RectangleShape m_rect;
    Vector2f m_startPos;//Начальная позиция клика мыши.
public:
    void onMousePress(Vector2f pos, Color color) override;
    void onMouseMove(Vector2f pos) override;
    Drawable* getDrawable() override;
};

class CircleTool : public ToolLogic {
    CircleShape m_circle;
    Vector2f m_startPos;
public:
    void onMousePress(Vector2f pos, Color color) override;
    void onMouseMove(Vector2f pos) override;
    Drawable* getDrawable() override;
};

class LineTool : public ToolLogic {
    VertexArray m_line;
public:
    LineTool();
    void onMousePress(Vector2f pos, Color color) override;
    void onMouseMove(Vector2f pos) override;
    Drawable* getDrawable() override;
};

class PencilTool : public ToolLogic {
    VertexArray m_points;
    Color m_color;
public:
    PencilTool();
    void onMousePress(Vector2f pos, Color color) override;
    void onMouseMove(Vector2f pos) override;
    void addPoint(Vector2f pos);
    Drawable* getDrawable() override;
};