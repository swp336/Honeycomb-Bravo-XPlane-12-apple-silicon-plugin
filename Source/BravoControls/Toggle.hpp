//
//  Toggle.hpp
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


#ifndef Toggle_hpp
#define Toggle_hpp

#include "XPlane.hpp"
#include "XPCommand.hpp"
#include "SwitchLabel.hpp"
#include "ToggleLabel.hpp"
#include "Switch.hpp"
#include "RotaryButtonLabel.hpp"


class ToggleMap {
   
public:
    ToggleMap();
    ~ToggleMap();
    switchLabel upperSwitchID(toggleLabel toggleID);
    switchLabel lowerSwitchID(toggleLabel toggleID);
private:
    std::map<toggleLabel, switchLabel> upperSwitchMap { {TG1,SW1}, {TG2,SW3}, {TG3,SW5}, {TG4,SW7}, {TG5,SW9},  {TG6,SW11}, {TG7,SW13} };
    std::map<toggleLabel, switchLabel> lowerSwitchMap { {TG1,SW2}, {TG2,SW4}, {TG3,SW6}, {TG4,SW8}, {TG5,SW10}, {TG6,SW12}, {TG7,SW14} };
};


class Toggle {
    
public:
    Toggle(toggleLabel toggleID);
    Toggle(toggleLabel toggleID, XPTwinCommands *newCommands);
    Toggle(toggleLabel toggleID, XPCommand* newCommand1, XPCommand* newCommand2);
    Toggle(toggleLabel toggleID, const char* newCommand1, const char* newCommand2);
    void setCommands(XPTwinCommands *newCommands);
    void setCommands(XPCommand* newCommand1, XPCommand* newCommand2);
    void setCommands(const char* newCommand1, const char* newCommand2);
    XPTwinCommands* commands();
    void delegateHandler();
    Switch* onSwitch();
    Switch* offSwitch();
    bool toggleIsOn();
    toggleLabel toggleID();
    ~Toggle();

protected:
    void toggleOnHandler();
    void toggleOffHandler();
    void commandOnHandler();
    void commandOffHandler();
    switchState toggleState;
    XPTwinCommands* myCommands  = NULL;
    Switch* myOnSwitch = NULL;
    Switch* myOffSwitch = NULL;
    XPLMCommandRef onHandlerRef;
    XPLMCommandRef offHandlerRef;
    ToggleMap toggleMap;
    SwitchMap switchMap;
    toggleLabel myToggleID;

private:
    friend class ToggleSet;
    void notifyChanges(bool* notifyHere);
    bool* notifyChange = NULL;
};

enum TogglePrecedence { RightToLeft, LeftToRight };

class ToggleSet {

public:
    ToggleSet();
    ToggleSet(TogglePrecedence precedenceOrder);
    ~ToggleSet();
    void addToggle(Toggle* newToggle);
    Toggle* getToggle(toggleLabel toggleToGet);
    bool isActive();
    Toggle* activeToggle();
    std::tuple<bool, Toggle*> activeToggle(CommandSet* commands);
    bool hasChanged();
    void resetChangeFlag();
    TogglePrecedence precedenceOrder();
    void SetTogglePrecedence(TogglePrecedence thisDirection);

protected:
    std::map<toggleLabel, Toggle*> toggleSet;
    std::map<toggleLabel, Toggle*>::iterator it;
    bool changeFlag = true;
    TogglePrecedence _direction = LeftToRight;
};

enum trackedControl { TKIASR, TKCRSR, TKHDGR, TKVSR, TKALTR, TKHDGB, TKNAVB, TKAPRB, TKREVB, TKALTB, TKVSB, TKIASB, TKAPB }; // TK = Tracked Control, IAS etc is the control being tracked, R = Rotary control, B = Button control

class TrackingToggleSet : public ToggleSet {

public:
    TrackingToggleSet();
    TrackingToggleSet(TogglePrecedence precedenceOrder);
    ~TrackingToggleSet();
    bool hasChanged(trackedControl thisControl);
    void resetChangeFlag(trackedControl thisControl);

private:
     std::map<trackedControl, bool> changeSet;
     void resetAll();
};



#endif /* Toggle_hpp */
