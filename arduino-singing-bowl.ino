#include <Servo.h>

Servo servo1;
const int buttonPin = 3;
const int servoPin = 9;
const int debounceDelay = 50;

int on;
int buttonReading;
int lastSteadyState = LOW;
int lastFlickerableState = LOW;
long timeInBetweenButtonPresses;
unsigned long lastDebounceTime = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("setting things up...");
  pinMode(buttonPin, INPUT);
  servo1.attach(servoPin);
  on = false;
}

void loop() {
  buttonReading = digitalRead(buttonPin);
  
  if (buttonReading != lastFlickerableState) {
    Serial.println("lastFlicerableState: " + String(lastFlickerableState));
    Serial.println("buttonReading: " + String(buttonReading)); 
    Serial.println("flickering...");
    lastDebounceTime = millis();
    lastFlickerableState = buttonReading;
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    Serial.println("millis: " + String(millis()));
    Serial.println("lastDebounce: " + String(lastDebounceTime));
    Serial.println("debounceDelay: " + String(debounceDelay));
    if (lastSteadyState == HIGH && buttonReading == LOW) {
      Serial.println("The button is pressed");
      on = !on;
    }
    else if (lastSteadyState == LOW && buttonReading == HIGH) {
      Serial.println("The button is released");
    }

   lastSteadyState = buttonReading;
  }
  
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
