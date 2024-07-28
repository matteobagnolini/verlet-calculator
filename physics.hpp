#pragma once

#include <SFML/Graphics.hpp>

#include "math.hpp"

// Class that models an object that follows Verlet integration rule

class VerletObject
{
public:
    sf::Vector2f position;
    sf::Vector2f position_last;
    sf::Vector2f acceleration;
    float radius;
    sf::Color color;

    VerletObject(sf::Vector2f initial_position, sf::Vector2f acceleration, float radius, sf::Color color)
    {
        this->position = initial_position;
        this->position_last = initial_position;
        this->acceleration = acceleration;
        this->radius = radius;
        this->color = color;
    }

    void updatePosition(float dt)
    {
        sf::Vector2f velocity = position - position_last;
        position_last = position;
        position = position + velocity + acceleration * dt * dt;
        std::cout << position.y - position_last.y << std::endl;
        acceleration = {};
    }

    void accelerate(sf::Vector2f acc)
    {
        acceleration += acc;
    }

};

// Vector containing all verlet objects

std::list<VerletObject*> objs;

// Class that solve collisions

class Solver
{
private:
    sf::Vector2f gravity = {0.f, 490.f};

public:
    void update(float dt)
    {
        applyGravity();
        updatePosition(dt);
        applyContraints();
        solveCollisions();
    }

    void updatePosition(float dt)
    {
        for (auto& obj : objs)
        {
            obj->updatePosition(dt);
        }

    }

    void applyGravity()
    {
        for (auto& obj : objs)
        {
            obj->accelerate(gravity);
        }
    }

    void applyContraints()
    {
        // Circular container
        sf::Vector2f center = {640.f, 360.f};
        float radius = 300.f;
        for (auto& obj : objs)
        {
            sf::Vector2f to_obj = obj->position - center;
            float dist = distance(to_obj);
            if (dist > radius - obj->radius)
            {
                sf::Vector2f norm = to_obj / dist;
                obj->position = center + norm * (radius - obj->radius);
            }
        }
    }

    void solveCollisions()
    {

    }
};
