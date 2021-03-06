// These "include" code from the C++ library and SFML too
#include <iostream>
#include "Bat.h"
#include "Ball.h"
#include "Menu.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Avoid having to put sf in front of all the SFML classes and functions
using namespace sf;

int windowWidth = 1920;
int windowHeight = 1080;
int score1 = 0;
int score2 = 0;
bool isAIOn = true;

//Window with the title "Pong"
RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

Menu menu(windowWidth, windowHeight);

sf::SoundBuffer buffer;
sf::Sound sound;


// create a bat
Bat bat(windowWidth - 50, windowHeight / 2);

Bat bat2(50, windowHeight / 2, 0.15f);

// create a ball
Ball ball(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);

// Create a "Text" object called "hud". Weird but we will learn about objects soon
Text hud;

// We need to choose a font
Font font;

enum State
{
	STATE_AI,
	STATE_2,
	STATE_MENU,
};

State state = STATE_MENU;

void playRandomSound()
{
	int r = std::rand() % 3;
	switch (r)
	{
	case 0:
		buffer.loadFromFile("pongblipf5.wav");
		break;
	case 1:
		buffer.loadFromFile("pongblipf4.wav");
		break;
	case 2:
		buffer.loadFromFile("pongblipf3.wav");
		break;
	}
	sound.setBuffer(buffer);
	sound.play();
}

void gameFunction()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			// Someone closed the window- bye
			window.close();
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Escape)
			{
				state = STATE_MENU;
				score1 = 0;
				score2 = 0;
				bat.getShape().setPosition(windowWidth - 50, windowHeight / 2);
				bat2.getShape().setPosition(50, windowHeight / 2);
				ball.getShape().setPosition(windowWidth / 2, windowHeight / 2);
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && bat.getPosition().top >= 7)
	{
		bat.moveUp();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && bat.getPosition().top + bat.getPosition().height <= (windowHeight - 7))
	{
		bat.moveDown();
	}

	if (Keyboard::isKeyPressed(Keyboard::W) && bat2.getPosition().top >= 7 && !isAIOn)
	{
		bat2.moveUp();
	}
	else if (Keyboard::isKeyPressed(Keyboard::S) && bat2.getPosition().top + bat2.getPosition().height <= (windowHeight - 7) && !isAIOn)
	{
		bat2.moveDown();
	}

	if (bat2.getPosition().top >= 7 && isAIOn)
	{
		if ((bat2.getPosition().top + (bat2.getPosition().height / 2)) > ball.getPosition().top)
		{
			bat2.moveUp();
		}
	}
	if (bat2.getPosition().top + bat2.getPosition().height <= (windowHeight - 7) && isAIOn)
	{
		if ((bat2.getPosition().top + (bat2.getPosition().height / 2)) < ball.getPosition().top)
		{
			bat2.moveDown();
		}
	}

	// Handle ball hitting right
	if (ball.getPosition().left >= windowWidth)
	{
		// reverse the ball direction
		ball.hitRight();
		score1++;
	}

	// Handle ball hitting left
	if (ball.getPosition().left <= 0)
	{
		// reverse the ball direction
		ball.hitLeft();
		score2++;
	}


	// Handle ball hitting sides
	if (ball.getPosition().top <= 0 || ball.getPosition().top + 10 > windowHeight)
	{
		playRandomSound();
		ball.reboundSides();
	}

	// Has the ball hit the bat?
	if (ball.getPosition().intersects(bat.getPosition()) && ball.getCenter().x < bat.getPosition().left + (bat.getPosition().width / 2))
	{
		playRandomSound();

		// Hit detected so reverse the ball
		if (ball.getCenter().y >= (bat.getPosition().top + bat.getPosition().height))
		{
			ball.reboundBatY();
		}
		else if (ball.getCenter().y <= bat.getPosition().top)
		{
			ball.reboundBatY();
		}
		else
		{
			ball.reboundBat();
		}
	}

	if (ball.getPosition().intersects(bat2.getPosition()) && ball.getCenter().x > bat2.getPosition().left + (bat2.getPosition().width / 2))
	{
		playRandomSound();

		// Hit detected so reverse the ball
		if (ball.getCenter().y >= (bat2.getPosition().top + bat2.getPosition().height))
		{
			ball.reboundBatY();
		}
		else if (ball.getCenter().y <= bat2.getPosition().top)
		{
			ball.reboundBatY();
		}
		else
		{
			ball.reboundBat();
		}
	}

	ball.update();
	bat.update();
	bat2.update();

	// Update the HUD text
	std::stringstream ss;
	ss << "Left:" << score1 << "      Right:" << score2;
	hud.setString(ss.str());

	// Clear everything from the last frame
	window.clear(Color(197, 174, 238, 255));

	window.draw(bat.getShape());
	window.draw(bat2.getShape());
	window.draw(ball.getShape());

	// Draw our score
	window.draw(hud);
}

void gameMenu()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			// Someone closed the window- bye
			window.close();
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Up)
			{
				menu.moveUp();
			}
			else if (event.key.code == Keyboard::Down)
			{
				menu.moveDown();
			}
			else if (event.key.code == Keyboard::Escape)
			{
				window.close();
			}
			else if (event.key.code == Keyboard::Return)
			{
				switch (menu.getItem())
				{
				case 0:
					state = STATE_AI;
					break;
				case 1:
					state = STATE_2;
					break;
				case 2:
					window.close();
					break;
				}
			}
		}
	}

	window.clear(Color(197, 174, 238, 255));
	menu.draw(window);
}

// This is where our game starts from
int main()
{
	// http://www.dafont.com/theme.php?cat=302
	font.loadFromFile("DS-DIGIT.ttf");

	buffer.loadFromFile("pongblipf5.wav");

	// Set the font to our message
	hud.setFont(font);

	std::srand(std::time(nullptr));

	// Make it really big
	hud.setCharacterSize(50);

	// Choose a color
	hud.setFillColor(sf::Color::White);

	// This "while" loop goes round and round- perhaps forever
	while (window.isOpen())
	{
		switch (state)
		{
		case STATE_AI:
			isAIOn = true;
			gameFunction();
			break;
		case STATE_2:
			isAIOn = false;
			gameFunction();
			break;
		case STATE_MENU:
			gameMenu();
			break;
		default:
			break;
		}

		// Show everything we just drew
		window.display();
		 

	}// This is the end of the "while" loop

	return 0;
}