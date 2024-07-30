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

// Class that solve collisions

class Solver
{
private:
    
    float time = 0.0f;
    float frame_dt = 0.0f;
    int sub_steps = 8;
    sf::Vector2f gravity = {0.f, 980.f};

    std::vector<VerletObject*> objs;
    

public:
    void update()
    {
        time += frame_dt;
        float sub_dt = frame_dt / sub_steps;
        for (int i = 0; i < sub_steps; i++)
        {
            applyGravity();
            solveCollisions();
            applyContraints();
            updatePosition(sub_dt);
        }
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
        float response_coefficient = 0.70f;
        uint32_t object_count = objs.size();
        for (uint32_t i = 0; i < object_count; i++)
        {
            VerletObject* obj1 = objs.at(i);
            for (uint32_t j = i+1; j < object_count; j++)
            {
                VerletObject* obj2 = objs.at(j);
                sf::Vector2f coll_axis = obj1->position - obj2->position;
                float dist = distance(coll_axis);
                if (dist <= obj1->radius + obj2->radius)
                {
                    sf::Vector2f norm = coll_axis / dist;
                    float delta = response_coefficient * (obj1->radius + obj2->radius - dist);
                    obj1->position += 0.5f * delta * norm;
                    obj2->position -= 0.5f * delta * norm;
                }
            }
        }
    }

    void addItem()
    {
        VerletObject* obj = new VerletObject(sf::Vector2f(400.f, 360.f), sf::Vector2f(100000.f, 980.f), rand() % 10 + 5, sf::Color(rand() % 0xFFFF, rand() % 0xFFFF, rand() % 0xFFFF));
        objs.push_back(obj);

    }

    std::vector<VerletObject*> getItems()
    {
        return objs;
    }

    void setRefreshRate(int refreshRate)
    {
        this->frame_dt = 1.f / refreshRate;
    }

    void destroy()
    {
        for (auto& obj : objs)
        {
            delete obj;
        }
    }
};
