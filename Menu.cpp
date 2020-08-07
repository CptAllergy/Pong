#include "Menu.h"

Menu::Menu(int width, int height) 
{

	font.loadFromFile("DS-DIGIT.ttf");
	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::White);
		text[i].setPosition(sf::Vector2f((width / 2), (height / 4) * (i + 1)));
		text[i].setCharacterSize(50);
	}

	text[0].setFillColor(sf::Color::Red);
	text[0].setString("Player VS PC");
	text[1].setString("Player VS Player");
	text[2].setString("Exit");

	selectedItemID = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(text[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemID > 0)
	{
		text[selectedItemID].setFillColor(sf::Color::White);
		selectedItemID--;
		text[selectedItemID].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemID < 2)
	{
		text[selectedItemID].setFillColor(sf::Color::White);
		selectedItemID++;
		text[selectedItemID].setFillColor(sf::Color::Red);
	}

}

int Menu::getItem()
{
	return selectedItemID;
}