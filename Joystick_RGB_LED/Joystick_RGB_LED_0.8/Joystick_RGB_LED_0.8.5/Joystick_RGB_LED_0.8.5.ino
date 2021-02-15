//2021/02/14
//Marian
//raw concept of circles working

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

//POINTS                                                        //middle ~ {5, 7}, values are corrected; commented below uncorrected
const int RED_P[2] = {516, 7};              //{511, 0}
const int GREEN_P[2] = {-251, -436};        //{-256, -443}
const int BLUE_P[2] = {-251, 450};          //{-256, 443}
int point[2] = {x, y};

float distanceToRed;
float distanceToGreen;
float distanceToBlue;

const int MAXIMUM = 1022;     //1023
const int MIDDLE = MAXIMUM / 2;

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

  x = x - MIDDLE;     // maybe -4 and -6 so that middle of joystick is 0 ; now borders are +-511
  y = y - MIDDLE;    //Hiermit habe ich nun ein "normales" Koordinatensystem

  point[0] = x;
  point[1] = y;

  distanceToRed = distanceBetweenPoints(RED_P, point);
  distanceToGreen = distanceBetweenPoints(GREEN_P, point);
  distanceToBlue = distanceBetweenPoints(BLUE_P, point);

  RGB[0] = (1150 - distanceToRed - (1150 - 700)) / ((1150 - 700) / 255);       //(maxDistance - distance - (maxDistanceRed - radiusOfColorCircle)) / ((maxDistanceRed - radiusOfColorCircle) / 255)
  RGB[1] = (1208 - distanceToGreen - (1208 - 700)) / ((1208 - 700) / 255);
  RGB[2] = (1225 - distanceToBlue - (1225 - 700)) / ((1225 - 700) / 255);
  enforceMaxMin();
  analogWrite(RED, RGB[0]);
  analogWrite(GREEN, RGB[1]);
  analogWrite(BLUE, RGB[2]);
  
  if (counter == 50) {
    consolePrint();
    counter = 0;
  }
  counter++;
  delay(20);     
}

float distanceBetweenPoints(int pointA[2], int pointB[2]) {
  return sqrt(sq((pointA[0] - pointB[0]) * 1.0) + sq((pointA[1] - pointB[1]) * 1.0));
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
  Serial.println(on);
 
  Serial.print("point == {");
  Serial.print(point[0]);
  Serial.print(", ");
  Serial.print(point[1]);
  Serial.println("}");

  Serial.print("distanceToRed   == ");
  Serial.println(distanceToRed);
  Serial.print("distanceToGreen == ");
  Serial.println(distanceToGreen);
  Serial.print("distanceToBlue   == ");
  Serial.println(distanceToBlue);
  
  Serial.print("RGB-Values: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(RGB[i]);
    Serial.print(", ");
  }
  Serial.print("\n");
  Serial.print("          red, green, blue");
  Serial.print("\n\n");
}
