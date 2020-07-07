/*
    PLEN5Stack Servo.ino
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

int16_t angle[8]= {0};

void setup()
{
  M5.begin();

  pinMode(POWERSWITCH, OUTPUT);
  digitalWrite(POWERSWITCH, LOW);
  Wire.begin(SDA, SCL);
  plen5stack.servoInitialSet();  //PLEN Servo init

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
  {
    // How to move the servo motor one by one.
    // plen5stack.servoWrite(servo number , degree);
    plen5stack.servoWrite(2,90);
    plen5stack.servoWrite(6,40);
    delay(500);
    plen5stack.servoWrite(2,30);
    plen5stack.servoWrite(6,100);
    delay(500);
  }
  else if(M5.BtnB.wasReleased())
  {
    // How to move multiple servo motors simultaneously.
    for(int i=0; i<2; i++)
    {
      // angle [ servo number ] = angle;
      // plen5stack.setAngle(angle, msec);
      
      // Initial angle of Servo motor 
      // 0:1000, 1:630, 2:300,  3:600
      // 4:240,  5:600, 6:1000, 7:720
      angle[1] = 900;
      angle[2] = -900;
      angle[5] = -900;
      angle[6] = 900;
      plen5stack.setAngle(angle,500);
      angle[1] = 0;
      angle[2] = 0;
      angle[5] = 0;
      angle[6] = 0;
      plen5stack.setAngle(angle,500);
    }
  }
  else if(M5.BtnC.wasReleased())
  {
    for(int i=0; i<2; i++)
    {
      angle[4] = -1393;
      angle[0] = 0;
      plen5stack.setAngle(angle,500);
      angle[4] = -413;
      angle[0] = 1121;
      plen5stack.setAngle(angle,500);
    }
    angle[0] = 0;
    angle[4] = 0;
    plen5stack.setAngle(angle,500);
  }// if button

//if(millis()-time1 >= 1000){
//  time1 = millis();
//}// 1 tick timer for debug

} // loop

void angleReset()
{
  for(int i=0; i<8; i++)
  {
    angle[i] = 0;
  }
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
