#include<string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

using namespace std;

class GameWindow{
public:
    //VARS
    int rowCount;
    int colCount;
    sf::Sprite smile;
    map<string,sf::Texture> defaultTextures;
    map<string,sf::Sprite> defaultSprites;

    //CONSTRUCTOR
    GameWindow(int num_row, int num_col);

    //Functions
    void loadSprite(sf::Texture &texture, sf::Sprite &sprite, string filename);
    void loadDefault(string filename, string key);

};