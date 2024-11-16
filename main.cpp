/*
 * File Name: main.cpp
 * Author: Phuc Nguyen Gia
 * Date: 2024-11-15
 * Description: This program simulates an electric motorcycle's dashboard display and user interaction.
 *              It provides a menu for the user to control various aspects of the motorcycle. Here's how
 *              you can interact with the program:
 *
 *              1. Press '1' to start the motorcycle.
 *              2. Press '0' to turn off the motorcycle.
 *              3. Press 'K' to activate the left turn signal (equivalent to an left arrow).
 *              4. Press 'M' to activate the right turn signal (equivalent to an right arrow).
 *              5. Press 'o' to turn off the turn signals.
 *              6. Press 'H' to increase the motorcycle's speed (equivalent to an up arrow).
 *              7. Press 'P' to decrease the motorcycle's speed (equivalent to an down arrow).
 *
 *              The program uses threads to handle user input and continuously update and display motorcycle
 *              data on the screen.
 */

#include <iostream>

using namespace std;

class MainMenu{
    private:
    public:
};

class Battery{
    private:
    public:
};

int getBatteryLevel(){
    return 1;
}

void startMenu(){
    cout<<"Battery temperarture: ----"<<endl;
    cout<<"Battery level: ----"<<endl;
    cout<<"Turn signal: ----"<<endl;
    cout<<"Fan mode: ----"<<endl;
    cout<<"Speed: ----"<<endl;
    cout<<"Start: OFF"<<endl;
}

void setStartUp(bool startUp){
    bool startUp = startUp;
}

void executeMenu(char key){
    if(key == "1"){
        setStartUp(true);
    }
    else if(key == "0"){
        setStartUp(false);
    }
}

void displayData(bool &exitProgram, char &key){
    // while(!exitProgram){
    //     startMenu();
    //     if (!getBatteryLevel()){
    //         exitProgram = true;
    //         cout<<endl;
    //         cout<<"Battery is empty"<<endl;
    //     }
    // }
    startMenu();
}


int main(){
    
    char key = ' ';
    bool exitProgram = false;

    displayData(exitProgram, key);

    return 0;
}