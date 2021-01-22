/*
    PLEN5Stack.h
    Copyright (c) 2019,
    - hkr352 @miya - https://github.com/hkr352
    - PLEN Project Company Inc. - https://plen.jp
    
    This software is released under the MIT License.
    (See also : http://opensource.org/licenses/mit-license.php)
*/
#ifndef PLEN5STACK_h
#define PLEN5STACK_h
//#include <M5Stack.h>
#include <Arduino.h>
#include <Wire.h>

/* i2c list memo
main
0x68 mpu
0x75
sub
0x48 ADC
0x6A CA9865
0x70 IP5306
0x56 eeprom
*/

//#define SCL 22
//#define SDA 21
#define SERVO_NUM 0x08
#define ROM_ADR1 0x56
#define SERVO_NUM_USED 8//plenbit = 8, plen2 max servo = 24

class PLEN5Stack
{
    public:
        int servoSetInit[SERVO_NUM_USED] = {1000, 630, 300, 600, 240, 600, 1000, 720};
        PLEN5Stack();
        void begin();
        void servoWrite(uint8_t num, float degrees);
        void initPCA9865();
        void servoInitialSet();
        void setAngle(int16_t angle[], uint16_t msec);
        String reep(uint16_t eepAdr, uint8_t num);
        byte *reepByte(uint16_t eepAdr, byte *c, uint8_t num);
        void motion(uint16_t fileName);
        void savePositon(uint8_t servoNum, int adjustNum);
        void loadPos();
        void resetROMPos();
        void changeMotionSpeed(uint16_t num);
    private:
        float servoAngle[SERVO_NUM_USED] = {1000, 630, 300, 600, 240, 600, 1000, 720};
        //int SERVO_SET_INIT[8] = {1000, 900, 300, 900, 800, 900, 1500, 900};
        bool initController  = false;
        uint16_t motionSpeed = 10;
        //byte error;
        void write8(uint8_t addr, uint8_t cmd);
        void weep(uint16_t eepAdr, uint8_t num);
};

#endif

/* motion list
0: 00_Lstep
1: 01_FStep
2: 02_RStep
3: 03_A-hem_bit
4: 04_Bow
5: 05_Propose
6: 06_Hug
7: 07_Clap_bit
8: 08_Highfive
9: 0A_Shake_a_Box
10: 0B_Pick_Up_High
11: 0C_Pick_Up_Low
12: 0D_Receive_a_Box
13: 0E_Present_a_Box
14: 0F_Pass_a_Box
15: 10_Throw_a_Box
16: 11_Put_Down_High
17: 12_Put_Down_Low
18: 14_Defense_LStep
19: 15_Dribble
20: 16_Defense_RStep
21: 17_LKick
22: 18_Long_Dribble
23: 19_RKick_bit
24: 1A_Pass_to_Left
25: 1B_Pass_It_to_Me!
26: 1C_Pass_to_Right
27: 1E_Dance_LStep
28: 1F_Dance_FStep
29: 20_Dance_RStep
30: 21_Dance_Finish_Pose
31: 22_Dance_Up_&_Down
32: 23_Wiggle_Dance
33: 24_Dance_BStep
34: 25_Dance_Bow
35: 26_Twist_Dance
36: 29_Arm_PataPata
37: 2A_4A_Carry_Forward
38: 2B_4B_Carry_LTurn
39: 2C_4C_Carry_RTurn
40: 2D_4D_Carry_Back
41: 46_Walk_Forward
42: 47_Walk_LTurn
43: 48_Walk_RTurn
44: 49_Walk_Back
45: 50_example_shaking_arm
*/