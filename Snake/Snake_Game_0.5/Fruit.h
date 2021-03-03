
class Fruit {

  byte x;
  byte y;
  
public: 
  Fruit() {
      
  }

  void respawn(byte snakeOccupied[][2]) {
    x = random(0, 8);   //a random number in [0; 8)
    y = random(0, 8);
    for (int i = 0; i < SNAKE_MAX_LENGTH; i++) {
      if (snakeOccupied[i][0] == x || snakeOccupied[i][1] == y) {
        respawn(snakeOccupied);
        return;
      }
    }
  }

  void setX(byte newX) {
    x = newX;
  }
  byte getX() {
    return x;
  }

  void setY(byte newY) {
    y = newY; 
  }
  
  byte getY() {
    return y;
  }
};
