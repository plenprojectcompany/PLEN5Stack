# PLEN5Stack | PLEN Project Company Inc.

IoT biped robot using M5Stack.

## Getting Started

https://plen.jp/wp/plen5stack/

1. Get PLEN5Stack assembly kit & M5Stack.
2. [Download](https://github.com/plenprojectcompany/PLEN5Stack/archive/master.zip) this repository.
3. Include library in Arduino IDE.
4. Install firmware on M5Stack.
5. Assemble PLEN5Stack.
6. Enjoy PLEN5Stack!

## Examples

### How to use motion
For the motion number, see the motion list
``` c 
// Shake_Arms
plen5stack.motion(41); //Number
// or 
plen5stack.motion(0x29); //Hex

// Walk_Forward
plen5stack.motion(70); //Number
// or
plen5stack.motion(0x46); //Hex
```

<details>
<summary>Motion list</summary>

| Number | Hex | Name |
| :---: | :---: | :---: |
| 0 | 0x00 | Lstep |
| 1 | 0x01 | FStep |
| 2 | 0x02 | RStep |
| 3 | 0x03 | A-hem |
| 4 | 0x04 | Bow |
| 5 | 0x05 | Propose |
| 6 | 0x06 | Hug |
| 7 | 0x07 | Clap |
| 8 | 0x08 | Highfive |
| 9 | 0x09 | None |
| 10 | 0x0A | Shake_a_Box |
| 11 | 0x0B | Pick_Up_High |
| 12 | 0x0C | Pick_Up_Low |
| 13 | 0x0D | Receive_a_Box |
| 14 | 0x0E | Present_a_Box |
| 15 | 0x0F | Pass_a_Box |
| 16 | 0x10 | Throw_a_Box |
| 17 | 0x11 | Put_Down_High |
| 18 | 0x12 | Put_Down_Low |
| 19 | 0x13 | None |
| 20 | 0x14 | Defense_LStep |
| 21 | 0x15 | Dribble |
| 22 | 0x16 | Defense_RStep |
| 23 | 0x17 | LKick |
| 24 | 0x18 | Long_Dribble |
| 25 | 0x19 | RKick_bit |
| 26 | 0x1A | Pass_to_Left |
| 27 | 0x1B | Pass_It_to_Me! |
| 28 | 0x1C | Pass_to_Right |
| 29 | 0x1D | None |
| 30 | 0x1E | Dance_LStep |
| 31 | 0x1F | Dance_FStep |
| 32 | 0x20 | Dance_RStep |
| 33 | 0x21 | Dance_Finish_Pose |
| 34 | 0x22 | Dance_Up_&_Down |
| 35 | 0x23 | Wiggle_Dance |
| 36 | 0x24 | Dance_BStep |
| 37 | 0x25 | Dance_Bow |
| 38 | 0x26 | Twist_Dance |
| 39 | 0x27 | None |
| 40 | 0x28 | None |
| 41 | 0x29 | Shake_Arms |
| 42 | 0x2A | 4A_Carry_Forward |
| 43 | 0x2B | 4B_Carry_LTurn |
| 44 | 0x2C | 4C_Carry_RTurn |
| 45 | 0x2D | 4D_Carry_Back |
| ~ | ~ | None |
| 70 | 0x46 | Walk_Forward |
| 71 | 0x47 | Walk_LTurn |
| 72 | 0x48 | Walk_RTurn |
| 73 | 0x49 | Walk_Back |

</details>

## Development Repositories
If you want to customize something of PLEN5Stack yourself, please check repositories below.

### 3D Model

- [PLEN2 & PLEN2 mini STL](https://github.com/plenprojectcompany/PLEN2)

- [PLEN2 3D Model for Autodesk Fusion 360](https://github.com/plenprojectcompany/plen-3DModel_Fusion360)

### Motion

- [PLEN:bit Motion](https://github.com/plenprojectcompany/plenbit-Motion)

## PLEN series robots history (evolution)

PLEN2 -> PLEN2-mini -> PLEN:bit -> PLEN5Stack

- [PLEN2](https://plen.jp/plen2/): The world's first printable open-source humanoid.
- [PLEN2mini](https://plen.jp/plen2/#plen2_mini): PLEN2 mini version
- [PLEN:bit](https://plen.jp/plenbit/): PLEN2mini for education, using the micro:bit.
- [PLEN5Stack](https://plen.jp/plen5stack/): PLEN2mini for developer, using the M5Stack.

## License

MIT

## Copyright

- [PLEN Project Company Inc](https://plen.jp/)