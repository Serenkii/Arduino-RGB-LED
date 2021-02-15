//2021/02/12
//Marian


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
  RGB[0] = ((x - X_DEFAULT) * (-1)) / (X_DEFAULT / 255);
  RGB[1] = ((y - Y_DEFAULT) * (-1)) / (Y_DEFAULT / 255);
  RGB[2] = (x - X_DEFAULT) / (X_DEFAULT / 255);
  enforceMaxMin();
  analogWrite(RED, RGB[0]);
  analogWrite(GREEN, RGB[1]);
  analogWrite(BLUE, RGB[2]);
  if (counter == 10) {
    consolePrint();
    counter = 0;
  }
  counter++;
  delay(100);
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
