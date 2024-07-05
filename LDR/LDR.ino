#include <Arduino.h>

#define sensorPin A0   // LDR connected to analog pin A0
#define outputPin 13   // LED connected to digital pin 13

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read analog value from LDR
  Serial.println(sensorValue);

  // Set a threshold value for darkness detection
  int threshold = 500; // Adjust this value based on your LDR and ambient light conditions

  // Check if the sensor value is below the threshold (indicating darkness)
  if (sensorValue < threshold) {
    digitalWrite(outputPin, 0); // Turn off LED
  } else {
    digitalWrite(outputPin, 1);  // Turn on LED
  }

  delay(100); // Add a small delay for stability
}
