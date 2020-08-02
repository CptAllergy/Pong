#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;

    // A RectangleShape object called ref
    CircleShape ballShape;

    float xVelocity = .1f;
    float yVelocity = .1f;
    float centerX, centerY;

public:
    Ball(float startX, float startY, float centerX, float centerY);

    FloatRect getPosition();

    CircleShape getShape();

    float getXVelocity();

    void reboundSides();

    void reboundBat();

    void hitRight();

    void hitLeft();

    void update();

};