#include "UI.h"


Slider::Slider(float x, float y, float width, Color color)
    : m_pos(x, y), m_width(width), m_value(0.0f), m_isDragging(false)
{
    track.setPosition(x, y + 5);
    track.setSize(Vector2f(width, 4));
    track.setFillColor(Color(200, 200, 200)); //Светло серый

    handle.setSize(Vector2f(10, 20));
    handle.setOrigin(5, 10); // Точка позиционирования на центр(при перетаскивании ползунка центрируется по этим коордам)
    handle.setPosition(x, y + 7);
    handle.setFillColor(color);
    handle.setOutlineThickness(1); //Толщина
    handle.setOutlineColor(Color::Black); //Обводка
}

void Slider::handleInput(const Event& event, const RenderWindow& window) {
    Vector2f mousePos = (Vector2f)Mouse::getPosition(window);
    if (event.type == Event::MouseButtonPressed) {
        if (handle.getGlobalBounds().contains(mousePos) || track.getGlobalBounds().contains(mousePos)) { //Внутри ли хендла или трака
            m_isDragging = true;
            updatePos(mousePos.x);
        }
    }
    if (event.type == Event::MouseButtonReleased) {
        m_isDragging = false;
    }
    if (event.type == Event::MouseMoved && m_isDragging) {
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
    return int(m_value * 255);//Отбрасываем дробную часть и приводим к 255 ргб
}

void Slider::draw(RenderWindow& window) {
    window.draw(track);
    window.draw(handle);
}



RadioButton::RadioButton(float x, float y, ToolType t)
    : type(t), isSelected(false), position(x, y)
{
    shape.setSize(Vector2f(50, 50));
    shape.setPosition(x, y);
    shape.setOutlineThickness(2);
    update();
}

void RadioButton::update() {
    shape.setFillColor(isSelected ? Color(150, 255, 150) : Color(220, 220, 220));
    shape.setOutlineColor(Color::Black);
}

bool RadioButton::isClicked(Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void RadioButton::draw(RenderWindow& window) {
    window.draw(shape);
    Vector2f center = position + Vector2f(25, 25); //Для центрирования кнопок

    if (type == ToolType::Rectangle) {
        RectangleShape icon(Vector2f(24, 18));
        icon.setOrigin(12, 9);
        icon.setPosition(center);
        icon.setFillColor(Color::Transparent);
        icon.setOutlineThickness(2);
        icon.setOutlineColor(Color::Black);
        window.draw(icon);
    }
    else if (type == ToolType::Circle) {
        CircleShape icon(10);
        icon.setOrigin(10, 10);
        icon.setPosition(center);
        icon.setFillColor(Color::Transparent);
        icon.setOutlineThickness(2);
        icon.setOutlineColor(Color::Black);
        window.draw(icon);
    }
    else if (type == ToolType::Line) {
        Vertex line[] = {
            Vertex(center + Vector2f(-10, 10), Color::Black), //Смещение точки от центра кнопки
            Vertex(center + Vector2f(10, -10), Color::Black) //Вправо и вверх
        };
        window.draw(line, 2, Lines);
    }
    else if (type == ToolType::Pencil) {
        CircleShape icon(3);
        icon.setOrigin(3, 3);
        icon.setPosition(center);
        icon.setFillColor(Color::Black);
        window.draw(icon);
        Vertex line[] = {
            Vertex(center + Vector2f(-8, 8), Color::Black),
            Vertex(center, Color::Black),
            Vertex(center + Vector2f(8, -8), Color::Black)
        };
        window.draw(line, 3, LineStrip);
    }
    else if (type == ToolType::Bucket) {
        RectangleShape icon(Vector2f(20, 20));
        icon.setOrigin(10, 10);
        icon.setPosition(center);
        icon.setFillColor(Color::Black);
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

void ToolSelector::handleInput(Vector2f mousePos) {
    for (auto& btn : buttons) {
        if (btn.isClicked(mousePos)) {
            selectedType = btn.type;
        }
    }
    updateButtons();
}

ToolType ToolSelector::getSelected() const { return selectedType; } //Чтение типа выбранной кнопки

void ToolSelector::draw(RenderWindow& window) {
    for (auto& btn : buttons) {
        btn.draw(window);
    }
}