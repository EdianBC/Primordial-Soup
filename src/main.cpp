#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

enum class ShapeType { Circle, Rectangle, Triangle };

sf::Shape* createRandomShape(const sf::Vector2f& position) {
    ShapeType type = static_cast<ShapeType>(std::rand() % 3);
    sf::Shape* shape = nullptr;

    switch (type) {
        case ShapeType::Circle: {
            float radius = 10 + std::rand() % 40;
            shape = new sf::CircleShape(radius);
            break;
        }
        case ShapeType::Rectangle: {
            float width = 20 + std::rand() % 80;
            float height = 20 + std::rand() % 80;
            shape = new sf::RectangleShape(sf::Vector2f(width, height));
            break;
        }
        case ShapeType::Triangle: {
            float size = 20 + std::rand() % 60;
            shape = new sf::CircleShape(size, 3);
            break;
        }
    }

    shape->setPosition(position);
    shape->setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
    return shape;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shapes");
    std::vector<sf::Shape*> shapes;

    sf::Font font;
    if (!font.loadFromFile("../resources/OpenSans-Regular.ttf")) { // Cambia el nombre si usaste otro archivo .ttf
        return -1;
    }

    sf::Text counterText;
    counterText.setFont(font);
    counterText.setCharacterSize(24);
    counterText.setFillColor(sf::Color::White);
    counterText.setPosition(10.f, 10.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    sf::Vector2f position(std::rand() % window.getSize().x, std::rand() % window.getSize().y);
                    shapes.push_back(createRandomShape(position));
                } else if (event.key.code == sf::Keyboard::D && !shapes.empty()) {
                    delete shapes.back();
                    shapes.pop_back();
                }
            }
        }

        window.clear();

        for (auto shape : shapes) {
            window.draw(*shape);
        }

        counterText.setString("Count: " + std::to_string(shapes.size()));
        window.draw(counterText);

        window.display();
    }

    // Cleanup shapes
    for (auto shape : shapes) {
        delete shape;
    }

    return 0;
}
