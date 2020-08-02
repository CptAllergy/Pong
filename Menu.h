#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu
{
public:
	Menu(int width, int height);

	void draw(RenderWindow &window);
	void moveUp();
	void moveDown();
	int getItem();

private:
	int selectedItemID;
	Font font;
	Text text[3];
};