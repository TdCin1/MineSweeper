#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

class GameWindow{
public:
    struct Tile{
        string texture;
        sf::Sprite sprite;
        vector<Tile*> neighbors={};
        int row;
        int col;
        bool isMine = false;
        bool touched = false;
        int number;
    };

    //VARS
    int timeChanged = 0;
    bool gameLost = false;
    int rowCount;
    int colCount;
    int mineCount;
    int flagCount;
    map<string,sf::Texture> textureMap;
    map<string,sf::Sprite> spriteMap;

    vector<Tile> tileVect;


    //CONSTRUCTOR
    GameWindow(int num_row, int num_col, int mines);

    //Functions
    sf::Texture& getTexture(const string& filename, const string& key);
    sf::Sprite& getSpriteFile(const string& filename, const string& key, float x, float y);
    Tile getSpriteText(const sf::Texture& texture, float x, float y);
    void setSpritePosition(const string& key, float x, float y);
    void changeTexture(Tile& tile,string key);
    void changeTexturePointer(Tile* tile, string key);
    void triggerMines();
    void setupTileNums();
    void displayNumber(Tile* tile);
    void flag(Tile* tile);

    void setTimeTextures(sf::Sprite& minuteTens, sf::Sprite& minuteOnes, sf::Sprite& secondTens, sf::Sprite& secondsOnes, int time);
    void flagCounter(sf::Sprite& negative, sf::Sprite& hundreds, sf::Sprite& tens, sf::Sprite& ones, int count);
    Tile& getTile(int row, int col);

private:
    sf::Texture& getTimeTexture(int num);


};