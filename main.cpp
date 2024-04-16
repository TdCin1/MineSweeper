#include <iostream>
#include"C:/Users/Landon Agic/CLionProjects/MineSweeper/src/WelcomeWindow.h"
#include"C:/Users/Landon Agic/CLionProjects/MineSweeper/src/GameWindow.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

int main() {

    GameWindow window(15,30,10);
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
    window.getTexture("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/flag.png","flag");
    //TIME TEXTURES

    //TIMER SPRITES
    //TENS PLACE
    sf::Sprite timeSecondTen;
    sf::FloatRect Rect = timeSecondTen.getLocalBounds();
    timeSecondTen.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeSecondTen.setPosition((window.colCount*32)-54,32*(window.rowCount+.5)+16);

    //ONES PLACE
    sf::Sprite timeSecondOne;
    timeSecondOne.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeSecondOne.setPosition((window.colCount*32)-33,32*(window.rowCount+.5)+16);

    //MINUTES PLACE
    sf::Sprite timeMinuteTen;
    timeMinuteTen.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeMinuteTen.setPosition((window.colCount*32)-97,32*(window.rowCount+.5)+16);

    sf::Sprite timeMinuteOne;
    timeMinuteOne.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeMinuteOne.setPosition((window.colCount*32)-76,32*(window.rowCount+.5)+16);


    //FLAG COUNTER
    sf::Sprite flagCounterHundred;
    flagCounterHundred.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterHundred.setPosition(33,32*(window.rowCount+.5)+16);

    sf::Sprite flagCounterTen;
    flagCounterTen.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterTen.setPosition(54,32*(window.rowCount+.5)+16);

    sf::Sprite flagCounterOne;
    flagCounterOne.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterOne.setPosition(75,32*(window.rowCount+.5)+16);

    sf::Sprite flagCounterNegative;
    flagCounterNegative.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterNegative.setPosition(12,32*(window.rowCount+.5)+16);


    //TILES
    for(int i = 0;i<window.rowCount;i++){
        for(int j = 0;j<window.colCount;j++){
            GameWindow::Tile tile = window.getSpriteText(window.textureMap["tile_hidden"],16+(32*j),16+(32*i));
            tile.texture = "tile_hidden";
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

    //HANDLES NEIGHBORS
    for(int row = 0;row<window.rowCount;row++){
        for(int col = 0; col<window.colCount;col++){
            GameWindow::Tile* currentTile = &window.getTile(row,col);
            //TOP
            if(row==0){
                //TOP LEFT
                if(col==0){
                    currentTile->neighbors.push_back(&window.getTile(row+1,col));
                    currentTile->neighbors.push_back(&window.getTile(row+1,col+1));
                    currentTile->neighbors.push_back(&window.getTile(row,col+1));
                }
                //TOP RIGHT
                else if(col==(window.colCount-1)){
                    currentTile->neighbors.push_back(&window.getTile(row,col-1));
                    currentTile->neighbors.push_back(&window.getTile(row+1,col));
                    currentTile->neighbors.push_back(&window.getTile(row+1,col-1));
                }
                //TOP GENERAL
                else{
                    currentTile->neighbors.push_back(&window.getTile(row,col-1));
                    currentTile->neighbors.push_back(&window.getTile(row+1,col-1));
                    currentTile->neighbors.push_back(&window.getTile(row+1,col));
                    currentTile->neighbors.push_back(&window.getTile(row,col+1));
                    currentTile->neighbors.push_back(&window.getTile(row+1,col+1));
                }
            }
            //BOTTOM
            else if(row==(window.rowCount-1)){
                //BOTTOM LEFT
                if(col==0){
                    currentTile->neighbors.push_back(&window.getTile(row-1,col));
                    currentTile->neighbors.push_back(&window.getTile(row-1,col+1));
                    currentTile->neighbors.push_back(&window.getTile(row,col+1));
                }
                //BOTTOM RIGHT
                else if(col==(window.colCount-1)){
                    currentTile->neighbors.push_back(&window.getTile(row,col-1));
                    currentTile->neighbors.push_back(&window.getTile(row-1,col));
                    currentTile->neighbors.push_back(&window.getTile(row-1,col-1));
                }
                //BOTTOM GENERAL
                else{
                    currentTile->neighbors.push_back(&window.getTile(row,col-1));
                    currentTile->neighbors.push_back(&window.getTile(row-1,col-1));
                    currentTile->neighbors.push_back(&window.getTile(row-1,col));
                    currentTile->neighbors.push_back(&window.getTile(row,col+1));
                    currentTile->neighbors.push_back(&window.getTile(row-1,col+1));
                }
            }
            //LEFT SIDE
            else if(col == 0){
                currentTile->neighbors.push_back(&window.getTile(row+1,col));
                currentTile->neighbors.push_back(&window.getTile(row+1,col+1));
                currentTile->neighbors.push_back(&window.getTile(row,col+1));
                currentTile->neighbors.push_back(&window.getTile(row-1,col));
                currentTile->neighbors.push_back(&window.getTile(row-1,col+1));
            }
            //RIGHT SIDE
            else if(col==(window.colCount-1)){
                currentTile->neighbors.push_back(&window.getTile(row-1,col));
                currentTile->neighbors.push_back(&window.getTile(row-1,col-1));
                currentTile->neighbors.push_back(&window.getTile(row,col-1));
                currentTile->neighbors.push_back(&window.getTile(row+1,col-1));
                currentTile->neighbors.push_back(&window.getTile(row+1,col));
            }
            //MIDDLES
            else{
                currentTile->neighbors.push_back(&window.getTile(row-1,col-1));
                currentTile->neighbors.push_back(&window.getTile(row,col-1));
                currentTile->neighbors.push_back(&window.getTile(row+1,col-1));
                currentTile->neighbors.push_back(&window.getTile(row-1,col));
                currentTile->neighbors.push_back(&window.getTile(row+1,col));
                currentTile->neighbors.push_back(&window.getTile(row-1,col+1));
                currentTile->neighbors.push_back(&window.getTile(row,col+1));
                currentTile->neighbors.push_back(&window.getTile(row+1,col+1));
            }
        }
    }

    //SET MINES
    srand(time(0));
    for(int i=0;i<window.mineCount;i++){
        int row = rand()%15;
        int col = rand()&30;
        GameWindow::Tile* tile = &window.getTile(row,col);
        if(tile->isMine){
            if(row==0){
                row=row+1;
            }
            else{
                row = row-1;
            }
            tile = &window.getTile(row,col);
        }
        tile->isMine = true;
    }

    //Set up tile counts
    window.setupTileNums();

    //TIME
    auto start = chrono::high_resolution_clock::now();



    //MAIN LOOPS
    sf::RenderWindow windowRender(sf::VideoMode((window.colCount * 32), (window.rowCount * 32) + 100), "Welcome Window");

    while (windowRender.isOpen()) {

        //Sets up event
        sf::Event event;

        //TIMER
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        window.timeChanged = duration.count();


        if(!window.gameLost) {
            window.setTimeTextures(timeMinuteTen, timeMinuteOne, timeSecondTen, timeSecondOne, window.timeChanged);
        }






        window.flagCounter(flagCounterNegative,flagCounterHundred,flagCounterTen,flagCounterOne,window.flagCount);



        //Loop
        while (windowRender.pollEvent(event)) {


            //Closes Window
            if (event.type == sf::Event::Closed) {
                windowRender.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(windowRender);
                int row = floor(mousePosition.y / 32);
                int col = floor(mousePosition.x/32);
                //NOT A TILE
                if(row>=window.rowCount||col>=window.colCount){
                    cout<<"NOT A TILE";
                }
                //TILE
                else{
                    GameWindow::Tile* tile = &window.getTile(row,col);
                    //LEFT CLICK
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(tile->isMine){
                            if(tile->texture != "flag"){
                                window.triggerMines();
                                window.spriteMap["face_happy"].setTexture(window.textureMap["face_lose"]);
                            }
                        }
                        else{
                            window.displayNumber(tile);
                        }
                    }
                    //RIGHT CLICK
                    else if(event.mouseButton.button == sf::Mouse::Right){
                        window.flag(tile);
                    }
                }

            }
        }

        //Drawing
        windowRender.clear(sf::Color::White);
        windowRender.draw(window.spriteMap["face_happy"]);
        windowRender.draw(window.spriteMap["debug"]);
        windowRender.draw(window.spriteMap["pause"]);
        windowRender.draw(window.spriteMap["leaderboard"]);
        windowRender.draw(timeSecondTen);
        windowRender.draw(timeSecondOne);
        windowRender.draw(timeMinuteOne);
        windowRender.draw(timeMinuteTen);
        windowRender.draw(flagCounterHundred);
        windowRender.draw(flagCounterTen);
        windowRender.draw(flagCounterOne);
        windowRender.draw(flagCounterNegative);

        for(int i=0;i<window.tileVect.size();i++){
            windowRender.draw(window.tileVect.at(i).sprite);
        }
        windowRender.display();

    }



    return 0;
}

