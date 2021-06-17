#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include "TimerOne.h"

Adafruit_SHT31 sht313 = Adafruit_SHT31();
Adafruit_SHT31 sht314 = Adafruit_SHT31();

  //Arduino A
  float TPETA ;
  float HPETA ;
  float TPETB ;
  float HPETB ;

void setup() {
  sht313.begin(0x44);
  sht314.begin(0x45);
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Timer1.initialize(3000000); // initialize timer1, and set a 1 second period
  //  "TimerX.initialize(period)"
  //
  //  here ,
  //
  //  X = 0, 1, 2; (Since arduino uno has three timer zero, one and two)
  //
  //period = period mean time in microsecond.By default period is set at 1 second.
  Timer1.attachInterrupt(kirim_data);
}

void loop()
{
   TPETA = sht313.readTemperature();
   HPETA = sht313.readHumidity();
   TPETB = sht314.readTemperature();
   HPETB = sht314.readHumidity();
}

void kirim_data()
{
  // Start
  Serial2.print('#');
  Serial2.print("PET");
  Serial2.print(",");

  // Arduino A
  Serial2.print(TPETA);
  Serial2.print(",");
  Serial2.print(HPETA);
  Serial2.print(",");
  Serial2.print(TPETB);
  Serial2.print(",");
  Serial2.print(HPETB);
  Serial2.print(",");
  Serial2.print("end");
  Serial2.print("\n");

  // Start
  Serial.print('#');
  Serial.print("PET");
  Serial.print(",");
  
  // Arduino A
  Serial.print(TPETA);
  Serial.print(",");
  Serial.print(HPETA);
  Serial.print(",");
  Serial.print(TPETB);
  Serial.print(",");
  Serial.print(HPETB);
  Serial.print(",");
  Serial.print("end");
  Serial.print("\n");
}
