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

    uint32_t ball_counter = 0;
    sf::Font font;
    font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");
    sf::Text text;
    text.setFont(font);

    int refreshRate = 60;

    solver.setRefreshRate(refreshRate);

    window.setFramerateLimit(refreshRate);

    sf::Clock clock;
    sf::Clock fps_clock;
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
            if (time.asSeconds() >= 0.01f)
            {
                solver.addItem();
                clock.restart();
                ball_counter++;
                text.setString(std::to_string(ball_counter));
            }
        }

        std::cout << 1 / fps_clock.restart().asSeconds() << std::endl;

        solver.update();
        window.clear();
        renderer.render(solver);
        window.draw(text);
        window.display();

    }

    solver.destroy();

    return 0;
}