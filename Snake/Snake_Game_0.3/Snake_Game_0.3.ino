/*  Serenkii
 *  2021-03-01
 *  I made a moving point that can be controlled with a keypad.
 *  I just realized that snake actually doesn't need four "direction-inputs" (in this case 2, 4, 6, 8)
 *  It only needs left and right. So probably I will switch to two simple buttons instead of this huge contraption...
 *  
 */

 
//We always have to include the library
#include <Keypad.h>
#include "LedControl.h"
#include "SnakeDirection.h"
#include "Snake.h"
#include "Fruit.h"

//Keypad constants
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


//LED-Matrix
LedControl lc = LedControl(12,10,11,1);

//Snake object --> Snake(size, x, y, facing)
Snake snake = Snake(1, 3, 3, UP);

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  lc.setIntensity(0,0);   //0,8
  lc.clearDisplay(0);

  Serial.begin(9600);
}

void loop() { 
  //debugMove();
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
    startTime += 5000;
    return true;
  }
  return false;
}

void drawSnake() {
  lc.clearDisplay(0);
  lc.setLed(0, snake.getHeadPositionX(), snake.getHeadPositionY(), true);
}

void getUserInput() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
    if(customKey == '2') {
      Serial.println("setDirection(UP)");
      snake.setDirection(UP);
    }
    if(customKey == '6') {
      snake.setDirection(RIGHT);
      Serial.println("setDirection(RIGHT)");
    }
    if(customKey == '8') {
      snake.setDirection(DOWN);
      Serial.println("setDirection(DOWN)");
    }
    if(customKey == '4') {
      snake.setDirection(LEFT);
      Serial.println("setDirection(LEFT)");
    }
  }
}

void debugMove() {
    snake.setSize(5);
  Serial.println(snake.getSize());
  
  snake.setDirection(UP);
  snake.move();
  Serial.print("X: ");
  Serial.print(snake.getHeadPositionX());
  Serial.print(" Y: ");
  Serial.println(snake.getHeadPositionY());
  delay(2000);
  
  snake.setDirection(DOWN);
  snake.move();
  Serial.print("X: ");
  Serial.print(snake.getHeadPositionX());
  Serial.print(" Y: ");
  Serial.println(snake.getHeadPositionY());
  delay(2000);
  
  snake.setDirection(LEFT);
  snake.move();
  Serial.print("X: ");
  Serial.print(snake.getHeadPositionX());
  Serial.print(" Y: ");
  Serial.println(snake.getHeadPositionY());
  delay(2000);
  
  snake.setDirection(RIGHT);
  snake.move();
  Serial.print("X: ");
  Serial.print(snake.getHeadPositionX());
  Serial.print(" Y: ");
  Serial.println(snake.getHeadPositionY());
  delay(2000);
  
  
  delay(1000);
}
