
//We always have to include the library
#include "LedControl.h"
#include "SnakeDirection.h"
#include "Snake.h"
#include "Fruit.h"

LedControl lc = LedControl(12,10,11,1);

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
