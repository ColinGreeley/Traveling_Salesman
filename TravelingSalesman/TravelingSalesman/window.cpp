#include "window.h"
#include <iostream>
#include <vector>

#define HEAP_SIZE 8

void renderWindow() {

	Array population;
	int generation = 0;
	float selectionRate = 0.1;
	float crossoverRate = 0.5;
	float mutationRate = 0.2;
	float flipRate = 0.2;

	std::vector<Array> heapSortList;
	for (int i = 0; i < HEAP_SIZE; i++) {
		Array *n = new Array;
		(*n).generatePopulation();
		(*n).shufflePopulation();
		heapSortList.push_back(*n);
	}

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
		window.clear(sf::Color::Color(50, 50, 50));

		for (int i = 0; i < heapSortList.size(); i++) {
			heapSortList[i].getBestPathIndex();
			heapSortList[i].selection(selectionRate);
			heapSortList[i].crossover(crossoverRate);
			heapSortList[i].mutation(mutationRate);
			heapSortList[i].flip(flipRate);
			drawBestPath(heapSortList[i].cityList, lines, heapSortList[i].bestPathIndex, window);
		}
		displayCities(heapSortList[0].cityList, city, window);
		window.display();

		if (generation % 50 == 0) 
			eliminate(heapSortList);
		
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

void eliminate(std::vector<Array> &n) {

	if (n.size() > 1) {
		for (int i = 0; i < n.size()-1; i+=2) {
			if (n[i].bestPathMag > n[i + 1].bestPathMag) {
				n.erase(n.begin() + i + 1);
			}
			else {
				n.erase(n.begin() + i);
			}
		}
	}
}