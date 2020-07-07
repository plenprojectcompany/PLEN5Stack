/*
    PLEN5Stack PlayMotion.ino
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
    //Standard motion
    plen5stack.motion(0x46);// Walk Forward
//    plen5stack.motion(0x47);// Walk Left Turn
//    plen5stack.motion(0x48);// Walk Right Turn
//    plen5stack.motion(0x49);// Walk Back
//    plen5stack.motion(0x00);// Left step
//    plen5stack.motion(0x01);// Forward step
//    plen5stack.motion(0x02);// Right step
//    plen5stack.motion(0x03);// A hem
//    plen5stack.motion(0x04);// Bow
//    plen5stack.motion(0x05);// Propose
//    plen5stack.motion(0x06);// Hug
//    plen5stack.motion(0x07);// Clap
//    plen5stack.motion(0x08);// Highfive
//    plen5stack.motion(0x29);// Shake Arms
  }
  else if(M5.BtnB.wasReleased())
  {
    // Soccer motion
//    plen5stack.motion(0x14);// Defense Left Step
//    plen5stack.motion(0x15);// Dribble
//    plen5stack.motion(0x16);// Defense Right Step
//    plen5stack.motion(0x17);// Left Kick
//    plen5stack.motion(0x18);// Long Dribble
    plen5stack.motion(0x19);// Right Kick
//    plen5stack.motion(0x1a);// Pass To Left
//    plen5stack.motion(0x1b);// Pass It To Me
//    plen5stack.motion(0x1c);// Pass To Right
  }
  else if(M5.BtnC.wasReleased())
  {
    // Dance motion
//    plen5stack.motion(0x1c);// Dance Left Step
//    plen5stack.motion(0x1c);// Dance Forward Step
//    plen5stack.motion(0x1c);// Dance Right Step
//    plen5stack.motion(0x1c);// Dance Fisnish Pose
//    plen5stack.motion(0x1c);// Dance Up Down
//    plen5stack.motion(0x1c);// Wiggle Dance
//    plen5stack.motion(0x1c);// Dance Back Step
//    plen5stack.motion(0x1c);// Dance Bow
    plen5stack.motion(0x1c);// Twist Dance
  }// if button

// Box motion
//    plen5stack.motion(0x0a);
//    plen5stack.motion(0x0b);
//    plen5stack.motion(0x0c);
//    plen5stack.motion(0x0d);
//    plen5stack.motion(0x0e);
//    plen5stack.motion(0x0f);
//    plen5stack.motion(0x10);
//    plen5stack.motion(0x11);
//    plen5stack.motion(0x12);

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
