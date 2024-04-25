//
//  BravoProfile.cpp
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


#include "BravoProfile.hpp"


BravoProfile::BravoProfile() {
    newBlankControls();
}

BravoProfile::~BravoProfile() {
    resetEverything();
}

void BravoProfile::AutopilotButton(APButtonLabel thisAPButton, const char *commandName) {
    
    switch (thisAPButton) {
        case APHDG: { if (bHDG != NULL) delete bHDG; bHDG = new HDG_Button(commandName); break; }
        case APNAV: { if (bNAV != NULL) delete bNAV; bNAV = new NAV_Button(commandName); break; }
        case APAPR: { if (bAPR != NULL) delete bAPR; bAPR = new APR_Button(commandName); break; }
        case APREV: { if (bREV != NULL) delete bREV; bREV = new REV_Button(commandName); break; }
        case APALT: { if (bALT != NULL) delete bALT; bALT = new ALT_Button(commandName); break; }
        case APVS:  { if (bVS  != NULL) delete bVS;  bVS  = new VS_Button(commandName);  break; }
        case APIAS: { if (bIAS != NULL) delete bIAS; bIAS = new IAS_Button(commandName); break; }
        case APAP:  { if (bAP  != NULL) delete bAP;  bAP  = new AP_Button(commandName);  break; }
        default: break;
    }
}

void BravoProfile::addCustomCommand(APButtonLabel thisAPButton, toggleLabel thisToggle, const char *commandName) {
   
    if (masterToggles == NULL) masterToggles = new TrackingToggleSet(RightToLeft);

    switch (thisAPButton) {
        case APHDG: { if (bHDG != NULL) bHDG -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        case APNAV: { if (bNAV != NULL) bNAV -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        case APAPR: { if (bAPR != NULL) bAPR -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        case APREV: { if (bREV != NULL) bREV -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        case APALT: { if (bALT != NULL) bALT -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        case APVS:  { if (bVS  != NULL) bVS  -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        case APIAS: { if (bIAS != NULL) bIAS -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        case APAP:  { if (bAP  != NULL) bAP  -> addCustomCommand(new XPCommand(commandName), thisToggle, masterToggles); break; }
        default: break;
    }
}

void BravoProfile::addCompanionCommand(APButtonLabel thisAPButton, const char *commandName) {

    switch (thisAPButton) {
        case APHDG: { if (bHDG == NULL) break; if (bHDG -> defaultCommand() == NULL) break; bHDG -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APNAV: { if (bNAV == NULL) break; if (bNAV -> defaultCommand() == NULL) break; bNAV -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APAPR: { if (bAPR == NULL) break; if (bAPR -> defaultCommand() == NULL) break; bAPR -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APREV: { if (bREV == NULL) break; if (bREV -> defaultCommand() == NULL) break; bREV -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APALT: { if (bALT == NULL) break; if (bALT -> defaultCommand() == NULL) break; bALT -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APVS:  { if (bVS  == NULL) break; if (bVS  -> defaultCommand() == NULL) break; bVS  -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APIAS: { if (bIAS == NULL) break; if (bIAS -> defaultCommand() == NULL) break; bIAS -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APAP:  { if (bAP  == NULL) break; if (bAP  -> defaultCommand() == NULL) break; bAP  -> defaultCommand() -> addCompanionCommand(new XPCommand(commandName)); break; }
        default: break;
    }
}

void BravoProfile::addCompanionCommand(APButtonLabel thisAPButton, toggleLabel thisToggle, const char *commandName) {

    switch (thisAPButton) {
        case APHDG: {   if (bHDG == NULL) break;
                        if (bHDG -> customCommands() == NULL) break;
                        if (bHDG -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bHDG -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APNAV: {   if (bNAV == NULL) break;
                        if (bNAV -> customCommands() == NULL) break;
                        if (bNAV -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bNAV -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APAPR: {   if (bAPR == NULL) break;
                        if (bAPR -> customCommands() == NULL) break;
                        if (bAPR -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bAPR -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APREV: {   if (bREV == NULL) break;
                        if (bREV -> customCommands() == NULL) break;
                        if (bREV -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bREV -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APALT: {   if (bALT == NULL) break;
                        if (bALT -> customCommands() == NULL) break;
                        if (bALT -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bALT -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APVS:  {   if (bVS  == NULL) break;
                        if (bVS  -> customCommands() == NULL) break;
                        if (bVS  -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bVS  -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APIAS: {   if (bIAS == NULL) break;
                        if (bIAS -> customCommands() == NULL) break;
                        if (bIAS -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bIAS -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        case APAP:  {   if (bAP  == NULL) break;
                        if (bAP  -> customCommands() == NULL) break;
                        if (bAP  -> customCommands() -> getCommand(thisToggle) == NULL) break;
                        bAP  -> customCommands() -> getCommand(thisToggle) -> addCompanionCommand(new XPCommand(commandName)); break; }
        default: break;
    }
}

void BravoProfile::RotaryControl(rotaryButtonLabel thisRotaryButton, const char *simCommandUp, const char *simCommandDown) {

    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS != NULL) delete rIAS; rIAS = new IAS_Rotary(simCommandUp, simCommandDown); break; }
        case RCCRS: { if (rCRS != NULL) delete rCRS; rCRS = new CRS_Rotary(simCommandUp, simCommandDown); break; }
        case RCHDG: { if (rHDG != NULL) delete rHDG; rHDG = new HDG_Rotary(simCommandUp, simCommandDown); break; }
        case RCVS:  { if (rVS  != NULL) delete rVS;  rVS  = new VS_Rotary(simCommandUp,  simCommandDown); break; }
        case RCALT: { if (rALT != NULL) delete rALT; rALT = new ALT_Rotary(simCommandUp, simCommandDown); break; }
        default: break;
    }
}

void BravoProfile::RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, int repeatSpeed) {

    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS != NULL) delete rIAS; rIAS = new IAS_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        case RCCRS: { if (rCRS != NULL) delete rCRS; rCRS = new CRS_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        case RCHDG: { if (rHDG != NULL) delete rHDG; rHDG = new HDG_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        case RCVS:  { if (rVS  != NULL) delete rVS;  rVS  = new VS_Rotary(simCommandUp,  simCommandDown, repeatSpeed); break; }
        case RCALT: { if (rALT != NULL) delete rALT; rALT = new ALT_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        default: break;
    }
}

void BravoProfile::RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed) {

    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS != NULL) delete rIAS; rIAS = new IAS_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        case RCCRS: { if (rCRS != NULL) delete rCRS; rCRS = new CRS_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        case RCHDG: { if (rHDG != NULL) delete rHDG; rHDG = new HDG_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        case RCVS:  { if (rVS  != NULL) delete rVS;  rVS  = new VS_Rotary(simCommandUp,  simCommandDown, lowSpeed, highSpeed); break; }
        case RCALT: { if (rALT != NULL) delete rALT; rALT = new ALT_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        default: break;
    }
}

void BravoProfile::RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference) {
    
    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS != NULL) delete rIAS; rIAS = new IAS_Rotary(simCommandUp, simCommandDown, speedPreference); break; }
        case RCCRS: { if (rCRS != NULL) delete rCRS; rCRS = new CRS_Rotary(simCommandUp, simCommandDown, speedPreference); break; }
        case RCHDG: { if (rHDG != NULL) delete rHDG; rHDG = new HDG_Rotary(simCommandUp, simCommandDown, speedPreference); break; }
        case RCVS:  { if (rVS  != NULL) delete rVS;  rVS  = new VS_Rotary(simCommandUp,  simCommandDown, speedPreference); break; }
        case RCALT: { if (rALT != NULL) delete rALT; rALT = new ALT_Rotary(simCommandUp, simCommandDown, speedPreference); break; }
        default: break;
    }
}

void BravoProfile::RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed) {

    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS != NULL) delete rIAS; rIAS = new IAS_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        case RCCRS: { if (rCRS != NULL) delete rCRS; rCRS = new CRS_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        case RCHDG: { if (rHDG != NULL) delete rHDG; rHDG = new HDG_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        case RCVS:  { if (rVS  != NULL) delete rVS;  rVS  = new VS_Rotary(simCommandUp,  simCommandDown, lowSpeed, highSpeed); break; }
        case RCALT: { if (rALT != NULL) delete rALT; rALT = new ALT_Rotary(simCommandUp, simCommandDown, lowSpeed, highSpeed); break; }
        default: break;
    }
}

void BravoProfile::RotaryControl(rotaryButtonLabel thisRotaryButton, const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed) {

    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS != NULL) delete rIAS; rIAS = new IAS_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        case RCCRS: { if (rCRS != NULL) delete rCRS; rCRS = new CRS_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        case RCHDG: { if (rHDG != NULL) delete rHDG; rHDG = new HDG_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        case RCVS:  { if (rVS  != NULL) delete rVS;  rVS  = new VS_Rotary(simCommandUp,  simCommandDown, repeatSpeed); break; }
        case RCALT: { if (rALT != NULL) delete rALT; rALT = new ALT_Rotary(simCommandUp, simCommandDown, repeatSpeed); break; }
        default: break;
    }
}

void BravoProfile::addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown) {

    if (masterToggles == NULL) masterToggles = new TrackingToggleSet(LeftToRight);
    
    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS == NULL) break; rIAS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown), thisToggle); break; }
        case RCCRS: { if (rCRS == NULL) break; rCRS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown), thisToggle); break; }
        case RCHDG: { if (rHDG == NULL) break; rHDG -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown), thisToggle); break; }
        case RCVS:  { if (rVS  == NULL) break; rVS  -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown), thisToggle); break; }
        case RCALT: { if (rALT == NULL) break; rALT -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown), thisToggle); break; }
        default: break;
    }
}

void BravoProfile::addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, int repeatSpeed) {

    if (masterToggles == NULL) masterToggles = new TrackingToggleSet(LeftToRight);
    
    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS == NULL) break; rIAS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCCRS: { if (rCRS == NULL) break; rCRS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCHDG: { if (rHDG == NULL) break; rHDG -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCVS:  { if (rVS  == NULL) break; rVS  -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCALT: { if (rALT == NULL) break; rALT -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        default: break;
    }
}

void BravoProfile::addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, int lowSpeed, int highSpeed) {
    
    if (masterToggles == NULL) masterToggles = new TrackingToggleSet(LeftToRight);
    
    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS == NULL) break; rIAS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCCRS: { if (rCRS == NULL) break; rCRS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCHDG: { if (rHDG == NULL) break; rHDG -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCVS:  { if (rVS  == NULL) break; rVS  -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCALT: { if (rALT == NULL) break; rALT -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        default: break;
    }
}

void BravoProfile::addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, commandSpeed speedPreference) {

    if (masterToggles == NULL) masterToggles = new TrackingToggleSet(LeftToRight);
        
    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS == NULL) break; rIAS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, speedPreference), thisToggle); break; }
        case RCCRS: { if (rCRS == NULL) break; rCRS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, speedPreference), thisToggle); break; }
        case RCHDG: { if (rHDG == NULL) break; rHDG -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, speedPreference), thisToggle); break; }
        case RCVS:  { if (rVS  == NULL) break; rVS  -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, speedPreference), thisToggle); break; }
        case RCALT: { if (rALT == NULL) break; rALT -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, speedPreference), thisToggle); break; }
        default: break;
    }
}

void BravoProfile::addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed) {

    if (masterToggles == NULL) masterToggles = new TrackingToggleSet(LeftToRight);
    
    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS == NULL) break; rIAS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCCRS: { if (rCRS == NULL) break; rCRS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCHDG: { if (rHDG == NULL) break; rHDG -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCVS:  { if (rVS  == NULL) break; rVS  -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        case RCALT: { if (rALT == NULL) break; rALT -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, lowSpeed, highSpeed), thisToggle); break; }
        default: break;
    }
}

void BravoProfile::addCustomCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown, XPCommandSpeed repeatSpeed) {

    if (masterToggles == NULL) masterToggles = new TrackingToggleSet(LeftToRight);
    
    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS == NULL) break; rIAS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCCRS: { if (rCRS == NULL) break; rCRS -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCHDG: { if (rHDG == NULL) break; rHDG -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCVS:  { if (rVS  == NULL) break; rVS  -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        case RCALT: { if (rALT == NULL) break; rALT -> addCustomCommands(new XPTwinCommands(simCommandUP, simCommandDown, repeatSpeed), thisToggle); break; }
        default: break;
    }
}

void BravoProfile::addCompanionCommand(rotaryButtonLabel thisRotaryButton, const char *simCommandUP,  const char *simCommandDown) {

    switch (thisRotaryButton) {
        case RCIAS: { if (rIAS == NULL) break; if (rIAS -> defaultCommands() == NULL) break; rIAS -> defaultCommands() -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCCRS: { if (rCRS == NULL) break; if (rCRS -> defaultCommands() == NULL) break; rCRS -> defaultCommands() -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCHDG: { if (rHDG == NULL) break; if (rHDG -> defaultCommands() == NULL) break; rHDG -> defaultCommands() -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCVS:  { if (rVS  == NULL) break; if (rVS -> defaultCommands()  == NULL) break; rVS  -> defaultCommands() -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCALT: { if (rALT == NULL) break; if (rALT -> defaultCommands() == NULL) break; rALT -> defaultCommands() -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        default: break;
    }
}

void BravoProfile::addCompanionCommand(rotaryButtonLabel thisRotaryButton, toggleLabel thisToggle, const char *simCommandUP,  const char *simCommandDown) {

    switch (thisRotaryButton) {
        case RCIAS: {   if (rIAS == NULL) break;
                        if (rIAS -> customCommands() == NULL) break;
                        if (rIAS -> customCommands() -> getCommands(thisToggle) == NULL) break;
                        rIAS -> customCommands() -> getCommands(thisToggle) -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCCRS: {   if (rCRS == NULL) break;
                        if (rCRS -> customCommands() == NULL) break;
                        if (rCRS -> customCommands() -> getCommands(thisToggle) == NULL) break;
                        rCRS -> customCommands() -> getCommands(thisToggle) -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCHDG: {   if (rHDG == NULL) break;
                        if (rHDG -> customCommands() == NULL) break;
                        if (rHDG -> customCommands() -> getCommands(thisToggle) == NULL) break;
                        rHDG -> customCommands() -> getCommands(thisToggle) -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCVS:  {   if (rVS == NULL) break;
                        if (rVS -> customCommands() == NULL) break;
                        if (rVS -> customCommands() -> getCommands(thisToggle) == NULL) break;
                        rVS -> customCommands() -> getCommands(thisToggle) -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        case RCALT: {   if (rALT == NULL) break;
                        if (rALT -> customCommands() == NULL) break;
                        if (rALT -> customCommands() -> getCommands(thisToggle) == NULL) break;
                        rALT -> customCommands() -> getCommands(thisToggle) -> addCompanionCommands(new XPTwinCommands(simCommandUP, simCommandDown)); break; }
        default: break;
    }
}

void BravoProfile::activateIncrDecrRotary() {
    
    if (rIAS == NULL) rIAS = new IAS_Rotary(NULL, NULL);
    if (rCRS == NULL) rCRS = new CRS_Rotary(NULL, NULL);
    if (rHDG == NULL) rHDG = new HDG_Rotary(NULL, NULL);
    if (rVS  == NULL) rVS  = new VS_Rotary(NULL, NULL);
    if (rALT == NULL) rALT = new ALT_Rotary(NULL, NULL);
    if (masterToggles == NULL) masterToggles = new TrackingToggleSet();

    rVAL = new IncrDecrRotary(rIAS, rCRS, rHDG, rVS, rALT, masterToggles);
}


void BravoProfile::addStateTransition(APButtonLabel thisButtonPress, int fromState, int toState) {
    
    if (APstateMachine == NULL) APstateMachine = new StateMachine();          // first call to addStateTransition?
    
    if (states[fromState] == NULL) {                                          // first entry for a new state
        states[fromState] = new LightState(fromState);
        
        APstateMachine -> addState(states[fromState]);                        // add new state to the state machine;
    }
    states[fromState] -> addStateTransition(thisButtonPress, toState);        // add the transition
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7, APButtonLabel light8) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1, light2, light3, light4, light5, light6, light7, light8);
    }
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1, light2, light3, light4, light5, light6, light7);
    }
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1, light2, light3, light4, light5, light6);
    }
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1, light2, light3, light4, light5);
    }
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1, light2, light3, light4);
    }
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1, light2, light3);
    }
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1, APButtonLabel light2) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1, light2);
    }
}

void BravoProfile::addStateLightsOn(int thisState, APButtonLabel light1) {
    
    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOn(light1);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7, APButtonLabel light8) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1, light2, light3, light4, light5, light6, light7, light8);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6, APButtonLabel light7) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1, light2, light3, light4, light5, light6, light7);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5, APButtonLabel light6) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1, light2, light3, light4, light5, light6);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4, APButtonLabel light5) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1, light2, light3, light4, light5);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3, APButtonLabel light4) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1, light2, light3, light4);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2, APButtonLabel light3) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1, light2, light3);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1, APButtonLabel light2) {

    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1, light2);
    }
}

void BravoProfile::addStateLightsOff(int thisState, APButtonLabel light1) {
    if (states[thisState] != NULL) {
        states[thisState] -> theseLightsToTurnOff(light1);
    }
}

void BravoProfile::activateStateMachine() {

    if (bHDG != NULL) bHDG -> useStateMachine(APstateMachine);
    if (bNAV != NULL) bNAV -> useStateMachine(APstateMachine);
    if (bAPR != NULL) bAPR -> useStateMachine(APstateMachine);
    if (bREV != NULL) bREV -> useStateMachine(APstateMachine);
    if (bALT != NULL) bALT -> useStateMachine(APstateMachine);
    if (bVS  != NULL) bVS  -> useStateMachine(APstateMachine);
    if (bIAS != NULL) bIAS -> useStateMachine(APstateMachine);
    if (bAP  != NULL) bAP  -> useStateMachine(APstateMachine);
}



void BravoProfile::newBlankControls() {
    
    toggle1 = new Toggle(TG1);
    toggle2 = new Toggle(TG2);
    toggle3 = new Toggle(TG3);
    toggle4 = new Toggle(TG4);
    toggle5 = new Toggle(TG5);
    toggle6 = new Toggle(TG6);
    toggle7 = new Toggle(TG7);
    
    masterToggles = new TrackingToggleSet();
    masterToggles -> addToggle(toggle1);
    masterToggles -> addToggle(toggle2);
    masterToggles -> addToggle(toggle3);
    masterToggles -> addToggle(toggle4);
    masterToggles -> addToggle(toggle5);
    masterToggles -> addToggle(toggle6);
    masterToggles -> addToggle(toggle7);
    
    resetStateArray();
}

void BravoProfile::resetEverything() {
    
    if (bHDG  != NULL) delete bHDG;
    if (bNAV  != NULL) delete bNAV;
    if (bAPR  != NULL) delete bAPR;
    if (bREV  != NULL) delete bREV;
    if (bALT  != NULL) delete bALT;
    if (bVS   != NULL) delete bVS;
    if (bIAS  != NULL) delete bIAS;
    if (bAP   != NULL) delete bAP;

    if(toggle1 != NULL) delete toggle1;
    if(toggle2 != NULL) delete toggle2;
    if(toggle3 != NULL) delete toggle3;
    if(toggle4 != NULL) delete toggle4;
    if(toggle5 != NULL) delete toggle5;
    if(toggle6 != NULL) delete toggle6;
    if(toggle7 != NULL) delete toggle7;

    if (rIAS != NULL) delete rIAS;
    if (rCRS != NULL) delete rCRS;
    if (rHDG != NULL) delete rHDG;
    if (rVS  != NULL) delete rVS;
    if (rALT != NULL) delete rALT;
    if (rVAL != NULL) delete rVAL;
    
    if (APstateMachine != NULL) delete APstateMachine;
    
    resetStateArray();
    
    if(masterToggles != NULL) delete masterToggles;
    
    xplane -> destroyCommands();
}

void BravoProfile::resetStateArray() {
    for (int state=0; state<MAX_STATES; state++) {
        if (states[state] != NULL) delete states[state];
        states[state] = NULL;
    }
}
