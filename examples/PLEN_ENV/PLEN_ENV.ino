***REMOVED***
    PLEN5Stack PLEN_ENV.ino
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***

***REMOVED***
***REMOVED***
***REMOVED***

#include "DHT12.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***

***REMOVED***
DHT12 dht12; //Preset scale CELSIUS and ID 0x5c.
Adafruit_BMP280 bme;

unsigned long time2;

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

  while (!bme.begin(0x76))
  ***REMOVED***
    M5.Lcd.println("not find BMP280, check wiring!");
    delay(100);
***REMOVED***

***REMOVED***  //PLEN Servo init
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
***REMOVED***// if button



  if(millis()-time2 >= 1000)
  ***REMOVED***
    time2 = millis();

    float temp = dht12.readTemperature();
    float humidity = dht12.readHumidity();
    float pressure = bme.readPressure();
    if(temp >= 30)
    ***REMOVED***
      M5.Lcd.setTextColor(RED, BLACK);
  ***REMOVED***
    ***REMOVED***
***REMOVED***
  ***REMOVED***
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.printf("\r\nTemp    : %2.1f\r\n", temp);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("Humidity: %2.0f%%\r\n", humidity);
    M5.Lcd.printf("Pressure: %.2fhPa\r\n", pressure/100.0);
      
***REMOVED***// 1 tick timer for sensor
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
