/*
    PLEN5Stack.cpp
    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/
#include "PLEN5Stack.h"

PLEN5Stack::PLEN5Stack(){}

void PLEN5Stack::begin()
{
  loadPos();
  servoInitialSet();
}

void PLEN5Stack::servoWrite(uint8_t num, float degrees)
{
    if (initController  == false)
    {
        initPCA9865();
        initController = true;
    }
    bool highByte = false;
    float pwmVal = degrees * 100 * 226 / 10000;
    pwmVal = round(pwmVal) + 0x66;
    //pwmVal = pwmVal + 0x66;
    if (pwmVal > 0xFF)
    {
        highByte = true;
    }
    write8(SERVO_NUM + num * 4, pwmVal);
    if (highByte)
    {
        write8(SERVO_NUM + num * 4 + 1, 0x01);
    }
    else
    {
        write8(SERVO_NUM + num * 4 + 1, 0x00);
    }
}

void PLEN5Stack::write8(uint8_t addr, uint8_t cmd)
{
    Wire.beginTransmission(0x6A);
    Wire.write(addr);
    Wire.write(cmd);
    //error = Wire.endTransmission();
    Wire.endTransmission();
}

void PLEN5Stack::initPCA9865()
{
    write8(0xFE, 0x85);//PRE_SCALE
    write8(0xFA, 0x00);//ALL_LED_ON_L
    write8(0xFB, 0x00);//ALL_LED_ON_H
    write8(0xFC, 0x66);//ALL_LED_OFF_L
    write8(0xFD, 0x00);//ALL_LED_OFF_H
    write8(0x00, 0x01);
}

void PLEN5Stack::servoInitialSet()
{
    for (uint8_t n = 0; n < SERVO_NUM_USED; n++ )
    {
        servoWrite(n, servoSetInit[n] / 10);
    }
}

void PLEN5Stack::setAngle(int16_t angle[], uint16_t msec)
{
    float steps[SERVO_NUM_USED] = {};
    uint16_t motionSpeed = 10;//6; //"C++ speed" is so speedy.
    msec = msec / motionSpeed;//default 10; Speed Adj
    for (uint8_t val = 0; val < SERVO_NUM_USED; val++)
    {
        float target = (servoSetInit[val] - angle[val]);
        if (target != servoAngle[val])
        {  // Target != Present
            steps[val] = (target - servoAngle[val]) / (msec);
        }
    }
    for (uint16_t i = 0; i <= msec; i++)
    {
        for (uint8_t val = 0; val < SERVO_NUM_USED; val++)
        {
            servoAngle[val] += steps[val];
            //Serial.println(servoAngle[val]);
            servoWrite(val, (servoAngle[val] / 10));
        }
        delay(1);
    }
}

String PLEN5Stack::reep(uint16_t eepAdr, uint8_t num)
{
    Wire.beginTransmission(ROM_ADR1);
    Wire.write(eepAdr >> 8);
    Wire.write(eepAdr & 0xFF);
    Wire.endTransmission();
    Wire.requestFrom(ROM_ADR1, num);
    String s="";
    while(Wire.available())
    {
        char c = Wire.read();// read 1 byte
        s = s + String(c);
    }
    return s;
}

byte *PLEN5Stack::reepByte(uint16_t eepAdr, byte *c, uint8_t num)
{
  Wire.beginTransmission(ROM_ADR1);
  Wire.write(eepAdr >> 8);
  Wire.write(eepAdr & 0xFF);
  Wire.endTransmission();
  Wire.requestFrom(ROM_ADR1, num);
  int i=0;
  while(Wire.available())
  {
    c[i] = Wire.read();// read 1 byte
    i++;
  }
  return c;
}

void PLEN5Stack::weep(uint16_t eepAdr, uint8_t num)
{
  Wire.beginTransmission(ROM_ADR1);
  Wire.write(eepAdr >> 8);
  Wire.write(eepAdr & 0xFF);
  Wire.write(num);
  Wire.endTransmission();
  delay(10);
}

void PLEN5Stack::motion(uint16_t fileName)
{
    int16_t angle[SERVO_NUM_USED]= {};
    const uint8_t listLen = 43;
    uint16_t readAdr = 0x32 + 860 * fileName;
    String str="";
    while (1)
    {
        String mFile = reep(readAdr, listLen);//"";
        readAdr += mFile.length();//listLen;

        Serial.print(",mf = "); Serial.println(mFile);
        uint16_t listNum = 0;
        str = mFile.substring(0, 3);
        if(! str.equals(">MF")) { break; }
        listNum += 3; // >MF
        str = mFile.substring(listNum, listNum+2);
        if (fileName != strtol(str.c_str(), NULL, 16)){ break; }
        listNum += 4;// slot,flame
        str = mFile.substring(listNum, listNum+4);
        uint16_t time = strtol(str.c_str(), NULL, 16);
        listNum += 4;// time
        //Serial.print(",time="); Serial.println(time);
        for (uint8_t val = 0; val < SERVO_NUM_USED; val++)
        {//plen2 max servo = 24, plenbit = 7
            str = mFile.substring(listNum, listNum+4);
            int16_t numHex = strtol(str.c_str(), NULL, 16);
            if (numHex >= 0x7fff)
            {
                numHex = numHex - 0x10000;
            }
            else
            {
                numHex = numHex & 0xffff;
            }
            angle[val] = numHex;
            //Serial.print(",val="); Serial.print(numHex);
            listNum += 4;
        }//for
        //Serial.println("");
        setAngle(angle, time);
    }
}

void PLEN5Stack::savePositon(uint8_t servoNum, int adjustNum)
{
  adjustNum = servoSetInit[servoNum] + adjustNum;
  weep(0, 1);    //write flag
  weep(servoNum * 2 + 2, (adjustNum & 0xff00) >> 8 );
  weep(servoNum * 2 + 3, adjustNum & 0xff);
}

void PLEN5Stack::loadPos()
{
  byte readBuf[17];
  reepByte(0x00, readBuf, 1);
  if (readBuf[0] == 0x01)
  {
    reepByte(0x02, readBuf, 16);
    for (int i = 0; i < 8; i++)
    {
      servoSetInit[i] = (readBuf[i * 2] << 8) | (readBuf[i * 2 + 1]);
      servoAngle[i] = servoSetInit[i];
    }
  }
}

void PLEN5Stack::resetROMPos()
{
  weep(0, 0);    //write flag reset
  for (int n = 0; n < 8; n++)
  {
    weep(n * 2 + 2, (servoSetInit[n] & 0xff00) >> 8 );
    weep(n * 2 + 3, servoSetInit[n] & 0xff);
  }
}