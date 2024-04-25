//
//  BravoProfile.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 12/07/2023.
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


#ifndef BravoProfile_hpp
#define BravoProfile_hpp

#include <stdio.h>
#include <set>
#include <map>
#include "APButtons.hpp"
#include "APButtonLabel.hpp"
#include "RotaryButtons.hpp"
#include "StateMachine.hpp"

class BravoJSON;

class BravoProfile {
  
public:
    BravoProfile();
    ~BravoProfile();
        
    void AutopilotButton(APButtonLabel thisAPButton, const char *commandName);
    void RotaryControl(rotaryButtonLabel thisRotaryButton, const char *simCommandUP,  const char *simCommandDown);
    void RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, int repeatSpeed);
    void RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed);
    void RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference);
    void RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed);
    void RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed);
    void addCustomCommand(APButtonLabel thisAPButton, toggleLabel thisToggle, const char *commandName);
    void addCompanionCommand(APButtonLabel thisAPButton, const char *commandName);
    void addCompanionCommand(APButtonLabel thisAPButton, toggleLabel thisToggle, const char *commandName);
    void addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown);
    void addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, int repeatSpeed);
    void addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, int lowSpeed, int highSpeed);
    void addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, commandSpeed speedPreference);
    void addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed);
    void addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, XPCommandSpeed repeatSpeed);
    void addCompanionCommand(rotaryButtonLabel thisRotaryButton, const char *simCommandUP,  const char *simCommandDown);
    void addCompanionCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown);
    void activateIncrDecrRotary();
    void addStateTransition(APButtonLabel thisButtonPress, int fromState, int toState);
    void addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7, APButtonLabel light8);
    void addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7);
    void addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6);
    void addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5);
    void addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4);
    void addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3);
    void addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2);
    void addStateLightsOn(int thisState, APButtonLabel light1);
    void addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7, APButtonLabel light8);
    void addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7);
    void addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6);
    void addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5);
    void addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4);
    void addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3);
    void addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2);
    void addStateLightsOff(int thisState, APButtonLabel light1);
    void activateStateMachine();

private:
    
    friend class BravoJSON;
    
    void newBlankControls();
    void resetEverything();
    void resetStateArray();
    
    HDG_Button* bHDG = NULL;          // Autopilot buttons
    NAV_Button* bNAV = NULL;
    APR_Button* bAPR = NULL;
    REV_Button* bREV = NULL;
    ALT_Button* bALT = NULL;
    VS_Button*  bVS  = NULL;
    IAS_Button* bIAS = NULL;
    AP_Button*  bAP  = NULL;

    Toggle* toggle1 = NULL;          // Control toggles
    Toggle* toggle2 = NULL;
    Toggle* toggle3 = NULL;
    Toggle* toggle4 = NULL;
    Toggle* toggle5 = NULL;
    Toggle* toggle6 = NULL;
    Toggle* toggle7 = NULL;
  
    IAS_Rotary* rIAS = NULL;         // Rotary controls
    CRS_Rotary* rCRS = NULL;
    HDG_Rotary* rHDG = NULL;
    VS_Rotary*  rVS  = NULL;
    ALT_Rotary* rALT = NULL;

    IncrDecrRotary* rVAL = NULL;        // incr/decr rotary control
    
    TrackingToggleSet* masterToggles = NULL;     // Status tracking for toggle positions
    
    StateMachine* APstateMachine = NULL;         // State machine for managing Autopilot button lights

    LightState*   states[MAX_STATES];
};



#endif /* BravoProfile_hpp */
