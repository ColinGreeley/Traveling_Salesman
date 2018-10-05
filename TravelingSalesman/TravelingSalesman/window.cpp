#include "window.h"
#include <iostream>
#include <vector>

#define MERGE_SIZE 1024  // values of 2^n
#define ELIMINATION_THRESHOLD 3

void renderWindow() {

	int generation = 0;
	float selectionRate = 0.3;
	float crossoverRate = 0.5;
	float mutationRate = 0.2;
	float flipRate = 0.2;

	bool eliminate = true;
	std::vector<Array> mergeSortList;
	for (int i = 0; i < MERGE_SIZE; i++) {
		Array n;
		n.generatePopulation();
		n.shufflePopulation();
		mergeSortList.push_back(n);
	}

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Traveling salesman", sf::Style::Fullscreen);
	sf::CircleShape city;
	sf::VertexArray lines(sf::LinesStrip, CITY_COUNT + 1);
	city.setRadius(4);
	city.setFillColor(sf::Color::Cyan);

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

		for (int i = 0; i < mergeSortList.size(); i++) {
			mergeSortList[i].getBestPathIndex();
			mergeSortList[i].selection(selectionRate);
			mergeSortList[i].crossover(crossoverRate);
			mergeSortList[i].mutation(mutationRate);
			mergeSortList[i].flip(flipRate);
			mergeSortList[i].checkConsecutiveEntries();
			drawBestPath(mergeSortList[i].cityList, lines, mergeSortList[i].bestPathIndex, window);
		}
		displayCities(mergeSortList[0].cityList, city, window);
		window.display();

		checkConsecutiveValues(mergeSortList, eliminate);
		//if (generation % 50 == 0) 
			//eliminate(mergeSortList);
		
		generation++;
		std::cout << generation << std::endl;
		
	}
}

void displayCities(sf::Vector2i **&cities, sf::CircleShape tempShape, sf::RenderWindow& window) {

	for (int i = 0; i < CITY_COUNT; i++) {
		tempShape.setPosition(cities[0][i].x - 4, cities[0][i].y - 4);
		window.draw(tempShape);
	}
}

void drawBestPath(sf::Vector2i **&cities, sf::VertexArray lines, int index,  sf::RenderWindow& window) {

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

void checkConsecutiveValues(std::vector<Array> &n, bool b) {

	b = true;

	for (int i = 0; i < n.size(); i++) {
		if (n[i].v.count < ELIMINATION_THRESHOLD && b == true)
			b = false;
	}

	if (b == true) {
		for (int i = 0; i < n.size(); i++)
			n[i].v.count = 0;
		eliminate(n);
	}
}