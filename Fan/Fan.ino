#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 3
#define DHTTYPE DHT11
#define SWITCH_PIN 13 // Example pin for pushbutton
#define FAN_PIN 6    // Example pin for fan

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(FAN_PIN, OUTPUT);    // Corrected pinMode for the fan pin
  pinMode(SWITCH_PIN, INPUT);  // Corrected pinMode for the switch pin
  dht.begin();
  lcd.begin();
  lcd.backlight(); // Turn on backlight
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(t, h);
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  Heat index: "));
  Serial.print(hif);
  Serial.println(F("°C"));

  // Send the data to serial monitor
  Serial.print("Fan state: ");
  if (digitalRead(FAN_PIN) == HIGH) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(t);
  lcd.print("C");
  
  delay(1500);

  if (digitalRead(SWITCH_PIN) == HIGH) {
   //  Switch is pressed, turn on the fan regardless of humidity
    digitalWrite(FAN_PIN, HIGH);
    Serial.println(F("Fan turned on"));
   } else {
    // Switch is not pressed, check temperature and humidity to determine fan status
    if (t >= 28 && h >= 25) { // Adjust threshold as needed
      // Turn on the fan
      digitalWrite(FAN_PIN, HIGH);
      Serial.println(F("Fan turned on"));
    } else {
      // Turn off the fan
      digitalWrite(FAN_PIN, LOW);
      Serial.println(F("Fan turned off"));
    }
   }

  delay(2000); // Wait for a few seconds before next reading
}
