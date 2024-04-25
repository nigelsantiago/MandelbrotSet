#include <iostream>
#include <complex>
#include <cmath>
#include <sstream>
#include <string>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;

int main()
{
    unsigned int desktop_w = VideoMode::getDesktopMode().width; // / 2;    //  /2
    unsigned int desktop_h = VideoMode::getDesktopMode().height; // / 2;    // divided by 2 temp edit only or use sep var?
    VideoMode vm(desktop_w, desktop_h);
    
    RenderWindow window(vm, "Mandelbrot Set", Style::Default);
    ComplexPlane complexPlane(desktop_w, desktop_h);
    
    Text text;
    Font font;
    if (!font.loadFromFile("fonts/Pixelate.ttf"))
    {
        cout << "Error loading font file." << endl;
    }
    text.setFont(font);
    text.setCharacterSize(30);
    text.setPosition(desktop_w/17.0f, desktop_h/11.5f);
    text.setFillColor(Color::White);
    text.setStyle(Text::Bold);

    while (window.isOpen())
	{
        Event event;
        while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) // fill in
            {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					complexPlane.zoomIn();
					complexPlane.setCenter({event.mouseButton.x, event.mouseButton.y});
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					complexPlane.zoomOut();
					complexPlane.setCenter({event.mouseButton.x, event.mouseButton.y});
				}
            }
            else if (event.type == Event::MouseMoved) // fill in
            {
				complexPlane.setMouseLocation({event.mouseMove.x, event.mouseMove.y}); // needs checking
            }
            else if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }
        
        complexPlane.updateRender();
        complexPlane.loadText(text);
        
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}
