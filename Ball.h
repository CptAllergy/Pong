#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;

    // A RectangleShape object called ref
    CircleShape ballShape;

    float xVelocity = .18f;
    float yVelocity = .18f;
    float centerX, centerY;

public:
    Ball(float startX, float startY, float centerX, float centerY);

    FloatRect getPosition();

    CircleShape getShape();

    Vector2f getCenter();

    float getXVelocity();

    void reboundSides();

    void reboundBat();

    void reboundBatY();

    void hitRight();

    void hitLeft();

    void update();

};