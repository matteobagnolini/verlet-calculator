#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "physics.hpp"

static void init();
static void update(float dt);
static void render();
static void destroy();

Solver solver;

sf::RenderWindow window(sf::VideoMode(1280, 720), "Verlet Experiment");

int main()
{
    window.setFramerateLimit(60);
    sf::Clock clock;
    sf::Clock ball_adding_clock;
    init();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            sf::Time time = ball_adding_clock.getElapsedTime();
            if (time.asSeconds() >= 0.15f)
            {
                init();
                ball_adding_clock.restart();
            }
        }
        float dt = clock.restart().asSeconds();
        update(dt);
        render();

    }

    destroy();

    return 0;
}

static void init()
{
    VerletObject* obj = new VerletObject(sf::Vector2f(400.f, 360.f), sf::Vector2f(1000000.f, 980.f), rand() % 10 + 5, sf::Color(rand() % 0xFFFF, rand() % 0xFFFF, rand() % 0xFFFF));
    objs.push_back(obj);
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