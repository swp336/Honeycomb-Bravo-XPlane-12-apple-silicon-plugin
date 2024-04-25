//
//  Switch.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 05/05/2023.
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


#include "Switch.hpp"
#include <map>


SwitchMap::SwitchMap() {
}

SwitchMap::~SwitchMap() {
}

std::string SwitchMap::switchRef(int switchNumber) {
    return std::string("Honeycomb/Bravo/Switch/") + std::to_string(switchNumber);
}

std::string SwitchMap::switchDescr(int switchNumber) {
    return std::string("Switch ") + std::to_string(switchNumber);
}

int SwitchMap::switchDeviceNumber(switchLabel switchID) {
    return switchMap[switchID];
}

int SwitchMap::switchLogicalNumber(switchLabel switchID) {
    return switchMap[switchID] - 12;
}


    
/***************************************************************
 *
 *  Basic switch for honeycomb bravo
 *
 *  Simplest for,m Tracks on / off switch status updated with each button press event
 *  For use when monitoring single switch status in some broader function
 *
 *  invoking setCommand (or using the constructor with the XPCommand parameter)
 *  causes the command to be executued each time the switch is pressed;
 *
 *  The commandHandler can be replaced by another object using the delegate
 *  method to remove the built in handler and then creating their own version
 *
 *********************************************************************************************/


Switch::Switch(switchLabel switchID, switchState defaultState) {
    
    switchMap = SwitchMap();
    mySwitchID = switchID;
    myDefault  = defaultState;
    userRef = switchMap.switchRef(switchMap.switchDeviceNumber(switchID));
    userDesc = switchMap.switchDescr(switchMap.switchDeviceNumber(switchID));
    myState = myDefault;
    switchHandlerRef = xplane -> createCommandAndTellMe(userRef.c_str(), userDesc.c_str(), [this] (CommandState s) { if (s == CommandState::START) switchOnStatusHandler(); else if (s == CommandState::END) switchOffStatusHandler(); });
}

Switch::Switch(switchLabel switchID, switchState defaultState, XPCommand* newCommand) : Switch(switchID, defaultState) {
    setCommand(newCommand);
}

void Switch::setCommand(XPCommand *newXPCommand) {
    
    myCommand = newXPCommand;
    delegateHandler();
    switchHandlerRef = xplane -> createCommandAndTellMe(userRef.c_str(), userDesc.c_str(), [this] (CommandState s) { if (s == CommandState::START) commandOnHandler(); else if (s == CommandState::END) commandOffHandler(); });
}

std::string Switch::userReference() {
    return userRef;
}

std::string Switch::userDescription() {
    return userDesc;
}

int Switch::switchID() {
    return mySwitchID;
}

switchState Switch::status() {
    return myState;
}

void Switch::toggleState() {
    if (myState == on) myState = off; else myState = on;
}

void Switch::delegateHandler() {
    xplane -> destroyCommand(switchHandlerRef);
}

void Switch::switchOnStatusHandler() {
    myState = on;
}

void Switch::switchOffStatusHandler() {
    myState = off;
}

void Switch::commandOnHandler() {
    if (!myCommand -> isNull()) {
        XPLMCommandOnce(myCommand -> commandRef());
    }
    myState = on;
}

void Switch::commandOffHandler() {
    myState = off;
}

Switch::~Switch() {
    xplane -> destroyCommand(switchHandlerRef);
}

