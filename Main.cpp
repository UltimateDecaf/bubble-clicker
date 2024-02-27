#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <random>
#include <vector>

int main()
{

	// define some constants
	const float wWidth = 1000;
	const float wHeight = 1200;
	const float timeLimitInSeconds = 30.f;
	const float bRadius = 40.f;
	const sf::Color bColorDefault = sf::Color::Cyan;
	const sf::Color bColorClicked = sf::Color::White;

	// create the window of the application
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Bubble Clicker",
							sf::Style::Titlebar | sf::Style::Close); //  the window cannot be resized or maximized
	window.setFramerateLimit(60);

	// load the font used in the game
	sf::Font myFont;
	if (!myFont.loadFromFile("C:/libraries/SFML-2.6.1/fonts/pixeloidmono.ttf"))
		return EXIT_FAILURE;  

	// load the sound used in the game
	sf::SoundBuffer soundBuffer;
	if (!soundBuffer.loadFromFile("pop.wav"))
	    return EXIT_FAILURE;
	 sf::Sound popSound;
	 popSound.setBuffer(soundBuffer);

	
	

	// create score variable
	int score = 0;


	// create score text
	sf::Text scoreText("Score: " + std::to_string(score), myFont, 32);
	sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setOrigin(sf::Vector2f(scoreTextBounds.width / 2, scoreTextBounds.height / 2));
	scoreText.setPosition(wWidth / 2 , scoreTextBounds.height);

	// create text to show outside of game state
	sf::Text pauseText("Press LMB To Start", myFont, 32);
	sf::FloatRect pauseTextBounds = pauseText.getLocalBounds();
	pauseText.setOrigin(sf::Vector2f(pauseTextBounds.width / 2, pauseTextBounds.height / 2));
	pauseText.setPosition(wWidth / 2, wHeight / 2 - pauseTextBounds.height);

	// set game clock and time limit
	sf::Clock clock;
	float seconds = clock.getElapsedTime().asSeconds();
	float secondsLeft = timeLimitInSeconds;

	// create text to show elapsed time
	sf::Text clockText("Time elapsed: " + std::to_string(static_cast<int>(secondsLeft)), myFont, 32);
	sf::FloatRect clockTextBounds = clockText.getLocalBounds();
	clockText.setOrigin(sf::Vector2f(clockTextBounds.width / 2, clockTextBounds.height / 2));
	clockText.setPosition(wWidth / 2, clockTextBounds.height + scoreTextBounds.height + 10);

	// create bubble 
	sf::CircleShape bubble;
	bubble.setRadius(bRadius);
	bubble.setFillColor(bColorDefault);
	bubble.setOrigin(bRadius, bRadius);

	// create bounds for bubbles
	sf::RectangleShape bubbleGameField;
	float gameFieldWidth = wWidth - (50 + 50);
	float gameFieldHeight = wHeight - (scoreTextBounds.height + clockTextBounds.height * 3 + 30); // 20 extra padding on top, and 30 extra padding on the bottom
	float gameFieldXPosition = 50 + gameFieldWidth / 2;
	float gameFieldYPosition = scoreTextBounds.height + clockTextBounds.height + 60 + gameFieldHeight / 2;
	bubbleGameField.setSize(sf::Vector2f(gameFieldWidth, gameFieldHeight));
	bubbleGameField.setOutlineThickness(5);
	bubbleGameField.setOutlineColor(sf::Color::White);
	bubbleGameField.setFillColor(sf::Color(11, 11, 69));
	bubbleGameField.setOrigin(gameFieldWidth / 2, gameFieldHeight / 2);
	bubbleGameField.setPosition(gameFieldXPosition, gameFieldYPosition);
	std::cout << bubbleGameField.getPosition().x << " " << bubbleGameField.getPosition().y;
	

	// generate random positions for the bubble
	std::vector<sf::Vector2f>           bubblePositions;
	size_t                              currentVectorCounter = 0;
	std::random_device                  rd;
	std::mt19937                        gen(rd());
	std::uniform_int_distribution<int>  distrib(gameFieldXPosition / 2 + (bRadius * 2), gameFieldYPosition * 1.5f - (bRadius * 2));
	for (size_t i = 0; i < 100; i++)
	{

		unsigned int x = distrib(gen);
		unsigned int y = distrib(gen);
		bubblePositions.push_back(sf::Vector2f(x, y));
	}

	bool isPlaying = false;
	while(window.isOpen())
	{
		if (isPlaying)
		{
			secondsLeft = timeLimitInSeconds - seconds;
			seconds = clock.getElapsedTime().asSeconds();
			clockText.setString("Time elapsed: " + std::to_string(static_cast<int>(secondsLeft)));
		}
		if(!isPlaying)
		{
			clock.restart();
			secondsLeft = timeLimitInSeconds - seconds;
		}
		// Handle events
		sf::Event event;
		while(window.pollEvent(event))
		{
			// If close button pressed, window closes
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}

			// Game starts, whenever player presses LMB 
			if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				if(!isPlaying)
				{
					currentVectorCounter = 0;
					isPlaying = true;
					clock.restart();
					seconds = clock.getElapsedTime().asSeconds();
					if(score > 0)
					{
						score = 0;
						scoreText.setString("Score: " + std::to_string(score));
					}
				}
				if (isPlaying && secondsLeft >= 0) 
				{
					bubble.setPosition(bubblePositions[currentVectorCounter]);
#pragma region BoundsCheckVariables
					bool checkXbounds = sf::Mouse::getPosition(window).x >= bubble.getPosition().x - bRadius
						&& sf::Mouse::getPosition(window).x <= bubble.getPosition().x + bRadius;
					bool checkYbounds = sf::Mouse::getPosition(window).y >= bubble.getPosition().y - bRadius
						&& sf::Mouse::getPosition(window).y <= bubble.getPosition().y + bRadius;
#pragma endregion
					// check if mouse click is within bubble's bounds
					if (checkXbounds && checkYbounds)
					{
						// update score's variable and UI
						popSound.play();
						score++;
						scoreText.setString("Score: " + std::to_string(score));

						// update bubble position
						if (currentVectorCounter < bubblePositions.size())
						{
							currentVectorCounter++;
						}
						else
						{
							currentVectorCounter = 0;
						}

						bubble.setPosition(bubblePositions[currentVectorCounter]);
						std::cout << bubble.getPosition().x << " " << bubble.getPosition().y << "\n";
					}
					
				 }
			}
		}

		if(isPlaying && secondsLeft <= 0)
		{
			isPlaying = false;
		}
		
		window.clear();
		
		if(!isPlaying && score > 0)
		{
			
			pauseText.setString("Game over! You clicked on " + std::to_string(score) + " bubbles! \n    Double click LMB to try again" );
			pauseTextBounds = pauseText.getLocalBounds();
			pauseText.setOrigin(pauseTextBounds.width / 2, pauseTextBounds.height / 2);
		}

		if(!isPlaying){ window.draw(pauseText); }
		if (isPlaying) 
		{ 
			window.draw(scoreText);
			window.draw(bubbleGameField);
			window.draw(clockText);
			window.draw(bubble); 
		}
		window.display();
	}

	return 0;
}