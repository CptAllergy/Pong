#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f position;

	// A RectangleShape object
	RectangleShape batShape;

	float batSpeed;

public:
	Bat(float startX, float startY);
	Bat(float startX, float startY, float batSpeed);

	FloatRect getPosition();

	RectangleShape getShape();

	void moveUp();

	void moveDown();

	void update();

};