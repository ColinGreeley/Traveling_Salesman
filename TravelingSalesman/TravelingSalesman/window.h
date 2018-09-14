#pragma once
#include "array.h"
#include <SFML\Graphics.hpp>

void renderWindow();
void displayCities(sf::Vector2i cities[][CITY_COUNT], sf::CircleShape tempShape, sf::RenderWindow& window);