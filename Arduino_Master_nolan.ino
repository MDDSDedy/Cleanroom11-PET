#include <SPI.h>
#include <Ethernet.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <LiquidCrystal.h>
#include "TimerOne.h" 

const int rs = 50, en = 51, d4 = 23, d5 = 22, d6 = 27, d7 = 26;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String readString;
String dataIn;
String dt[30];
int i;
boolean parsing = false;

  float TPETB ; int tpb;
  float HPETB ; int hpb;
  float TPETC ; int tpc;
  float HPETC ; int hpc;
  
  float TCRA ; int tra;
  float HCRA ; int hra;
  float TCRB ; int trb;
  float HCRB ; int hrb;

  float TCRC ; int trc;
  float HCRC ; int hrc;
  float TCRD ; int trd;
  float HCRD ; int hrd;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);
Adafruit_SHT31 sht1 = Adafruit_SHT31();
Adafruit_SHT31 sht2 = Adafruit_SHT31();

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Keteknikan Corp");
  lcd.setCursor(1, 1);
  lcd.print("Suhu RH CR 13");  
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  dataIn = "";
  Timer1.initialize(24000000);
  Timer1.attachInterrupt(kirim_data);
}

void loop()
{
  if (Serial2.available() > 0)
  {
    char inChar = (char)Serial2.read();
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
  TPETB = dt[1].toFloat() ;
  HPETB = dt[2].toFloat() ;
  TPETC = dt[3].toFloat() ;
  HPETC = dt[4].toFloat() ;
  TCRA  = dt[5].toFloat() ;
  HCRA  = dt[6].toFloat() ;
  TCRB  = dt[7].toFloat() ;
  HCRB  = dt[8].toFloat() ;
  TCRC  = dt[9].toFloat() ;
  HCRC  = dt[10].toFloat() ;
  TCRD  = dt[11].toFloat() ;
  HCRD  = dt[12].toFloat() ;

  tpb = dt[1].toInt() ; 
  hpb = dt[2].toInt() ;
  tpc = dt[3].toInt() ;
  hpc = dt[4].toInt() ;
  tra = dt[5].toInt() ;
  hra = dt[6].toInt() ;
  trb = dt[7].toInt() ;
  hrb = dt[8].toInt() ;
  trc = dt[9].toInt() ;
  hrc = dt[10].toInt() ;
  trd = dt[11].toInt() ;
  hrd = dt[12].toInt() ;
}

void kirim_data()
{
    Serial.print('#');
    Serial.print("PET");
    Serial.print(",");
    Serial.print(TPETB);
    Serial.print(",");
    Serial.print(HPETB);
    Serial.print(",");
    Serial.print(TPETC);
    Serial.print(",");
    Serial.print(HPETC);
    Serial.print(",");
    Serial.print(TCRA);
    Serial.print(",");
    Serial.print(HCRA);
    Serial.print(",");
    Serial.print(TCRB);
    Serial.print(",");
    Serial.print(HCRB);
    Serial.print(",");
    Serial.print(TCRC);
    Serial.print(",");
    Serial.print(HCRC);
    Serial.print(",");
    Serial.print(TCRD);
    Serial.print(",");
    Serial.print(HCRD);    
    Serial.print("\n");

//  //lcd.setCursor(15, 0);
  lcd.setCursor(0, 0);
  lcd.print(tpb);
  lcd.setCursor(3, 0);
  lcd.print(hpb);
  lcd.setCursor(6, 0);
  lcd.print(tpc);
  lcd.setCursor(8, 0);
  lcd.print(hpc);
  lcd.setCursor(11, 0);
  lcd.print(tra);
  lcd.setCursor(14, 0);
  lcd.print(hra);
  lcd.setCursor(0, 1);
  lcd.print(trb);
  lcd.setCursor(3, 1);
  lcd.print(hrb);
  lcd.setCursor(6, 1);
  lcd.print(trc);
  lcd.setCursor(8, 1);
  lcd.print(hrc);
  lcd.setCursor(11, 1);
  lcd.print(trd);
  lcd.setCursor(14, 1);
  lcd.print(hrd); 
}
