#pragma once
#include <SFML\Audio.hpp>

#define CITY_COUNT 40
#define POPULATION_SIZE 1000

class Array {

public:
	
	sf::Vector2i cityList[POPULATION_SIZE][CITY_COUNT];
	float bestPathMag = 10000000;
	int bestPathIndex = 0;

	void generatePopulation();
	void printCityLocations();
	void shufflePopulation();

	void calculatePathMagnitudes(float pathSum[]);
	void getBestPathIndex();

	// genetic algorithm
	void selection(float selectionRate);
	void crossover(float crossoverRate);
	void mutation(float mutationRate);
	void flip(float flipRate);
};
