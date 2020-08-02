#include <iostream>
#include "Ball.h"

// This the constructor and it is called when we create an object
Ball::Ball(float startX, float startY, float centerX, float centerY)
{
    position.x = startX;
    position.y = startY;

    this->centerX = centerX;
    this->centerY = centerY;

    ballShape.setRadius(12);
    ballShape.setPosition(position);
}

FloatRect Ball::getPosition()
{
    return ballShape.getGlobalBounds();
}

CircleShape Ball::getShape()
{
    return ballShape;
}

float Ball::getXVelocity()
{
    return xVelocity;
}

void Ball::reboundSides()
{
    yVelocity = -yVelocity;
}

void Ball::reboundBat()
{
    position.x -= (xVelocity * 30);
    xVelocity = -xVelocity;

}

void Ball::hitRight()
{
    position.y = centerY;
    position.x = centerX;
}

void Ball::hitLeft()
{
    position.y = centerY;
    position.x = centerX;
}

void Ball::update()
{
    // Update the ball position variables
    position.y += yVelocity;
    position.x += xVelocity;

    // Move the ball and the bat
    ballShape.setPosition(position);
}