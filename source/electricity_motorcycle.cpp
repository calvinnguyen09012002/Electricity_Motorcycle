/*
 * File Name: ElectricMotorcycle.cpp
 * Author: Phuc Nguyen Gia
 * Date: 16/11/2024
 * Description: This C++ program simulates an electric motorcycle control system.
 *              It includes classes to manage the motorcycle's battery, turn signals,
 *              and main menu. The Battery class monitors battery capacity and temperature,
 *              simulating gradual capacity decrease and random temperature changes.
 *              The MainMenu class displays and controls the motorcycle's status and menu.
 *              The program uses threads to manage these functionalities concurrently,
 *              and it provides a user interface to interact with the motorcycle's features.
 */

 #include "electricity_motorcycle.h"

 mutex decreaseBattery;
 mutex randomTemperature;
 mutex input;
 mutex display;

 /*
 * Function: getRandomNumber
 * Description: Generates a random integer within the specified range [min, max].
 * Input:
 *   min - The minimum value of the range.
 *   max - The maximum value of the range.
 * Output:
 *   Returns a random integer within the specified range.
 */
 int getRandomNumber(int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
 }

 /*
 * Class: Battery
 * Method: Battery (constructor)
 * Description: Constructs a Battery object with random initial capacity and temperature.
 *              It also starts threads for decreasing battery capacity and random temperature changes.
 * Input:
 *   None
 * Output:
 *   None
 */
 Battery::Battery(){
    maxBatteryCapacity = 70; // 100%
    minBatteryCapacity = 30; // 0%

    currentBatteryCapacity = getRandomNumber(minBatteryCapacity, maxBatteryCapacity);
    setBatteryLevel(minBatteryCapacity, maxBatteryCapacity, currentBatteryCapacity);

    batteryTemperature = getRandomNumber(20, 80);
    setFanMode(batteryTemperature);

    startDecreaseBattery();
    startRandomTemperature();
 }

 /*
 * Class: Battery
 * Method: ~Battery (destructor)
 * Description: Destructor for the Battery class. Stops the decreaseBatteryThread
 *              and the randomTemperatureThread if they are joinable.
 * Input:
 *   None
 * Output:
 *   None
 */
Battery::~Battery(){
    stopDecreaseBattery();
    stopRandomTemperature();   
}

/*
 * Class: Battery
 * Method: startDecreaseBattery
 * Description: Starts a thread to continuously decrease currentBatteryCapacity over time.
 *              It periodically reduces the capacity and updates the batteryLevel.
 * Input:
 *   None
 * Output:
 *   None
 */
 void Battery::startDecreaseBattery(){
    //Define a function to reduce currentBatteryCapacity.
    auto decreaseFunction = [this](){
        while(true){
            this_thread::sleep_for(chrono::seconds(4));

            decreaseBattery.lock();
            if (currentBatteryCapacity > minBatteryCapacity){
                currentBatteryCapacity--;
                setBatteryLevel(minBatteryCapacity, maxBatteryCapacity, currentBatteryCapacity); // Update bateryLevel
            }
            decreaseBattery.unclock();
        }
    };

    decreaseBatteryThread = thread(decreaseFunction);
 }

/*
 * Class: Battery
 * Method: stopDecreaseBattery
 * Description: Stops the decreaseBatteryThread by detaching it if it's joinable.
 * Input:
 *   None
 * Output:
 *   None
 */
 