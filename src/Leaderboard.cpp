#include "Leaderboard.h"
using namespace std;

Leaderboard::Leaderboard(int row, int col){
    colCount = col;
    rowCount = row;
    displayWindow = new sf::RenderWindow(sf::VideoMode((colCount * 16), (rowCount * 16) + 50), "Leaderboard Window");
    size = displayWindow->getSize();
    font.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/font.ttf");

};

void Leaderboard::readData() {
    ifstream file("../files/leaderboard.txt");
    string line;
    while(getline(file,line)){
        lines.push_back(line);
    }
}

void Leaderboard::addText(string str, int value) {
    sf::Text leader;
    leader.setString("LEADERBOARD");
    leader.setFont(font);
    leader.setCharacterSize(20);
    leader.setFillColor(sf::Color::White);
    leader.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect nameRect = leader.getLocalBounds();
    leader.setOrigin(nameRect.left + nameRect.width/2.0f, nameRect.top + nameRect.height/2.0f);
    leader.setPosition(size.x/2,(size.y/2)-120);

}

void Leaderboard::Sort() {

}


void Leaderboard::operator()() {

    Sort();

    sf::Text leader;
    leader.setString("LEADERBOARD\th\ngg");
    leader.setFont(font);
    leader.setCharacterSize(20);
    leader.setFillColor(sf::Color::White);
    leader.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect nameRect = leader.getLocalBounds();
    leader.setOrigin(nameRect.left + nameRect.width/2.0f, nameRect.top + nameRect.height/2.0f);
    leader.setPosition(size.x/2,(size.y/2)-120);

    while (displayWindow->isOpen())
    {
        // check all the window event since last event
        sf::Event event;
        while (displayWindow->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                displayWindow->close();
                return;
            }
        }
        displayWindow->clear(sf::Color::Blue);
        displayWindow->draw(leader);
        displayWindow->display();
    }
}