#include "Tools.h"
#include <cmath> 


void RectTool::onMousePress(Vector2f pos, Color color) {
    m_startPos = pos;
    m_rect.setPosition(pos);
    m_rect.setSize({ 0, 0 });
    m_rect.setFillColor(Color::Transparent);
    m_rect.setOutlineColor(color);
    m_rect.setOutlineThickness(3.0f);
}
void RectTool::onMouseMove(Vector2f pos) {
    m_rect.setSize(pos - m_startPos);
}
Drawable* RectTool::getDrawable() { return &m_rect; } // Отрисовка при движении мышкой

void CircleTool::onMousePress(Vector2f pos, Color color) {
    m_startPos = pos;
    m_circle.setPosition(pos);
    m_circle.setRadius(0);
    m_circle.setFillColor(Color::Transparent);
    m_circle.setOutlineColor(color);
    m_circle.setOutlineThickness(3.0f);
}
void CircleTool::onMouseMove(Vector2f pos) {
    float radius = hypot(pos.x - m_startPos.x, pos.y - m_startPos.y);//Радиус круга, который динамически растягивается по мере движения мыши
    m_circle.setRadius(radius);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(m_startPos);
}
Drawable* CircleTool::getDrawable() { return &m_circle; }


LineTool::LineTool() : m_line(Lines, 2) {}
void LineTool::onMousePress(Vector2f pos, Color color) {
    m_line[0].position = pos;
    m_line[0].color = color;
    m_line[1].position = pos;
    m_line[1].color = color;
}
void LineTool::onMouseMove(Vector2f pos) {
    m_line[1].position = pos;
}
Drawable* LineTool::getDrawable() { return &m_line; }


PencilTool::PencilTool() : m_points(LineStrip) {}
void PencilTool::onMousePress(Vector2f pos, Color color) {
    m_points.clear();
    m_color = color;
    addPoint(pos);
}
void PencilTool::onMouseMove(Vector2f pos) {
    addPoint(pos);
}
void PencilTool::addPoint(Vector2f pos) {
    m_points.append(Vertex(pos, m_color));
}
Drawable* PencilTool::getDrawable() { return &m_points; }