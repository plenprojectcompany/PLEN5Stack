/*
    PLEN5Stack FirmwareFullColorLED.ino
    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/
#include <M5Stack.h>
#include <PLEN5Stack.h>
#include <Adafruit_NeoPixel.h> //ver 1.3.4

#define SCL 22
#define SDA 21
#define POWERSWITCH 5
#define LEDEYE 26
#define LED_COUNT 2
PLEN5Stack plen5stack;
Adafruit_NeoPixel strip(LED_COUNT, LEDEYE, NEO_GRB + NEO_KHZ800);
//unsigned long time1;

void setup()
{
  M5.begin();

  pinMode(POWERSWITCH, OUTPUT);
  digitalWrite(POWERSWITCH, LOW);
  Wire.begin(SDA, SCL);
  plen5stack.servoInitialSet();  //PLEN Servo init

  strip.begin();
  strip.setBrightness(10);
  setColor(strip.Color(  0,255,  0),500); // Red
  //setColor(strip.Color(  0,  0,255),500); // Blue
  setColor(strip.Color(255,255,  0),500); // Yellow
  setColor(strip.Color(255,  0,  0),500); // Green

  //Serial.begin(115200);
  digitalWrite(POWERSWITCH, HIGH);    // motor power on
  plenMenu();
}

void loop()
{
  M5.update();
  if(M5.BtnA.wasReleased())
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
  }// if button

//if(millis()-time1 >= 1000){
//  time1 = millis();
//}// 1 tick timer for debug

} // loop

void plenBlink(uint32_t color, int wait)
{
  setColor(strip.Color(0,0,0),wait);
  setColor(color,wait);
  setColor(strip.Color(0,0,0),wait);
  setColor(color,wait);
}

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

void setColor(uint32_t color, int wait)
{
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, color);
    strip.show();
  }
  delay(wait);
}
