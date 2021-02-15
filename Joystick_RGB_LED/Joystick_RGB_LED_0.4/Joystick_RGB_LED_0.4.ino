//2021/02/12
//Marian

/*
 * VERSON 0.4:
 * broken mess
 * 
 */
// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

const int BLUE = 3; //outputs to RGB LED
const int GREEN = 5;
const int RED = 6;

int x;
int y;
bool on;
int RGB[3];

const int MAXIMUM = 1023;
const int X_DEFAULT = 516;
const int Y_DEFAULT = 518;

int counter = 0;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  analogWrite(RED, 127);
  analogWrite(GREEN, 127);
  analogWrite(BLUE, 127);
  
  Serial.begin(9600);
}

void loop() {
  x = analogRead(X_pin);
  y = analogRead(Y_pin);
  on = digitalRead(SW_pin);

  int xNegativeAbsolute = (x - X_DEFAULT) * (-1);
  int yNegativeAbsolute = (y - Y_DEFAULT) * (-1);
  int xPositveAbsolute = x - X_DEFAULT;
  int yPositveAbsolute = y - Y_DEFAULT;

  xNegativeAbsolute = makeMinimumZero(xNegativeAbsolute);
  yNegativeAbsolute = makeMinimumZero(yNegativeAbsolute);
  xPositveAbsolute = makeMinimumZero(xPositveAbsolute);
  yPositveAbsolute = makeMinimumZero(yPositveAbsolute);
      
  int redDiagonal = round(abs((xNegativeAbsolute * cos(degreeToRadian(0)))+ (yNegativeAbsolute * sin(degreeToRadian(0)))));
  int greenDiagonal = round(abs((xNegativeAbsolute * cos(degreeToRadian(120)))+ (yNegativeAbsolute * sin(degreeToRadian(120)))));
  int blueDiagonal = round(abs((xNegativeAbsolute * cos(degreeToRadian(240)))+ (yPositveAbsolute * sin(degreeToRadian(240)))));

  RGB[0] = redDiagonal / (517 / 255);          
  RGB[1] = greenDiagonal / (517 / 255);
  RGB[2] = blueDiagonal / (517 / 255);
  enforceMaxMin();
  analogWrite(RED, RGB[0]);
  analogWrite(GREEN, RGB[1]);
  analogWrite(BLUE, RGB[2]);
  
  if (counter == 50) {
    consolePrint();
    counter = 0;
  }
  counter++;
  delay(20);        //50
}

float degreeToRadian(int degree) {
  return (degree / 360) * 2 * PI;
}

int makeMinimumZero(int number) {
  if (number < 0) {
    number == 0;
  }
  return number;
}

void enforceMaxMin() {
  for (int i = 0; i < 3; i++) {
    if (RGB[i] > 255) {
      RGB[i] = 255;
    }
    if (RGB[i] < 0) {
      RGB[i] = 0;
    }
  }
}

void consolePrint() {
  Serial.print("Switch:  ");
  Serial.print(on);
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.println(x);
  Serial.print("Y-axis: ");
  Serial.println(y);
  Serial.print("RGB-Values: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(RGB[i]);
    Serial.print(", ");
  }
  Serial.print("\n");
  Serial.print("          red, green, blue");
  Serial.print("\n\n");
}
