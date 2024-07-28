#pragma once

#include <SFML/Graphics.hpp>

float distance(sf::Vector2f right, sf::Vector2f left);

float distance(sf::Vector2f right, sf::Vector2f left)
{
    return sqrt((right.x - left.x) * (right.x - left.x) + (right.y - left.y) * (right.y - left.y));
}

float distance(sf::Vector2f vect)
{
    return sqrt(vect.x * vect.x + vect.y * vect.y);
}