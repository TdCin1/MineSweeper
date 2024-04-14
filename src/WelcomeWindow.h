#include <SFML/Graphics.hpp>
#include <iostream>

class WelcomeWindow {
public:
    //Vars
    int rowCount;
    int colCount;

    //Constructor
    WelcomeWindow(int num_rows, int num_cols);

    //Functions
    bool operator()();

};


