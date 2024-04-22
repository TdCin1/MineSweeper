#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Leaderboard{
public:
    vector<string> lines;

    sf::RenderWindow* displayWindow;
    sf::Font font;
    sf::Vector2u size;
    int colCount;
    int rowCount;
    string content;

    Leaderboard(int row, int col);
    void operator()();
    void readData();
    void addText(string str, int value);
    void Sort();
    bool compareTimes(string time1, string time2);
};