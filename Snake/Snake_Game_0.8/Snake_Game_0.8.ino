/*  Serenkii
    2021-03-03
    The snake now checks for collision with itself.
*/


//We always have to include the library
#include "LedControl.h"
#include "Snake.h"
#include "Fruit.h"

//constants
#define MOVEMENT_SPEED 1000

//buttons
#define LEFT_BUTTON_PIN 3
#define RIGHT_BUTTON_PIN 2

bool leftButton = HIGH;   //HIGH == true
bool rightButton = HIGH;  //HIGH == true

//LED-Matrix
LedControl lc = LedControl(12, 10, 11, 1);

//Snake object --> Snake(size, x, y, facing)
Snake snake = Snake(3, 3, UP);

//Fruit object
Fruit fruit = Fruit(6, 6);


void setup() {
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);   //if button is pressed, digitialRead will return false
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);


  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.shutdown(0, false);
  lc.setIntensity(0, 4);  //0,8
  lc.clearDisplay(0);
  drawSnake();
  drawFruit();
  
  Serial.begin(9600);
}

void loop() {
  getUserInput();
  if (cooldownOver()) {
    bool succesfulMove = snake.move();

    if (succesfulMove) {
      lc.clearDisplay(0);
      drawSnake();
      drawFruit();
      
      if (collidesWithFruit()) {
        snake.setSize(snake.getSize() + 1);
        fruit.respawn(snake.body);
      }
    }
    else {
      Serial.println("You lost");
    }
  }
}

void drawFruit() {
  lc.setLed(0, fruit.getX(), fruit.getY(), true);
}

bool collidesWithFruit() {
  if (snake.body[0][0] == fruit.getX() && snake.body[0][1] == fruit.getY()) {
    Serial.println("Snake eats Fruit");
    return true;
  }
  return false;
}

bool cooldownOver() {   //return true every x ms, so drawSnake and move is executed.
  static unsigned long startTime = millis();
  //Serial.println(startTime);
  unsigned long currentTime = millis();
  if (currentTime - startTime >= MOVEMENT_SPEED) {
    //Serial.print("The move-cooldown is over! The current time (ms) is: ");
    //Serial.println(currentTime);
    startTime = currentTime;
    return true;
  }
  return false;
}

void drawSnake() {
  for (byte i = 0; i < snake.getSize(); i++) {
      lc.setLed(0, snake.body[i][0], snake.body[i][1], true);
  }
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
