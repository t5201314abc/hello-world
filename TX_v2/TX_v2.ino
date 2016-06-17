#include "DHT.h"
//uv index sensor
#include <Wire.h>
#include "Adafruit_SI1145.h"

#define DHTPIN 2     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);
//uv index sensor
Adafruit_SI1145 uv = Adafruit_SI1145();

void setup()
{
  Serial.begin(115200);
  
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }

  Serial.println("OK!");
}

void loop()
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  float UVindex = uv.readUV();
  UVindex /= 100.0;  
  //Serial.print("UV: ");  Serial.println(UVindex);

  Serial.print("<T");
  Serial.print(t); 
  Serial.print(">");

  delay(2000);

  Serial.print("<H");
  Serial.print(h); 
  Serial.print(">");

  delay(2000);
  
  Serial.print("<U");
  Serial.print(UVindex); 
  Serial.print(">");

  delay(2000);
}
