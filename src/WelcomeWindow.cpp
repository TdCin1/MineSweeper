#include "WelcomeWindow.h"
#include <string>

using namespace std;

WelcomeWindow::WelcomeWindow(int num_rows, int num_cols) {
    rowCount = num_rows;
    colCount = num_cols;
}

bool WelcomeWindow::operator()() {
    //WINDOW
    sf::RenderWindow window(sf::VideoMode((colCount*32),(rowCount*32)+100),"Welcome Window");
    sf::Vector2u size = window.getSize();

    //FONT
    sf::Font font;
    font.loadFromFile("C:/Users/Landon Agic/CLionProjects/MineSweeper/files/font.ttf");

    //TEXT
    sf::Text textName;
    textName.setString("|");
    textName.setFont(font);
    textName.setCharacterSize(18);
    textName.setFillColor(sf::Color::Yellow);
    textName.setStyle(sf::Text::Bold);
    sf::FloatRect nameRect = textName.getLocalBounds();
    textName.setOrigin(nameRect.left + nameRect.width/2.0f, nameRect.top + nameRect.height/2.0f);
    textName.setPosition(size.x/2,(size.y/2)-45);

    sf::Text textPrompt;
    textPrompt.setString("Enter your name");
    textPrompt.setFont(font);
    textPrompt.setCharacterSize(20);
    textPrompt.setFillColor(sf::Color::White);
    textPrompt.setStyle(sf::Text::Bold);
    sf::FloatRect promptRect = textPrompt.getLocalBounds();
    textPrompt.setOrigin(promptRect.left + promptRect.width/2.0f, promptRect.top + promptRect.height/2.0f);
    textPrompt.setPosition(size.x/2,(size.y/2)-75);



    sf::Text textWelcome;
    textWelcome.setString("WELCOME TO MINESWEEPER!");
    textWelcome.setFont(font);
    textWelcome.setCharacterSize(24);
    textWelcome.setFillColor(sf::Color::White);
    textWelcome.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect welcomeRect = textWelcome.getLocalBounds();
    textWelcome.setOrigin(welcomeRect.left + welcomeRect.width/2.0f, welcomeRect.top + welcomeRect.height/2.0f);
    textWelcome.setPosition(size.x/2,(size.y/2)-150);

    //VARS
    string username = "|";
    // run when open
    while (window.isOpen())
    {
        // check all the window event since last event
        sf::Event event;
        while (window.pollEvent(event)){
            // closes window
            if (event.type == sf::Event::Closed){
                window.close();
                return false;
            }
            else if(event.key.code == sf::Keyboard::Enter){
                if(username.size()!=1){
                    window.close();
                    return true;
                }
            }
            else if(event.type == sf::Event::TextEntered){
                if((event.text.unicode <=122 && event.text.unicode>=97)||event.text.unicode==8){
                    if(event.text.unicode == 8){
                        if(username.size()>1){
                            username.erase(username.end()-2);
                            textName.setString(username);
                        }
                    }
                    else{
                        if(username.size()<11){
                            char temp = static_cast<char>(event.text.unicode);
                            if(username.size()==1){
                                char result = static_cast<char>(toupper(static_cast<unsigned char>(temp)));
                                username.insert(username.size()-1,1,result);
                            }
                            else{
                                char result = static_cast<char>(tolower(static_cast<unsigned char>(temp)));
                                username.insert(username.size()-1,1,result);
                            }
                            textName.setString(username);
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(textName);
        window.draw(textPrompt);
        window.draw(textWelcome);
        window.display();
    }
}

