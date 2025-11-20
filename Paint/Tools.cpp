#include "Tools.h"
#include <cmath> 


void RectTool::onMousePress(sf::Vector2f pos, sf::Color color) {
    m_startPos = pos;
    m_rect.setPosition(pos);
    m_rect.setSize({ 0, 0 });
    m_rect.setFillColor(sf::Color::Transparent);
    m_rect.setOutlineColor(color);
    m_rect.setOutlineThickness(3.0f);
}
void RectTool::onMouseMove(sf::Vector2f pos) {
    m_rect.setSize(pos - m_startPos);
}
sf::Drawable* RectTool::getDrawable() { return &m_rect; } // Отрисовка при движении мышкой

void CircleTool::onMousePress(sf::Vector2f pos, sf::Color color) {
    m_startPos = pos;
    m_circle.setPosition(pos);
    m_circle.setRadius(0);
    m_circle.setFillColor(sf::Color::Transparent);
    m_circle.setOutlineColor(color);
    m_circle.setOutlineThickness(3.0f);
}
void CircleTool::onMouseMove(sf::Vector2f pos) {
    float radius = std::hypot(pos.x - m_startPos.x, pos.y - m_startPos.y);//Радиус круга, который динамически растягивается по мере движения мыши
    m_circle.setRadius(radius);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(m_startPos);
}
sf::Drawable* CircleTool::getDrawable() { return &m_circle; }


LineTool::LineTool() : m_line(sf::Lines, 2) {}
void LineTool::onMousePress(sf::Vector2f pos, sf::Color color) {
    m_line[0].position = pos;
    m_line[0].color = color;
    m_line[1].position = pos;
    m_line[1].color = color;
}
void LineTool::onMouseMove(sf::Vector2f pos) {
    m_line[1].position = pos;
}
sf::Drawable* LineTool::getDrawable() { return &m_line; }


PencilTool::PencilTool() : m_points(sf::LineStrip) {}
void PencilTool::onMousePress(sf::Vector2f pos, sf::Color color) {
    m_points.clear();
    m_color = color;
    addPoint(pos);
}
void PencilTool::onMouseMove(sf::Vector2f pos) {
    addPoint(pos);
}
void PencilTool::addPoint(sf::Vector2f pos) {
    m_points.append(sf::Vertex(pos, m_color));
}
sf::Drawable* PencilTool::getDrawable() { return &m_points; }