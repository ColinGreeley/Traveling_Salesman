#include "array.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

void Array::generatePopulation() {

	srand(time(NULL));

	int randomX;
	int randomY;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		for (int j = 0; j < CITY_COUNT; j++) {

			randomX = rand() % 800 + 100;
			randomY = rand() % 800 + 200;

			cityList[i][j] = sf::Vector2i(randomX, randomY);
		}
	}
}

void Array::printCityLocations() {

	for (int i = 0; i < POPULATION_SIZE; i++) {
		for (int j = 0; j < CITY_COUNT; j++) {

			std::cout << cityList[i][j].x << ", " << cityList[i][j].y << " ";
		}
		std::cout << "\n";
	}
	std::cout << POPULATION_SIZE << " X " << CITY_COUNT << " matrix\n";
}

void Array::shufflePopulation() {

	for (int i = 0; i < POPULATION_SIZE; i++) {
		shuffleCities(i);
	}
}

void Array::shuffleCities(int rowNumber) {

	int random;
	int randomValues[CITY_COUNT];

	for (int i = 0; i < CITY_COUNT; i++) {
		random = rand() % 1000000000 + 1;
		randomValues[i] = random;
	}
	mergeSort(randomValues, CITY_COUNT);
}

void Array::merger(int arr[], int lo, int  mi, int hi) {

    int *temp = new int[hi - lo + 1];//temporary merger array
    int i = lo, j = mi + 1;//i is for left-hand,j is for right-hand
    int k = 0;//k is for the temporary array

    while(i <= mi && j <= hi) {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    //rest elements of left-half
    while(i <= mi)
        temp[k++] = arr[i++];
    //rest elements of right-half
    while(j <= hi)
        temp[k++] = arr[j++];
    //copy the mergered temporary array to the original array
    for(k = 0, i = lo; i <= hi; ++i, ++k)
        arr[i] = temp[k];
 
    delete []temp;
}

void Array::mergeSortHelper(int arr[], int lo, int hi) {

    int mid;
    if (lo < hi) {
        mid = (lo + hi) >> 1;
        mergeSortHelper(arr, lo, mid);
        mergeSortHelper(arr, mid+1, hi);
        merger(arr, lo, mid, hi);
    }
}

void Array::mergeSort(int arr[], int arr_size) {

    mergeSortHelper(arr, 0, arr_size-1);
}