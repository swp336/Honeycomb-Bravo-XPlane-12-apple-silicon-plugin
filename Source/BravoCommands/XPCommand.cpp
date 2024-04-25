//
//  XPCommand.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 17/04/2023.
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


#include <map>
#include "XPCommand.hpp"
#include "Switch.hpp"
#include "Toggle.hpp"


std::map<commandSpeed, int> speedMap { {slowest,300}, {slow,150}, {medium,100}, {fast,25}, {fastest,0} };

XPCommandSpeed::XPCommandSpeed(int speed) {
    _defaultSpeed = speed;
    _differential = false;
}

XPCommandSpeed::XPCommandSpeed(int slow, int fast) {
    _slowSpeed = slow;
    _fastSpeed = fast;
    _differential = true;
}

XPCommandSpeed::XPCommandSpeed(commandSpeed speed) {
    _defaultSpeed = speedMap[speed];
    _differential = false;
}

XPCommandSpeed::XPCommandSpeed(commandSpeed slow, commandSpeed fast) {
    _slowSpeed = speedMap[slow];
    _fastSpeed = speedMap[fast];
    _differential = true;
}

void XPCommandSpeed::setSpeed(int repeatSpeed) {
    _defaultSpeed = repeatSpeed;
    _differential = false;
}

void XPCommandSpeed::setSpeed(int lowSpeed, int highSpeed) {
    _slowSpeed = lowSpeed;
    _fastSpeed = highSpeed;
    _differential = true;
}

void XPCommandSpeed::setSpeed(commandSpeed repeatSpeed) {
    _defaultSpeed = speedMap[repeatSpeed];
    _differential = false;
}

void XPCommandSpeed::setSpeed(commandSpeed lowSpeed, commandSpeed highSpeed) {
    _slowSpeed = speedMap[lowSpeed];
    _fastSpeed = speedMap[highSpeed];
    _differential = true;

}

void XPCommandSpeed::setSpeed(XPCommandSpeed repeatSpeed) {
}


int XPCommandSpeed::defaultSpeed() {
    return _defaultSpeed;
}

bool XPCommandSpeed::differentialSpeed() {
    return _differential;
}

int XPCommandSpeed::fastSpeed() {
    return _fastSpeed;
}

int XPCommandSpeed::slowSpeed() {
    return _slowSpeed;
}



XPCommand::XPCommand() : mySpeed(slowest) {
    active = false;
}

XPCommand::~XPCommand() {
    active = false;
}

XPCommand::XPCommand(const char* simCommand) : mySpeed(slowest) {
    setCommand(simCommand);
}

XPCommand::XPCommand(const char * simCommand, int repeatSpeed) : mySpeed(repeatSpeed) {
    setCommand(simCommand);
}

XPCommand::XPCommand(const char * simCommand, int lowSpeed, int highSpeed) : mySpeed(lowSpeed, highSpeed) {
    setCommand(simCommand);
}

XPCommand::XPCommand(const char * simCommand, commandSpeed repeatSpeed) : mySpeed(repeatSpeed) {
    setCommand(simCommand);
}

XPCommand::XPCommand(const char * simCommand, commandSpeed lowSpeed, commandSpeed highSpeed) : mySpeed(lowSpeed, highSpeed) {
    setCommand(simCommand);
}

XPCommand::XPCommand(const char * simCommand, XPCommandSpeed repeatSpeed) : mySpeed(repeatSpeed) {
    setCommand(simCommand);
}

void XPCommand::setCommand(const char * simCommand) {
        
    if (simCommand == NULL) {
        commandIsNull = true;
        mySimCommandRef = XPLMFindCommand("");
        myCommandString = std::string("NOT_USED");
    } else
    {   commandIsNull = false;
        mySimCommandRef = XPLMFindCommand(simCommand);
        myCommandString = std::string(simCommand);
    }
    active = true;
}

void XPCommand::addCompanionCommand(XPCommand* companion) {
    
    if (_companionCommand == NULL)
        _companionCommand = companion;
    else {  XPCommand* companionTracker;
            XPCommand* currentCommand;
            
            currentCommand = _companionCommand;
            companionTracker = currentCommand -> _companionCommand;
        
            while (companionTracker != NULL)       // find the end of the companion tree;
            {   currentCommand = companionTracker;
                companionTracker = currentCommand -> _companionCommand;
            }
            currentCommand -> _companionCommand = companion;     // found the end of the tree.  add the new comapion command to the end of the tree
        }
}

XPCommand* XPCommand::companionCommand() {
    return _companionCommand;
}


void XPCommand::setSpeed(int newSpeed) {
    mySpeed.setSpeed(newSpeed);
}

void XPCommand::setSpeed(int lowSpeed, int highSpeed) {
    mySpeed.setSpeed(lowSpeed, highSpeed);
}

void XPCommand::setSpeed(commandSpeed repeatSpeed) {
    mySpeed.setSpeed(repeatSpeed);
}

void XPCommand::setSpeed(commandSpeed lowSpeed, commandSpeed highSpeed) {
    mySpeed.setSpeed(lowSpeed, highSpeed);
}

void XPCommand::setSpeed(XPCommandSpeed repeatSpeed) {
    mySpeed.setSpeed(repeatSpeed);
}

std::string XPCommand::commandName() {
    return myCommandString;
}

bool XPCommand::isActive() {
    return active;
}

bool XPCommand::isNull() {
    return commandIsNull;
}

void XPCommand::activate() {
    active = true;
}

void XPCommand::deActivate() {
    active = false;
}

XPLMCommandRef XPCommand::commandRef() {
    return mySimCommandRef;
}

XPCommandSpeed* XPCommand::speed() {
    return &mySpeed;
}


XPTwinCommands::XPTwinCommands() {
    active = false;
}

XPTwinCommands::~XPTwinCommands() {
    delete myCommand1;
    delete myCommand2;
}

XPTwinCommands::XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2) {
    
    if (newCommand1 != NULL)
        myCommand1 = newCommand1;
    else myCommand1 = new XPCommand(NULL);
    
    if (newCommand2 != NULL)
        myCommand2 = newCommand2;
    else myCommand2 = new XPCommand(NULL);
    active = true;
}

XPTwinCommands::XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, int repeatSpeed) {
    myCommand1 = newCommand1;
    myCommand2 = newCommand2;
    myCommand1 -> setSpeed(repeatSpeed);
    myCommand2 -> setSpeed(repeatSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, int lowSpeed, int highSpeed) {
    myCommand1 = newCommand1;
    myCommand2 = newCommand2;
    myCommand1 -> setSpeed(lowSpeed, highSpeed);
    myCommand2 -> setSpeed(lowSpeed, highSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, commandSpeed repeatSpeed) {
    myCommand1 = newCommand1;
    myCommand2 = newCommand2;
    myCommand1 -> setSpeed(repeatSpeed);
    myCommand2 -> setSpeed(repeatSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, commandSpeed lowSpeed, commandSpeed highSpeed) {
    myCommand1 = newCommand1;
    myCommand2 = newCommand2;
    myCommand1 -> setSpeed(lowSpeed, highSpeed);
    myCommand2 -> setSpeed(lowSpeed, highSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, XPCommandSpeed repeatSpeed) {
    myCommand1 = newCommand1;
    myCommand2 = newCommand2;
    myCommand1 -> setSpeed(repeatSpeed);
    myCommand2 -> setSpeed(repeatSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(const char * simCommand1, const char * simCommand2) {
    myCommand1 = new XPCommand(simCommand1);
    myCommand2 = new XPCommand(simCommand2);
    active = true;
}

XPTwinCommands::XPTwinCommands(const char * simCommand1, const char * simCommand2, int repeatSpeed) {
    myCommand1 = new XPCommand(simCommand1, repeatSpeed);
    myCommand2 = new XPCommand(simCommand2, repeatSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(const char * simCommand1, const char * simCommand2, int lowSpeed, int highSpeed) {
    myCommand1 = new XPCommand(simCommand1, lowSpeed, highSpeed);
    myCommand2 = new XPCommand(simCommand2, lowSpeed, highSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(const char * simCommand1, const char * simCommand2, commandSpeed repeatSpeed) {
    myCommand1 = new XPCommand(simCommand1, repeatSpeed);
    myCommand2 = new XPCommand(simCommand2, repeatSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(const char * simCommand1, const char * simCommand2, commandSpeed lowSpeed, commandSpeed highSpeed) {
    myCommand1 = new XPCommand(simCommand1, lowSpeed, highSpeed);
    myCommand2 = new XPCommand(simCommand2, lowSpeed, highSpeed);
    active = true;
}

XPTwinCommands::XPTwinCommands(const char * simCommand1, const char * simCommand2, XPCommandSpeed repeatSpeed) {
    myCommand1 = new XPCommand(simCommand1, repeatSpeed);
    myCommand2 = new XPCommand(simCommand2, repeatSpeed);
    active = true;
}

void XPTwinCommands::addCompanionCommands(XPTwinCommands* companions) {
    myCommand1 -> addCompanionCommand(companions -> myCommand1);
    myCommand2 -> addCompanionCommand(companions -> myCommand2);
}

XPCommand* XPTwinCommands::command1() {
    return myCommand1;
}

XPCommand* XPTwinCommands::command2() {
    return myCommand2;
}

XPCommand* XPTwinCommands::command() {
    return myCommand1;
}

void XPTwinCommands::activate() {
    myCommand1 -> activate();
    myCommand2 -> activate();
    active = true;
}

void XPTwinCommands::deActivate() {
    myCommand1 -> deActivate();
    myCommand2 -> deActivate();
    active = false;
}

bool XPTwinCommands::isActive() {
    return active;
}



/***************************************************************
 *
 *  Command Set for honeycomb bravo
 *
 *  Maintains a set of commands indexed by switches / toggles
 *
 *********************************************************************************************/


namespace std {

    template <>                 // required to enable a toggleLabel to be uniquely hashed so it can provide a unique key for the map
    struct hash<switchLabel>
        { size_t operator()(const switchLabel key)
            { switch (key) {
                case SW1:
                    return 1;
                    break;
                case SW2:
                    return 2;
                    break;
                case SW3:
                    return 3;
                    break;
                case SW4:
                    return 4;
                    break;
                case SW5:
                    return 5;
                    break;
                case SW6:
                    return 6;
                    break;
                case SW7:
                    return 7;
                    break;
                case SW8:
                    return 8;
                    break;
                case SW9:
                    return 9;
                    break;
                case SW10:
                    return 10;
                    break;
                case SW11:
                    return 11;
                    break;
                case SW12:
                    return 12;
                    break;
                case SW13:
                    return 13;
                    break;
                case SW14:
                    return 14;
                    break;
                    return 0;
                }
            }
        };
}


ToggleMap toggleMap = ToggleMap();

CommandSet::CommandSet() {
}

CommandSet::~CommandSet() {
    commandSwitchSet.clear();
}

/*
void CommandSet::addCommand(XPCommand* newCommand, switchLabel addToSwitch) {
    commandSwitchSet.insert(std::make_pair(addToSwitch, newCommand));
}
*/
void CommandSet::addCommands(XPTwinCommands* newCommands, toggleLabel addToToggle) {
      
    commandSwitchSet.insert(std::make_pair(addToToggle, newCommands));
}

void CommandSet::addCommand(XPCommand* newCommand, toggleLabel addToToggle) {
      
    commandSwitchSet.insert(std::make_pair(addToToggle, new XPTwinCommands(newCommand, NULL)));
}

/*
XPCommand* CommandSet::getCommand(switchLabel switchToLookUp) {
    return commandSwitchSet[switchToLookUp];
}
*/

XPCommand* CommandSet::getCommand(toggleLabel toggleToLookUp) {

    return commandSwitchSet[toggleToLookUp] -> command();
}

XPTwinCommands* CommandSet::getCommands(toggleLabel toggleToLookUp) {

//    return new XPTwinCommands(commandSwitchSet[toggleMap.upperSwitchID(toggleToLookUp)], commandSwitchSet[toggleMap.lowerSwitchID(toggleToLookUp)]);
    return commandSwitchSet[toggleToLookUp];
}

bool CommandSet::isEmpty() {
    return commandSwitchSet.empty();
}

