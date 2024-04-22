#include "GameWindow.h"

using namespace std;

GameWindow::GameWindow(int num_row, int num_col, int mines) {
    rowCount = num_row;
    colCount = num_col;
    mineCount = mines;
    flagCount = mines;

    displayWindow = new sf::RenderWindow(sf::VideoMode((colCount * 32), (rowCount * 32) + 100), "Welcome Window");

    SetUpTextures();
    SetUpElements();
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
    if(!gameLost && !gameWon &&!isPaused) {
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
    bool done = false;
    if(!gameLost && !isPaused) {
        if (tile->texture == "flag") {
            changeTexturePointer(tile, "tile_hidden");
            tile->texture = "tile_hidden";
            flagCount++;
            done = true;
        }

        else if (tile->texture == "tile_hidden" && !done) {
            changeTexturePointer(tile, "flag");
            tile->texture = "flag";
            flagCount--;
        }

        checkWin();
        if(gameWon){
            return;
        }
    }
}

void GameWindow::setTimeTextures(sf::Sprite &minuteTens, sf::Sprite &minuteOnes, sf::Sprite &secondTens,
                                 sf::Sprite &secondsOnes, int time) {
    if(isPaused){

    }

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
    if(flagCount>= 0){
        sf::Texture texture;
        negative.setTexture(texture);
    }
    if(flagCount<0){
        negative.setTexture(textureMap["dash"]);
        count = abs(count);
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

void GameWindow::checkWin() {
    bool allRevealed = true;
    for(int i=0;i<tileVect.size();i++){
        if(tileVect.at(i).texture == "tile_hidden" && !tileVect.at(i).isMine){
            allRevealed = false;
        }
    }
    gameWon = allRevealed;
    if(gameWon) {
        for (int i = 0; i < tileVect.size(); i++) {
            if(tileVect.at(i).isMine){
                changeTexture(tileVect.at(i),"flag");
            }
        }
    }
}

sf::Vector2i GameWindow::getMousePosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*displayWindow);
    return mousePosition;
}

int GameWindow::Time(){
    if(firstRun){
        firstRun = false;
        pause = std::chrono::high_resolution_clock::now();
        start = std::chrono::high_resolution_clock::now();
    }
    if(isPaused){
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        return timeChanged;
    }
    else{
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start );
        timeChanged = duration.count();
        pause = std::chrono::high_resolution_clock::now();
        return timeChanged;
    }

}

void GameWindow::Reset() {

    firstRun = true;
    isPaused = true;
    timeFinal= 0;
    timeChanged = 0;
    gameLost = false;
    gameWon = false;
    flagCount = mineCount;

    spriteMap.clear();
    tileVect.clear();

    SetUpElements();

}

void GameWindow::SetUpElements() {

    //SETTING UP STARTING SPRITES
    sf::Sprite& face_happy = getSpriteFile("../files/images/face_happy.png",
                                           "face_happy", ((colCount/2)*32)-32, 32*(rowCount+.5)+32);
    sf::Sprite& debug = getSpriteFile("../files/images/debug.png",
                                      "debug", (colCount*32)-304, 32*(rowCount+.5)+32);
    sf::Sprite& leaderboard = getSpriteFile("../files/images/leaderboard.png",
                                            "leaderboard", (colCount*32)-176,32*(rowCount+.5)+32);
    sf::Sprite& play = getSpriteFile("../files/images/play.png",
                                      "play", (colCount*32)-240, 32*(rowCount+.5)+32);


    //TIME SPRITES
    sf::Sprite& timeSecondTen = spriteMap["timeSecondTen"];
    sf::FloatRect Rect = timeSecondTen.getLocalBounds();
    timeSecondTen.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeSecondTen.setPosition((colCount*32)-54,32*(rowCount+.5)+16);

    sf::Sprite& timeSecondOne = spriteMap["timeSecondOne"];
    timeSecondOne.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeSecondOne.setPosition((colCount*32)-33,32*(rowCount+.5)+16);

    sf::Sprite& timeMinuteTen = spriteMap["timeMinuteTen"];
    timeMinuteTen.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeMinuteTen.setPosition((colCount*32)-97,32*(rowCount+.5)+16);

    sf::Sprite& timeMinuteOne = spriteMap["timeMinuteOne"];
    timeMinuteOne.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    timeMinuteOne.setPosition((colCount*32)-76,32*(rowCount+.5)+16);

    //FLAG COUNTER

    sf::Sprite& flagCounterHundred= spriteMap["flagCounterHundred"];
    flagCounterHundred.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterHundred.setPosition(33,32*(rowCount+.5)+16);

    sf::Sprite& flagCounterTen= spriteMap["flagCounterTen"];
    flagCounterTen.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterTen.setPosition(54,32*(rowCount+.5)+16);

    sf::Sprite& flagCounterOne= spriteMap["flagCounterOne"];
    flagCounterOne.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterOne.setPosition(75,32*(rowCount+.5)+16);

    sf::Sprite& flagCounterNegative= spriteMap["flagCounterNegative"];
    flagCounterNegative.setOrigin(Rect.left + Rect.width/2.0f, Rect.top + Rect.height/2.0f);
    flagCounterNegative.setPosition(12,32*(rowCount+.5)+16);
    flagCounterNegative.setTexture(textureMap["dash"]);

    //TILES
    for(int i = 0;i<rowCount;i++){
        for(int j = 0;j<colCount;j++){
            GameWindow::Tile tile = getSpriteText(textureMap["tile_hidden"],16+(32*j),16+(32*i));
            tile.texture = "tile_hidden";
            tileVect.push_back(tile);
        }
    }
    //SET ROWS AND COLS FOR TILES
    for(int i =0;i<tileVect.size();i++){
        int row = i/colCount;
        int rowStart = (((row+1)*colCount)-(colCount-1))-1;
        int col = i - rowStart;
        tileVect.at(i).row = row;
        tileVect.at(i).col = col;
    }


    //SETS HANDLES NEIGHBORS
    for(int row = 0;row<rowCount;row++){
        for(int col = 0; col<colCount;col++){
            GameWindow::Tile* currentTile = &getTile(row,col);
            //TOP
            if(row==0){
                //TOP LEFT
                if(col==0){
                    currentTile->neighbors.push_back(&getTile(row+1,col));
                    currentTile->neighbors.push_back(&getTile(row+1,col+1));
                    currentTile->neighbors.push_back(&getTile(row,col+1));
                }
                    //TOP RIGHT
                else if(col==(colCount-1)){
                    currentTile->neighbors.push_back(&getTile(row,col-1));
                    currentTile->neighbors.push_back(&getTile(row+1,col));
                    currentTile->neighbors.push_back(&getTile(row+1,col-1));
                }
                    //TOP GENERAL
                else{
                    currentTile->neighbors.push_back(&getTile(row,col-1));
                    currentTile->neighbors.push_back(&getTile(row+1,col-1));
                    currentTile->neighbors.push_back(&getTile(row+1,col));
                    currentTile->neighbors.push_back(&getTile(row,col+1));
                    currentTile->neighbors.push_back(&getTile(row+1,col+1));
                }
            }
                //BOTTOM
            else if(row==(rowCount-1)){
                //BOTTOM LEFT
                if(col==0){
                    currentTile->neighbors.push_back(&getTile(row-1,col));
                    currentTile->neighbors.push_back(&getTile(row-1,col+1));
                    currentTile->neighbors.push_back(&getTile(row,col+1));
                }
                    //BOTTOM RIGHT
                else if(col==(colCount-1)){
                    currentTile->neighbors.push_back(&getTile(row,col-1));
                    currentTile->neighbors.push_back(&getTile(row-1,col));
                    currentTile->neighbors.push_back(&getTile(row-1,col-1));
                }
                    //BOTTOM GENERAL
                else{
                    currentTile->neighbors.push_back(&getTile(row,col-1));
                    currentTile->neighbors.push_back(&getTile(row-1,col-1));
                    currentTile->neighbors.push_back(&getTile(row-1,col));
                    currentTile->neighbors.push_back(&getTile(row,col+1));
                    currentTile->neighbors.push_back(&getTile(row-1,col+1));
                }
            }
                //LEFT SIDE
            else if(col == 0){
                currentTile->neighbors.push_back(&getTile(row+1,col));
                currentTile->neighbors.push_back(&getTile(row+1,col+1));
                currentTile->neighbors.push_back(&getTile(row,col+1));
                currentTile->neighbors.push_back(&getTile(row-1,col));
                currentTile->neighbors.push_back(&getTile(row-1,col+1));
            }
                //RIGHT SIDE
            else if(col==(colCount-1)){
                currentTile->neighbors.push_back(&getTile(row-1,col));
                currentTile->neighbors.push_back(&getTile(row-1,col-1));
                currentTile->neighbors.push_back(&getTile(row,col-1));
                currentTile->neighbors.push_back(&getTile(row+1,col-1));
                currentTile->neighbors.push_back(&getTile(row+1,col));
            }
                //MIDDLES
            else{
                currentTile->neighbors.push_back(&getTile(row-1,col-1));
                currentTile->neighbors.push_back(&getTile(row,col-1));
                currentTile->neighbors.push_back(&getTile(row+1,col-1));
                currentTile->neighbors.push_back(&getTile(row-1,col));
                currentTile->neighbors.push_back(&getTile(row+1,col));
                currentTile->neighbors.push_back(&getTile(row-1,col+1));
                currentTile->neighbors.push_back(&getTile(row,col+1));
                currentTile->neighbors.push_back(&getTile(row+1,col+1));
            }
        }
    }
    //SET MINES
    srand(time(0));
    for(int i=0;i<mineCount;i++){
        int row = rand()%15;
        int col = rand()%30;
        GameWindow::Tile* tile = &getTile(row,col);
        if(tile->isMine){
            if(row==0){
                row=row+1;
            }
            else{
                row = row-1;
            }
            tile = &getTile(row,col);
        }
        tile->isMine = true;
    }

    start = chrono::high_resolution_clock::now();

    setupTileNums();
}

void GameWindow::SetUpTextures() {
    //SETTING UP NUMBER TEXTURES
    sf::Texture& zero = textureMap["zero"];
    zero.loadFromFile("../files/images/digits.png",sf::IntRect(0, 0, 21, 32));
    sf::Texture& one= textureMap["one"];
    one.loadFromFile("../files/images/digits.png",sf::IntRect(21, 0, 21, 32));
    sf::Texture& two= textureMap["two"];
    two.loadFromFile("../files/images/digits.png",sf::IntRect(42, 0, 21, 32));
    sf::Texture& three= textureMap["three"];
    three.loadFromFile("../files/images/digits.png",sf::IntRect(63, 0, 21, 32));
    sf::Texture& four= textureMap["four"];
    four.loadFromFile("../files/images/digits.png",sf::IntRect(84, 0, 21, 32));
    sf::Texture& five= textureMap["five"];
    five.loadFromFile("../files/images/digits.png",sf::IntRect(105, 0, 21, 32));
    sf::Texture& six= textureMap["six"];
    six.loadFromFile("../files/images/digits.png",sf::IntRect(126, 0, 21, 32));
    sf::Texture& seven= textureMap["seven"];
    seven.loadFromFile("../files/images/digits.png",sf::IntRect(147, 0, 21, 32));
    sf::Texture& eight= textureMap["eight"];
    eight.loadFromFile("../files/images/digits.png",sf::IntRect(168, 0, 21, 32));
    sf::Texture& nine= textureMap["nine"];
    nine.loadFromFile("../files/images/digits.png",sf::IntRect(189, 0, 21, 32));
    sf::Texture& dash= textureMap["dash"];
    dash.loadFromFile("../files/images/digits.png",sf::IntRect(210, 0, 21, 32));



    //LOADING REST OF TEXTURES
    getTexture("../files/images/face_lose.png","face_lose");
    getTexture("../files/images/face_win.png","face_win");
    getTexture("../files/images/number_1.png","1");
    getTexture("../files/images/number_2.png","2");
    getTexture("../files/images/number_3.png","3");
    getTexture("../files/images/number_4.png","4");
    getTexture("../files/images/number_5.png","5");
    getTexture("../files/images/number_6.png","6");
    getTexture("../files/images/number_7.png","7");
    getTexture("../files/images/number_8.png","8");
    getTexture("../files/images/mine.png","mine");
    getTexture("../files/images/tile_hidden.png","tile_hidden");
    getTexture("../files/images/tile_revealed.png","tile_revealed");
    getTexture("../files/images/flag.png","flag");
    getTexture("../files/images/pause.png","pause");

}

void GameWindow::debug() {
    if(!gameWon && ! gameLost){
        if (debugPressed) {
            for(int i =0;i<tileVect.size();i++) {
                //Hide
                if(tileVect.at(i).isMine){
                    changeTexture(tileVect.at(i),"tile_hidden");
                    debugPressed =  false;

                }
            }
            return;
        }
        else{
            for(int i =0;i<tileVect.size();i++) {
                //Hide
                if(tileVect.at(i).isMine){
                    changeTexture(tileVect.at(i),"mine");
                    debugPressed =  true;
                }
            }
        }
    }
}