//
//  BravoControls.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 06/06/2023.
//

/*
 *   X-Plane 12 Plugin for Apple Silicon Computers
 *
 *   Copyright (C) 2024 Steve Proctor <swp336@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef BravoControls_hpp
#define BravoControls_hpp

#include <cstdint>
#include "BravoUSB.hpp"
#include "RotaryButtonLabel.hpp"

enum BravoControl { GearUp,GearDown,
                    FlapsIncrease, FlapsDecrease,
                    TrimwheelUp, TrimwheelDown,
                    IncrementSelectorControl, DecrementSelectorControl,
                    Throttle2ButtonControl, Throttle3ButtonControl, Throttle4ButtonControl,
                    Throttle1, Throttle2, Throttle3, Throttle4, Throttle5, Throttle6,
                    Switch1, Switch2, Switch3, Switch4, Switch5, Switch6, Switch7,
                    Switch8, Switch9, Switch10, Switch11, Switch12, Switch13, Switch14,
                    HDGButtonControl, NAVButtonControl, APRButtonControl, REVButtonControl, VSButtonControl, IASButtonControl, AutoPilotButtonControl
};

struct BravoControlSettings {
    int throttleSetting[6];
    bool throttleReverser[5];
    bool throttleDetent[6];
    rotaryButtonLabel rotaryValue;
    bool switchPressed[14];
    bool gearDown, gearUp;
};

class BravoControls {
    
public:
    BravoControls();
    ~BravoControls();
//    BravoControlSettings getBravoSettings();
    int throttle1();
    int throttle2();
    int throttle3();
    int throttle4();
    int throttle5();
    int throttle6();
    int throttle(BravoControl throttleID);
    int throttle(int throttleID);
    bool throttle1Reverser();
    bool throttle2Reverser();
    bool throttle3Reverser();
    bool throttle4Reverser();
    bool throttle5Reverser();
    bool throttleReverser(BravoControl throttleID);
    bool throttleReverser(int throttleID);
    bool throttle1Detent();
    bool throttle2Detent();
    bool throttle3Detent();
    bool throttle4Detent();
    bool throttle5Detent();
    bool throttle6Detent();
    bool throttleDetent(BravoControl throttleID);
    bool throttleDetent(int throttleID);
    bool switch1();                                  // true = switch is pressed
    bool switch2();                                  // note: switches are in pairs, so if 1 is true, 2 will be false, same for 3-4, 5-6 etc
    bool switch3();
    bool switch4();
    bool switch5();
    bool switch6();
    bool switch7();
    bool switch8();
    bool switch9();
    bool switch10();
    bool switch11();
    bool switch12();
    bool switch13();
    bool switch14();
    bool switchState(BravoControl switchID);      // can't use function name 'switch' as this is a reserved word in C++
    bool switchState(int switchID);

    rotaryButtonLabel rotaryLabel();
    
private:
    BravoUSB* bravo = NULL;
    
    unsigned char USBControlsBuffer[18];
    
    bool fetchUSBControlsBuffer();
    
    uint16_t Throttle1Value;                // bytes 1-2         18 byte data block sent by Honeycomb Bravo in response to a USB read-input request
    uint16_t Throttle2Value;                // bytes 3-4
    uint16_t Throttle3Value;                // bytes 5-6
    uint16_t Throttle4Value;                // bytes 7-8
    uint16_t Throttle5Value;                // bytes 9-10
    uint16_t Throttle6Value;                // bytes 11-12
    
    uint8_t  APHDGmask = 1;                 // byte 13
    uint8_t  APNAVmask = 2;                 // byte 13
    uint8_t  APAPRmask = 4;                 // byte 13
    uint8_t  APREVmask = 8;                 // byte 13
    uint8_t  APALTmask = 16;                // byte 13
    uint8_t  APVSmask  = 32;                // byte 13
    uint8_t  APIASmask = 64;                // byte 13
    uint8_t  APAutoPilotmask = 128;         // byte 13
    
    uint8_t Throttle2ReverserMask = 1;      // byte 14
    uint8_t Throttle3ReverserMask = 2;      // byte 14
    uint8_t Throttle4ReverserMask = 4;      // byte 14
    uint8_t Throttle5ReverserMask = 8;      // byte 14
    uint8_t IncrementSelectorMask = 16;     // byte 14
    uint8_t DecrementSelectorMask = 32;     // byte 14
    uint8_t FlapsIncreaseMask     = 64;     // byte 14
    uint8_t FlapsDecreaseMask     = 128;    // byte 14

    uint8_t IASRotarySelectorMask = 1;      // byte 15
    uint8_t CRSRotarySelectorMask = 2;      // byte 15
    uint8_t HDGRotarySelectorMask = 4;      // byte 15
    uint8_t VSRotarySelectorMask  = 8;      // byte 15
    uint8_t ALTRotarySelectorMask = 16;     // byte 15
    uint8_t TrimDownMask          = 32;     // byte 15
    uint8_t TrimUpMask            = 64;     // byte 15
    uint8_t Throttle1DetentMask   = 128;    // byte 15
    
    uint8_t Throttle2DetentMask   = 1;      // byte 16
    uint8_t Throttle3DetentMask   = 2;      // byte 16
    uint8_t Throttle4DetentMask   = 4;      // byte 16
    uint8_t Throttle5DetentMask   = 8;      // byte 16
    uint8_t Throttle2ButtonMask   = 16;     // byte 16
    uint8_t Throttle1ReverserMask = 16;     // byte 16 - not an error.  Both are reporerted on this same bit.
    uint8_t Throttle3ButtonMask   = 32;     // byte 16
    uint8_t GearUpMask            = 64;     // byte 16
    uint8_t GearDownMask          = 128;    // byte 16

    uint8_t Throttle6DetentMask   = 1;      // byte 17
    uint8_t Switch1Mask           = 2;      // byte 17
    uint8_t Switch2Mask           = 4;      // byte 17
    uint8_t Switch3Mask           = 8;      // byte 17
    uint8_t Switch4Mask           = 16;     // byte 17
    uint8_t Switch5Mask           = 32;     // byte 17
    uint8_t Switch6Mask           = 64;     // byte 17
    uint8_t Switch7Mask           = 128;    // byte 17

    uint8_t Switch8Mask           = 1;      // byte 18
    uint8_t Switch9Mask           = 2;      // byte 18
    uint8_t Switch10Mask          = 4;      // byte 18
    uint8_t Switch11Mask          = 8;      // byte 18
    uint8_t Switch12Mask          = 16;     // byte 18
    uint8_t Switch13Mask          = 32;     // byte 18
    uint8_t Switch14Mask          = 64;     // byte 18
    uint8_t Throttle4ButtonMask   = 128;    // byte 18

    BravoControlSettings currentBravoSettings;
    uint16_t getU16(unsigned char char1, unsigned char char2);
    bool getBool(unsigned char char1, uint8_t mask);
    rotaryButtonLabel getRotaryLabel(unsigned char char1);
};


#endif /* BravoControls_hpp */
