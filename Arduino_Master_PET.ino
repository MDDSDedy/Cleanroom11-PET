#include <SPI.h>
#include <Ethernet.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <LiquidCrystal.h>
#include "TimerOne.h"

//const int rs = 50, en = 51, d4 = 23, d5 = 22, d6 = 27, d7 = 26;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_SHT31 sht313 = Adafruit_SHT31();
Adafruit_SHT31 sht314 = Adafruit_SHT31();

String readString;
String dataIn;
String dt[30];
int i;
boolean parsing = false;
float t1, h1, t2, h2, t3, h3, t4, h4;
char c, st;
String statsa, statsb, statsc, statsd, statse, statsf;

float TPETA ; int tpa;
float HPETA ; int hpa;
float TPETB ; int tpb;
float HPETB ; int hpb;

float TPETC ; int tpc;
float HPETC ; int hpc;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10, 1, 26, 44);
EthernetServer server(80);

void setup() {
  sht313.begin(0x44);
  sht314.begin(0x45);
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  dataIn = "";
  Timer1.initialize(24000000);
  Timer1.attachInterrupt(kirim_data);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print(Ethernet.localIP());

  //  lcd.setCursor(0, 1);
  //  lcd.print(Ethernet.localIP());

}

void loop()
{
   TPETC = sht313.readTemperature();
   HPETC = sht313.readHumidity();
  
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

  EthernetClient client = server.available();
  if (client)
  {
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        c = client.read();
        if (readString.length() < 100)
        {
          readString += c;
        }
        if (c == '\n' && currentLineIsBlank)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta http-equiv=\"Refresh\" content=\"4; url=/PET\" />");
          client.println("<meta http-equiv=\"Content-Type\"      content=\"application/vnd.wap.xhtml+xml; charset=utf-8\" />");
          client.println("<link type=\"text/css\" rel=\"stylesheet\" href=\"http://haidao.mw.lt/js_css/css_pages.css\" />");
          client.println("<TITLE>PET</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY align=\"center\" bgcolor=\"#34495E\">");
          client.println("<h1><p align=\"left\">Suhu dan RH PET</h1>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<br />");
          client.println("<table align=\"center\"><tr>");
          client.println("<th width=\"5%\">No</th>");
          client.println("<th width=\"30%\">Ruangan</th>");
          client.println("<th width=\"10%\">Kelas</th>");
          client.println("<th width=\"20%\">Suhu (°C)</th>");
          client.println("<th width=\"20%\">RH (%)</th>");
          client.println("<th width=\"30%\">Keterangan</th></tr>");
          client.println("<tr class=\"trh1\"><td align=\"left\">");
          client.println(" ");
          client.println(" ");

          client.println("1");
          client.println("</td><td align=\"center\">");
          client.println("PET");
          client.println("</td><td align=\"center\">");
          client.println("LAF");
          client.println("</td><td align=\"center\">");
          client.print(TPETA);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.print(HPETA);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.print(statsa);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.println("<p />");
          client.println("<H2>");
          client.println("</td></tr>");
          client.println();
          client.println("<tr class=\"trh2\"><td align=\"left\">");
          client.println(" ");
          client.println(" ");

          client.println("2");
          client.println("</td><td align=\"center\">");
          client.println("PET");
          client.println("</td><td align=\"center\">");
          client.println("B");
          client.println("</td><td align=\"center\">");
          client.print(TPETB);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.print(HPETB);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.print(statsb);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.println("<p />");
          client.println("<H2>");
          client.println("</td></tr>");
          client.println();
          client.println("<tr class=\"trh1\"><td align=\"left\">");
          client.println(" ");
          client.println(" ");

//          client.println("3");
//          client.println("</td><td align=\"center\">");
//          client.println("PET");
//          client.println("</td><td align=\"center\">");
//          client.println("C");
//          client.println("</td><td align=\"center\">");
//          client.print(TPETC);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.print(HPETC);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.print(statsc);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.println("<p />");
//          client.println("<H2>");
//          client.println("</td></tr>");
//          client.println();
//          client.println("<tr class=\"trh2\"><td align=\"left\">");
//          client.println(" ");
//          client.println(" ");
//
//          client.println("4");
//          client.println("</td><td align=\"center\">");
//          client.println("CLEANROOM");
//          client.println("</td><td align=\"center\">");
//          client.println("LAF");
//          client.println("</td><td align=\"center\">");
//          client.print(TCRA);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.print(HCRA);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.print(statsd);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.println("<p />");
//          client.println("<H2>");
//          client.println("</td></tr>");
//          client.println();
//          client.println("<tr class=\"trh2\"><td align=\"left\">");
//          client.println(" ");
//          client.println(" ");
//
//          client.println("5");
//          client.println("</td><td align=\"center\">");
//          client.println("CLEANROOM");
//          client.println("</td><td align=\"center\">");
//          client.println("B");
//          client.println("</td><td align=\"center\">");
//          client.print(TCRB);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.print(HCRB);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.print(statse);
//          client.println("</H1>");
//          client.println("</td><td align=\"center\">");
//          client.println("<p />");
//          client.println("<H2>");
//          client.println("</td></tr>");
//          client.println();
//          client.println("<tr class=\"trh2\"><td align=\"left\">");
//          client.println(" ");
//          client.println(" ");

          client.println("3");
          client.println("</td><td align=\"center\">");
          client.println("PET");
          client.println("</td><td align=\"center\">");
          client.println("C");
          client.println("</td><td align=\"center\">");
          client.print(TPETC);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.print(HPETC);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.print(statsc);
          client.println("</H1>");
          client.println("</td><td align=\"center\">");
          client.println("<p />");
          client.println("<H2>");
          client.println("</td></tr>");
          client.println();
          client.println("<H2>");
          client.println("</BODY>");
          delay(1);
          client.stop();

          if (c == '\n') {
            currentLineIsBlank = true;
          }
          else if (c != '\r') {
            currentLineIsBlank = false;
          }
          readString = "";
        }
      }
    }
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
}

void kirim_data()
{
  //Arduino A
  TPETA = dt[1].toFloat() ;
  HPETA = dt[2].toFloat() ;
  TPETB = dt[3].toFloat() ;
  HPETB = dt[4].toFloat() ;

//  //Arduino B
//  TPETC = dt[5].toFloat() ;
//  HPETC = dt[6].toFloat() ;
//  TCRA  = dt[7].toFloat() ;
//  HCRA  = dt[8].toFloat() ;
//
//  //Arduino C
//  TCRB  = dt[9].toFloat() ;
//  HCRB  = dt[10].toFloat() ;
//  TCRC  = dt[11].toFloat() ;
//  HCRC  = dt[12].toFloat() ;

  
  if ((TPETA > 14 && TPETA < 26) && (HPETA > 44 && HPETA < 56))
  {
      statsa = "OK";
  }
    else
  {
      statsa = "Out of Range";
  }

  if ((TPETB > 14 && TPETB < 26) && (HPETB > 44 && HPETB < 56))
  {
      statsb = "OK";
  }
    else
  {
      statsb = "Out of Range";
  }

  if ((TPETC > 14 && TPETC < 26) && (HPETC > 44 && HPETC < 56))
  {
      statsc = "OK";
  }
    else
  {
      statsc = "Out of Range";
  }

//  if ((TCRA > 14 && TCRA < 26) && (HCRA > 44 && HCRA < 56))
//  {
//      statsd = "OK";
//  }
//    else
//  {
//      statsd = "Out of Range";
//  }
//
//  if ((TCRB > 14 && TCRB < 26) && (HCRB > 44 && HCRB < 56))
//  {
//      statse = "OK";
//  }
//    else
//  {
//      statse = "Out of Range";
//  }
//
//  if ((TCRC > 14 && TCRC < 26) && (HCRC > 44 && HCRC < 56))
//  {
//      statsf = "OK";
//  }
//    else
//  {
//      statsf = "Out of Range";
//  }
  
  // Start
  Serial.print('#');
  Serial.print("PET");
  Serial.print(",");
  Serial.print(TPETA);
  Serial.print(",");
  Serial.print(HPETA);
  Serial.print(",");
  Serial.print(TPETB);
  Serial.print(",");
  Serial.print(HPETB);
  Serial.print(",");
  Serial.print(TPETC);
  Serial.print(",");
  Serial.print(HPETC);
//  Serial.print(",");
//  Serial.print(TCRA);
//  Serial.print(",");
//  Serial.print(HCRA);
//  Serial.print(",");
//  Serial.print(TCRB);
//  Serial.print(",");
//  Serial.print(HCRB);
//  Serial.print(",");
//  Serial.print(TCRC);
//  Serial.print(",");
//  Serial.print(HCRC);
  Serial.print("\n");
}
