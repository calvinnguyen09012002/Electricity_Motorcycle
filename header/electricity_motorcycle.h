/*
 * File Name: electricity_motorcycle.h
 * Author: Phuc Nguyen Gia
 * Date: 16/11/2024
 * Description: This header file contains the declaration of classes, enum and functions
 * for a electric motorcycle.
 */

#ifndef __ELECTRICITY_MOTORCYCLE_H
#define __ELECTRICITY_MOTORCYCLE_H

#include <iostream>

#include <thread>
#include <chrono>

#include <random>



using namespace std;

// Generate a random number between 'min' and 'max'.
int getRandomNumber(int min, int max);

class Battery{
    private:
        int batteryTemperature;
        int currentBatteryCapacity;
        int maxBatteryCapacity;
        int minBatteryCapacity;
        int batteryLevel;
        bool fanMode;
        thread decreaseBatteryThread;
        thread randomTemperatureThread;

    public:
        // Battery class contructor.
        Battery();

        // Battery class destructor.
        ~Battery();

        // Set the battery level based on specific minimum, maximum and current value.
        void setBatteryLevel(int min, int max, int current);

        // Get the current battery level.
        void getBatteryLevel();

        // Start the battery capacity decrease thread.
        void startDecreaseBattery();

        // Stop the battery capacity decrease thread.
        void stopDecreaseBattery();

        // Get the battery temperature.
        void getBatteryTemperature();

        // Start the random temperature.
        void startRandomTemperature();

        // Stop the random temperature.
        void stopRandomTemperature();

        // Get the current battery capacity.
        int getCurrentBatteryCapacity();

        // Set the fan mode based on battery temperature.
        void setFanMode(int batteryTemperature);

        // Get the fan mode status.
        bool getfanMode();
};

// Enumerate type for turn signals.
enum TurnSignal{
    OFF,
    LEFT,
    RIGHT
};

class MainMenu{
    private:
        TurnSignal signal;
        bool startUp;
        int speed;
    public:
        Battery battery;

        // Enumerate type for turn signals.
        MainMenu();

        // Activate the left turn signal.
        void leftTurn();

        // Activate the right turn signal.
        void rightTurn();

        // Activate the off turn signal.
        void offTurn();

        // Display the current turn signal.
        void turnSignal();

        // Set the turn signal to the specific value.
        void setSignal(TurnSignal signal);

        // Get the current turn signal.
        TurnSignal getSignal();

        // Set the startup status.
        void setStartUp(bool startUp);

        // Get the startuo status.
        bool getStartUp();

        // Set the speed of the vehicle.
        void setSpeed();

        // Get the current speed of the vehicle.
        int getSpeed();

        // Display the main menu.
        void startMenu();

        // Display the main menu and handle user input.
        void displayMenu();

        // Execute menu actions based on user input.
        void executeMenu(char key);
};

// Monitor user input for program exit and key press.
void getInput(bool &exitProgram, char &key);

// Display program data, update the menu and handle program exit.
void displayData(bool &exitProgram, char &key, MainMenu &menu);

#endif