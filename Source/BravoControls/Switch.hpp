//
//  Switch.hpp
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


#ifndef Switch_hpp
#define Switch_hpp

#include "XPCommand.hpp"
#include "XPlane.hpp"
#include "XPlaneEnvironment.hpp"
#include "SwitchLabel.hpp"
#include <string>



class SwitchMap {
public:
    SwitchMap();
    ~SwitchMap();
    std::string switchRef(int switchNumber);
    std::string switchDescr(int switchNumber);
    int switchDeviceNumber(switchLabel switchID);
    int switchLogicalNumber(switchLabel switchID);

private:
    std::map<switchLabel, int> switchMap { {SW1,13}, {SW2,14}, {SW3,15}, { SW4,16},  {SW5,17},  {SW6,18},  {SW7,19},
                                           {SW8,20}, {SW9,21}, {SW10,22}, {SW11,23}, {SW12,24}, {SW13,25}, {SW14,26} };
};


class Switch {
public:
    Switch(switchLabel switchID, switchState defaultState);
    Switch(switchLabel switchID, switchState defaultState, XPCommand* newCommand);
    ~Switch();
    void setCommand(XPCommand *newXPCommand);
    void toggleState();
    void delegateHandler();
    int switchID();
    switchState status();
    std::string userReference();
    std::string userDescription();
    XPCommand* command();

protected:
    void switchOnStatusHandler();
    void switchOffStatusHandler();
    void commandOnHandler();
    void commandOffHandler();
    switchState myState;
    switchState myDefault;
    switchLabel mySwitchID;
    std::string userRef;
    std::string userDesc;
    XPCommand*     myCommand     = NULL;
    XPLMCommandRef switchHandlerRef;
    SwitchMap switchMap;
};

#endif /* Switch_hpp */
