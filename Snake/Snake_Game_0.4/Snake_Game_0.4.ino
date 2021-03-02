/*  Serenkii
    2021-03-02
    The moving point on the matrix is now controlled by two buttons. One to turn left, one to turn right.
*/


//We always have to include the library
#include "LedControl.h"
#include "SnakeDirection.h"
#include "Snake.h"
#include "Fruit.h"

//buttons
#define LEFT_BUTTON_PIN 3
#define RIGHT_BUTTON_PIN 2

bool leftButton = HIGH;   //HIGH == true
bool rightButton = HIGH;  //HIGH == true

//LED-Matrix
LedControl lc = LedControl(12, 10, 11, 1);

//Snake object --> Snake(size, x, y, facing)
Snake snake = Snake(1, 3, 3, UP);

void setup() {
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);   //if button is pressed, digitialRead will return false
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);

  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);  //0,8
  lc.clearDisplay(0);
  drawSnake();

  Serial.begin(9600);
}

void loop() {
  getUserInput();
  if (cooldownOver()) {
    snake.move();
    drawSnake();
  }
  //delay(5000);
}

bool cooldownOver() {   //return true every x ms, so drawSnake and move is executed.
  static unsigned long startTime = millis();
  //Serial.println(startTime);
  unsigned long currentTime = millis();
  if (currentTime - startTime >= 5000) {
    Serial.print("The move-cooldown is over! The current time (ms) is: ");
    Serial.println(currentTime);
    startTime = currentTime;
    return true;
  }
  return false;
}

void drawSnake() {
  lc.clearDisplay(0);
  lc.setLed(0, snake.getHeadPositionX(), snake.getHeadPositionY(), true);
}

void getUserInput() {
  if (digitalRead(LEFT_BUTTON_PIN) == false) {
  //Serial.println("left button is being pressed...");    //DEBUG
    if (leftButton == true) {
      snake.turnLeft();
      //Serial.println("left button wasn't pressed before, so the snake should turn left and the leftButton-bool should be false");    //DEBUG
      leftButton = false;
    }
  }
  else {
    leftButton = true;    //no input
    //Serial.println("left button is not being pressed, so leftButton-bool is true");    //DEBUG
  }

  if (digitalRead(RIGHT_BUTTON_PIN) == false) {
    //Serial.println("right button is being pressed...");    //DEBUG
    if (rightButton == true) {
      snake.turnRight();
      //Serial.println("right button wasn't pressed before, so the snake should turn right and the rightButton-bool should be false");    //DEBUG
      rightButton = false;
    }
  }
  else {
    rightButton = true;    //no input
    //Serial.println("right button is not being pressed, so rightButton-bool is true");    //DEBUG
  }
  //Serial.println(); 
}
