
#include <Wire.h>
#include <hd44780.h>  // Main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i/o class header

#define ECHO_PIN 3
#define TRIG_PIN 4

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Distance:");

  // Initialize the HC-SR04 sensor
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);

  // Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Ultrasonic sensor:");
}

void loop() {
  float distance = readDistance();  // Call the function to read the sensor data and get the distance
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear the previous value
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Serial output for debugging
  Serial.print(distance);           
  Serial.println(" cm");            

  delay(400);  // Delay for 400 milliseconds before repeating the loop
}

// Function to read the sensor data and calculate the distance
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);   // Set trig pin to low to ensure a clean pulse
  delayMicroseconds(2);         // Delay for 2 microseconds
  digitalWrite(TRIG_PIN, HIGH);  // Send a 10 microsecond pulse by setting trig pin to high
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);  // Set trig pin back to low

  // Measure the pulse width of the echo pin and calculate the distance value
  float distance = pulseIn(ECHO_PIN, HIGH) / 58.00;  // Formula: (340m/s * 1us) / 2
  return distance;
}
