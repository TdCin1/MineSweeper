#include "GameWindow.h"

using namespace std;

GameWindow::GameWindow(int num_row, int num_col) {
    rowCount = num_row;
    colCount = num_col;
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

GameWindow::Tile& GameWindow::getTile(int row, int col) {
    int i = row*colCount + col;
    return (Tile &) tileVect.at(i);
}