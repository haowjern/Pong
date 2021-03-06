// Pong.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include <time.h>
#include <SFML\Audio.hpp>


int main() 
{
	// variables 
	int game_score_leftPaddle = 0;
	int game_score_rightPaddle = 0; 
	const int WINNING_SCORE = 3; 

	// functions declarations
	void GameOverDisplay(sf::RenderWindow &window, sf::Clock &clockInGame, sf::Text &text);

	enum game_states
	{
		game_over = 0,
		new_game = 1,
		current_game = 2,
	};

	game_states game_state;
	game_state = new_game; // default starting  value 

	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Pong Game", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	sf::Vector2u windowSize = window.getSize();

	// get time per frame 
	sf::Clock clockFrame;
	sf::Clock clockInGame;
	// initiate ball 
	float BALL_RADIUS = 20;
	sf::Vector2f CENTER_POSITION(windowSize / (unsigned int) 2);
	sf::Vector2f BALL_ORIGIN(BALL_RADIUS, BALL_RADIUS); 
	sf::Vector2f ball_pixel_moved(0., 0.); // pixels moved per second (x,y)
	float BALL_VEL_MULTIPLIER = 1.2f;
	Ball ball(BALL_RADIUS, sf::Color::White, CENTER_POSITION, BALL_ORIGIN);
	
	srand((uint16_t)time(NULL)); // initialise seed for random generator


	
	// initiate paddles
	sf::Vector2f PADDLE_SIZE(60, 200);
	sf::Vector2f PADDLE_SHAPE(PADDLE_SIZE.x, PADDLE_SIZE.y);
	sf::Vector2f PADDLE_LEFT_POS(0.f, windowSize.y / 2.f);
	sf::Vector2f PADDLE_LEFT_ORIGIN(0., PADDLE_SIZE.y / 2);

	sf::Vector2f PADDLE_RIGHT_POS(windowSize);
	PADDLE_RIGHT_POS.y /= 2; 
	sf::Vector2f PADDLE_RIGHT_ORIGIN(PADDLE_SIZE.x, PADDLE_SIZE.y / 2);

	Paddle paddleLeft(PADDLE_SIZE, sf::Color::White, PADDLE_LEFT_POS, PADDLE_LEFT_ORIGIN);
	Paddle paddleRight(PADDLE_SIZE, sf::Color::White, PADDLE_RIGHT_POS, PADDLE_RIGHT_ORIGIN);


	// load text
	// load fonts
	sf::Text text;
	sf::Font font;
	int TEXT_GAMEOVER_SIZE = 60;
	if (!font.loadFromFile("res/fonts/arial.ttf"))
	{
		std::cout << "font loading failed" << std::endl; 
	}
		text.setFont(font);
		text.setString("Game Over");
		text.setCharacterSize(TEXT_GAMEOVER_SIZE);
		text.setFillColor(sf::Color::Green);
		text.setStyle(sf::Text::Bold);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
		text.setPosition(windowSize.x/2.f, windowSize.y/2.f - 100.f);

	sf::Text text_score;
	int TEXT_SCORE_SIZE = 30;
	text_score.setFont(font);
	text_score.setCharacterSize(TEXT_SCORE_SIZE);
	text_score.setFillColor(sf::Color::Yellow);
	text_score.setStyle(sf::Text::Bold);
	text_score.setOrigin((float) TEXT_SCORE_SIZE, 0.f);
	text_score.setPosition(windowSize.x/2.f, 0);

	sf::Text s_PlayAgain; 
	int const S_PLAYAGAIN_SIZE = 45;
	s_PlayAgain.setFont(font);
	s_PlayAgain.setString("Press space to play again");
	s_PlayAgain.setCharacterSize(S_PLAYAGAIN_SIZE);
	s_PlayAgain.setFillColor(sf::Color::Yellow);
	s_PlayAgain.setStyle(sf::Text::Bold);
	sf::FloatRect s_PlayAgainRect = s_PlayAgain.getLocalBounds();
	s_PlayAgain.setOrigin(s_PlayAgainRect.left + s_PlayAgainRect.width / 2.0f, s_PlayAgainRect.top + s_PlayAgainRect.height / 2.0f);
	s_PlayAgain.setPosition(static_cast<sf::Vector2f>(windowSize/(unsigned int) 2));

	// load sounds 
	sf::SoundBuffer bufferPaddleHit;
	if (!bufferPaddleHit.loadFromFile("C:/Users/haowjern/Desktop/SFML/Pong/Pong/res/sounds/paddle_hit.wav"))
	{
		return -1;
	}

	sf::Sound soundPaddleHit;
	soundPaddleHit.setBuffer(bufferPaddleHit);

	sf::SoundBuffer bufferWallHit;
	if (!bufferWallHit.loadFromFile("C:/Users/haowjern/Desktop/SFML/Pong/Pong/res/sounds/wall_hit.wav"))
	{
		return -1;
	}

	sf::Sound soundWallHit;
	soundPaddleHit.setBuffer(bufferWallHit);

	sf::SoundBuffer bufferScoreHit;
	if (!bufferScoreHit.loadFromFile("C:/Users/haowjern/Desktop/SFML/Pong/Pong/res/sounds/score.wav"))
	{
		return -1;
	}

	sf::Sound soundScoreHit;
	soundScoreHit.setBuffer(bufferScoreHit);


	// 
	while (window.isOpen())
	{
		if (game_state == new_game)
		{
			// reset positions and speed 
			paddleLeft.setPosition(PADDLE_LEFT_POS);
			paddleRight.setPosition(PADDLE_RIGHT_POS);
			ball.setPosition(CENTER_POSITION);

			int ball_xVel = rand() % 400 + 300; // 300 to 700
			int ball_yVel = rand() % 100 + 150; // 100 to 250

			if (rand() % 2 == 0) // randomly choose direction of motion
			{
				ball_xVel = -ball_xVel;
			}

			if (rand() % 2 == 0) // randomly choose direction of motion 
			{
				ball_yVel = -ball_yVel;
			}
				
			
			int change_sign = rand() % 1;
			if (change_sign ==  1)
			{
				ball_xVel = -ball_xVel;
			}

			if (change_sign == 1)
			{
				ball_yVel = -ball_yVel;
			}

			ball_pixel_moved.x = (float) ball_xVel;
			ball_pixel_moved.y = (float) ball_yVel;
			game_state = current_game;
		}

		else if (game_state == current_game)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}

			// INPUT 
			// paddle left
			sf::Vector2f paddleLeft_pixelMoved(0., 0.);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				paddleLeft_pixelMoved.x = 0;
				paddleLeft_pixelMoved.y = -400;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				paddleLeft_pixelMoved.x = 0;
				paddleLeft_pixelMoved.y = +400;
			}

			// paddle right
			sf::Vector2f paddleRight_pixelMoved(0., 0.);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				paddleRight_pixelMoved.x = 0;
				paddleRight_pixelMoved.y = -400;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				paddleRight_pixelMoved.x = 0;
				paddleRight_pixelMoved.y = +400;
			}

			// UPDATE
			// check score
			if ((game_score_leftPaddle == WINNING_SCORE) || (game_score_rightPaddle == WINNING_SCORE))
			{
				game_state = game_over;
				continue;
			}

			sf::Time frame_time = clockFrame.restart();
			float delta_time = frame_time.asSeconds(); // seconds per frame

			// update bounds
			paddleLeft.updateBounds();
			paddleRight.updateBounds();
			ball.updateBounds();

			std::string tempString;
			tempString = std::to_string(game_score_leftPaddle) + " - " + std::to_string(game_score_rightPaddle);
			text_score.setString(tempString);

			sf::Vector2f new_pos = ball.getPosition();
			// check collision with upper and lower walls
			if (ball.checkCollision_topbtm((float) windowSize.y))
			{
				ball_pixel_moved.y = -ball_pixel_moved.y*BALL_VEL_MULTIPLIER;
				soundWallHit.play();

				// place ball to be within walls
				if (ball.getPosition().y < windowSize.y / 2) // ball is closer to top wall
				{
					new_pos.y = ball.getRadius();
				}

				else
				{
					new_pos.y = windowSize.y - ball.getRadius();
				}
			}

			// check collision with paddles 
			else if (ball.checkCollision(paddleLeft) || ball.checkCollision(paddleRight))
			{
				ball_pixel_moved.x = -ball_pixel_moved.x*BALL_VEL_MULTIPLIER;
				soundPaddleHit.play();

				//if ball is closer to the left paddle 
				if (ball.getPosition().x < windowSize.y/2)
				{
					new_pos.x = paddleLeft.getPosition().x + paddleLeft.getSize().x + ball.getRadius();
				}

				else
				{
					new_pos.x = paddleRight.getPosition().x - paddleRight.getSize().x - ball.getRadius();	
				}
			}

			else if (ball.checkCollision_leftright((float) windowSize.x))
			{
				soundScoreHit.play();
				if (ball_pixel_moved.x > 0) // if ball is moving right
				{
					game_score_leftPaddle += 1;
				}

				else
				{
					game_score_rightPaddle += 1;
				}
				game_state = new_game;
			}

			// place ball 
			ball.setPosition(new_pos);

			// this ensures movement speed is consistent across different fps as delta_time sums up to 1 second
			// new_pos = new position every second 
			sf::Vector2f ball_pos = ball_pixel_moved * delta_time;
			ball.move(ball_pos);

			sf::Vector2f paddleLeft_pos = paddleLeft_pixelMoved * delta_time;
			paddleLeft.move(paddleLeft_pos);

			sf::Vector2f paddleRight_pos = paddleRight_pixelMoved * delta_time;
			paddleRight.move(paddleRight_pos);

			// RENDER
			window.draw(ball);
			window.draw(paddleLeft);
			window.draw(paddleRight);
			window.draw(text_score);
		}

		else if (game_state == game_over)
		{
			// INPUT 
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Space)
					{
						game_state = new_game;
					}
					break;

				}
			}

			// UPDATE
			game_score_leftPaddle = 0;
			game_score_rightPaddle = 0;
			ball_pixel_moved.x = 0;
			ball_pixel_moved.y = 0;
			ball.setPosition(CENTER_POSITION);

			// DISPLAY
			window.draw(s_PlayAgain);
			GameOverDisplay(window, clockInGame, text);
		}

		window.display();
		window.clear(sf::Color::Black);
	}
    return 0;
}

void GameOverDisplay(sf::RenderWindow &window, sf::Clock &clockInGame, sf::Text &text)
{
	sf::Time game_over_time = clockInGame.getElapsedTime();
	if (game_over_time.asSeconds() < 0.50)
	{
		window.draw(text);
	}

	else if (game_over_time.asSeconds() > 1)
	{
		clockInGame.restart();
	}
}

