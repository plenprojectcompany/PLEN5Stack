***REMOVED***
    PLEN5Stack FullColorLedEye

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
***REMOVED***

***REMOVED***
***REMOVED***

***REMOVED***

***REMOVED***
***REMOVED***    
  ***REMOVED***
    
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
    
  ***REMOVED***
    
    servoInitialSet();  //PLEN Servo init
    
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.setCursor(10, 10);
	M5.Lcd.setTextColor(WHITE);
	M5.Lcd.setTextSize(1);
	M5.Lcd.println("PLEN5Stack");
    
***REMOVED***
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
***REMOVED***

***REMOVED***
***REMOVED***
  ***REMOVED***

    if(M5.BtnA.wasReleased())
    ***REMOVED***
    ***REMOVED***
    ***REMOVED***
    ***REMOVED***
    ***REMOVED***
    ***REMOVED***
        motion(0x29);//Patapata: Shake arms
    ***REMOVED***
    ***REMOVED***
        motion(38);//Dance Twist
    ***REMOVED***
    ***REMOVED***
   	***REMOVED***
   	else if(M5.BtnB.wasReleased())
   	***REMOVED***
    ***REMOVED***
        motion(0x46);//Walk
        motion(8);//Highfive
    ***REMOVED***
        
  ***REMOVED***
  ***REMOVED***
    ***REMOVED***
    ***REMOVED***
    	servoInitialSet();
  ***REMOVED***
***REMOVED***

***REMOVED***
***REMOVED***
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
  ***REMOVED***
***REMOVED***

***REMOVED***
***REMOVED***
***REMOVED***
  ***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
