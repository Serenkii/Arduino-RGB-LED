
class Fruit {

  byte x;
  byte y;
  
public: 
  Fruit(byte newX, byte newY) {
      setX(newX);
      setY(newY);
  }

  void respawn(byte snakeOccupied[][2]) {
    Serial.println("Fruit needs to respawn");
    x = random(0, 8);   //a random number in [0; 8)
    y = random(0, 8);
    for (byte i = 0; i < SNAKE_MAX_LENGTH; i++) {
      if (snakeOccupied[i][0] == x && snakeOccupied[i][1] == y) {
        Serial.println("The random fruit position is taken, let's try again.");
        respawn(snakeOccupied);
        break;                
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
