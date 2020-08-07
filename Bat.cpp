#include <iostream>
#include "Bat.h"

// This the constructor and it is called when we create an object
Bat::Bat(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    batShape.setSize(sf::Vector2f(10, 200));
    batShape.setPosition(position);
    this->batSpeed = 0.15f;
}

Bat::Bat(float startX, float startY, float batSpeed)
{
    position.x = startX;
    position.y = startY;

    batShape.setSize(sf::Vector2f(10, 200));
    batShape.setPosition(position);
    this->batSpeed = batSpeed;
}

FloatRect Bat::getPosition()
{
    return batShape.getGlobalBounds();
}

RectangleShape Bat::getShape()
{
    return batShape;
}

void Bat::moveUp()
{
    position.y -= batSpeed;
}

void Bat::moveDown()
{
    position.y += batSpeed;
}

void Bat::update()
{
    batShape.setPosition(position);
}