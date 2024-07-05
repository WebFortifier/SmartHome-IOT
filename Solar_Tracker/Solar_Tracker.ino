#include <Servo.h> // Includes the servo library

Servo myservo;

#define ldr1 A3 // Set ldr1 analog input pin of East ldr as an integer
#define ldr2 A5 // Set ldr2 analog input pin of West ldr as an integer

int pos = 90; // Initial position of the horizontal movement controlling servo motor
int tolerance = 20; // Allowable tolerance setting - so solar servo motor isn't constantly in motion
   
void setup() {
  myservo.attach(9); // Attaches the servo on digital pin 9 to the horizontal movement servo motor 
  pinMode(ldr1, INPUT); // Set East ldr pin as an input
  pinMode(ldr2, INPUT); // Set West ldr pin as an input
  myservo.write(pos); // Write the starting position of the horizontal movement servo motor 
  delay(1000); // 1 second delay to allow the solar panel to move to its starting position before commencing solar tracking
}

void loop() {      
  int val1 = analogRead(ldr1); // Read the value of ldr1
  int val2 = analogRead(ldr2); // Read the value of ldr2
      
  if ((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
    // No servo motor horizontal movement will take place if the ldr value is within the allowable tolerance
  } else {
    if (val1 > val2) { // If ldr1 senses more light than ldr2 
      pos++; // Increment the position of the horizontal servo motor - this will move the panel position Eastward
    }
    if (val1 < val2) { // If ldr2 senses more light than ldr1
      pos--; // Decrement the position of the horizontal motor - this will move the panel position Westward
    }
  }
     
  if (pos > 180) {
    pos = 180; // Reset the horizontal position of the motor to 180 if it tries to move past this point
  }
  if (pos < 0) {
    pos = 0; // Reset the horizontal position of the motor to 0 if it tries to move past this point
  }
  myservo.write(pos); // Write the new position to the horizontal motor
  delay(50);
}
