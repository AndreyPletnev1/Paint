#include "UI.h"


Slider::Slider(float x, float y, float width, sf::Color color)
    : m_pos(x, y), m_width(width), m_value(0.0f), m_isDragging(false)
{
    track.setPosition(x, y + 5);
    track.setSize(sf::Vector2f(width, 4));
    track.setFillColor(sf::Color(200, 200, 200)); //Светло серый

    handle.setSize(sf::Vector2f(10, 20));
    handle.setOrigin(5, 10); // Точка позиционирования на центр(при перетаскивании ползунка центрируется по этим коордам)
    handle.setPosition(x, y + 7);
    handle.setFillColor(color);
    handle.setOutlineThickness(1); //Толщина
    handle.setOutlineColor(sf::Color::Black); //Обводка
}

void Slider::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (handle.getGlobalBounds().contains(mousePos) || track.getGlobalBounds().contains(mousePos)) { //Внутри ли хендла или трака
            m_isDragging = true;
            updatePos(mousePos.x);
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        m_isDragging = false;
    }
    if (event.type == sf::Event::MouseMoved && m_isDragging) {
        updatePos(mousePos.x);
    }
}

void Slider::updatePos(float mouseX) {
    float relativeX = mouseX - m_pos.x; 
    if (relativeX < 0) relativeX = 0;
    if (relativeX > m_width) relativeX = m_width;

    m_value = relativeX / m_width;
    handle.setPosition(m_pos.x + relativeX, m_pos.y + 7);
}

int Slider::getValue() const {
    return static_cast<int>(m_value * 255);//Отбрасываем дробную часть и приводим к 255 ргб
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(track);
    window.draw(handle);
}



RadioButton::RadioButton(float x, float y, ToolType t)
    : type(t), isSelected(false), position(x, y)
{
    shape.setSize(sf::Vector2f(50, 50));
    shape.setPosition(x, y);
    shape.setOutlineThickness(2);
    update();
}

void RadioButton::update() {
    shape.setFillColor(isSelected ? sf::Color(150, 255, 150) : sf::Color(220, 220, 220));
    shape.setOutlineColor(sf::Color::Black);
}

bool RadioButton::isClicked(sf::Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void RadioButton::draw(sf::RenderWindow& window) {
    window.draw(shape);
    sf::Vector2f center = position + sf::Vector2f(25, 25); //Для центрирования кнопок

    if (type == ToolType::Rectangle) {
        sf::RectangleShape icon(sf::Vector2f(24, 18));
        icon.setOrigin(12, 9);
        icon.setPosition(center);
        icon.setFillColor(sf::Color::Transparent);
        icon.setOutlineThickness(2);
        icon.setOutlineColor(sf::Color::Black);
        window.draw(icon);
    }
    else if (type == ToolType::Circle) {
        sf::CircleShape icon(10);
        icon.setOrigin(10, 10);
        icon.setPosition(center);
        icon.setFillColor(sf::Color::Transparent);
        icon.setOutlineThickness(2);
        icon.setOutlineColor(sf::Color::Black);
        window.draw(icon);
    }
    else if (type == ToolType::Line) {
        sf::Vertex line[] = {
            sf::Vertex(center + sf::Vector2f(-10, 10), sf::Color::Black), //Смещение точки от центра кнопки
            sf::Vertex(center + sf::Vector2f(10, -10), sf::Color::Black) //Вправо и вверх
        };
        window.draw(line, 2, sf::Lines);
    }
    else if (type == ToolType::Pencil) {
        sf::CircleShape icon(3);
        icon.setOrigin(3, 3);
        icon.setPosition(center);
        icon.setFillColor(sf::Color::Black);
        window.draw(icon);
        sf::Vertex line[] = {
            sf::Vertex(center + sf::Vector2f(-8, 8), sf::Color::Black),
            sf::Vertex(center, sf::Color::Black),
            sf::Vertex(center + sf::Vector2f(8, -8), sf::Color::Black)
        };
        window.draw(line, 3, sf::LineStrip);
    }
    else if (type == ToolType::Bucket) {
        sf::RectangleShape icon(sf::Vector2f(20, 20));
        icon.setOrigin(10, 10);
        icon.setPosition(center);
        icon.setFillColor(sf::Color::Black);
        window.draw(icon);
    }
}


ToolSelector::ToolSelector() {
    float startX = 10;//Координата левой кнопки
    float gap = 60;//Расстояние между центрами кнопок(т.к кнопки 50 на 50, то расстояние 10)

    buttons.emplace_back(startX, 10, ToolType::Rectangle);
    buttons.emplace_back(startX + gap, 10, ToolType::Circle);
    buttons.emplace_back(startX + gap * 2, 10, ToolType::Line);
    buttons.emplace_back(startX + gap * 3, 10, ToolType::Pencil);
    buttons.emplace_back(startX + gap * 4, 10, ToolType::Bucket);

    selectedType = ToolType::Rectangle;
    updateButtons();
}

void ToolSelector::updateButtons() {
    for (auto& btn : buttons) {
        btn.isSelected = (btn.type == selectedType);
        btn.update();
    }
}

void ToolSelector::handleInput(sf::Vector2f mousePos) {
    for (auto& btn : buttons) {
        if (btn.isClicked(mousePos)) {
            selectedType = btn.type;
        }
    }
    updateButtons();
}

ToolType ToolSelector::getSelected() const { return selectedType; } //Чтение типа выбранной кнопки

void ToolSelector::draw(sf::RenderWindow& window) {
    for (auto& btn : buttons) {
        btn.draw(window);
    }
}