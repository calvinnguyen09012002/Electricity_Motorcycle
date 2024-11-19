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
            decreaseBattery.unlock();
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
 void Battery::stopDecreaseBattery(){
    if (decreaseBatteryThread.joinable()){
        decreaseBatteryThread.detach();
    }
 }

/*
 * Class: Battery
 * Method: setBatteryLevel
 * Description: Sets the battery level based on the current and specified min/max values.
 * Input:
 *   min - The minimum battery capacity.
 *   max - The maximum battery capacity.
 *   current - The current battery capacity.
 * Output:
 *   None
 */
 void Battery::setBatteryLevel(int min, int max, int current){
    this->batteryLevel = (current - min)*100/(max - min);
 }

/*
 * Class: Battery
 * Method: getBatteryLevel
 * Description: Gets the current battery level.
 * Input:
 *   None
 * Output:
 *   Returns the battery level as an integer.
 */
 int Battery::getBatteryLevel(){
    return this->batteryLevel;
 }

/*
 * Class: Battery
 * Method: getBatteryTemperature
 * Description: Gets the current battery temperature.
 * Input:
 *   None
 * Output:
 *   Returns the battery temperature as an integer.
 */
 int Battery::getBatteryTemperature(){
    return this->batteryTemperature;
 }

/*
 * Class: Battery
 * Method: startRandomTemperature
 * Description: Starts a thread to periodically update the battery temperature.
 *              It simulates temperature changes and updates the fan mode accordingly.
 * Input:
 *   None
 * Output:
 *   None
 */
 void Battery::startRandomTemperature(){
    auto randomTemperatureFunction = [this](){
        while (true){
            this_thread::sleep_for(chrono::seconds(3));

            randomTemperature.lock();
            batteryTemperature = getRandomNumber(20, 80);
            setFanMode(batteryTemperature);
            randomTemperature.unlock();
        }
    };

    randomTemperatureThread = thread(randomTemperatureFunction);
 }

/*
 * Class: Battery
 * Method: stopRandomTemperature
 * Description: Stops the randomTemperatureThread by detaching it if it's joinable.
 * Input:
 *   None
 * Output:
 *   None
 */
 void Battery::stopRandomTemperature(){
    if(randomTemperatureThread.joinable()){
        randomTemperatureThread.detach();
    }
 }

/*
 * Class: Battery
 * Method: getCurrentBatteryCapacity
 * Description: Gets the current battery capacity.
 * Input:
 *   None
 * Output:
 *   Returns the current battery capacity as an integer.
 */
 int Battery::getCurrentBatteryCapacity(){
    return this->currentBatteryCapacity;
 }

/*
 * Class: Battery
 * Method: setFanMode
 * Description: Sets the fan mode based on the given battery temperature.
 *              If the temperature is greater than 50, the fan mode is set to true (ON),
 *              otherwise, it's set to false (OFF).
 * Input:
 *   batteryTemperature - The current battery temperature.
 * Output:
 *   None
 */
 void Battery::setFanMode(int batteryTemperature){
    if (batteryTemperature > 50){
        this->fanMode = true;
    }else{
        this->fanMode = false;
    }
 }

/*
 * Class: Battery
 * Method: getFanMode
 * Description: Gets the current fan mode status.
 * Input:
 *   None
 * Output:
 *   Returns true if the fan mode is ON, false if it's OFF.
 */
 bool Battery::getFanMode(){
    return this->fanMode;
 }

/*
 * Class: MainMenu
 * Method: MainMenu
 * Description: Constructor for the MainMenu class. Initializes signal, startUp, and speed.
 * Input:
 *   None
 * Output:
 *   None
 */
 MainMenu::MainMenu(){
    signal = OFF;
    startUp = false;
    speed = 50;
 }

/*
 * Class: MainMenu
 * Method: leftTurn
 * Description: Displays a left turn arrow made of '*' characters.
 * Input:
 *   None
 * Output:
 *   None
 */
 void MainMenu::leftTurn(){
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j > i; j--) {
            mvprintw(i, 3 - j, "*"); // In dấu '*' tại vị trí (i, 3 - j)
        }
    }
 }

/*
 * Class: MainMenu
 * Method: rightTurn
 * Description: Displays a right turn arrow made of '*' characters.
 * Input:
 *   None
 * Output:
 *   None
 */
 void MainMenu::rightTurn(){
   int height = 3;

   for (int i = 0; i < height; i++) {
      mvprintw(i, 0, "%*s", 24, ""); 

      for (int k = 0; k < i; k++) {
         mvprintw(i, 24 + k, " ");
      }

      for (int j = 0; j < height - i; j++) {
         mvprintw(i, 24 + i + j, "*");
      }

   }
 }

/*
 * Class: MainMenu
 * Method: offTurn
 * Description: Displays an "OFF" symbol.
 * Input:
 *   None
 * Output:
 *   None
 */
 void MainMenu::offTurn(){
   mvprintw(1, 0, "---");
   mvprintw(1, 3, "/%*s\\", 20, "");
   mvprintw(1, 25, "---");

   mvprintw(2, 0, "|%*s/", 2, "");
   mvprintw(2, 2, "/%*s\\ ", 22, ""); 
   mvprintw(2, 27, "|");

   mvprintw(3, 0, "|");
   mvprintw(3, 1, "/%*s\\", 24, "");
   mvprintw(3, 27, "|");
 }

/*
 * Class: MainMenu
 * Method: turnSignal
 * Description: Displays the appropriate turn signal arrow or "OFF" symbol based on the current signal status.
 * Input:
 *   None
 * Output:
 *   None
 */
 void MainMenu::turnSignal(){
    if(signal == OFF){
        offTurn();
    }else if(signal == LEFT){
        leftTurn();
    }else if(signal == RIGHT){
        rightTurn();
    }
 }

/*
 * Class: MainMenu
 * Method: setSignal
 * Description: Sets the turn signal of the electric motorcycle.
 * Input:
 *   signal - The desired turn signal (OFF, LEFT, or RIGHT).
 * Output:
 *   None
 */
 void MainMenu::setSignal(TurnSignal signal){
    this->signal = signal;
 }

/*
 * Class: MainMenu
 * Method: getSignal
 * Description: Gets the current turn signal of the electric motorcycle.
 * Input:
 *   None
 * Output:
 *   Returns the current turn signal.
 */
 TurnSignal MainMenu::getSignal(){
    return this->signal;
 }

/*
 * Class: MainMenu
 * Method: setStartUp
 * Description: Sets the startup status of the electric motorcycle.
 * Input:
 *   startUp - True if the motorcycle is starting up, false otherwise.
 * Output:
 *   None
 */
 void MainMenu::setStartUp(bool startUp){
    this->startUp = startUp;
 }

/*
 * Class: MainMenu
 * Method: getStartUp
 * Description: Gets the current startup status of the electric motorcycle.
 * Input:
 *   None
 * Output:
 *   Returns true if the motorcycle is starting up, false otherwise.
 */
 bool MainMenu::getStartUp(){
    return this->startUp;
 }

/*
 * Class: MainMenu
 * Method: setSpeed
 * Description: Sets the speed of the electric motorcycle.
 * Input:
 *   speed - The desired speed value.
 * Output:
 *   None
 */
 void MainMenu::setSpeed(int speed){
    this->speed = speed;
 }

/*
 * Class: MainMenu
 * Method: getSpeed
 * Description: Gets the current speed of the electric motorcycle.
 * Input:
 *   None
 * Output:
 *   Returns the current speed value.
 */
 int MainMenu::getSpeed(){
    return this->speed;
 }

/*
 * Class: MainMenu
 * Method: startMenu
 * Description: Displays the startup menu for the electric motorcycle, showing default values.
 * Input:
 *   None
 * Output:
 *   None
 */
 void MainMenu::startMenu(){
   string dashes(28, '-');
	string asterisks(4, '*');
   clear();
	turnSignal();
   mvprintw(4, 0, "%sELECTRIC MOTORCYCLE%s", asterisks.c_str(), asterisks.c_str());
	mvprintw(5, 0, "%s", dashes.c_str());
   mvprintw(6, 0, "Battery temperature: ----");
   mvprintw(7, 0, "Battery level: ----");
   mvprintw(8, 0, "Turn signal: ----");
   mvprintw(9, 0, "Fan mode: ----");
   mvprintw(10, 0, "Speed: ----");
   mvprintw(11, 0, "%s", dashes.c_str());
   mvprintw(12, 0, "Start : OFF");
   refresh();
 }

/*
 * Class: MainMenu
 * Method: displayMenu
 * Description: Displays the main menu for the electric motorcycle, showing current status.
 * Input:
 *   None
 * Output:
 *   None
 */
 void MainMenu::displayMenu(){
	if (getStartUp())
	{     
		string dashes(28, '-');
      string asterisks(4, '*');
      clear();
		turnSignal();
		mvprintw(4, 0, "%sELECTRIC MOTORCYCLE%s", asterisks.c_str(), asterisks.c_str());
      mvprintw(5, 0, "%s", dashes.c_str());
      mvprintw(6, 0, "Battery temperature: %d", battery.getBatteryTemperature());
      mvprintw(7, 0, "Battery level: %d", battery.getBatteryLevel());
      if (signal == OFF) {
         mvprintw(8, 0, "Turn signal: OFF");
      } else if (signal == LEFT) {
         mvprintw(8, 0, "Turn signal: LEFT");
      } else if (signal == RIGHT) {
         mvprintw(8, 0, "Turn signal: RIGHT");
      }
      mvprintw(9, 0, "Fan mode: %s", (battery.getFanMode() ? "ON" : "OFF"));
      mvprintw(10, 0, "Speed: %d", speed);
      mvprintw(11, 0, "%s", dashes.c_str());
      mvprintw(12, 0, "Start : ON");
      refresh();
	}
	else
	{
		startMenu();
	}
 }

/*
 * Class: MainMenu
 * Method: executeMenu
 * Description: Executes menu options based on the input key.
 * Input:
 *   key - The key pressed by the user.
 * Output:
 *   None
 */
 void MainMenu::executeMenu(char key){
	if (key == '1')
	{
		setStartUp(true);
	}
	else if (key == '0')
	{
		setStartUp(false);
	}

	if (getStartUp())
	{
		int newSpeed = getSpeed();
		if (key == 'K') // tương ứng với mũi tên trái, xi nhan trái
		{
			setSignal(LEFT);
		}
		else if (key == 'M') // tương ứng với mũi tên phải, xi nhan phải
		{
			setSignal(RIGHT);
		}
		else if (key == 'O') // tắt đèn
		{
			setSignal(OFF);
		}
		else if (key == 'H') // tương ứng với mũi tên lên, tăng tốc độ
		{
			newSpeed++;
			setSpeed(newSpeed);
		}
		else if (key == 'P') // tương ứng với mũi tên xuống, giảm tốc độ
		{
			newSpeed--;
			setSpeed(newSpeed);
		}
	}
 }

/*
 * Function: getInput
 * Description: Monitors user input and sets the exit flag if '0' is pressed.
 * Input:
 *   exitProgram - A flag to indicate whether the program should exit.
 *   key - The key pressed by the user.
 * Output:
 *   None
 */
 void getInput(bool &exitProgram, char &key){
   input.lock();
   while (!exitProgram){   
      key = getch();      
      if (key == '0') {
         cout << endl;
         cout << "The program has exited." << endl;
         exitProgram = true; // Set exit flag to true
      }       
   }
   input.unlock();
}

/*
 * Function: displayData
 * Description: Continuously displays data from the MainMenu object and checks for exit conditions.
 * Input:
 *   exitProgram - A flag to indicate whether the program should exit.
 *   key - The key pressed by the user.
 *   menu - A reference to the MainMenu object.
 * Output:
 *   None
 */
void displayData(bool &exitProgram, char &key, MainMenu &menu){
	while (!exitProgram){
		display.lock();
		menu.executeMenu(key);
		menu.displayMenu();
		key = ' ';
		if (menu.battery.getBatteryLevel() == 0){
			exitProgram = true;
			cout << endl;
			cout << "Battery is empty" << endl;
		}
		display.unlock();
		this_thread::sleep_for(chrono::milliseconds(50));
	}
 }