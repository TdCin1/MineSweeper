#include <iostream>
#include"C:/Users/Landon Agic/CLionProjects/MineSweeper/src/WelcomeWindow.h"
#include"C:/Users/Landon Agic/CLionProjects/MineSweeper/src/GameWindow.h"
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;

int main() {

    GameWindow window(15,30);
    window.loadDefault("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/face_happy.png", "Smile");
    window.smile.setPosition(300,300);
    /*
    sf::Texture text;
    sf::Sprite sprite;
    window.loadSprite(text, sprite,"C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/face_happy.png");
    window.smile = sprite;
     */

    sf::RenderWindow windowRender(sf::VideoMode((window.colCount * 32), (window.rowCount * 32) + 100), "Welcome Window");
    sf::Vector2u size = windowRender.getSize();
    while (windowRender.isOpen()) {

        //Sets up event
        sf::Event event;

        //Loop
        while (windowRender.pollEvent(event)) {

            //Closes Window
            if (event.type == sf::Event::Closed) {
                windowRender.close();
                return false;
            }
        }

        //Drawing
        windowRender.clear(sf::Color::Blue);
        sf::Sprite* temp = window.defaultSprites["Smile"];
        temp->setPosition(300,300);
        windowRender.draw(*temp);
        windowRender.display();
    }



    return 0;
}

