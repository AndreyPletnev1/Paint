#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tools.h" 


class Slider {
private:
    sf::RectangleShape track; //Прямоугольник, по которому движется ползунок
    sf::RectangleShape handle; //Ползунок
    float m_value;
    sf::Vector2f m_pos; //Начальная позиция
    float m_width; //Длина дорожки
    bool m_isDragging; 

public:
    Slider(float x, float y, float width, sf::Color color);
    //Клики и перетаскивание ползунка
    void handleInput(const sf::Event& event, const sf::RenderWindow& window);
    int getValue() const; // Значение ползунка
    void draw(sf::RenderWindow& window);

private:
    void updatePos(float mouseX);
};


class RadioButton {
public:
    sf::RectangleShape shape; //Визуал кнопки
    ToolType type; //Какая кнопка выбрана
    bool isSelected; //Если кнопка выбрана - выделение ее 
    sf::Vector2f position;// Позиция кнопок

    RadioButton(float x, float y, ToolType t);
    void update();
    bool isClicked(sf::Vector2f mousePos); // Проверка выбора
    void draw(sf::RenderWindow& window); // Отрисовка кнопок
};


class ToolSelector {
private:
    std::vector<RadioButton> buttons; //Контейнер(хранит все кнопки радио баттон)
    ToolType selectedType; //Текущий выбор.

public:
    ToolSelector();
    void updateButtons(); // Обновление состояния кнопок
    //Обработка кликов
    void handleInput(sf::Vector2f mousePos); 
    ToolType getSelected() const;
    void draw(sf::RenderWindow& window); 
};