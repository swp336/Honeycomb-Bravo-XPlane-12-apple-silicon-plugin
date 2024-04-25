//
//  Toggle.cpp
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


#include "XPlaneEnvironment.hpp"
#include "Toggle.hpp"
#include "Switch.hpp"

#include <map>

ToggleMap::ToggleMap() {
}

ToggleMap::~ToggleMap() {
}

switchLabel ToggleMap:: upperSwitchID(toggleLabel toggleID) {
    return upperSwitchMap[toggleID];
}

switchLabel ToggleMap::lowerSwitchID(toggleLabel toggleID) {
    return lowerSwitchMap[toggleID];
}


/***************************************************************
 *
 *  Basic Rocker switch for honeycomb bravo
 *
 *  Tracks on / off switch status updated with each button press event
 *  For use when monitoring switch status in some broader function
 *
 *   calling setCommand (or using one of the command-based constructors)
 *  casues the toggle to execute a command with each toggle flip
 *
 *  Command handler is invoked at the start of each switch press switch event
 *
 *  The commandHandler can be replaced by another object using the delegate
 *  method to remove the built in handler and then creating their own version
 *
 *********************************************************************************************/

Toggle::Toggle(toggleLabel toggleID) {

    toggleMap = ToggleMap();
    
    myToggleID = toggleID;
    toggleState = off;
    switchLabel offSwitchID = toggleMap.upperSwitchID(toggleID);
    switchLabel onSwitchID  = toggleMap.lowerSwitchID(toggleID);
    myOffSwitch = new Switch(offSwitchID, off);
    myOnSwitch  = new Switch(onSwitchID, on);
    myOffSwitch -> delegateHandler();
    myOnSwitch -> delegateHandler();
    offHandlerRef =  xplane -> createCommandAndTellMe(myOffSwitch->userReference().c_str(), myOffSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) toggleOffHandler(); });
    onHandlerRef = xplane -> createCommandAndTellMe(myOnSwitch->userReference().c_str(), myOnSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) toggleOnHandler(); });

    int logicalSwitchID = switchMap.switchLogicalNumber(onSwitchID);
    bool deviceSwitchState = controls -> switchState(logicalSwitchID);    // get the current position of the switch via the USB connection
    if (deviceSwitchState)
        toggleState = on;
    else toggleState = off;
}

Toggle::Toggle(toggleLabel toggleID, XPTwinCommands* newCommands) : Toggle(toggleID) {
    setCommands(newCommands);
}

Toggle::Toggle(toggleLabel toggleID, XPCommand* newCommand1, XPCommand* newCommand2) : Toggle(toggleID, new XPTwinCommands(newCommand1, newCommand2)) {
}

Toggle::Toggle(toggleLabel toggleID, const char* newCommand1, const char* newCommand2) : Toggle(toggleID, new XPCommand(newCommand1), new XPCommand(newCommand2)){
}

void Toggle::setCommands(XPTwinCommands *newCommands) {
    
    myCommands = newCommands;
    delegateHandler();
    offHandlerRef =  xplane -> createCommandAndTellMe(myOffSwitch->userReference().c_str(), myOffSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) commandOffHandler(); });
    onHandlerRef = xplane -> createCommandAndTellMe(myOnSwitch->userReference().c_str(), myOnSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) commandOnHandler(); });
}

void Toggle::setCommands(XPCommand* newCommand1, XPCommand* newCommand2) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

void Toggle::setCommands(const char* newCommand1, const char* newCommand2) {
    setCommands(new XPCommand(newCommand1), new XPCommand(newCommand2));
}

XPTwinCommands* Toggle::commands() {
    return myCommands;
}

bool Toggle::toggleIsOn() {
    return (toggleState == on);
}

Switch* Toggle::onSwitch() {
    return myOnSwitch;
}

Switch* Toggle::offSwitch() {
    return myOffSwitch;
}

toggleLabel Toggle::toggleID() {
    return myToggleID;
}

void Toggle::delegateHandler() {
    xplane -> destroyCommand(offHandlerRef);
    xplane -> destroyCommand(onHandlerRef);
}

void Toggle::notifyChanges(bool* notifyHere) {
    notifyChange = notifyHere;
}

void Toggle::toggleOffHandler() {
    
    switch (toggleState) {
            
        case on:  toggleState = off;
                  myOnSwitch -> toggleState();
                  break;
        case off: toggleState = off;
                  break;
    }
    if (notifyChange !=NULL) *notifyChange = true;
}

void Toggle::toggleOnHandler() {
    
    switch (toggleState) {
            
        case on:  toggleState = on;
                  break;
        case off: toggleState = on;
                  myOffSwitch -> toggleState();
                  break;
    }
    if (notifyChange !=NULL) *notifyChange = true;
}

void Toggle::commandOffHandler() {
    toggleOffHandler();
    if (!myCommands -> command1() -> isNull()) {
        XPLMCommandOnce(myCommands -> command1() -> commandRef());
    }
}


void Toggle::commandOnHandler() {
    toggleOnHandler();
    if (!myCommands -> command2() -> isNull()) {
        XPLMCommandOnce(myCommands -> command2() -> commandRef());
    }
}


Toggle::~Toggle() {
    xplane -> destroyCommand(offHandlerRef);
    xplane -> destroyCommand(onHandlerRef);
    delete myOffSwitch;
    delete myOnSwitch;
    notifyChange = NULL;
}



/***************************************************************
 *
 *  Toggle Set for honeycomb bravo
 *
 *  Maintains a set of toggles
 *
 *********************************************************************************************/

namespace std {

    template <>                 // required to enable a toggleLabel to be uniquely hashed so it can provide a unique key for the map
    struct hash<toggleLabel>
        { size_t operator()(const toggleLabel key)
            { switch (key) {
                case TG1:
                    return 1;
                    break;
                case TG2:
                    return 2;
                    break;
                case TG3:
                    return 3;
                    break;
                case TG4:
                    return 4;
                    break;
                case TG5:
                    return 5;
                    break;
                case TG6:
                    return 6;
                    break;
                case TG7:
                    return 7;
                    break;
                    return 0;
                }
            }
        };
}

ToggleSet::ToggleSet() {
}

ToggleSet::ToggleSet(TogglePrecedence precedenceOrder) {
    _direction = precedenceOrder;
}

ToggleSet::~ToggleSet() {
    toggleSet.clear();
}

void ToggleSet::addToggle(Toggle* newToggle) {
    
    newToggle -> notifyChanges(&changeFlag);
    toggleSet.insert(std::make_pair(newToggle->toggleID(), newToggle));
}

Toggle* ToggleSet::getToggle(toggleLabel toggleToGet) {
    return toggleSet[toggleToGet];
}

bool ToggleSet::isActive() {
    
    bool foundActive = false;
    
    for(it = toggleSet.begin(); it != toggleSet.end(); ++it) {
        try {
            foundActive = foundActive || it -> second -> toggleIsOn();
        }
        catch (...)
        {
        }
    }
    return foundActive;
}

Toggle* ToggleSet::activeToggle() {
    
    bool found = false;
    Toggle* foundToggle = NULL;
    
    switch (_direction) {
    
        case LeftToRight: { for(auto it = toggleSet.begin(); ((it != toggleSet.end()) && (!found)); ++it) {
                                try { if (it -> second != NULL) {
                                        found = it -> second -> toggleIsOn();
                                        if (found) foundToggle = it ->second;
                                    }
                                }
                                catch (...) { }
                            }
                        } break;
        case RightToLeft: { for(auto it = toggleSet.rbegin(); ((it != toggleSet.rend()) && (!found)); ++it) {
                                try { if (it -> second != NULL) {
                                        found = it -> second -> toggleIsOn();
                                        if (found) foundToggle = it ->second;
                                    }
                                }
                                catch (...) { }
                            }
                        } break;
        default: return NULL;
    }
    return foundToggle;
}

std::tuple<bool, Toggle*> ToggleSet::activeToggle(CommandSet* commands) {
        
    switch (_direction) {
            
        case LeftToRight: { for (toggleLabel toggle : {TG1, TG2, TG3, TG4, TG5, TG6, TG7} ) {
                                if (commands->getCommands(toggle) != NULL)  {
                                    if (getToggle(toggle) -> toggleIsOn()) return {true, getToggle(toggle) };
                                    }
                                }
                          } break;
        case RightToLeft: { for (toggleLabel toggle : {TG7, TG6, TG5, TG4, TG3, TG2, TG1} ) {
                                if (commands->getCommands(toggle) != NULL)  {
                                    if (getToggle(toggle) -> toggleIsOn()) return {true, getToggle(toggle) };
                                    }
                                }
                          } break;
        default: return {false, NULL}; break;
    } return {false, NULL};
}


bool ToggleSet::hasChanged() {    
    return changeFlag;
}

void ToggleSet::resetChangeFlag() {
    changeFlag = false;
}

TogglePrecedence ToggleSet::precedenceOrder() {
    return _direction;
}

void ToggleSet::SetTogglePrecedence(TogglePrecedence thisDirection) {
    _direction = thisDirection;
}

TrackingToggleSet::TrackingToggleSet() : ToggleSet() {

    for (trackedControl thisControl : {TKIASR, TKCRSR, TKHDGR, TKVSR, TKALTR, TKHDGB, TKNAVB, TKAPRB, TKREVB, TKALTB, TKVSB, TKIASB, TKAPB} ) {
        changeSet.insert(std::make_pair(thisControl, true));
    }
}

TrackingToggleSet::TrackingToggleSet(TogglePrecedence thisDirection) : ToggleSet(thisDirection) {

    for (trackedControl thisControl : {TKIASR, TKCRSR, TKHDGR, TKVSR, TKALTR, TKHDGB, TKNAVB, TKAPRB, TKREVB, TKALTB, TKVSB, TKIASB, TKAPB} ) {
        changeSet.insert(std::make_pair(thisControl, true));
    }
}

TrackingToggleSet::~TrackingToggleSet() {
    resetAll();
}

bool TrackingToggleSet::hasChanged(trackedControl thisControl) {
    return (changeSet[thisControl] || changeFlag);             //  false if thisControl was the last one to resetChangeFlag and there have been no toggle changes since then.  Otherwise = true
}

void TrackingToggleSet::resetChangeFlag(trackedControl thisControl) {
    resetAll();                                 // thisControl is aware the latest changes and doesn't need to see them again.  none of the other rotary's have seen them yet so set their status to changed = true
    changeSet.at(thisControl) = false;          // record that thisControl is aware of the latest change
    changeFlag = false;                         // reset the flag to say the latest changes have been piecked up
}

void TrackingToggleSet::resetAll() {
    for (trackedControl thisControl : {TKIASR, TKCRSR, TKHDGR, TKVSR, TKALTR, TKHDGB, TKNAVB, TKAPRB, TKREVB, TKALTB, TKVSB, TKIASB, TKAPB} ) {
        changeSet.at(thisControl) = true;
    }
}


