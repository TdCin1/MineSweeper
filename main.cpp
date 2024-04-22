#include <iostream>
#include"src/WelcomeWindow.h"
#include"src/GameWindow.h"
#include"src/Leaderboard.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

int main() {
    WelcomeWindow welcome(15, 30);
    Leaderboard leaderboard(15,30);
    leaderboard.readData();
    leaderboard();


    if (true) {
        GameWindow window(15, 30, 10);

        //MAIN LOOPS
        while (window.displayWindow->isOpen()) {

            //Sets up event
            sf::Event event;

            //TIMER
            window.Time();


            if (!window.gameLost && !window.gameWon) {
                window.setTimeTextures(window.spriteMap["timeMinuteTen"], window.spriteMap["timeMinuteOne"],
                                       window.spriteMap["timeSecondTen"], window.spriteMap["timeSecondOne"],
                                       window.timeChanged);
            } else if (window.gameWon) {
                window.timeFinal = window.timeChanged;
            }


            window.flagCounter(window.spriteMap["flagCounterNegative"], window.spriteMap["flagCounterHundred"],
                               window.spriteMap["flagCounterTen"], window.spriteMap["flagCounterOne"],
                               window.flagCount);



            //Loop
            while (window.displayWindow->pollEvent(event)) {


                //Closes Window
                if (event.type == sf::Event::Closed) {
                    window.displayWindow->close();
                    return false;
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePosition = window.getMousePosition();
                    int row = floor(mousePosition.y / 32);
                    int col = floor(mousePosition.x / 32);

                    //NOT A TILE
                    if (row >= window.rowCount || col >= window.colCount) {
                        float faceStartX = ((window.colCount / 2) * 32) - 64;
                        float faceStartY = 32 * (window.rowCount + .5);
                        float debugStartX = (window.colCount * 32) - 336;
                        float debugStartY = 32 * (window.rowCount + .5);
                        float LeaderboardStartX = (window.colCount * 32) - 208;
                        float LeaderboardStartY = 32 * (window.rowCount + .5);
                        float pauseStartX = (window.colCount * 32) - 272;
                        float pauseStartY = 32 * (window.rowCount + .5);


                        if (event.mouseButton.button == sf::Mouse::Left) {
                            //SMILEY HIT
                            if ((faceStartX <= mousePosition.x && mousePosition.x <= faceStartX + 64) &&
                                (faceStartY <= mousePosition.y && mousePosition.y <= faceStartY + 64)) {
                                cout << "SMIELY HIT" << endl;
                                window.Reset();
                            }
                                //DEBUG HIT
                            else if ((debugStartX <= mousePosition.x && mousePosition.x <= debugStartX + 64) &&
                                     (debugStartY <= mousePosition.y && mousePosition.y <= debugStartY + 64)) {
                                cout << "DEBUG HIT" << endl;
                                window.debug();

                            }
                                //LEADERBOARD HIT
                            else if ((LeaderboardStartX <= mousePosition.x &&
                                      mousePosition.x <= LeaderboardStartX + 64) &&
                                     (LeaderboardStartY <= mousePosition.y &&
                                      mousePosition.y <= LeaderboardStartY + 64)) {
                                cout << "LEADERBOARD HIT" << endl;

                            }
                                //PAUSE HIT
                            else if ((pauseStartX <= mousePosition.x && mousePosition.x <= pauseStartX + 64) &&
                                     (pauseStartY <= mousePosition.y && mousePosition.y <= pauseStartY + 64)) {
                                if (!window.gameLost && !window.gameWon) {
                                    bool done = false;
                                    if (window.isPaused) {
                                        window.spriteMap["play"].setTexture(window.textureMap["pause"]);
                                        window.isPaused = false;
                                        done = true;
                                    } else if (!window.isPaused && !done) {
                                        window.spriteMap["play"].setTexture(window.textureMap["play"]);
                                        window.isPaused = true;
                                    }
                                }
                            }
                        }
                    }

                        //TILE
                    else {
                        GameWindow::Tile *tile = &window.getTile(row, col);
                        //LEFT CLICK
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (tile->isMine) {
                                if (tile->texture != "flag") {
                                    window.triggerMines();
                                    window.spriteMap["face_happy"].setTexture(window.textureMap["face_lose"]);
                                }
                            } else {
                                window.displayNumber(tile);
                                window.checkWin();
                            }
                        }
                            //RIGHT CLICK
                        else if (event.mouseButton.button == sf::Mouse::Right) {
                            window.flag(tile);
                        }
                        if (window.gameWon) {
                            window.spriteMap["face_happy"].setTexture(window.textureMap["face_win"]);
                        }
                    }

                }
            }

            //Drawing
            window.displayWindow->clear(sf::Color::White);
            window.displayWindow->draw(window.spriteMap["face_happy"]);
            window.displayWindow->draw(window.spriteMap["debug"]);
            window.displayWindow->draw(window.spriteMap["play"]);
            window.displayWindow->draw(window.spriteMap["leaderboard"]);
            window.displayWindow->draw(window.spriteMap["timeSecondTen"]);
            window.displayWindow->draw(window.spriteMap["timeSecondOne"]);
            window.displayWindow->draw(window.spriteMap["timeMinuteOne"]);
            window.displayWindow->draw(window.spriteMap["timeMinuteTen"]);
            window.displayWindow->draw(window.spriteMap["flagCounterHundred"]);
            window.displayWindow->draw(window.spriteMap["flagCounterTen"]);
            window.displayWindow->draw(window.spriteMap["flagCounterOne"]);
            window.displayWindow->draw(window.spriteMap["flagCounterNegative"]);

            for (int i = 0; i < window.tileVect.size(); i++) {
                window.displayWindow->draw(window.tileVect.at(i).sprite);
            }
            window.displayWindow->display();

        }

        return 0;
    }
}
