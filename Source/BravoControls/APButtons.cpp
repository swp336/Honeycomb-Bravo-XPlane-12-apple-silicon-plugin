//
//  Buttons.cpp
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


#include "APButtons.hpp"
#include "APButtonLabel.hpp"
#include <string>
#include "XPLMUtilities.h"

HDG_Button::HDG_Button(XPCommand* newXPCommand) : Button("Honeycomb/Bravo/Button/HDG", "HDG Button", APHDG) {
    setCommand(newXPCommand);
}

HDG_Button::HDG_Button(const char* newCommandName) : Button("Honeycomb/Bravo/Button/HDG", "HDG Button", APHDG) {
    setCommand(new XPCommand(newCommandName));
}

HDG_Button::HDG_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/HDG", "HDG Button", APHDG, bravoToggles) {
    setCommand(newXPCommand);
}

HDG_Button::~HDG_Button() {
}

NAV_Button::NAV_Button(XPCommand* newXPCommand) :  Button("Honeycomb/Bravo/Button/NAV", "NAV Button", APNAV) {
    setCommand(newXPCommand);
}

NAV_Button::NAV_Button(const char* newCommandName) :  Button("Honeycomb/Bravo/Button/NAV", "NAV Button", APNAV) {
    setCommand(new XPCommand(newCommandName));
}

NAV_Button::NAV_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/NAV", "NAV Button", APNAV, bravoToggles ) {
    setCommand(newXPCommand);
}

NAV_Button::~NAV_Button() {
}

APR_Button::APR_Button(XPCommand* newXPCommand) :  Button("Honeycomb/Bravo/Button/APR", "APR Button", APAPR) {
    setCommand(newXPCommand);
}

APR_Button::APR_Button(const char* newCommandName) :  Button("Honeycomb/Bravo/Button/APR", "APR Button", APAPR) {
    setCommand(new XPCommand(newCommandName));
}

APR_Button::APR_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/APR", "APR Button", APAPR, bravoToggles) {
    setCommand(newXPCommand);
}

APR_Button::~APR_Button() {
}

REV_Button::REV_Button(XPCommand* newXPCommand) :  Button("Honeycomb/Bravo/Button/REV", "REV Button", APREV) {
    setCommand(newXPCommand);
}

REV_Button::REV_Button(const char* newCommandName) :  Button("Honeycomb/Bravo/Button/REV", "REV Button", APREV) {
    setCommand(new XPCommand(newCommandName));
}

REV_Button::REV_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/REV", "REV Button", APREV, bravoToggles) {
    setCommand(newXPCommand);
}

REV_Button::~REV_Button() {
}

ALT_Button::ALT_Button(XPCommand* newXPCommand) :  Button("Honeycomb/Bravo/Button/ALT", "ALT Button", APALT) {
    setCommand(newXPCommand);
}

ALT_Button::ALT_Button(const char* newCommandName) :  Button("Honeycomb/Bravo/Button/ALT", "ALT Button", APALT) {
    setCommand(new XPCommand(newCommandName));
}

ALT_Button::ALT_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/ALT", "ALT Button", APALT, bravoToggles) {
    setCommand(newXPCommand);
}

ALT_Button::~ALT_Button() {
}

VS_Button::VS_Button(XPCommand* newXPCommand) :  Button("Honeycomb/Bravo/Button/VS", "VS Button", APVS) {
    setCommand(newXPCommand);
}

VS_Button::VS_Button(const char* newCommandName) :  Button("Honeycomb/Bravo/Button/VS", "VS Button", APVS) {
    setCommand(new XPCommand(newCommandName));
}

VS_Button::VS_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/VS", "VS Button", APVS, bravoToggles) {
    setCommand(newXPCommand);
}

VS_Button::~VS_Button() {
    }

IAS_Button::IAS_Button(XPCommand* newXPCommand) :  Button("Honeycomb/Bravo/Button/IAS", "IAS Button", APIAS) {
    setCommand(newXPCommand);
}

IAS_Button::IAS_Button(const char* newCommandName) :  Button("Honeycomb/Bravo/Button/IAS", "IAS Button", APIAS) {
    setCommand(new XPCommand(newCommandName));
}

IAS_Button::IAS_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/IAS", "IAS Button", APIAS, bravoToggles) {
    setCommand(newXPCommand);
}

IAS_Button::~IAS_Button() {
    
}

AP_Button::AP_Button(XPCommand* newXPCommand) :  Button("Honeycomb/Bravo/Button/AutoPilot", "Auto Pilot Button", APAP) {
    setCommand(newXPCommand);
}

AP_Button::AP_Button(const char* newCommandName) :  Button("Honeycomb/Bravo/Button/AutoPilot", "Auto Pilot Button", APAP) {
    setCommand(new XPCommand(newCommandName));
}

AP_Button::AP_Button(XPCommand* newXPCommand, TrackingToggleSet* bravoToggles) :  Button("Honeycomb/Bravo/Button/AutoPilot", "Auto Pilot Button", APAP, bravoToggles) {
    setCommand(newXPCommand);
}

AP_Button::~AP_Button() {
    
}



