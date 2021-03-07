/*  Serenkii
    2021-03-07
    Changes:
    -more messages are added and game ending overhauled
*/


//We always have to include the library
#include "LedControl.h"
#include "Snake.h"
#include "Fruit.h"

//constants
#define MOVEMENT_SPEED 700

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
  lc.setIntensity(0, 0);  //0,8
  lc.clearDisplay(0);
  snake.setHeadPosition(random(2, 6), random(2, 6));      //random starting position
  snake.setDirection(random(0, 4));                       //random direction
  drawSnake();
  fruit.respawn(snake.body);
  drawFruit();
  
  Serial.begin(9600);
}

void loop() {
  getUserInput();
  if (cooldownOver()) {
    bool succesfulMove = snake.move();

    if(snake.getSize() == SNAKE_MAX_LENGTH) {
      win();
    }

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
      lose();
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




//MESSAGES FOR GAME ENDINGS
void win() {
  //                     Y                                                   O                                                  U
  byte wonMessage[48]={0,0,0,0,0,0,0,0,B00000110,B00001000,B01110000,B00001000,B00000110,0,B00111100,B01000010,B01000010,B01000010,B00111100,0,B00111110,B01000000,B01000000,B01000000,B00111110,0,0,0,
  B00111110,B01000000,B00111000,B01000000,B00111110,0,B00111100,B01000010,B01000010,B01000010,B00111100,0,B01111110,B00001100,B00011000,B00110000,B01111110,0,B01011110,0};
  //W                                                 O                                                   N                                                   !

  for (byte loops = 0; loops < 9; loops++) {
    delay(5000);
  
    gameOver();
  
    for (byte i = 0; i <= 48 - 8; i++) {
      for (byte j = 0; j < 8; j++) {
        lc.setRow(0, j, wonMessage[j + i]);
      }
      delay(200);
    }
    delay(500);
    lc.clearDisplay(0);
    drawSnake();
    drawFruit();
  }

  Serial.println("The game will shut down in one minute. (Because you won...)");
  delay(60000);
  exit(0);
}

void lose() {
  //                                     Y                                                   O                                                  U
  byte lostMessage[58]={0,0,0,0,0,0,0,B00000110,B00001000,B01110000,B00001000,B00000110,0,B00111100,B01000010,B01000010,B01000010,B00111100,0,B00111110,B01000000,B01000000,B01000000,B00111110,0,0,0,
  B01111110,B01000000,B01000000,B01000000,B01000000,0,B00111100,B01000010,B01000010,B01000010,B00111100,0,B00100100,B01001010,B01001010,B01001010,B00110000,0,B00000010,B00000010,B01111110,B00000010,B00000010,0,
  B01000000,B00100110,B00100000,B00100000,B00100110,B01000000,0};
  //L                                                 O                                                   S                                                 T
  //:(

  for (byte loops = 0; loops < 9; loops++) {
    delay(5000);
  
    gameOver();
  
    for (byte i = 0; i <= 58 - 8; i++) {
      for (byte j = 0; j < 8; j++) {
        lc.setRow(0, j, lostMessage[j + i]);
      }
      delay(250);
    }
    delay(500);
    lc.clearDisplay(0);
    drawSnake();
    drawFruit();
  }

  Serial.println("The game will shut down in one minute. (Because you lost...)");
  delay(60000);
  exit(0);
}

void gameOver() {
  //                                        G                                                   A                                                   M                                                   E
  byte gameOverMessage[62]={0,0,0,0,0,0,0,0,B00111100,B01000010,B01010010,B01010010,B00110000,0,B01111100,B00010010,B00010010,B00010010,B01111100,0,B01111110,B00000100,B00001000,B00000100,B01111110,0,B01111110,B01010010,B01010010,
  B01010010,0,0,0,B00111100,B01000010,B01000010,B01000010,B00111100,0,B00001110,B00110000,B01000000,B00110000,B00001110,0,B01111110,B01010010,B01010010,B01010010,0,B01111110,B00010010,B00010010,B01101100,0,0,0,0,0,0,0,0};
  //(E)           O                                                   V                                                   E                                         R
  
  for (byte i = 0; i <= 62 - 8; i++) {
    for (byte j = 0; j < 8; j++) {
      lc.setRow(0, j, gameOverMessage[j + i]);
    }
    delay(250);
  }
}
