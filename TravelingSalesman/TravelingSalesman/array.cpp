#include "array.h"
#include <stdlib.h>
#include <iostream>
#include <random>
#include <math.h>

Array::Array() {

	cityList = new sf::Vector2i*[POPULATION_SIZE];
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		cityList[i] = new sf::Vector2i[CITY_COUNT];
	}
}

Array::~Array() {
	/*
	for (int i = 0; i < POPULATION_SIZE; i++) {
		delete[] cityList[i];
	}
	delete[] cityList;*/
}

void Array::generatePopulation() {

	srand(time(NULL));

	int randomX;
	int randomY;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		for (int j = 0; j < CITY_COUNT; j++) {

			if (i == 0) {
				randomX = rand() % 1700 + 100;
				randomY = rand() % 800 + 100;
				cityList[i][j] = sf::Vector2i(randomX, randomY);
			}
			else {
				cityList[i][j] = cityList[0][j];
			}
		}
	}
}

void Array::printCityLocations() {

	for (int i = 0; i < POPULATION_SIZE; i++) {
		for (int j = 0; j < CITY_COUNT; j++) {

			std::cout << cityList[i][j].x << "," << cityList[i][j].y << " ";
		}
		std::cout << "\n";
	}
	std::cout << POPULATION_SIZE << " X " << CITY_COUNT << " matrix\n";
}

void Array::shufflePopulation() {

	sf::Vector2i t1, t2;
	int r;

	for (int shuffleCount = 3; shuffleCount > 0; shuffleCount--) {
		for (int k = 0; k < POPULATION_SIZE; k++) {
			r = rand() % CITY_COUNT;
			for (int m = 0; m < CITY_COUNT; m++) {
				t1 = cityList[k][m];
				t2 = cityList[k][r];
				cityList[k][r] = t1;
				cityList[k][m] = t2;

			}
		}
	}
}

void Array::calculatePathMagnitudes(float pathMag[]) {


	for (int i = 0; i < POPULATION_SIZE; i++) {
		pathMag[i] = sqrt(pow(cityList[i][0].x - cityList[i][CITY_COUNT - 1].x, 2) + pow(cityList[i][0].y - cityList[i][CITY_COUNT - 1].y, 2));
	}
	for (int i = 0; i < POPULATION_SIZE; i++) {
		for (int j = 0; j < CITY_COUNT - 1; j++) {
			pathMag[i] += sqrt(pow(cityList[i][j + 1].x - cityList[i][j].x, 2) + pow(cityList[i][j + 1].y - cityList[i][j].y, 2));
		}
	}
}

void Array::getBestPathIndex() {

	float pathSum[POPULATION_SIZE];
	calculatePathMagnitudes(pathSum);

	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (pathSum[i] < bestPathMag) {
			bestPathIndex = i;
			v.bestPath = bestPathMag = pathSum[i];
		}
	}
}

void Array::checkConsecutiveEntries() {

	if (v.bestPath == bestPathMag) {
		v.count++;
	}
}

void Array::selection(float selectionRate) {

	int sRate = (int)(selectionRate * pow(10, 4));
	int random;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		random = rand() % 10000 + 1;
		if (random < sRate) {
			for (int j = 0; j < CITY_COUNT; j++) {
				cityList[i][j] = cityList[bestPathIndex][j];
			}
		}
	}
}

void Array::crossover(float crossoverRate) {

	int start, end, index;
	int cRate = (int)(crossoverRate * pow(10, 4));
	float random;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		random = rand() % 10000 + 1;
		if (random < cRate) {
			start = rand() % (CITY_COUNT-1) + 1;
			end = rand() % (CITY_COUNT-start) + (start + 1);
			index = rand() % (POPULATION_SIZE-1) + 1;
			if (i != index && i != bestPathIndex) {
				for (int j = 0; j < CITY_COUNT; j++) {
					if (j < (end - start)) {
						cityList[i][j] = cityList[index][j + start];
					}
					else if ((j > (end - start) - 1) && (j < start + (end - start))) {
						cityList[i][j] = cityList[index][j - (end - start)];
					}
					else {
						cityList[i][j] = cityList[index][j];
					}
				}
			}
		}
	}
}

void Array::mutation(float mutationRate) {

	int random, index1, index2;
	int mRate = (int)(mutationRate * pow(10, 4));
	sf::Vector2i temp;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		random = rand() % 10000 + 1;
		index1 = rand() % (CITY_COUNT - 1);
		index2 = rand() % (CITY_COUNT - 1);
		if (random < mRate && i != bestPathIndex) {
			temp = cityList[i][index1];
			cityList[i][index1] = cityList[i][index2];
			cityList[i][index2] = temp;
		}
	}
}

void Array::flip(float flipRate) {

	int start, end, random;
	int fRate = (int)(flipRate * pow(10, 4));
	sf::Vector2i temp;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (i != bestPathIndex) {
			random = rand() % 10000 + 1;
			if (random < fRate) {
				start = rand() % CITY_COUNT;
				end = rand() % (CITY_COUNT - start) + (start);
				for (int j = 0; j < (end - start) / 2; j++) {
					if (start < end) {
						temp = cityList[i][start];
						cityList[i][start] = cityList[i][end];
						cityList[i][end] = temp;
						start++;
						end--;
					}
				}
			}
		}
	}
}
