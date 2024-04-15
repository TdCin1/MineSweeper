#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class GameWindow{
public:
    struct Tile{
        sf::Sprite sprite;
        vector<Tile*> neighbors={};
        int row;
        int col;
        bool isMine;
    };

    //VARS
    int rowCount;
    int colCount;
    map<string,sf::Texture> textureMap;
    map<string,sf::Sprite> spriteMap;

    vector<Tile> tileVect;


    //CONSTRUCTOR
    GameWindow(int num_row, int num_col);

    //Functions
    sf::Texture& getTexture(const string& filename, const string& key);
    sf::Sprite& getSpriteFile(const string& filename, const string& key, float x, float y);
    Tile getSpriteText(const sf::Texture& texture, float x, float y);
    void setSpritePosition(const string& key, float x, float y);
    void changeTexture(Tile& tile,string key);

    Tile& getTile(int row, int col);

};