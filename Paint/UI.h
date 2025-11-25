#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tools.h" 
using namespace std;
using namespace sf;

class Slider {
private:
    RectangleShape track; //Прямоугольник, по которому движется ползунок
    RectangleShape handle; //Ползунок
    float m_value;
    Vector2f m_pos; //Начальная позиция
    float m_width; //Длина дорожки
    bool m_isDragging; 

public:
    Slider(float x, float y, float width, Color color);
    //Клики и перетаскивание ползунка
    void handleInput(const Event& event, const RenderWindow& window);
    int getValue() const; // Значение ползунка
    void draw(RenderWindow& window);

private:
    void updatePos(float mouseX);
};


class RadioButton {
public:
    RectangleShape shape; //Визуал кнопки
    ToolType type; //Какая кнопка выбрана
    bool isSelected; //Если кнопка выбрана - выделение ее 
    Vector2f position;// Позиция кнопок

    RadioButton(float x, float y, ToolType t);
    void update();
    bool isClicked(Vector2f mousePos); // Проверка выбора
    void draw(RenderWindow& window); // Отрисовка кнопок
};


class ToolSelector {
private:
    vector<RadioButton> buttons; //Контейнер(хранит все кнопки радио баттон)
    ToolType selectedType; //Текущий выбор.

public:
    ToolSelector();
    void updateButtons(); // Обновление состояния кнопок
    //Обработка кликов
    void handleInput(Vector2f mousePos); 
    ToolType getSelected() const;
    void draw(RenderWindow& window); 
};