#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "physics.hpp"

static void init();
static void update(float dt);
static void render();
static void destroy();

Solver solver;

sf::RenderWindow window(sf::VideoMode(1280, 720), "Verlet Experiment");

int main()
{
    window.setFramerateLimit(160);
    sf::Clock clock;
    
    init();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        float dt = clock.restart().asSeconds() * 2;
        update(dt);
        render();

    }

    destroy();

    return 0;
}

static void init()
{
    VerletObject* obj = new VerletObject(sf::Vector2f(700.f, 360.f), sf::Vector2f(0.f, 9.8f), 25.f, sf::Color::Green);
    objs.push_front(obj);

    obj = new VerletObject(sf::Vector2f(600.f, 500.f), sf::Vector2f(0.f, 9.8f), 25.f, sf::Color::Green);
    objs.push_front(obj);


    obj = new VerletObject(sf::Vector2f(800.f, 250.f), sf::Vector2f(0.f, 9.8f), 25.f, sf::Color::Green);
    objs.push_front(obj);

}

static void update(float dt)
{
    solver.update(dt);
}

static void render()
{
    window.clear();
    sf::CircleShape constr;
    constr.setOrigin(300.f, 300.f);
    constr.setPosition(640.f, 360.f);
    constr.setRadius(300.f);
    constr.setOutlineColor(sf::Color::Green);
    window.draw(constr);

    for (auto& obj : objs)
    {
        sf::CircleShape circle(obj->radius);
        circle.setOrigin(obj->radius, obj->radius);
        circle.setPosition(obj->position);
        circle.setFillColor(obj->color);
        window.draw(circle);
    }
    window.display();
}

static void destroy()
{
    for (auto& obj : objs)
    {
        delete obj;
    }
}