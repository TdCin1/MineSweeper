#include "GameWindow.h"

using namespace std;

GameWindow::GameWindow(int num_row, int num_col) {
    rowCount = num_row;
    colCount = num_col;
}

void GameWindow::loadSprite(sf::Texture &texture, sf::Sprite &sprite, string filename) {
    if(!texture.loadFromFile(filename)){
        cout<<"error";
    }
    sprite.setTexture(texture);
    sf::FloatRect Dimensions = sprite.getLocalBounds();
    sprite.setOrigin(Dimensions.left + Dimensions.width/2.0f, Dimensions.top + Dimensions.height/2.0f);
}


void GameWindow::loadDefault(string filename, string key) {
    //Smile 64 64
    sf::Texture text = new sf::Texture;
    sf::Sprite sprite = new sf::Sprite;
    text->loadFromFile(filename);
    sprite->setPosition(300,300);
    sf::FloatRect Dimensions = sprite->getLocalBounds();
    sprite->setOrigin(Dimensions.left + Dimensions.width/2.0f, Dimensions.top + Dimensions.height/2.0f);
    defaultTextures.emplace(key,text);
    defaultSprites.emplace(key,sprite);
    smile = *sprite;

}

/*bool GameWindow::operator()() {
    //Sprites basic
    //Smile 64 64
    string filename = "C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/face_happy.png";
    sf::Texture text;
    sf::Sprite smile;
    loadSprite(text, smile, filename);
    smile.setPosition(300,300);
    this->smile = smile;

    //Frown 64 64
    string filename1 = "C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/face_lose.png";
    sf::Texture text1;
    sf::Sprite frown;
    loadSprite(text1, frown, filename1);
    frown.setPosition(300,300);
    //Debug 64 64
    string filename3 = "C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/debug.png";
    sf::Texture text3;
    sf::Sprite debug;
    loadSprite(text3, debug, filename3);
    debug.setPosition(300,300);
    //Play 64 64
    string filename4 = "C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/play.png";
    sf::Texture text4;
    sf::Sprite play;
    loadSprite(text4, play, filename4);
    play.setPosition(300,300);
    //Pause 64 64
    string filename5 = "C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/pause.png";
    sf::Texture text5;
    sf::Sprite pause;
    loadSprite(text5, pause, filename5);
    pause.setPosition(300,300);
    //Leaderboard 64 64
    string filename6 = "C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/leaderboard.png";
    sf::Texture text6;
    sf::Sprite leaderboard;
    loadSprite(text6, leaderboard, filename6);
    leaderboard.setPosition(300,300);
}
 */
