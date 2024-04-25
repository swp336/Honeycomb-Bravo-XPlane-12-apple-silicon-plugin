//
//  Button.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 08/04/2023.
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

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include <memory>
#include "XPlane.hpp"
#include "XPlaneEnvironment.hpp"
#include "XPCommand.hpp"
#include "Toggle.hpp"
#include "APButtonLabel.hpp"
#include "StateMachine.hpp"

class Button {

public:
    Button(const char *userRef, const char *userDesc);
    Button(const char *userRef, const char *userDesc, APButtonLabel thisAPButton);
    Button(const char *userRef, const char *userDesc, APButtonLabel thisAPButton, TrackingToggleSet* bravoToggles);
    ~Button();
    void setCommand(XPCommand *newXPCommand);
    void setCommand(const char *newCommandName);
    void addCustomCommand(XPCommand* newCommand, toggleLabel newToggle, TrackingToggleSet* bravoToggles);
    XPCommand* defaultCommand();
    bool customised();
    CommandSet* customCommands();
    void useStateMachine(StateMachine* thisStateMachine);

    
protected:
    void buttonHandler();
    void  refetchCommandIfRequired(trackedControl thisControl,  Button* button, TrackingToggleSet* toggles);
    XPCommand* activeCommand = NULL;
    APButtonLabel option;
    std::string userReference;
    std::string userDescription;
    XPLMCommandRef buttonRef     = NULL;
    XPCommand* _defaultCommand   = NULL;
    XPLMCommandRef XPHandlerRef  = NULL;
    CommandSet* _customCommands  = NULL;
    TrackingToggleSet  *masterToggles = NULL;
    bool _customised             = false;
    std::chrono::steady_clock::time_point rStartAt;
    std::chrono::steady_clock::time_point rDuration;
    int buttonDebouncePeriod = 300;  //mseconds
    StateMachine* _stateMachine = NULL;
};

#endif /* Button_hpp */
