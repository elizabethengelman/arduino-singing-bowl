#include <Servo.h>

Servo servo1;
const int buttonPin = 3;
const int servoPin = 9;
int on;
int buttonReading;
int buttonPrevious = 0;
long timeInBetweenButtonPresses;
long debounce = 200;


void setup() {
  Serial.begin(9600);
  Serial.println("setting things up...");
  pinMode(buttonPin, INPUT);
  servo1.attach(servoPin);
  on = false;
}

void loop() {
  buttonReading = digitalRead(buttonPin);
 
  if (buttonReading == HIGH && buttonPrevious == LOW && millis() - timeInBetweenButtonPresses > debounce ) {
    on = !on;
    timeInBetweenButtonPresses = millis();
  }

  buttonPrevious = buttonReading;
  if (on) {
    startStriker();
  }    
}

void startStriker() {
    int position = 180;
    int timeInBetween = 1000;
  
    servo1.write(position);   // Tell servo to go to 180 degrees

    delay(500);         // Pause to get it time to move

    servo1.write(0);     // Tell servo to go to 0 degrees

    delay(timeInBetween);  
}
