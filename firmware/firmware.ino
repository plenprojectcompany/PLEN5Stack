/*
    PLEN2mini & M5Stack -> PLEN5Stack

    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/

#include <M5Stack.h>
#include "Plen5Stack.h"

#define SCL 22
#define SDA 21

//unsigned long time1;
//unsigned long time2;

void setup(){
    
    M5.begin();

    pinMode(5, OUTPUT);   // LED EYE
    digitalWrite(5, LOW); //Active Low
    Wire.begin(SDA, SCL);
    
    servoInitialSet();  //PLEN Servo init

    //Serial.begin(115200);
    
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.setCursor(10, 10);
	M5.Lcd.setTextColor(WHITE);
	M5.Lcd.setTextSize(1);
	M5.Lcd.println("PLEN5Stack");
    
    M5.Lcd.setTextSize(6);
    M5.Lcd.println("");//("  PUSH ");
    M5.Lcd.println("");//(" BUTTON");
    M5.Lcd.println("");
    M5.Lcd.println("  A B C  ");
}

void loop(){
    
    M5.update();

    if(M5.BtnA.wasReleased()){

        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(10, 10);
        M5.Lcd.setTextSize(6);
        M5.Lcd.println(" Hello !");
        motion(0x29);//Patapata: Shake arms
        M5.Lcd.println("I'm PLEN");
        M5.Lcd.println("5 Stack!");
        motion(38);//Dance Twist
        M5.Lcd.fillScreen(BLACK);

   	}else if(M5.BtnB.wasReleased()){
        
        motion(0x46);//Walk
        motion(8);//Highfive
        
    }else if(M5.BtnC.wasReleased()){
        
        plenBlink();
    	servoInitialSet();
      
    }// if button

//    time1 = millis();
//    if(time1-time2 >= 1000){
//        time2 = time1;
//    }// 1 tick timer for debug

}

void plenBlink(){
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
}
