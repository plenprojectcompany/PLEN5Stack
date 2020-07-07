/*
    PLEN5Stack PLEN_IMU.ino
    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/
// define must ahead #include <M5Stack.h>
#define M5STACK_MPU6886 
// #define M5STACK_MPU9250 
// #define M5STACK_MPU6050
// #define M5STACK_200Q

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

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
bool motorEnable = true;
bool viewReset = false;
unsigned long time1;

void setup()
{
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();

  pinMode(POWERSWITCH, OUTPUT);
  digitalWrite(POWERSWITCH, LOW);
  Wire.begin(SDA, SCL);
  plen5stack.servoInitialSet();  //PLEN Servo init

  strip.begin();
  strip.setBrightness(10);
  setColor(strip.Color(255,  0,  0),500); // Green

  digitalWrite(POWERSWITCH, HIGH);    // motor power on

}

void loop()
{
  M5.update();
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.Lcd.setCursor(0, 110);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
  M5.Lcd.setCursor(220, 132);
  M5.Lcd.print(" G");
  
  if(accY < 0.3)
  {
      M5.Lcd.setCursor(10, 50);
      M5.Lcd.setTextColor(RED);
      M5.Lcd.setTextSize(6);
      M5.Lcd.println("HELP ME!");
      setColor(strip.Color(  0,255,  0),500);
      if (motorEnable)
      {
        plen5stack.motion(0x29);
        delay(1000);
      }
      viewReset = true;
  }else
  {
    if (viewReset)
    {
      M5.Lcd.fillScreen(BLACK);
      setColor(strip.Color(255,  0,  0),500);
      viewReset = false;
    }
  }

  if(M5.BtnC.wasReleased())
  {
    motorEnable = !motorEnable;
  }
  //delay(1);
} // loop

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
