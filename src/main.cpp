#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace sf;
using namespace std;

// Función para calcular la distancia entre dos puntos
float distance(Vector2f a, Vector2f b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
    // Crear la ventana
    RenderWindow window(VideoMode(1200, 800), "Primordial Soup");

    // Cargar la fuente
    Font font;
    if (!font.loadFromFile("../resources/OpenSans-Regular.ttf"))
    {
        return -1;
    }

    // Crear el texto del título
    Text titleText;
    titleText.setFont(font);
    titleText.setString("Primordial Soup");
    titleText.setCharacterSize(36);
    titleText.setFillColor(Color::White);
    titleText.setStyle(Text::Bold);
    titleText.setPosition(850, 20); // Posición en el panel de datos

    // Crear el área de visualización del mapa
    RectangleShape mapArea(Vector2f(800, 800));
    mapArea.setFillColor(Color(50, 50, 50)); // Color gris oscuro
    mapArea.setPosition(0, 0);

    // Crear el panel de datos
    RectangleShape dataPanel(Vector2f(400, 800));
    dataPanel.setFillColor(Color(30, 30, 30)); // Color gris más oscuro
    dataPanel.setPosition(800, 0);

    // Semilla para números aleatorios
    srand(static_cast<unsigned>(time(0)));

    // Crear los círculos
    const int numCircles = 1000;
    vector<CircleShape> circles(numCircles);
    vector<Vector2f> velocities(numCircles);

    for (int i = 0; i < numCircles; ++i)
    {
        for (int i = 0; i < numCircles; ++i)
        {
            circles[i].setRadius(3.f);

            // Color aleatorio
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;
            circles[i].setFillColor(Color(r, g, b));

            // Posición aleatoria dentro del área del mapa
            float x = static_cast<float>(rand() % 800);
            float y = static_cast<float>(rand() % 800);
            circles[i].setPosition(x, y);

            // Dirección aleatoria
            float vx = (static_cast<float>(rand()) / RAND_MAX) * 2.f - 1.f;
            float vy = (static_cast<float>(rand()) / RAND_MAX) * 2.f - 1.f;
            velocities[i] = Vector2f(vx, vy);
        }
    }

    // Bucle principal
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        // Actualizar posiciones y gestionar colisiones
        for (int i = 0; i < numCircles; ++i)
        {
            Vector2f pos = circles[i].getPosition();
            pos += velocities[i];

            // Rebotar en los bordes del mapa
            if (pos.x <= 0 || pos.x >= 797)
                velocities[i].x = -velocities[i].x;
            if (pos.y <= 0 || pos.y >= 797)
                velocities[i].y = -velocities[i].y;

            // Actualizar la posición
            circles[i].setPosition(pos);
        }

        // Detectar y manejar colisiones entre partículas
        for (int i = 0; i < numCircles; ++i)
        {
            for (int j = i + 1; j < numCircles; ++j)
            {
                if (distance(circles[i].getPosition(), circles[j].getPosition()) <= 2 * circles[i].getRadius())
                {
                    // Intercambiar las velocidades (rebote elástico simple)
                    swap(velocities[i], velocities[j]);
                }
            }
        }

        window.clear();

        // Dibujar el área del mapa
        window.draw(mapArea);

        // Dibujar los círculos
        for (const auto &circle : circles)
        {
            window.draw(circle);
        }

        // Dibujar el panel de datos
        window.draw(dataPanel);

        // Dibujar el título del proyecto
        window.draw(titleText);

        window.display();
    }

    return 0;
}
