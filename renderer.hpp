#include <SFML/Graphics.hpp>

class Renderer
{
private:
    sf::RenderTarget& window;

public:
    Renderer (sf::RenderTarget& wd)
    : window{wd}
    {}

    void render(Solver solver)
    {
        sf::CircleShape constr;
        constr.setOrigin(300.f, 300.f);
        constr.setPosition(640.f, 360.f);
        constr.setRadius(300.f);
        constr.setOutlineColor(sf::Color::Green);
        window.draw(constr);

        for (auto& obj : solver.getItems())
        {
            sf::CircleShape circle(obj->radius);
            circle.setOrigin(obj->radius, obj->radius);
            circle.setPosition(obj->position);
            circle.setFillColor(obj->color);
            window.draw(circle);
        }
    }
};