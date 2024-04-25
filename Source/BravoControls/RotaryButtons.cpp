
//
//  RotaryButtons.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 21/03/2023.
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


#include "RotaryButtons.hpp"
#include "Button.hpp"
#include <tuple>

rotaryButtonLabel activeRotary = RCHDG;

XPTwinCommands* activeCommands = NULL;

int rDebouncePeriod = 70;  //mseconds


/***************************************************************
 *
 *  Debounce control for honeycomb bravo
 *
 *  Sets the time (in milliseconds) to be used by button and switch commands to filter
 *  out mechanical bounce which can appear as multiple button presses for one user press
 *
 *  Provides for a 'high' and 'low' value primarilty for use with the incr and decr rotary
 *  controls.  Useful for for features such as altitude, heading, speed etc where you often
 *  want the rotary to quickly move along the range of values.  A low debounce threshold
 *  will let bounces through, giving the impression the value (altitude etc) is moving quickly.
 *  The down side is when you need to select a specific value the bounce effect makes the
 *  altitude etc skip over valiues and it can take multiuple attempts ot make it land on a specific
 *  value.  Having two values creates the opportunity to implement a 'fast' but inaccurate
 *  rotary feature and a 'slow' but accurate feature.  Can be combined with a rocker switch
 *  to toggle between 'fast' and 'slow' modes.
 *
 *  valid range is 0 (highest speed, lowest precision) to 300 (lowest speed, highest precision)
 *
 *  There is no Command handler for this class.
 *
 *********************************************************************************************/


DebounceControls::DebounceControls(int fastLevel, int slowLevel) {
    setRange(fastLevel, slowLevel);
    active = true;
}

DebounceControls::DebounceControls() {
    setRange(rangeMinimum, rangeMaximum);
    active = false;
}

bool DebounceControls::isActive() {
    return active;
}

void DebounceControls::activate() {
    active = true;
    
}

void DebounceControls::deActivate() {
    active = false;
}

void DebounceControls::setRange(int fastLevel, int slowLevel) {

    if (validDebounce(fastLevel)) fastSpeed = fastLevel; else fastSpeed = rangeMinimum;
    if (validDebounce(slowLevel)) slowSpeed = slowLevel; else slowSpeed = rangeMaximum;
    active = true;
}

void DebounceControls::alwaysSlow() {
    slowSpeed = rangeMaximum;
    fastSpeed = slowSpeed;
    active = true;
}

void DebounceControls::alwaysFast() {
    fastSpeed = rangeMinimum;
    slowSpeed = fastSpeed;
    active = true;
}

void DebounceControls::alwaysSplit() {
    fastSpeed = rangeMinimum;
    slowSpeed = rangeMaximum;
    active = true;
}

int DebounceControls::fastValue() {
    return fastSpeed;
}

int DebounceControls::slowValue() {
    return slowSpeed;
}

DebounceControls::~DebounceControls(){
}

bool DebounceControls::validDebounce(int level) {
    return ((level>=rangeMinimum) && (level<=rangeMaximum));
}


RotaryButton::RotaryButton(const char *userRef, const char *userDesc, rotaryButtonLabel rotaryToAssociate) : userReference(userRef), userDescription(userDesc), option(rotaryToAssociate) {
    _customCommands = new CommandSet();
    rStartAt = std::chrono::steady_clock::now();
}

void RotaryButton::setCommands(XPTwinCommands* newCommands){
    _defaultCommands = newCommands;
    xplane -> createCommand(userReference.c_str(), userDescription.c_str(), [this] (CommandState s) { rotaryHandler(); });
}

void RotaryButton::addCustomCommands(XPTwinCommands* newCommands, toggleLabel newToggle) {
    _customCommands -> addCommands(newCommands, newToggle);
    _customised = true;
}

XPTwinCommands* RotaryButton::defaultCommands() {
    return _defaultCommands;
}

bool RotaryButton::customised() {
    return (_customised);
}

CommandSet* RotaryButton::customCommands() {
    return _customCommands;
}

void RotaryButton::rotaryHandler() {
    
    auto rDuration = std::chrono::steady_clock::now() - rStartAt;
    
    if (std::chrono::duration_cast<std::chrono::milliseconds>(rDuration).count() > buttonDebounce)   // debounce the switch

        {  activeRotary = option;
        }
    rStartAt = std::chrono::steady_clock::now();
}

RotaryButton::~RotaryButton() {
    delete _customCommands;
}


/***************************************************************
 *
 *  IAS Rotary
 *
 *********************************************************************************************/

IAS_Rotary::IAS_Rotary(const char * simCommandUp, const char * simCommandDown) : RotaryButton("Honeycomb/Bravo/Rotary/IAS", "Rotary Selector IAS", RCIAS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown));
}

IAS_Rotary::IAS_Rotary(const char * simCommandUp, const char * simCommandDown, int repeatSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/IAS", "Rotary Selector IAS", RCIAS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, repeatSpeed));
}

IAS_Rotary::IAS_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/IAS", "Rotary Selector IAS", RCIAS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

IAS_Rotary::IAS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/IAS", "Rotary Selector IAS", RCIAS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

IAS_Rotary::IAS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/IAS", "Rotary Selector IAS", RCIAS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

IAS_Rotary::IAS_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/IAS", "Rotary Selector IAS", RCIAS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, repeatSpeed));
}

IAS_Rotary::~IAS_Rotary() {
}

/***************************************************************
 *
 *  CRS Rotary
 *
 *********************************************************************************************/

CRS_Rotary::CRS_Rotary(const char * simCommandUp, const char * simCommandDown) : RotaryButton("Honeycomb/Bravo/Rotary/CRS", "Rotary Selector CRS", RCCRS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown));
 }

CRS_Rotary::CRS_Rotary(const char * simCommandUp, const char * simCommandDown, int speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/CRS", "Rotary Selector CRS", RCCRS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

CRS_Rotary::CRS_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/CRS", "Rotary Selector CRS", RCCRS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

CRS_Rotary::CRS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/CRS", "Rotary Selector CRS", RCCRS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

CRS_Rotary::CRS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/CRS", "Rotary Selector CRS", RCCRS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

CRS_Rotary::CRS_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/CRS", "Rotary Selector CRS", RCCRS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

CRS_Rotary::~CRS_Rotary() {
}

/***************************************************************
 *
 *  HDG Rotary
 *
 *********************************************************************************************/

HDG_Rotary::HDG_Rotary(const char * simCommandUp, const char * simCommandDown) : RotaryButton("Honeycomb/Bravo/Rotary/HDG", "Rotary Selector HDG", RCHDG) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown));
}

HDG_Rotary::HDG_Rotary(const char * simCommandUp, const char * simCommandDown, int speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/HDG", "Rotary Selector HDG", RCHDG)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

HDG_Rotary::HDG_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeeed, int highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/HDG", "Rotary Selector HDG", RCHDG)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeeed, highSpeed));
}

HDG_Rotary::HDG_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/HDG", "Rotary Selector HDG", RCHDG)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

HDG_Rotary::HDG_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeeed, commandSpeed highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/HDG", "Rotary Selector HDG", RCHDG)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeeed, highSpeed));
}

HDG_Rotary::HDG_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/HDG", "Rotary Selector HDG", RCHDG)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

HDG_Rotary::~HDG_Rotary() {
}

/***************************************************************
 *
 *  VS Rotary
 *
 *********************************************************************************************/

VS_Rotary::VS_Rotary(const char * simCommandUp, const char * simCommandDown) : RotaryButton("Honeycomb/Bravo/Rotary/VS", "Rotary Selector VS", RCVS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown));
}

VS_Rotary::VS_Rotary(const char * simCommandUp, const char * simCommandDown, int speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/VS", "Rotary Selector VS", RCVS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

VS_Rotary::VS_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/VS", "Rotary Selector VS", RCVS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

VS_Rotary::VS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/VS", "Rotary Selector VS", RCVS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

VS_Rotary::VS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/VS", "Rotary Selector VS", RCVS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

VS_Rotary::VS_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/VS", "Rotary Selector VS", RCVS) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

VS_Rotary::~VS_Rotary() {
}

/***************************************************************
 *
 *  ALT Rotary
 *
 *********************************************************************************************/

ALT_Rotary::ALT_Rotary(const char * simCommandUp, const char * simCommandDown) : RotaryButton("Honeycomb/Bravo/Rotary/ALT", "Rotary Selector ALT", RCALT) {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown));
}

ALT_Rotary::ALT_Rotary(const char * simCommandUp, const char * simCommandDown, int speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/ALT", "Rotary Selector ALT", RCALT)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

ALT_Rotary::ALT_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/ALT", "Rotary Selector ALT", RCALT)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

ALT_Rotary::ALT_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/ALT", "Rotary Selector ALT", RCALT)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

ALT_Rotary::ALT_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed) : RotaryButton("Honeycomb/Bravo/Rotary/ALT", "Rotary Selector ALT", RCALT)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, lowSpeed, highSpeed));
}

ALT_Rotary::ALT_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed speedPreference) : RotaryButton("Honeycomb/Bravo/Rotary/ALT", "Rotary Selector ALT", RCALT)  {
    this -> setCommands(new XPTwinCommands(simCommandUp, simCommandDown, speedPreference));
}

ALT_Rotary::~ALT_Rotary() {
}


/***************************************************************
 *
 *  various utilies for managing the selecton of the right command based on which
 *  customised funtion is selected and which toggles are active and/or have changed
 *  since the  last pass through
 *
 *********************************************************************************************/


std::tuple<XPTwinCommands*, int> selectCommands (RotaryButton* rotary, ToggleSet* toggles)

{   XPTwinCommands* requiredCommands;
    int debouncePeriod;

    toggles -> SetTogglePrecedence(LeftToRight);
    auto [active, activeToggle] = toggles -> activeToggle(rotary->customCommands());

    if (active)
        requiredCommands = rotary -> customCommands() -> getCommands(activeToggle -> toggleID());
    else
        requiredCommands = rotary -> defaultCommands();
        
    if (requiredCommands -> command1() -> speed() -> differentialSpeed()) {
        if (toggles -> getToggle(TG7) -> toggleIsOn())
            debouncePeriod = requiredCommands -> command1() -> speed() -> slowSpeed();
        else debouncePeriod = requiredCommands -> command1() -> speed() -> fastSpeed();
    } else debouncePeriod = requiredCommands -> command1() -> speed() -> defaultSpeed();
    return {requiredCommands, debouncePeriod};
}


void  refetchCommandsIfRequired(trackedControl thisControl,  RotaryButton* rotary, TrackingToggleSet* toggles) {
    
    if (toggles -> hasChanged(thisControl)) {
        auto [requiredCommands, debouncePeriod]  = selectCommands(rotary, toggles);
        activeCommands = requiredCommands;
        rDebouncePeriod = debouncePeriod;
        toggles ->resetChangeFlag(thisControl);
    }
}


/***************************************************************
 *
 *  Rotary Increment
 *
 *********************************************************************************************/


INC_Rotary::INC_Rotary(IAS_Rotary *rIAS, CRS_Rotary *rCRS,  HDG_Rotary *rHDG, VS_Rotary *rVS, ALT_Rotary *rALT, TrackingToggleSet* bravoToggles) : sIAS(rIAS), sCRS(rCRS), sHDG(rHDG), sVS(rVS), sALT(rALT), masterToggles(bravoToggles) {
 
    XPHandlerRef = xplane -> createCommandAndTellMe("Honeycomb/Bravo/Rotary/INCR", "Rotary Selector Increment", [this] (CommandState s) { commandHandler(); });

    activeRotary = controls -> rotaryLabel();
    
    rStartAt = std::chrono::steady_clock::now();
}
   
void INC_Rotary::commandHandler() {
     
    switch (activeRotary) {
        case RCIAS:
            refetchCommandsIfRequired(TKIASR, sIAS, masterToggles);
            break;
            
        case RCCRS:
            refetchCommandsIfRequired(TKCRSR, sCRS, masterToggles);
            break;

        case RCHDG:
            refetchCommandsIfRequired(TKHDGR, sHDG, masterToggles);
            break;
                            
        case RCVS:
            refetchCommandsIfRequired(TKVSR, sVS, masterToggles);
            break;

        case RCALT:
            refetchCommandsIfRequired(TKALTR, sALT, masterToggles);
            break;
    }
    
    auto rDuration = std::chrono::steady_clock::now() - rStartAt;
    
    if (std::chrono::duration_cast<std::chrono::milliseconds>(rDuration).count() > rDebouncePeriod)   // debounce the switch
    {   if (activeCommands != NULL) {
            XPLMCommandOnce(activeCommands -> command1() -> commandRef());
        
            XPCommand* companionTracker = activeCommands -> command1() -> companionCommand();       // now check for companion commands
        
            while (companionTracker != NULL)                                                        // execute the companion tree if it exists
            {   XPLMCommandOnce(companionTracker -> commandRef());
                companionTracker = companionTracker -> companionCommand();
            }
        }
        rStartAt = std::chrono::steady_clock::now();
    }
}


INC_Rotary::~INC_Rotary() {
    xplane -> destroyCommand(XPHandlerRef);
    delete sIAS;
    delete sCRS;
    delete sHDG;
    delete sVS;
    delete sALT;
}


/***************************************************************
 *
 *  Rotary Decrement
 *
 *********************************************************************************************/


DEC_Rotary::DEC_Rotary(IAS_Rotary *rIAS,CRS_Rotary *rCRS,  HDG_Rotary *rHDG, VS_Rotary *rVS, ALT_Rotary *rALT, TrackingToggleSet* bravoToggles) : sIAS(rIAS), sCRS(rCRS), sHDG(rHDG), sVS(rVS), sALT(rALT), masterToggles(bravoToggles) {
 
    XPHandlerRef = xplane -> createCommandAndTellMe("Honeycomb/Bravo/Rotary/DECR", "Rotary Selector Decrement", [this] (CommandState s) { commandHandler(); });
    rStartAt = std::chrono::steady_clock::now();
}



void DEC_Rotary::commandHandler() {
  
    switch (activeRotary) {
            
        case RCIAS:
            refetchCommandsIfRequired(TKIASR, sIAS, masterToggles);
            break;
            
        case RCCRS:
            refetchCommandsIfRequired(TKCRSR, sCRS, masterToggles);
            break;
            
        case RCHDG:
            refetchCommandsIfRequired(TKHDGR, sHDG, masterToggles);
            break;
            
        case RCVS:
            refetchCommandsIfRequired(TKVSR, sVS, masterToggles);
            break;
            
        case RCALT:
            refetchCommandsIfRequired(TKALTR, sALT, masterToggles);
            break;
    }
    
    auto rDuration = std::chrono::steady_clock::now() - rStartAt;
    
    if (std::chrono::duration_cast<std::chrono::milliseconds>(rDuration).count() > rDebouncePeriod)   // debounce the switch

    {   if (activeCommands != NULL ) {
            XPLMCommandOnce(activeCommands -> command2() -> commandRef());

        XPCommand* companionTracker = activeCommands -> command2() -> companionCommand();       // now check for companion commands
        
        while (companionTracker != NULL)                                                        // execute the companion tree if it exists
        {   XPLMCommandOnce(companionTracker -> commandRef());
            companionTracker = companionTracker -> companionCommand();
            }
        }
        rStartAt = std::chrono::steady_clock::now();
    }
}


DEC_Rotary::~DEC_Rotary() {
    
    xplane -> destroyCommand(XPHandlerRef);
    delete sIAS;
    delete sCRS;
    delete sHDG;
    delete sVS;
    delete sALT;
}


IncrDecrRotary::IncrDecrRotary(IAS_Rotary *rIAS,CRS_Rotary *rCRS,  HDG_Rotary *rHDG, VS_Rotary *rVS, ALT_Rotary *rALT, TrackingToggleSet* bravoToggles) {
    rINC = new INC_Rotary(rIAS, rCRS, rHDG, rVS, rALT, bravoToggles);
    rDEC = new DEC_Rotary(rIAS, rCRS, rHDG, rVS, rALT, bravoToggles);
}

IncrDecrRotary::~IncrDecrRotary() {
    delete rINC;
    delete rDEC;
    delete activeCommands;
}


