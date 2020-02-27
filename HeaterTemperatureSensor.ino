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

// Define variables
int relay=5;  // Defines relay as pin 5
int TempLow = 25; // Defines the lower boundary of our range 
int TempHigh = 26; // Defines the upper boundary of our range 

Adafruit_AM2320 am2320 = Adafruit_AM2320();  // Defines temperature sensor using library

void setup() 
{
  Serial.begin(9600);  // Begins communication
  while (!Serial)
  {
    delay(10); // Waits until serial port opens
  }
  
  
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
  display.println("Room Temperature:");        // prints out message
  display.println(x);                          // prints out the value for room temperature
  display.println("Heater Status:");           // prints out message
  display.display();                           // Update the display
  
  if (x<TempLow)   // Logical condition to turn on the heater when the temperature goes below the lower value.  
  {
    digitalWrite(relay,HIGH);
    display.println("ON");
    display.display();
  }
  
  elseif (x=>TempLow && x<=TempHigh) // Logical condition to keep the heater on until it hits the upper value for temperature
  {
    digitalWrite(relay,HIGH);
    display.println("ON");
    display.display();
  }

  else // anything above TempHigh will turn the heater off 
    {
    digitalWrite(relay,LOW);
    display.println("OFF");
    display.display();
    } 
}
