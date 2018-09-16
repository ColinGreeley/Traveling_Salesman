#include "window.h"
#include <iostream>

void renderWindow() {

	Array population;
	int generation = 0;
	float selectionRate = 0.3;
	float crossoverRate = 0.3;
	float mutationRate = 0.2;
	float flipRate = 0.3;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Traveling salesman", sf::Style::Fullscreen);
	sf::CircleShape city;
	sf::VertexArray lines(sf::LinesStrip, CITY_COUNT + 1);
	city.setRadius(4);
	city.setFillColor(sf::Color::Cyan);
	
	population.generatePopulation();
	population.shufflePopulation();
	
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
		
		population.getBestPathIndex();
		population.selection(selectionRate);
		population.crossover(crossoverRate);
		population.mutation(mutationRate);
		population.flip(flipRate);
		//population.printCityLocations();

		window.clear(sf::Color::Color(50, 50, 50)); 
		drawBestPath(population.cityList, lines, population.bestPathIndex, window);
		displayCities(population.cityList, city, window);
		window.display();

		generation++;
		std::cout << generation << std::endl;
	}
}

void displayCities(sf::Vector2i cities[][CITY_COUNT], sf::CircleShape tempShape, sf::RenderWindow& window) {

	for (int i = 0; i < CITY_COUNT; i++) {
		tempShape.setPosition(cities[0][i].x - 4, cities[0][i].y - 4);
		window.draw(tempShape);
	}
}

void drawBestPath(sf::Vector2i cities[][CITY_COUNT], sf::VertexArray lines, int index,  sf::RenderWindow& window) {

	int count = 0;

	for (int i = 0; i < CITY_COUNT; i++) {
		lines[count].position = sf::Vector2f(cities[index][i].x, cities[index][i].y);
		count++;
	}
	lines[count].position = sf::Vector2f(cities[index][0].x, cities[index][0].y);
	window.draw(lines);
}