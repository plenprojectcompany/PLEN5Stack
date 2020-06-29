/*
    PLEN5Stack Plen5Connect.ino
    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/
#include <M5Stack.h>
#include <PLEN5Stack.h>
#include <Adafruit_NeoPixel.h> //ver 1.3.4
#include <WiFiClient.h>
#include <WebServer.h>
#include "webpage.h"

#define SCL 22
#define SDA 21
#define POWERSWITCH 5
#define LEDEYE 26
#define LED_COUNT 2

PLEN5Stack plen5stack;
Adafruit_NeoPixel strip(LED_COUNT, LEDEYE, NEO_GRB + NEO_KHZ800);
WiFiClient client;
const char* WIFI_SSID = "ssid";
const char* WIFI_PASS = "pass";
WebServer webserver(80);
int acCount = 0;

unsigned long time1;
bool ipEnable = false;

void setup()
{
  M5.begin();
  pinMode(POWERSWITCH, OUTPUT);
  digitalWrite(POWERSWITCH, LOW);
  
  Wire.begin(SDA, SCL);
  plen5stack.servoInitialSet();
  
  strip.begin();
  strip.setBrightness(10);
  setColor(strip.Color(0,  0,  0),0); // OFF
  setColor(strip.Color(  0,255,  0),500); // Red
  //setColor(strip.Color(  0,  0,255),500); // Blue
  setColor(strip.Color(255,255,  0),500); // Yellow
  setColor(strip.Color(255,  0,  0),500); // Green
  
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  checkWifiConnected();

  if(WiFi.status() == WL_CONNECTED)
  {
    M5.Lcd.println("WiFi connected");
    M5.Lcd.print("IP adr: ");
    M5.Lcd.println(WiFi.localIP());
  }else
  {
    WiFi.softAP("mySSID", "myPass");
    M5.Lcd.println("WiFi Hotspot mode");
    M5.Lcd.print("IP adr: ");
    M5.Lcd.println(WiFi.softAPIP());
  }

  webserver.on("/", handlePLEN);
  webserver.begin();                  //start Web server
  //delay(1000);
  
  digitalWrite(POWERSWITCH, HIGH);    // motor power on
  plenMenu();
}

void loop()
{
  M5.update();

  if (M5.BtnA.wasReleased())
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.setTextSize(6);
    M5.Lcd.println(" Hello !");
    setColor(strip.Color(0,0,255),0);
    plen5stack.motion(0x29);//Patapata: Shake arms
    M5.Lcd.println("I'm PLEN");
    M5.Lcd.println("5 Stack!");
    plen5stack.motion(38);//Dance Twist
    M5.Lcd.fillScreen(BLACK);
    setColor(strip.Color(255,0,0),0); // Green
    plenMenu();
  }
  else if(M5.BtnB.wasReleased())
  {
    setColor(strip.Color(0,255,255),0);
    plen5stack.motion(0x46);//Walk
    plen5stack.motion(8);//Highfive
    setColor(strip.Color(255,0,0),0);
  }
  else if(M5.BtnC.wasReleased())
  {
    plenBlink(strip.Color(255,0,0),100);
    ipEnable = !ipEnable;
    if(ipEnable)
    {
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.setTextSize(2);
      M5.Lcd.setTextColor(WHITE, BLACK);
      M5.Lcd.println("");
      M5.Lcd.println("");
      M5.Lcd.println("");
      M5.Lcd.println("");
      M5.Lcd.print("localIP : ");
      M5.Lcd.println(WiFi.localIP());
      M5.Lcd.print("softAPIP: ");
      M5.Lcd.println(WiFi.softAPIP());
    }else
    {
      plenMenu();
    }
  }

  webserver.handleClient();
  if(acCount>10000)
  {
    acCount=0;
  }
  
//if(millis()-time1 >= 1000){
//  time1 = millis();
//}// 1 tick timer for debug
}//loop

void plenMenu()
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(5, 5);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("PLEN5Stack");
  
  M5.Lcd.setTextSize(6);
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("  A B C  ");
}

void plenBlink(uint32_t color, int wait)
{
  setColor(strip.Color(0,0,0),wait);
  setColor(color,wait);
  setColor(strip.Color(0,0,0),wait);
  setColor(color,wait);
}

void setColor(uint32_t color, int wait)
{
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, color);
    strip.show();
  }
  delay(wait);
}

bool checkWifiConnected()
{
  int count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    count++;
    if (count > 15) {return false;}
  }
  return true;
}

// Web page
void handlePLEN()
{
  if(webserver.method() == HTTP_GET)
  {
    for (uint8_t i=0; i<webserver.args(); i++)
    {
      String strCMD = webserver.argName(i);
      if(strCMD == "1")
      {
        setColor(strip.Color(255,  0,  0),500); // Green
        delay(100);
      }else if(strCMD == "0")
      {
        setColor(strip.Color(0,  0,  0),0); 
        delay(100);
      }else
      {
        //M5.Lcd.printf(strCMD); //walk: 70 = 0x46, patapata: 41 = 0x29
        Serial.println(strCMD);
        int cmdNum = strCMD.toInt();
        plen5stack.motion(cmdNum);
      }
    }
  }
  webserver.send(200, "text/html", plenPage);
  Serial.print("access=");
  Serial.println(++acCount);
}
