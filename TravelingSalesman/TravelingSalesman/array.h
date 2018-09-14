#pragma once
#include <SFML\Audio.hpp>

#define CITY_COUNT 30
#define POPULATION_SIZE 10

class Array {

public:
	
	sf::Vector2i cityList[POPULATION_SIZE][CITY_COUNT];
	void generatePopulation();
	void printCityLocations();
	void shufflePopulation();
	void shuffleCities(int rowNumber);
	void merger(int arr[], int lo, int  mi, int hi);
	void mergeSortHelper(int arr[], int lo, int hi);
	void mergeSort(int arr[], int arr_size);
};
