#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include "TimerOne.h"

Adafruit_SHT31 sht313 = Adafruit_SHT31();
Adafruit_SHT31 sht314 = Adafruit_SHT31();

String readString;
String dataIn;
String dt[20];
int i;
boolean parsing = false;

  //Arduino A
  float TPETA ;
  float HPETA ;
  float TPETB ;
  float HPETB ;

  //Arduino B
  float TPETC ;
  float HPETC ;
  float TCRA ;
  float HCRA ;

void setup() 
{
  dataIn = "";
  sht313.begin(0x44);
  sht314.begin(0x45);
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Timer1.initialize(6000000);
  Timer1.attachInterrupt(kirim_data);
}

void loop() 
{
  TPETC = sht313.readTemperature();
  HPETC = sht313.readHumidity();
  TCRA = sht314.readTemperature();
  HCRA = sht314.readHumidity();

  if (Serial3.available() > 0)
  {
    char inChar = (char)Serial3.read();
    dataIn += inChar;
    if (inChar == '#')
    {
      parsing = true;
    }
  }
  if (parsing)
  {
    parsingData();
    parsing = false;
    dataIn = "";
  }
}

void parsingData() {
  int j = 0;
  
  //inisialisasi variabel, (reset isi variabel)
  dt[j] = "";
  //proses parsing data
  for (i = 1; i < dataIn.length(); i++) {
    //pengecekan tiap karakter dengan karakter (#) dan (,)
    if ((dataIn[i] == '#') || (dataIn[i] == ','))
    {
      //increment variabel j, digunakan untuk merubah index array penampung
      j++;
      dt[j] = "";     //inisialisasi variabel array dt[j]
    }
    else
    {
      //proses tampung data saat pengecekan karakter selesai.
      dt[j] = dt[j] + dataIn[i];
    }
  } 
  TPETA = dt[1].toFloat() ;
  HPETA = dt[2].toFloat() ;
  TPETB = dt[3].toFloat() ;
  HPETB = dt[4].toFloat() ;
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
    
    // Arduino B
    Serial2.print(TPETC);
    Serial2.print(",");
    Serial2.print(HPETC);
    Serial2.print(",");
    Serial2.print(TCRA);
    Serial2.print(",");
    Serial2.print(HCRA);
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
    
    // Arduino B
    Serial.print(TPETC);
    Serial.print(",");
    Serial.print(HPETC);
    Serial.print(",");
    Serial.print(TCRA);
    Serial.print(",");
    Serial.print(HCRA);
    Serial.print(",");
    Serial.print("end");
    Serial.print("\n");
}
