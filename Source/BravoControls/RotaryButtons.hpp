//
//  RotaryButtons.hpp
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


#ifndef RotaryButtons_hpp
#define RotaryButtons_hpp

#include <chrono>
#include <string>
#include <stdio.h>
#include <map>
#include "XPlane.hpp"
#include "XPlaneEnvironment.hpp"
#include "Toggle.hpp"
#include "RotaryButtonLabel.hpp"



class DebounceControls {
    
public:
    DebounceControls(int fastLevel, int slowLevel);
    DebounceControls();
    bool isActive();
    void activate();
    void deActivate();
    void setRange(int fastLevel, int slowLevel);
    void alwaysSlow();
    void alwaysFast();
    void alwaysSplit();
    int fastValue();
    int slowValue();
    ~DebounceControls();
    
protected:
    int  slowSpeed;
    int  fastSpeed;
    int  rangeMinimum = 0;
    int  rangeMaximum = 300;
    bool active = false;
    bool validDebounce(int level);
};


class RotaryButton {

public:
    RotaryButton(const char* userRef, const char* userDesc, rotaryButtonLabel rotaryToAsssociate);
    void setCommands(XPTwinCommands* newCommands);
    void addCustomCommands(XPTwinCommands* newCommands, toggleLabel newToggle);
    XPTwinCommands* defaultCommands();
    bool customised();
    CommandSet* customCommands();
    ~RotaryButton();

protected:
    void rotaryHandler();
    rotaryButtonLabel option;
    XPTwinCommands* _defaultCommands  = NULL;
    XPLMCommandRef XPHandlerRef       = NULL;
    CommandSet* _customCommands       = NULL;
    int buttonDebounce = 200;   //milliseconds
    bool _customised = false;
    std::string userReference;
    std::string userDescription;
    std::chrono::steady_clock::time_point rStartAt;
    std::chrono::steady_clock::time_point rDuration;
};



class IAS_Rotary : public RotaryButton {
    
public:
    IAS_Rotary(const char * simCommandUp, const char * simCommandDown);
    IAS_Rotary(const char * simCommandUp, const char * simCommandDown, int repeatSpeed);
    IAS_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed);
    IAS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference);
    IAS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed);
    IAS_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed);
    ~IAS_Rotary();
};

class CRS_Rotary : public RotaryButton {

public:
    CRS_Rotary(const char * simCommandUp, const char * simCommandDown);
    CRS_Rotary(const char * simCommandUp, const char * simCommandDown, int repeatSpeed);
    CRS_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed);
    CRS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference);
    CRS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed);
    CRS_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed);
    ~CRS_Rotary();
};

class HDG_Rotary : public RotaryButton {
    
public:
    HDG_Rotary(const char * simCommandUp, const char * simCommandDown);
    HDG_Rotary(const char * simCommandUp, const char * simCommandDown, int repeatSpeed);
    HDG_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed);
    HDG_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference);
    HDG_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed);
    HDG_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed);
    ~HDG_Rotary();
};

class VS_Rotary : public RotaryButton {
    
public:
    VS_Rotary(const char * simCommandUp, const char * simCommandDown);
    VS_Rotary(const char * simCommandUp, const char * simCommandDown, int repeatSpeed);
    VS_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed);
    VS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference);
    VS_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed);
    VS_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed);
    ~VS_Rotary();
};

class ALT_Rotary : public RotaryButton {
    
public:
    ALT_Rotary(const char * simCommandUp, const char * simCommandDown);
    ALT_Rotary(const char * simCommandUp, const char * simCommandDown, int repeatSpeed);
    ALT_Rotary(const char * simCommandUp, const char * simCommandDown, int lowSpeed, int highSpeed);
    ALT_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed speedPreference);
    ALT_Rotary(const char * simCommandUp, const char * simCommandDown, commandSpeed lowSpeed, commandSpeed highSpeed);
    ALT_Rotary(const char * simCommandUp, const char * simCommandDown, XPCommandSpeed repeatSpeed);
    ~ALT_Rotary();
};



class INC_Rotary {
    
private:
    friend class IncrDecrRotary;
    
    INC_Rotary(IAS_Rotary *rIAS,CRS_Rotary *rCRS,  HDG_Rotary *rHDG, VS_Rotary *rVS, ALT_Rotary *rALT, TrackingToggleSet* bravoToggles);
    ~INC_Rotary();
    
    void commandHandler();
    std::chrono::steady_clock::time_point rStartAt;
    std::chrono::steady_clock::time_point rDuration;
    IAS_Rotary *sIAS                 = NULL;
    CRS_Rotary *sCRS                 = NULL;
    HDG_Rotary *sHDG                 = NULL;
    VS_Rotary  *sVS                  = NULL;
    ALT_Rotary *sALT                 = NULL;
    TrackingToggleSet  *masterToggles = NULL;
    XPLMCommandRef XPHandlerRef       = NULL;
};


class DEC_Rotary {

private:
    friend class IncrDecrRotary;
    
    DEC_Rotary(IAS_Rotary *rIAS,CRS_Rotary *rCRS,  HDG_Rotary *rHDG, VS_Rotary *rVS, ALT_Rotary *rALT, TrackingToggleSet* bravoToggles);
    ~DEC_Rotary();
    
    void commandHandler();
    std::chrono::steady_clock::time_point rStartAt;
    std::chrono::steady_clock::time_point rDuration;
    IAS_Rotary *sIAS                 = NULL;
    CRS_Rotary *sCRS                 = NULL;
    HDG_Rotary *sHDG                 = NULL;
    VS_Rotary  *sVS                  = NULL;
    ALT_Rotary *sALT                 = NULL;
    TrackingToggleSet *masterToggles = NULL;
    XPLMCommandRef XPHandlerRef       = NULL;
};

class IncrDecrRotary {
 
public:
    IncrDecrRotary(IAS_Rotary *rIAS,CRS_Rotary *rCRS,  HDG_Rotary *rHDG, VS_Rotary *rVS, ALT_Rotary *rALT, TrackingToggleSet* bravoToggles);
    ~IncrDecrRotary();
    
private:
    INC_Rotary* rINC = NULL;
    DEC_Rotary* rDEC = NULL;
};


#endif /* RotaryButtons_hpp */
