//
//  Button.cpp
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

#include "Button.hpp"


extern void  refetchCommandIfRequired(trackedControl thisControl,  Button* button, TrackingToggleSet* toggles);

Button::Button(const char *userRef, const char *userDesc) : userReference(userRef), userDescription(userDesc) {
      
    _customCommands = new CommandSet();
    rStartAt = std::chrono::steady_clock::now();
}

Button::Button(const char *userRef, const char *userDesc, APButtonLabel thisAPButton) : userReference(userRef), userDescription(userDesc), option(thisAPButton) {
      
    _customCommands = new CommandSet();
    rStartAt = std::chrono::steady_clock::now();
}

Button::Button(const char *userRef, const char *userDesc, APButtonLabel thisAPButton, TrackingToggleSet* bravoToggles) : userReference(userRef), userDescription(userDesc), option(thisAPButton), masterToggles(bravoToggles){
      
    _customCommands = new CommandSet();
    rStartAt = std::chrono::steady_clock::now();
}

void Button::setCommand(XPCommand *newXPCommand) {
    
    _defaultCommand = newXPCommand;
    XPHandlerRef = xplane -> createCommandAndTellMe(userReference.c_str(), userDescription.c_str(), [this] (CommandState s) { buttonHandler(); });
}

void Button::setCommand(const char *newCommandName) {
    setCommand(new XPCommand(newCommandName));
}

void Button::addCustomCommand(XPCommand* newCommand, toggleLabel newToggle, TrackingToggleSet* bravoToggles) {
    
    if (masterToggles == NULL) masterToggles = bravoToggles;
    
    _customCommands -> addCommand(newCommand, newToggle);
    _customised = true;
}

XPCommand* Button::defaultCommand() {
    return _defaultCommand;
}

bool Button::customised() {
    return (_customised);
}

CommandSet* Button::customCommands() {
    return _customCommands;
}

void Button::useStateMachine(StateMachine* thisStateMachine) {
    _stateMachine = thisStateMachine;
}

/***************************************************************
 *
 *  various utilies for managing the selecton of the right command based on which
 *  customised funtion is selected and which toggles are active and/or have changed
 *  since the  last pass through
 *
 *********************************************************************************************/


XPCommand* selectCommand (Button* button, ToggleSet* toggles)

{   XPCommand* requiredCommand;

    toggles -> SetTogglePrecedence(RightToLeft);
    auto [active, activeToggle] = toggles -> activeToggle(button->customCommands());

    if (active)
        requiredCommand = button -> customCommands() -> getCommands(activeToggle -> toggleID()) -> command();
    else
        requiredCommand = button -> defaultCommand();
            
    return requiredCommand;
}

void  Button::refetchCommandIfRequired(trackedControl thisControl,  Button* button, TrackingToggleSet* toggles) {
    
    if (toggles -> hasChanged(thisControl)) {
        activeCommand = selectCommand(button, toggles);
        toggles ->resetChangeFlag(thisControl);
    }
}


void Button::buttonHandler() {
    
    auto rDuration = std::chrono::steady_clock::now() - rStartAt;
    
    if (std::chrono::duration_cast<std::chrono::milliseconds>(rDuration).count() > buttonDebouncePeriod)   // debounce the switch
    {
        if (_customised) {
            switch (option) {
                case APHDG: refetchCommandIfRequired(TKHDGB, this, masterToggles); break;
                case APNAV: refetchCommandIfRequired(TKNAVB, this, masterToggles); break;
                case APAPR: refetchCommandIfRequired(TKAPRB, this, masterToggles); break;
                case APREV: refetchCommandIfRequired(TKREVB, this, masterToggles); break;
                case APALT: refetchCommandIfRequired(TKALTB, this, masterToggles); break;
                case APVS:  refetchCommandIfRequired(TKVSB,  this, masterToggles); break;
                case APIAS: refetchCommandIfRequired(TKIASB, this, masterToggles); break;
                case APAP:  refetchCommandIfRequired(TKAPB,  this, masterToggles); break;
            }
        } else activeCommand = _defaultCommand;
        
        if (activeCommand != NULL) {
            XPLMCommandOnce(activeCommand -> commandRef());
            if (_stateMachine != NULL) {
                _stateMachine -> goToNextState(option);
            }

            XPCommand* companionTracker = activeCommand -> companionCommand();                      // now check for companion commands
        
            while (companionTracker != NULL)                                                        // execute the companion tree if it exists
            {   XPLMCommandOnce(companionTracker -> commandRef());
                companionTracker = companionTracker -> companionCommand();
            }

            
        }
        rStartAt = std::chrono::steady_clock::now();
    }
}

Button::~Button() {
    xplane -> destroyCommand(XPHandlerRef);
}

