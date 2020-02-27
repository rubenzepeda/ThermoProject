#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

int relay=5;

Adafruit_AM2320 am2320 = Adafruit_AM2320();

void setup() 
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(10); // hang out until serial port opens
  }

  Serial.println("Temperature Readings");
  am2320.begin();
  pinMode(relay,OUTPUT);

}

void loop() 
{
  float x=am2320.readTemperature();
  Serial.print("Room Temperature: "); Serial.println(x);
  delay(2000);

  if (x<25)
  {
    digitalWrite(relay,HIGH); 
  }

  if (x>=26) 
    {
    digitalWrite(relay,LOW);
    }  
}
