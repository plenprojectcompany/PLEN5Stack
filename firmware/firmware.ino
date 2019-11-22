***REMOVED***
    PLEN2mini & M5Stack -> PLEN5Stack

***REMOVED***
***REMOVED***
***REMOVED***
    
***REMOVED***
***REMOVED***
***REMOVED***

***REMOVED***
#include "Plen5Stack.h"

***REMOVED***
***REMOVED***

//***REMOVED***
//unsigned long time2;

***REMOVED******REMOVED***
    
  ***REMOVED***

    pinMode(5, OUTPUT);   // LED EYE
    digitalWrite(5, LOW); //Active Low
  ***REMOVED***
    
    servoInitialSet();  //PLEN Servo init

    //Serial.begin(115200);
    
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.setCursor(10, 10);
	M5.Lcd.setTextColor(WHITE);
	M5.Lcd.setTextSize(1);
	M5.Lcd.println("PLEN5Stack");
    
***REMOVED***
  ***REMOVED***//("  PUSH ");
  ***REMOVED***//(" BUTTON");
  ***REMOVED***
  ***REMOVED***
***REMOVED***

***REMOVED******REMOVED***
    
  ***REMOVED***

    if(M5.BtnA.wasReleased())***REMOVED***

    ***REMOVED***
    ***REMOVED***
    ***REMOVED***
    ***REMOVED***
        motion(0x29);//Patapata: Shake arms
    ***REMOVED***
    ***REMOVED***
        motion(38);//Dance Twist
    ***REMOVED***

   	***REMOVED***else if(M5.BtnB.wasReleased())***REMOVED***
        
        motion(0x46);//Walk
        motion(8);//Highfive
        
  ***REMOVED*** if(M5.BtnC.wasReleased())***REMOVED***
        
        plenBlink();
    	servoInitialSet();
      
  ***REMOVED***// if button

//    time1 = millis();
//    if(time1-time2 >= 1000)***REMOVED***
//        time2 = time1;
//  ***REMOVED***// 1 tick timer for debug

***REMOVED***

void plenBlink()***REMOVED***
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
***REMOVED***
