#include "GameWindow.h"

using namespace std;

GameWindow::GameWindow(int num_row, int num_col, int mines) {
    srand(time(0));
    rowCount = num_row;
    colCount = num_col;
    mineCount = mines;
    flagCount = mines;

    sf::Texture& zero = textureMap["zero"];
    zero.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(0, 0, 21, 32));
    sf::Texture& one= textureMap["one"];
    one.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(21, 0, 21, 32));
    sf::Texture& two= textureMap["two"];
    two.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(42, 0, 21, 32));
    sf::Texture& three= textureMap["three"];
    three.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(63, 0, 21, 32));
    sf::Texture& four= textureMap["four"];
    four.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(84, 0, 21, 32));
    sf::Texture& five= textureMap["five"];
    five.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(105, 0, 21, 32));
    sf::Texture& six= textureMap["six"];
    six.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(126, 0, 21, 32));
    sf::Texture& seven= textureMap["seven"];
    seven.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(147, 0, 21, 32));
    sf::Texture& eight= textureMap["eight"];
    eight.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(168, 0, 21, 32));
    sf::Texture& nine= textureMap["nine"];
    nine.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(189, 0, 21, 32));
    sf::Texture& dash= textureMap["dash"];
    dash.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/images/digits.png",sf::IntRect(210, 0, 21, 32));

}

sf::Texture& GameWindow::getTexture(const string& filename, const string& key) {
    sf::Texture& texture = textureMap[key];
    texture.loadFromFile(filename);
    return texture;
}

sf::Sprite& GameWindow::getSpriteFile(const std::string &filename, const std::string &key, float x, float y) {
    sf::Texture& texture = getTexture(filename,key);
    sf::Sprite& sprite = spriteMap[key];
    sprite.setTexture(texture);
    sf::FloatRect Rect = sprite.getLocalBounds();
    sprite.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    sprite.setPosition(x,y);
    return sprite;
}

GameWindow::Tile GameWindow::getSpriteText(const sf::Texture &texture, float x, float y) {
    Tile tile;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::FloatRect Rect = sprite.getLocalBounds();
    sprite.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    sprite.setPosition(x,y);
    tile.sprite = sprite;
    return tile;
}

void GameWindow::setSpritePosition(const std::string &key,float x, float y) {
    spriteMap[key].setPosition(x,y);
}

void GameWindow::changeTexture(GameWindow::Tile &tile, std::string key) {
    tile.sprite.setTexture(textureMap[key]);
}

void GameWindow::changeTexturePointer(GameWindow::Tile *tile, std::string key) {
    tile->sprite.setTexture(textureMap[key]);
}

GameWindow::Tile& GameWindow::getTile(int row, int col) {
    int i = row*colCount + col;
    return (Tile &) tileVect.at(i);
}

void GameWindow::triggerMines() {
    gameLost = true;
    for(int i =0; i<tileVect.size();i++){
        Tile* tile = &tileVect.at(i);
        if(tile->isMine){
            changeTexturePointer(tile,"mine");
        }
    }
}

void GameWindow::setupTileNums() {
    for(int i =0; i<tileVect.size();i++){
        Tile* tile = &tileVect.at(i);
        if(tile->isMine){
            tile->number = -1;
        }
        else{
            tile->number = 0;
            for(int j=0;j<tile->neighbors.size();j++){
                if(tile->neighbors.at(j)->isMine){
                    tile->number++;
                }
            }
        }
    }
}

void GameWindow::displayNumber(Tile* tile) {
    if(!gameLost) {
        if (tile->texture != "flag") {
            if (!tile->touched) {
                tile->touched = true;
                if (tile->number == 0) {
                    changeTexturePointer(tile, "tile_revealed");
                    tile->texture = "tile_revealed";
                    for (int i = 0; i < tile->neighbors.size(); i++) {
                        displayNumber(tile->neighbors.at(i));
                    }
                } else if (tile->number == 1) {
                    tile->texture = "1";
                    changeTexturePointer(tile, "1");
                } else if (tile->number == 2) {
                    changeTexturePointer(tile, "2");
                    tile->texture = "2";
                } else if (tile->number == 3) {
                    changeTexturePointer(tile, "3");
                    tile->texture = "3";
                } else if (tile->number == 4) {
                    changeTexturePointer(tile, "4");
                    tile->texture = "4";
                } else if (tile->number == 5) {
                    changeTexturePointer(tile, "5");
                    tile->texture = "5";
                } else if (tile->number == 6) {
                    changeTexturePointer(tile, "6");
                    tile->texture = "6";
                } else if (tile->number == 7) {
                    changeTexturePointer(tile, "7");
                    tile->texture = "7";
                } else if (tile->number == 8) {
                    changeTexturePointer(tile, "8");
                    tile->texture = "8";
                }
            }
        }
    }
}

void GameWindow::flag(GameWindow::Tile *tile) {
    if(!gameLost) {
        if (tile->texture == "flag") {
            changeTexturePointer(tile, "tile_hidden");
            tile->texture = "tile_hidden";
            flagCount++;
            return;
        }

        if (tile->texture == "tile_hidden") {
            changeTexturePointer(tile, "flag");
            tile->texture = "flag";
            flagCount--;
        }
    }
    cout<<flagCount;
}

void GameWindow::setTimeTextures(sf::Sprite &minuteTens, sf::Sprite &minuteOnes, sf::Sprite &secondTens,
                                 sf::Sprite &secondsOnes, int time) {
    if(time<=9){
        secondsOnes.setTexture(getTimeTexture(time));
        secondTens.setTexture(getTimeTexture(0));
        minuteOnes.setTexture(getTimeTexture(0));
        minuteTens.setTexture(getTimeTexture(0));

    }
    else if(time<= 59){
        int tens = floor(time/10);
        int ones = floor(time%10);
        secondsOnes.setTexture(getTimeTexture(ones));
        secondTens.setTexture(getTimeTexture(tens));
        minuteOnes.setTexture(getTimeTexture(0));
        minuteTens.setTexture(getTimeTexture(0));
    }
    else if(time<=599){
        int minutes = floor(time/60);
        int tens = floor((time-(60*minutes))/10);
        int ones = time - ((tens*10) + (minutes*60));
        secondsOnes.setTexture(getTimeTexture(ones));
        secondTens.setTexture(getTimeTexture(tens));
        minuteOnes.setTexture(getTimeTexture(minutes));
        minuteTens.setTexture(getTimeTexture(0));
    }
    else{
        int minuteTen = floor(time/600);
        int minuteOne = floor((time-(minuteTen*600))/60);
        int secondTen = floor((time-(60*minuteOne+600*minuteTen))/10);
        int secondOne = time -((600*minuteTen)+(60*minuteOne)+(secondTen*10));
        secondsOnes.setTexture(getTimeTexture(secondOne));
        secondTens.setTexture(getTimeTexture(secondTen));
        minuteOnes.setTexture(getTimeTexture(minuteOne));
        minuteTens.setTexture(getTimeTexture(minuteTen));
    }
}
void GameWindow::flagCounter(sf::Sprite &negative, sf::Sprite& hundreds, sf::Sprite &tens, sf::Sprite &ones, int count) {
    if(flagCount<0){
        negative.setTexture(textureMap["dash"]);
        count = abs(count);
    }
    else{
        sf::Texture texture;
        negative.setTexture(texture);
    }
    if(count<=9){
        hundreds.setTexture(getTimeTexture(0));
        tens.setTexture(getTimeTexture(0));
        ones.setTexture(getTimeTexture(count));

    }
    else if(count<=59){
        int hundred = floor(count/60);
        int ten = floor((count-(60*hundred))/10);
        int one = count - ((ten*10) + (hundred*60));
        ones.setTexture(getTimeTexture(one));
        tens.setTexture(getTimeTexture(ten));
        hundreds.setTexture(getTimeTexture(hundred));
    }
    else{
        int hundred = floor(count/100);
        int ten = floor((count - hundred*100)/10);
        int one = count - ((hundred*100)+(ten*10));

        hundreds.setTexture(getTimeTexture(hundred));
        tens.setTexture(getTimeTexture(ten));
        ones.setTexture(getTimeTexture(one));
    }

}

sf::Texture& GameWindow::getTimeTexture(int num) {
    if(num == 0)
        return textureMap["zero"];
    else if(num == 1)
        return textureMap["one"];
    else if(num == 2)
        return textureMap["two"];
    else if(num == 3)
        return textureMap["three"];
    else if(num == 4)
        return textureMap["four"];
    else if(num == 5)
        return textureMap["five"];
    else if(num == 6)
        return textureMap["six"];
    else if(num == 7)
        return textureMap["seven"];
    else if(num == 8)
        return textureMap["eight"];
    else if(num == 9)
        return textureMap["nine"];

}