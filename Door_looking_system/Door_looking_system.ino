#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;
int pos = 0; // position of servo motor
int currentposition = 0;
char password[] = "8888"; // Change this to your desired password


const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'} // Fixed the last row definition
};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0}; // Corrected parentheses

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int red = 13;
int green = 12;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change pin numbers according to your LCD connections

void setup() {
  displayscreen();
  myservo.attach(8); // Servo motor connection
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  lcd.begin();
}

void loop() {
  if (currentposition == 0) {
    displayscreen();
  }
  char code = keypad.getKey();
  if (code != NO_KEY) {
    if (code == '*') { // Reset input
      currentposition = 0;
      lcd.clear();
      displayscreen();
    } else {
      if (currentposition < 4) { // Check if the password is not complete
        password[currentposition++] = code; // Add entered character to the password
        lcd.setCursor(currentposition - 1, 1);
        lcd.print("*");
      }
      if (currentposition == 4) { // Check if the password is complete
        if (checkPassword()) {
          unlockdoor();
        } else {
          incorrect();
        }
        currentposition = 0;
      }
    }
  }
}


// Function to check the entered password
// Function to check the entered password
bool checkPassword() {
  for (int i = 0; i < 4; ++i) {
    if (password[i] != "8888"[i]) { // Compare with the predefined password
      return false;
    }
  }
  return true;
}

// Function to unlock the door
void unlockdoor() {
  delay(2000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Access Granted");
  lcd.setCursor(4, 1);
  lcd.print("WELCOME!!");
  // Open the door
  for (pos = 90; pos >= 0; pos -= 5) {
    myservo.write(pos);
    delay(5);
  }
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  delay(2000);

  delay(1000);
  counterbeep();

  delay(1000);

  // Close the door
  for (pos = 0; pos <= 90; pos += 5) {
    myservo.write(pos);
    delay(15);
  }
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  delay(500);
  lcd.clear();
  displayscreen();
}

// Function for incorrect code
void incorrect() {
  delay(500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CODE");
  lcd.setCursor(6, 0);
  lcd.print("INCORRECT");
  lcd.setCursor(4, 1);
  lcd.print("TRY AGAIN !!!");
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  delay(3000);
  lcd.clear();
  displayscreen();
}

// Function to display the screen
void displayscreen() {
  lcd.setCursor(0, 0);
  lcd.print("Enter password:");
}

// Function for countdown and re-locking
void counterbeep() {
  // Your countdown logic here
}
