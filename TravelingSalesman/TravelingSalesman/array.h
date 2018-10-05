#pragma once
#include <SFML\Audio.hpp>

#define CITY_COUNT 50
#define POPULATION_SIZE 100

typedef struct {

	int count = 0;
	float bestPath = 0;

} ConsecutiveValue;

class Array {

public:
	
	sf::Vector2i** cityList;
	float bestPathMag = 10000000;
	int bestPathIndex = 0;
	ConsecutiveValue v;
	
	Array();
	~Array();

	void generatePopulation();
	void printCityLocations();
	void shufflePopulation();

	void calculatePathMagnitudes(float pathSum[]);
	void getBestPathIndex();
	void checkConsecutiveEntries();

	// genetic algorithm
	void selection(float selectionRate);
	void crossover(float crossoverRate);
	void mutation(float mutationRate);
	void flip(float flipRate);
};
