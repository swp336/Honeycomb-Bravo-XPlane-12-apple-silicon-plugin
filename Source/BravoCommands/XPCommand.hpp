//
//  XPCommand.hpp
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


#ifndef XPCommand_hpp
#define XPCommand_hpp

#include <stdio.h>
#include <string>
#include "XPlane.hpp"
#include "SwitchLabel.hpp"
#include "ToggleLabel.hpp"


enum commandSpeed {slowest, slow, medium, fast, fastest};

class XPCommandSpeed {

public:
    XPCommandSpeed(int speed);
    XPCommandSpeed(int slow, int fast);
    XPCommandSpeed(commandSpeed speed);
    XPCommandSpeed(commandSpeed slow, commandSpeed fast);
    void setSpeed(int repeatSpeed);
    void setSpeed(int lowSpeed, int highSpeed);
    void setSpeed(commandSpeed repeatSpeed);
    void setSpeed(commandSpeed lowSpeed, commandSpeed highSpeed);
    void setSpeed(XPCommandSpeed repeatSpeed);
    int defaultSpeed();
    bool differentialSpeed();
    int fastSpeed();
    int slowSpeed();
    
private:
    int _minSpeed = 0;
    int _maxSpeed = 300;
    int _defaultSpeed = 300;
    int _fastSpeed = 0;
    int _slowSpeed = 150;
    bool _differential = false;
};


class XPCommand {

public:
    
    XPCommand();
    ~XPCommand();
    XPCommand(const char * simCommand);
    XPCommand(const char * simCommand, int repeatSpeed);
    XPCommand(const char * simCommand, int lowSpeed, int highSpeed);
    XPCommand(const char * simCommand, commandSpeed repeatSpeed);
    XPCommand(const char * simCommand, commandSpeed lowSpeed, commandSpeed highSpeed);
    XPCommand(const char * simCommand, XPCommandSpeed repeatSpeed);
    void setCommand(const char * simCommand);
    void addCompanionCommand(XPCommand* companion);
    XPCommand* companionCommand();
    void setSpeed(int newSpeed);
    void setSpeed(int lowSpeed, int highSpeed);
    void setSpeed(commandSpeed repeatSpeed);
    void setSpeed(commandSpeed lowSpeed, commandSpeed highSpeed);
    void setSpeed(XPCommandSpeed repeatSpeed);
    bool isActive();
    bool isNull();
    void activate();
    void deActivate();
    std::string commandName();
    XPLMCommandRef commandRef();
    XPCommandSpeed* speed();
    
protected:
    friend class BravoJSON;
    bool commandIsNull = true;
    XPLMCommandRef mySimCommandRef = NULL;
    bool active = false;
    XPCommandSpeed mySpeed;
    std::string myCommandString;
    XPCommand* _companionCommand = NULL;
};

class XPTwinCommands {

public:
    XPTwinCommands();
    ~XPTwinCommands();
    XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2);
    XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, int repeatSpeed);
    XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, int lowSpeed, int highSpeed);
    XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, commandSpeed repeatSpeed);
    XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, commandSpeed lowSpeed, commandSpeed highSpeed);
    XPTwinCommands(XPCommand* newCommand1, XPCommand* newCommand2, XPCommandSpeed repeatSpeed);
    XPTwinCommands(const char * simCommand1, const char * simCommand2);
    XPTwinCommands(const char * simCommand1, const char * simCommand2, int repeatSpeed);
    XPTwinCommands(const char * simCommand1, const char * simCommand2, int lowSpeed, int highSpeed);
    XPTwinCommands(const char * simCommand1, const char * simCommand2, commandSpeed repeatSpeed);
    XPTwinCommands(const char * simCommand1, const char * simCommand2, commandSpeed lowSpeed, commandSpeed highSpeed);
    XPTwinCommands(const char * simCommand1, const char * simCommand2, XPCommandSpeed lowSpeed);
    void addCompanionCommands(XPTwinCommands* companions);
    XPCommand* command1();
    XPCommand* command2();
    XPCommand* command();
    void activate();
    void deActivate();
    bool isActive();
    
protected:
    XPCommand* myCommand1;
    XPCommand* myCommand2;

    bool active = false;
};


class CommandSet {

public:
    CommandSet();
    ~CommandSet();
    void addCommands(XPTwinCommands* newCommands, toggleLabel addToToggle);
    void addCommand(XPCommand* newCommand, toggleLabel addToToggle);
    XPTwinCommands* getCommands(toggleLabel toggleToLookUp);
    XPCommand* getCommand(toggleLabel toggleToLookUp);
    bool isEmpty();

protected:
    std::map<toggleLabel, XPTwinCommands*> commandSwitchSet;
//    std::map<switchLabel, XPTwinCommand*>::iterator cs_it;
};


#endif /* XPCommand_hpp */
