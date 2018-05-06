/* YourDuino.com Example Software Sketch
 16 character 2 line I2C Display
 Backpack Interface labelled "A0 A1 A2" at lower right.
 ..and
 Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
 MOST use address 0x27, a FEW use 0x3F
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define fan 4

int maxHum = 60;
int maxTemp = 40;

DHT dht(DHTPIN, DHTTYPE);

// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
//LiquidCrystal_I2C lcd1(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD#1 I2C address

const int lcdCount = 8;
LiquidCrystal_I2C lcd[lcdCount] = 
{
  LiquidCrystal_I2C(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE),
  LiquidCrystal_I2C(0x21, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE),
  LiquidCrystal_I2C(0x22, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE),
  LiquidCrystal_I2C(0x23, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE),
  LiquidCrystal_I2C(0x24, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE),
  LiquidCrystal_I2C(0x25, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE),
  LiquidCrystal_I2C(0x26, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE),
  LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE)
};

const int cols = 16;
const int rows = 2;

void setup()
{
  pinMode(fan, OUTPUT);
  Serial.begin(9600);
  dht.begin();
//  InitialLCD();  
}

void loop()
{
  //每讀取一筆資料前閃爍一次    
  lcd[i].backlight();
  delay(250);
  lcd[i].noBacklight();
  delay(250);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if(h > maxHum || t > maxTemp) {
      digitalWrite(fan, HIGH);
  } else {
     digitalWrite(fan, LOW); 
  }
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  
//  for(int i=0; i<lcdCount; i++)
//  {
//    lcd[i].begin(cols, rows);   //LCD initialization and associated HW.
//    
//    // ------- Quick 3 blinks of backlight  -------------
//    
//    lcd[i].backlight();   //Switch-on the LCD backlight.
//    
//    lcd[i].clear();   //清除 LCD 畫面
//    lcd[i].setCursor(0,0);  //將游標移至第一行第一列
//    lcd[i].print("Hello, world!");
//    delay(500);
//    lcd[i].setCursor(0,1);  //將游標移至第一行第二列
//    lcd[i].print("It's LCD#" + String(i+1) + ".");
//  }
//  delay(1000);
}

//void InitialLCD()
//{
//  for(int i=0; i<lcdCount; i++)
//  {
//    lcd[i].begin(cols, rows);   //LCD initialization and associated HW.
//    
//    // ------- Quick 3 blinks of backlight  -------------
//    for(int j = 0; j< 3; j++)
//    {
//      lcd[i].backlight();
//      delay(250);
//      lcd[i].noBacklight();
//      delay(250);
//    }
//    
//    lcd[i].backlight();   //Switch-on the LCD backlight.
//    
//    lcd[i].clear();   //清除 LCD 畫面
//    lcd[i].setCursor(0,0);  //將游標移至第一行第一列
//    lcd[i].print("Hello, world!");
//    delay(500);
//    lcd[i].setCursor(0,1);  //將游標移至第一行第二列
//    lcd[i].print("It's LCD#" + String(i+1) + ".");
//  }
//  delay(1000);
//}

