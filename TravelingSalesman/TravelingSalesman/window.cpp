#include "window.h"
#include <iostream>

void renderWindow() {

	Array population;
	int generation = 0;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Traveling salesman", sf::Style::Fullscreen);
	sf::CircleShape city;
	city.setRadius(5);
	city.setFillColor(sf::Color::White);
	
	population.generatePopulation();

	while (window.isOpen()) {

		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::Escape) {
					window.close();
					break;
				}
			}
		}
		
		window.clear(sf::Color::Color(50, 50, 50));
		displayCities(population.cityList, city, window);
		window.display();
		generation++;
		std::cout << generation << std::endl;
	}
}

void displayCities(sf::Vector2i cities[][CITY_COUNT], sf::CircleShape tempShape, sf::RenderWindow& window) {

	for (int i = 0; i < CITY_COUNT; i++) {
		tempShape.setPosition(cities[0][i].x - 5, cities[0][i].y - 5);
		window.draw(tempShape);
	}
}