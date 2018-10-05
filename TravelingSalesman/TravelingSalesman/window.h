#pragma once
#include "array.h"
#include <SFML\Graphics.hpp>

void renderWindow();
void displayCities(sf::Vector2i **&cities, sf::CircleShape tempShape, sf::RenderWindow& window);
void drawBestPath(sf::Vector2i **&cities, sf::VertexArray lines, int index, sf::RenderWindow& window);
void eliminate(std::vector<Array> &n);
void checkConsecutiveValues(std::vector<Array> &n, bool b);