enum SnakeDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

#define SNAKE_MAX_LENGTH 32

class Snake {
  byte size;
  char direction;
    
public:
  char body[SNAKE_MAX_LENGTH][2];   //position of all bodyparts (/-pixels)

  Snake(char headPositionX, char headPositionY, SnakeDirection facing) {
      setSize(1);
      setDirection(facing);
      body[0][0] = headPositionX;
      body[0][1] = headPositionY;
  }

  void turnRight() {
    Serial.print("turnRight() was called | direction was: ");
    Serial.println(direction, DEC);
    direction++;
    if (direction >= 4) {
      direction = 0; 
    }
    Serial.print("direction is now: ");
    Serial.println(direction, DEC);
  }
  void turnLeft() {
    Serial.print("turnLeft() was called | direction was: ");
    Serial.println(direction, DEC);
    direction--;
    if (direction < 0) {  
      direction = 3; 
    }
    Serial.print("direction is now: ");
    Serial.println(direction, DEC);
  }
  
  void setDirection(SnakeDirection facing) {
    direction = facing;
    //Serial.print("Snake is now facing ");
    //Serial.println(facing);     //debug
  }
  SnakeDirection getDirection() {
    return direction;
  }

  void setSize(byte newSize) {
    if (newSize < 1) {
      newSize = 1;
    }
    if (newSize > SNAKE_MAX_LENGTH) {
      newSize = SNAKE_MAX_LENGTH;
    }
    size = newSize;
    Serial.print("new size: ");
    Serial.println(size);
  }
  
  byte getSize() {
    return size;
  }
  
  char getHeadPositionX() {
    return body[0][0];
  }
  
  char getHeadPositionY() {
    return body[0][1];
  }

  void setHeadPosition(char x, char y) {
    body[0][0] = x;
    body[0][1] = y;
  }

  bool move() {
    Serial.println("move");

    char snakeEnding[2] = {body[size - 1][0],body[size - 1][1]};
    
    for (int i = size - 1; i > 0 ; i--) {
      body[i][0] = body[i - 1][0];
      body[i][1] = body[i - 1][1];
    }
    if (direction == UP) {
      //Serial.println("move UP");
      body[0][1]++;
    }
    else if (direction == DOWN) {
      //Serial.println("move DOWN");
      body[0][1]--;
    }
    else if (direction == LEFT) {
      //Serial.println("move LEFT");
      body[0][0]--;
    }
    else if (direction == RIGHT) {
      //Serial.println("move RIGHT");
      body[0][0]++;
    }
    else {
      Serial.println("problem with direction");
    }

    if (outOfBound()) {
      Serial.println("Snake will now go through the wall.");
      wallTeleport();
    }
    if (collidesWithItself()) {
      Serial.println("Snake hit itself.");
      body[0][0] = snakeEnding[0];
      body[0][1] = snakeEnding[1];
      return false;
    }
    
    return true;
  }

  void wallTeleport() {
    
//    Serial.print("Snake Position:     x == ");
//    Serial.print(body[0][0]);
//    Serial.print("  y == ");
//    Serial.println(body[0][1]);

    if (body[0][0] < 0) {   //I just found out bytes are always unsigned... makeshift solution... will fix later with char instead of byte
      //Serial.println("Snake goes through wall because:      body[0][0] < 0   -->   body[0][0] = 7;");
      body[0][0] = 7;
    }
    else if (body[0][1] < 0) {
      //Serial.println("Snake goes through wall because:      body[0][1] < 0   -->   body[0][1] = 7;");
      body[0][1] = 7;
    }
    else if (body[0][0] >= 8) {
      //Serial.println("Snake goes through wall because:      body[0][0] > 7   -->   body[0][0] = 0;");
      body[0][0] = 0;
    }
    else if (body[0][1] >= 8) {
      //Serial.println("Snake goes through wall because:      body[0][1] > 7   -->   body[0][1] = 0;");
      body[0][1] = 0;
    }
    else {
      Serial.println("The snake isn't out of bound at all... exit");
      exit(1);
    }

//    Serial.print("NEW Snake Position: x == ");
//    Serial.print(body[0][0]);
//    Serial.print("  y == ");
//    Serial.println(body[0][1]);
//    Serial.println();
  }

  bool collidesWithItself() {
    for (byte i = 1; i < size; i++) {
      if (body[i][0] == body[0][0] && body[i][1] == body[0][1]) {
        return true;
      }
    }
    return false;
  }

  bool outOfBound() {
    if (body[0][0] < 0 || body[0][0] >= 8) {
      return true;
    }
    if (body[0][1] < 0 || body[0][1] >= 8) {
      return true;
    }
    return false;
  }
  
  
};
