#include <iostream>
#include"C:/Users/Landon Agic/CLionProjects/MineSweeper/src/WelcomeWindow.h"
#include"C:/Users/Landon Agic/CLionProjects/MineSweeper/src/GameWindow.h"
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;

int main() {

    GameWindow window(15,30);
    //STARTING SPRITES
    sf::Sprite face_happy = window.getSpriteFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/face_happy.png",
                                                 "face_happy", ((window.colCount/2)*32)-32, 32*(window.rowCount+.5)+32);
    sf::Sprite debug = window.getSpriteFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/debug.png",
                                            "debug", (window.colCount*32)-304, 32*(window.rowCount+.5)+32);
    sf::Sprite leaderboard = window.getSpriteFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/leaderboard.png",
                                                  "leaderboard", (window.colCount*32)-176,32*(window.rowCount+.5)+32);
    sf::Sprite pause = window.getSpriteFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/pause.png",
                                            "pause", (window.colCount*32)-240, 32*(window.rowCount+.5)+32);
    //TEXTURES
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/face_lose.png","face_lose");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/face_win.png","face_win");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_1.png","1");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_2.png","2");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_3.png","3");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_4.png","4");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_5.png","5");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_6.png","6");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_7.png","7");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/number_8.png","8");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/mine.png","mine");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/tile_hidden.png","tile_hidden");
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/tile_revealed.png","tile_revealed");

    //TILES
    for(int i = 0;i<window.rowCount;i++){
        for(int j = 0;j<window.colCount;j++){
            GameWindow::Tile tile = window.getSpriteText(window.textureMap["tile_hidden"],16+(32*j),16+(32*i));
            window.tileVect.push_back(tile);
        }
    }
    for(int i =0;i<window.tileVect.size();i++){
         int row = i/window.colCount;
         int rowStart = (((row+1)*window.colCount)-(window.colCount-1))-1;
         int col = i - rowStart;
         window.tileVect.at(i).row = row;
         window.tileVect.at(i).col = col;
    }



    sf::RenderWindow windowRender(sf::VideoMode((window.colCount * 32), (window.rowCount * 32) + 100), "Welcome Window");

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
        windowRender.clear(sf::Color::White);
        windowRender.draw(window.spriteMap["face_happy"]);
        windowRender.draw(window.spriteMap["debug"]);
        windowRender.draw(window.spriteMap["pause"]);
        windowRender.draw(window.spriteMap["leaderboard"]);
        window.changeTexture(window.getTile(14,1),"mine");
        for(int i=0;i<window.tileVect.size();i++){
            windowRender.draw(window.tileVect.at(i).sprite);
        }
        windowRender.display();
    }



    return 0;
}

