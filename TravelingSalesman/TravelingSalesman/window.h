#pragma once
#include "array.h"
#include <SFML\Graphics.hpp>

void renderWindow();
void displayCities(sf::Vector2i cities[][CITY_COUNT], sf::CircleShape tempShape, sf::RenderWindow& window);
void drawBestPath(sf::Vector2i cities[][CITY_COUNT], sf::VertexArray lines, int index, sf::RenderWindow& window);