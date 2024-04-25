//
//  BravoControls.cpp
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


#include "BravoControls.hpp"


BravoControls::BravoControls() {
    bravo = new BravoUSB();
}

BravoControls::~BravoControls() {
    
}

bool BravoControls::fetchUSBControlsBuffer() {
    return bravo->getCurrentSettings(USBControlsBuffer);
}

uint16_t BravoControls::getU16(unsigned char char1, unsigned char char2) {
    return (uint8_t) char1 + ((uint8_t) char2 << 8);
}

bool BravoControls::getBool(unsigned char char1, uint8_t mask) {
    return (char1 & mask);
}

rotaryButtonLabel BravoControls::getRotaryLabel(unsigned char char1) {
    
    uint8_t mask = (uint8_t) char1 & 0b00011111;  // the bottome 5 bits represent the selection. one will have value 1, 4 will be 0;
    
    switch (mask) {
        case 1: return RCIAS;
            break;
        case 2: return RCCRS;
            break;
        case 4: return RCHDG;
            break;
        case 8: return RCVS;
            break;
        case 16: return RCALT;
            break;
    }
    return RCHDG;
}


int BravoControls::throttle1() {
    if (fetchUSBControlsBuffer())
        return (int) getU16(USBControlsBuffer[2], USBControlsBuffer[3]);
    else return 0;
}

int BravoControls::throttle2() {
    if (fetchUSBControlsBuffer())
        return (int) getU16(USBControlsBuffer[0], USBControlsBuffer[1]);
    else return 0;
}

int BravoControls::throttle3() {
    if (fetchUSBControlsBuffer())
        return (int) getU16(USBControlsBuffer[8], USBControlsBuffer[9]);
    else return 0;
}

int BravoControls::throttle4() {
    if (fetchUSBControlsBuffer())
        return (int) getU16(USBControlsBuffer[6], USBControlsBuffer[7]);
    else return 0;
}

int BravoControls::throttle5() {
    if (fetchUSBControlsBuffer())
        return (int) getU16(USBControlsBuffer[4], USBControlsBuffer[5]);
    else return 0;
}

int BravoControls::throttle6() {
    if (fetchUSBControlsBuffer())
        return (int) getU16(USBControlsBuffer[10], USBControlsBuffer[11]);
    else return 0;
}

int BravoControls::throttle(BravoControl throttleID) {
    
    switch (throttleID) {
        case Throttle1: return throttle1();
            break;
        case Throttle2: return throttle2();
            break;
        case Throttle3: return throttle3();
            break;
        case Throttle4: return throttle4();
            break;
        case Throttle5: return throttle5();
            break;
        case Throttle6: return throttle6();
            break;
        default: return -1;
            break;
    }
}

int BravoControls::throttle(int32_t throttleID) {
    
    switch (throttleID) {
        case 1: return throttle1();
            break;
        case 2: return throttle2();
            break;
        case 3: return throttle3();
            break;
        case 4: return throttle4();
            break;
        case 5: return throttle5();
            break;
        case 6: return throttle6();
            break;
        default: return -1;
            break;
    }
}

bool BravoControls::throttle1Reverser() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[15], Throttle1ReverserMask);
    else return false;
}

bool BravoControls::throttle2Reverser() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[13], Throttle2ReverserMask);
    else return false;
}

bool BravoControls::throttle3Reverser() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[13], Throttle3ReverserMask);
    else return false;
}

bool BravoControls::throttle4Reverser() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[13], Throttle4ReverserMask);
    else return false;
}

bool BravoControls::throttle5Reverser() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[13], Throttle5ReverserMask);
    else return false;
}

bool BravoControls::throttleReverser(BravoControl reverserID) {
    
    switch (reverserID) {
        case Throttle1: return throttle1Reverser();
            break;
        case Throttle2: return throttle2Reverser();
            break;
        case Throttle3: return throttle3Reverser();
            break;
        case Throttle4: return throttle4Reverser();
            break;
        case Throttle5: return throttle5Reverser();
            break;
        default: return false;                            // Note: throttle6 does not support the reverser function
            break;
    }
}

bool BravoControls::throttleReverser(int reverserID) {
    
    switch (reverserID) {
        case 1: return throttle1Reverser();
            break;
        case 2: return throttle2Reverser();
            break;
        case 3: return throttle3Reverser();
            break;
        case 4: return throttle4Reverser();
            break;
        case 5: return throttle5Reverser();
            break;
        default: return false;                            // Note: throttle6 does not support the reverser function
            break;
    }
}

bool BravoControls::throttle1Detent() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[14], Throttle1DetentMask);
    else return false;
}

bool BravoControls::throttle2Detent() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[15], Throttle2DetentMask);
    else return false;
}

bool BravoControls::throttle3Detent() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[15], Throttle3DetentMask);
    else return false;
}

bool BravoControls::throttle4Detent() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[15], Throttle4DetentMask);
    else return false;
}

bool BravoControls::throttle5Detent() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[15], Throttle5DetentMask);
    else return false;
}

bool BravoControls::throttle6Detent() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Throttle6DetentMask);
    else return false;
}

bool BravoControls::throttleDetent(BravoControl detentID) {

    switch (detentID) {
        case Throttle1: return throttle1Detent();
            break;
        case Throttle2: return throttle2Detent();
            break;
        case Throttle3: return throttle3Detent();
            break;
        case Throttle4: return throttle4Detent();
            break;
        case Throttle5: return throttle5Detent();
            break;
        case Throttle6: return throttle6Detent();
            break;
        default: return false;
            break;
    }
}

bool BravoControls::throttleDetent(int detentID) {

    switch (detentID) {
        case 1: return throttle1Detent();
            break;
        case 2: return throttle2Detent();
            break;
        case 3: return throttle3Detent();
            break;
        case 4: return throttle4Detent();
            break;
        case 5: return throttle5Detent();
            break;
        case 6: return throttle6Detent();
            break;
        default: return false;
            break;
    }
}


rotaryButtonLabel BravoControls::rotaryLabel() {
    if (fetchUSBControlsBuffer())
        return getRotaryLabel(USBControlsBuffer[14]);
    else return RCHDG;
}


bool BravoControls::switch1() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Switch1Mask);
    else return false;
}

bool BravoControls::switch2() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Switch2Mask);
    else return false;
}

bool BravoControls::switch3() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Switch3Mask);
    else return false;
}

bool BravoControls::switch4() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Switch4Mask);
    else return false;
}

bool BravoControls::switch5() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Switch5Mask);
    else return false;
}

bool BravoControls::switch6() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Switch6Mask);
    else return false;
}

bool BravoControls::switch7() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[16], Switch7Mask);
    else return false;
}

bool BravoControls::switch8() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[17], Switch8Mask);
    else return false;
}

bool BravoControls::switch9() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[17], Switch9Mask);
    else return false;
}

bool BravoControls::switch10() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[17], Switch10Mask);
    else return false;
}

bool BravoControls::switch11() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[17], Switch11Mask);
    else return false;
}

bool BravoControls::switch12() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[17], Switch12Mask);
    else return false;
}

bool BravoControls::switch13() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[17], Switch13Mask);
    else return false;
}

bool BravoControls::switch14() {
    if (fetchUSBControlsBuffer())
        return getBool(USBControlsBuffer[17], Switch14Mask);
    else return false;
}

bool BravoControls::switchState(BravoControl switchID) {
    
    switch (switchID) {
        case Switch1: return switch1();
            break;
        case Switch2: return switch2();
            break;
        case Switch3: return switch3();
            break;
        case Switch4: return switch4();
            break;
        case Switch5: return switch5();
            break;
        case Switch6: return switch6();
            break;
        case Switch7: return switch7();
            break;
        case Switch8: return switch8();
            break;
        case Switch9: return switch9();
            break;
        case Switch10: return switch10();
            break;
        case Switch11: return switch11();
            break;
        case Switch12: return switch12();
            break;
        case Switch13: return switch13();
            break;
        case Switch14: return switch14();
            break;
        default: return false;
            break;
    }
}

bool BravoControls::switchState(int switchID) {
    
    switch (switchID) {
        case 1: return switch1();
            break;
        case 2: return switch2();
            break;
        case 3: return switch3();
            break;
        case 4: return switch4();
            break;
        case 5: return switch5();
            break;
        case 6: return switch6();
            break;
        case 7: return switch7();
            break;
        case 8: return switch8();
            break;
        case 9: return switch9();
            break;
        case 10: return switch10();
            break;
        case 11: return switch11();
            break;
        case 12: return switch12();
            break;
        case 13: return switch13();
            break;
        case 14: return switch14();
            break;
        default: return false;
            break;
    }
}

/*
BravoControlSettings BravoControls::getBravoSettings() {
    
    unsigned char buffer[18];
    
    if (bravo->getCurrentSettings(buffer)) {
        currentBravoSettings.throttleSetting[1] = getU16(buffer[0], buffer[1]);
        currentBravoSettings.throttleSetting[0] = getU16(buffer[2], buffer[3]);
        currentBravoSettings.throttleSetting[4] = getU16(buffer[4], buffer[5]);
        currentBravoSettings.throttleSetting[3] = getU16(buffer[6], buffer[7]);
        currentBravoSettings.throttleSetting[2] = getU16(buffer[8], buffer[9]);
        currentBravoSettings.throttleSetting[5] = getU16(buffer[10], buffer[11]);
        currentBravoSettings.throttleReverser[0] = getBool(buffer[15], Throttle1ReverserMask);
        currentBravoSettings.throttleReverser[1] = getBool(buffer[13], Throttle2ReverserMask);
        currentBravoSettings.throttleReverser[2] = getBool(buffer[13], Throttle3ReverserMask);
        currentBravoSettings.throttleReverser[3] = getBool(buffer[13], Throttle4ReverserMask);
        currentBravoSettings.throttleReverser[4] = getBool(buffer[13], Throttle5ReverserMask);
        currentBravoSettings.throttleDetent[0] = getBool(buffer[14], Throttle1DetentMask);
        currentBravoSettings.throttleDetent[1] = getBool(buffer[15], Throttle2DetentMask);
        currentBravoSettings.throttleDetent[2] = getBool(buffer[15], Throttle3DetentMask);
        currentBravoSettings.throttleDetent[3] = getBool(buffer[15], Throttle4DetentMask);
        currentBravoSettings.throttleDetent[4] = getBool(buffer[15], Throttle5DetentMask);
        currentBravoSettings.throttleDetent[5] = getBool(buffer[16], Throttle6DetentMask);
        currentBravoSettings.rotaryValue = getRotaryLabel(buffer[14]);
        currentBravoSettings.switchPressed[0] = getBool(buffer[16], Switch1Mask);
        currentBravoSettings.switchPressed[1] = getBool(buffer[16], Switch2Mask);
        currentBravoSettings.switchPressed[2] = getBool(buffer[16], Switch3Mask);
        currentBravoSettings.switchPressed[3] = getBool(buffer[16], Switch4Mask);
        currentBravoSettings.switchPressed[4] = getBool(buffer[16], Switch5Mask);
        currentBravoSettings.switchPressed[5] = getBool(buffer[16], Switch6Mask);
        currentBravoSettings.switchPressed[6] = getBool(buffer[16], Switch7Mask);
        currentBravoSettings.switchPressed[7] = getBool(buffer[17], Switch8Mask);
        currentBravoSettings.switchPressed[8] = getBool(buffer[17], Switch9Mask);
        currentBravoSettings.switchPressed[9] = getBool(buffer[17], Switch10Mask);
        currentBravoSettings.switchPressed[10] = getBool(buffer[17], Switch11Mask);
        currentBravoSettings.switchPressed[11] = getBool(buffer[17], Switch12Mask);
        currentBravoSettings.switchPressed[12] = getBool(buffer[17], Switch13Mask);
        currentBravoSettings.switchPressed[13] = getBool(buffer[17], Switch14Mask);
        currentBravoSettings.gearDown = getBool(buffer[15], GearDownMask);
        currentBravoSettings.gearUp = getBool(buffer[15], GearUpMask);
    }
    return currentBravoSettings;
    

}

*/
