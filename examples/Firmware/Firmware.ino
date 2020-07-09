/*
    PLEN5Stack Firmware.ino
    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/
#include <M5Stack.h>
#include <PLEN5Stack.h>

#define SCL 22
#define SDA 21
#define POWERSWITCH 5
#define LEDEYE 26
PLEN5Stack plen5stack;
//unsigned long time1;

void setup()
{
  M5.begin();

  pinMode(POWERSWITCH, OUTPUT);
  digitalWrite(POWERSWITCH, LOW);
  pinMode(LEDEYE, OUTPUT);   // LED EYE
  digitalWrite(LEDEYE, LOW); // Active Low
  Wire.begin(SDA, SCL);
  plen5stack.begin();  // PLEN Servo init

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
    plenBlink();
    plen5stack.motion(0x29);//Patapata: Shake arms
    M5.Lcd.println("I'm PLEN");
    M5.Lcd.println("5 Stack!");
    plen5stack.motion(38);//Dance Twist
    M5.Lcd.fillScreen(BLACK);
    plenBlink();
    plenMenu();
  }
  else if(M5.BtnB.wasReleased())
  {    
    plenBlink();
    plen5stack.motion(0x46);//Walk
    plen5stack.motion(8);//Highfive
    plenBlink();
  }
  else if(M5.BtnC.wasReleased())
  {
    plenBlink();
  }// if button

//if(millis()-time1 >= 1000){
//  time1 = millis();
//}// 1 tick timer for debug

} // loop

void plenBlink()
{
  digitalWrite(LEDEYE, HIGH);
  delay(100);
  digitalWrite(LEDEYE, LOW);
  delay(100);
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
