/*
    PLEN5Stack ServoAdjust.ino
    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/
#include <M5Stack.h>
#include "PLEN5Stack.h"
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
  plen5stack.begin();
  
  strip.begin();
  strip.setBrightness(10);
  setColor(strip.Color(255,  0,  0),500); // Green

  digitalWrite(POWERSWITCH, HIGH);    // motor power on
  plenMenu();
}

void loop()
{
  M5.update();
  if(M5.BtnA.wasReleased())
  { // Start servo position adjust
    servoAdjust();
  }
  else if(M5.BtnB.wasReleased())
  { // Motion test
    setColor(strip.Color(0,255,255),0);
    plen5stack.motion(0x46);//Walk
    plen5stack.motion(8);//Highfive
    setColor(strip.Color(255,0,0),0);
  }
  else if(M5.BtnC.wasReleased())
  { // Servo position reset
    setColor(strip.Color(0,255,255),0);
    plen5stack.resetROMPos();
    plen5stack.loadPos();
    setColor(strip.Color(255,0,0),0);
  }// if button

//if(millis()-time1 >= 1000){
//  time1 = millis();
//}// 1 tick timer for debug

} // loop

void servoAdjust(){
  int servoNum = 0;
  int adjNum = 0;
  sensorMonitor(servoNum,adjNum);
  plenMenu2();
  while (1)
  {
    M5.update();
    if (M5.BtnC.wasReleased())
    {
      plen5stack.savePositon(servoNum,adjNum);
      servoNum += 1;
      adjNum = 0;
      sensorMonitor(servoNum,adjNum);
    } else if (M5.BtnA.isPressed())
    {
      adjNum += 10;
      adjNum = servoTweak(servoNum, adjNum);
      sensorMonitor(servoNum,adjNum);
    } else if (M5.BtnB.isPressed())
    {
      adjNum += -10;
      adjNum = servoTweak(servoNum, adjNum);
      sensorMonitor(servoNum,adjNum);
    } else if (servoNum > 7)
    {
      plenMenu();
      delay(2000);
      break;
    }
  } // while
  plenMenu();
}

int servoTweak(int servoNum, int adjustNum)
{
  int adjNum = plen5stack.servoSetInit[servoNum] + adjustNum;
  if (100 > adjNum)
  {
    adjustNum = adjustNum + 1;
  } else if (adjNum > 1700)
  {
    adjustNum = adjustNum - 1;
  } else
  {
    plen5stack.servoWrite(servoNum, (adjNum / 10));
    delay(100);
  }
  return adjustNum;
}

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
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.print("PLEN servo adjust");
  M5.Lcd.setCursor(0, 42);
  M5.Lcd.print("A: Start");
  M5.Lcd.setCursor(0, 65);
  M5.Lcd.print("B: Motion TEST");
  M5.Lcd.setCursor(0, 87);
  M5.Lcd.print("C: Position reset");
  M5.Lcd.setCursor(0, 190);
  M5.Lcd.setTextSize(6);
  M5.Lcd.print("  A B C  ");
}

void plenMenu2()
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.print("PLEN servo adjust");
  M5.Lcd.setCursor(0, 42);
  M5.Lcd.print("A: +");
  M5.Lcd.setCursor(0, 65);
  M5.Lcd.print("B: -");
  M5.Lcd.setCursor(0, 87);
  M5.Lcd.print("C: Enter");
  M5.Lcd.setCursor(0, 190);
  M5.Lcd.setTextSize(6);
  M5.Lcd.print("  A B C  ");
}

void sensorMonitor(int num, int value)
{
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 110);
  M5.Lcd.printf("Num  : %d", num);
  M5.Lcd.setCursor(0, 132);
  M5.Lcd.printf("Value: %d", value);
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
