#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "physics.hpp"
#include "renderer.hpp"

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Verlet Experiment", sf::Style::Default, settings);

    Solver solver;
    Renderer renderer{window};


    int refreshRate = 60;

    solver.setRefreshRate(refreshRate);

    window.setFramerateLimit(refreshRate);

    sf::Clock clock;
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
            sf::Time time = clock.getElapsedTime();
            if (time.asSeconds() >= 0.15f)
            {
                solver.addItem();
                clock.restart();
            }
        }
        solver.update();
        window.clear();
        renderer.render(solver);
        window.display();

    }

    solver.destroy();

    return 0;
}