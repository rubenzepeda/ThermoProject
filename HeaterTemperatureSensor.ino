// Libraries needed for Sensor
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

// Libraries needed for Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define Display 
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

int relay=5; // Defines pin 5 as the pin for the relay.

Adafruit_AM2320 am2320 = Adafruit_AM2320();

void setup() 
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(10); // hang out until serial port opens
  }

  Serial.println("Temperature Readings"); 
  am2320.begin(); // starts the temperature sensor
  pinMode(relay,OUTPUT); // sets relay pin as an OUTPUT
  
}

void loop() 
{
  float x=am2320.readTemperature();  // reads the temperature value and stores it in the variable x
  Serial.print("Room Temperature: "); Serial.println(x);  // prints out the temperature
  delay(2000);

  // Set up for Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();                      // Make sure the display is cleared
  display.setTextSize(1.5);                    // Size of the text
  display.setTextColor(WHITE);                 // Color of the text
  display.setCursor(0,0);                      // Location of the text
  display.println("Room Temperature:"); 
  display.println(x);                          // prints out the value for room temperature
  display.println("Heater Status:");
  display.display();                                         // Update the display
  
  if (x<25)   // Logical condition to turn on the heater 
  {
    digitalWrite(relay,HIGH);
    display.println("ON");
    display.display();
  }

  if (x>=26)   // Logical condition to turn off the heater
    {
    digitalWrite(relay,LOW);
    display.println("OFF");
    display.display();
    } 
}
