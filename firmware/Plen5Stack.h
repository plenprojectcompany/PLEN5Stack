//plen5.h plen5stack

***REMOVED***

***REMOVED*** i2c list memo
main
0x68 mpu
0x75
sub
0x48 ADC
0x6A CA9865
0x70 IP5306
0x56 eeprom
***REMOVED***

//***REMOVED***
//***REMOVED***

#define SERVO_NUM 0x08
#define ROM_ADR1 0x56

bool initController  = false;
//byte error;

int servoSetInit[8] = ***REMOVED***1000, 630, 300, 600, 240, 600, 1000, 720***REMOVED***;
float servoAngle[8] = ***REMOVED***1000, 630, 300, 600, 240, 600, 1000, 720***REMOVED***;
//int SERVO_SET_INIT[8] = ***REMOVED***1000, 900, 300, 900, 800, 900, 1500, 900***REMOVED***;

void servoWrite(uint8_t num, float degrees);
void write8(uint8_t addr, uint8_t cmd);
void initPCA9865();
void servoInitialSet();
void setAngle(int16_t angle[], uint16_t msec);
String reep(uint16_t eepAdr, uint8_t num);
void motion(uint16_t fileName);


void servoWrite(uint8_t num, float degrees) ***REMOVED***
    if (initController  == false) ***REMOVED***
        initPCA9865();
        initController = true;
  ***REMOVED***
    bool highByte = false;
    float pwmVal = degrees * 100 * 226 / 10000;
    pwmVal = round(pwmVal) + 0x66;
    //pwmVal = pwmVal + 0x66;
    if (pwmVal > 0xFF) ***REMOVED***
        highByte = true;
  ***REMOVED***
    write8(SERVO_NUM + num * 4, pwmVal);
    if (highByte) ***REMOVED***
        write8(SERVO_NUM + num * 4 + 1, 0x01);
  ***REMOVED*** else ***REMOVED***
        write8(SERVO_NUM + num * 4 + 1, 0x00);
  ***REMOVED***
***REMOVED***

void write8(uint8_t addr, uint8_t cmd) ***REMOVED***
    Wire.beginTransmission(0x6A);
    Wire.write(addr);
    Wire.write(cmd);
    //error = Wire.endTransmission();
    Wire.endTransmission();
***REMOVED***

void initPCA9865() ***REMOVED***
    write8(0xFE, 0x85);//PRE_SCALE
    write8(0xFA, 0x00);//ALL_LED_ON_L
    write8(0xFB, 0x00);//ALL_LED_ON_H
    write8(0xFC, 0x66);//ALL_LED_OFF_L
    write8(0xFD, 0x00);//ALL_LED_OFF_H
    write8(0x00, 0x01);
***REMOVED***

void servoInitialSet() ***REMOVED***
    for (uint8_t n = 0; n < 8; n++ )***REMOVED***
        servoWrite(n, servoSetInit[n] / 10);
  ***REMOVED***
***REMOVED***

void setAngle(int16_t angle[], uint16_t msec) ***REMOVED***
    float steps[8] = ***REMOVED******REMOVED***;
    uint16_t motionSpeed = 10;//6; //C++ speed is so speedy.
    msec = msec / motionSpeed;//default 10; Speed Adj
    for (uint8_t val = 0; val < 8; val++) ***REMOVED***
        float target = (servoSetInit[val] - angle[val]);
        if (target != servoAngle[val]) ***REMOVED***  // Target != Present
            steps[val] = (target - servoAngle[val]) / (msec);
      ***REMOVED***
  ***REMOVED***
    for (uint16_t i = 0; i <= msec; i++) ***REMOVED***
        for (uint8_t val = 0; val < 8; val++) ***REMOVED***
            servoAngle[val] += steps[val];
            //Serial.println(servoAngle[val]);
            servoWrite(val, (servoAngle[val] / 10));
      ***REMOVED***
        delay(1);
  ***REMOVED***
***REMOVED***

String reep(uint16_t eepAdr, uint8_t num) ***REMOVED***
    Wire.beginTransmission(ROM_ADR1);
    Wire.write(eepAdr >> 8);
    Wire.write(eepAdr & 0xFF);
    Wire.endTransmission();
    Wire.requestFrom(ROM_ADR1, num);
    String s="";
    while(Wire.available())  ***REMOVED***
        char c = Wire.read();// read 1 byte
        s = s + String(c);
  ***REMOVED***
    return s;
***REMOVED***

void motion(uint16_t fileName) ***REMOVED***
    int16_t angle[8]= ***REMOVED******REMOVED***;
    const uint8_t listLen = 43;
    uint16_t readAdr = 0x32 + 860 * fileName;
    String str="";
    while (1) ***REMOVED***
        String mFile = reep(readAdr, listLen);//"";
        readAdr += mFile.length();//listLen;

        Serial.print(",mf = "); Serial.println(mFile);
        uint16_t listNum = 0;
        str = mFile.substring(0, 3);
        if(! str.equals(">MF"))***REMOVED***
            break;
      ***REMOVED***
        listNum += 3; // >MF
        str = mFile.substring(listNum, listNum+2);
        if (fileName != strtol(str.c_str(), NULL, 16)) ***REMOVED***
            break;
      ***REMOVED***
        listNum += 4;// slot,flame
        str = mFile.substring(listNum, listNum+4);
        uint16_t time = strtol(str.c_str(), NULL, 16);
        listNum += 4;// time
        //Serial.print(",time="); Serial.println(time);
        for (uint8_t val = 0; val < 8; val++)***REMOVED***//plen2 max servo = 24, plenbit = 7
            str = mFile.substring(listNum, listNum+4);
            int16_t numHex = strtol(str.c_str(), NULL, 16);
            if (numHex >= 0x7fff) ***REMOVED***
                numHex = numHex - 0x10000;
          ***REMOVED*** else ***REMOVED***
                numHex = numHex & 0xffff;
          ***REMOVED***
            angle[val] = numHex;
            //Serial.print(",val="); Serial.print(numHex);
            listNum += 4;
      ***REMOVED***//for
        //Serial.println("");
        setAngle(angle, time);
  ***REMOVED***
***REMOVED***
