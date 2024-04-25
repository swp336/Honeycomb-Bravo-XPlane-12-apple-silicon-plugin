//
//  Buttons.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 20/03/2023.
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


#ifndef Buttons_hpp
#define Buttons_hpp

#include <chrono>
#include <string>
#include <stdio.h>
#include "XPlane.hpp"
#include "XPlaneEnvironment.hpp"
#include <XPLMUtilities.h>
#include "Button.hpp"

class HDG_Button : public Button {
    
public:
    HDG_Button(XPCommand* newXPCommand);
    HDG_Button(const char* newCommandName);
    HDG_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~HDG_Button();
};

class NAV_Button : public Button {
    
public:
    NAV_Button(XPCommand* newXPCommand);
    NAV_Button(const char* newCommandName);
    NAV_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~NAV_Button();
};

class APR_Button : public Button {
    
public:
    APR_Button(XPCommand* newXPCommand);
    APR_Button(const char* newCommandName);
    APR_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~APR_Button();
};

class REV_Button : public Button {
    
public:
    REV_Button(XPCommand* newXPCommand);
    REV_Button(const char* newCommandName);
    REV_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~REV_Button();
};

class ALT_Button : public Button {
    
public:
    ALT_Button(XPCommand* newXPCommand);
    ALT_Button(const char* newCommandName);
    ALT_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~ALT_Button();
};

class VS_Button : public Button {
    
public:
    VS_Button(XPCommand* newXPCommand);
    VS_Button(const char* newCommandName);
    VS_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~VS_Button();
};

class IAS_Button : public Button {
    
public:
    IAS_Button(XPCommand* newXPCommand);
    IAS_Button(const char* newCommandName);
    IAS_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~IAS_Button();
};

class AP_Button : public Button {
    
public:
    AP_Button(XPCommand* newXPCommand);
    AP_Button(const char* newCommandName);
    AP_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles);
    ~AP_Button();
};



#endif /* Buttons_hpp */
