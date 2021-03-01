//#include "SnakeDirection.h"

#define SNAKE_MAX_LENGTH 32

class Snake {

  byte size;
  byte headPositionX;
  byte headPositionY;
  SnakeDirection direction;
    
public:
  Snake(byte newSize, byte headPositionX, byte headPositionY, SnakeDirection facing) {
      setSize(newSize);
      setDirection(facing);
      setHeadPositionX(headPositionX);
      setHeadPositionY(headPositionY);
  }
  
  void setDirection(SnakeDirection facing) {
    direction = facing;
    Serial.print("Snake is now facing ");
    Serial.println(facing);     //debug
  }
  SnakeDirection getDirection() {
    return direction;
  }

  void setSize(byte newSize) {
    if (newSize < 1) {
      newSize = 1;
    }
    if (newSize > 60) {
      newSize = 60;
    }
    size = newSize;
  }
  
  byte getSize() {
    return size;
  }

  void setHeadPositionX(byte x) {
    if (x < 0) {
      x = 0;
      Serial.println("The x-value was set out of bound and was corrected. (x < 0) --> x = 0");
    }
    if (x >= 8) {
      x = 7;
      Serial.println("The x-value was set out of bound and was corrected. (x >= 8) --> x = 7");
    }
    headPositionX = x;
  }
  
  byte getHeadPositionX() {
    return headPositionX;
  }

  
  void setHeadPositionY(byte y) {
    if (y < 0) {
      y = 0;
      Serial.println("The y-value was set out of bound and was corrected. (y < 0) --> y = 0");
    }
    if (y >= 8) {
      y = 7;
      Serial.println("The y-value was set out of bound and was corrected. (y >= 8) --> y = 7");
    }
    headPositionY = y;
  }
  
  byte getHeadPositionY() {
    return headPositionY;
  }


  bool move() {
    if (direction == UP) {
      Serial.println("move UP");
      headPositionY++;
    }
    else if (direction == DOWN) {
      Serial.println("move DOWN");
      headPositionY--;
    }
    else if (direction == LEFT) {
      Serial.println("move LEFT");
      headPositionX--;
    }
    else if (direction == RIGHT) {
      Serial.println("move RIGHT");
      headPositionX++;
    }
    else {
      
    }

    if (outOfBound()) {
      Serial.println("out of bound -- debug shutdown in 10000ms");
      delay(10000);
      exit(0);
      return false;
      
    }
    return true;
  }

  bool outOfBound() {
    if (headPositionX < 0 || headPositionX >= 8) {
      return true;
    }
    if (headPositionY < 0 || headPositionY >= 8) {
      return true;
    }
    return false;
  }
  
  
};
