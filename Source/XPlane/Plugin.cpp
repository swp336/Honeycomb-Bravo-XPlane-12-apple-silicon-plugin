//
//  Plugin.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 31/03/2023.
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

/*
 *   My thanks to AviTab developer Folke Will <folko@solhost.org> for
 *   releasing the AviTab code as open source.  It gave me a working example
 *   of an X-Plane plugin that helped jump-start my own X-Plane coding journey
 */

#include "Plugin.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <XPLMPlugin.h>
#include <XPLMUtilities.h>
#include <XPLMDataAccess.h>
#include <XPLMMenus.h>
#include "XPLMDisplay.h"
#include "XPlane.hpp"
#include "Honeycomb.h"
#include "BravoLights.hpp"
#include "BravoControls.hpp"

std::shared_ptr<XPlane> xplane;
std::shared_ptr<BravoLights> lights;
std::shared_ptr<BravoControls> controls;
Honeycomb* honeycomb = NULL;
std::string aircraftName;

float lightCheck(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon) {
    lights -> refreshBravoAnnunciators();
    return 0.3;
}

PLUGIN_API int XPluginStart(char *outName, char *outSignature, char *outDescription) {
        
    strncpy(outName, "HoneycombOnArm64MacOS", 255);
    strncpy(outSignature, "swp.testbuild.honeycomb", 255);
    strncpy(outDescription, "Honeycomb configurator for Apple Silicon Macs - vBeta1.02", 255);
    
    xplane = std::make_shared<XPlane>();
    lights = std::make_shared<BravoLights>();
    controls = std::make_shared<BravoControls>();
    
    XPLMRegisterFlightLoopCallback(lightCheck, 0.3, NULL);
    return 1;
}


PLUGIN_API int XPluginEnable(void) {
    
    honeycomb = new Honeycomb();
    honeycomb -> startApp();

    return 1;
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID src, int msg, void *inParam) {
    
    switch (msg) {
        case XPLM_MSG_PLANE_LOADED: aircraftName = xplane -> updateAircraftName();
            break;
        case XPLM_MSG_AIRPORT_LOADED: honeycomb -> setPlane(aircraftName);
            break;
    }
}

PLUGIN_API void XPluginDisable(void) {

    honeycomb -> finishApp();
    delete honeycomb;
}

PLUGIN_API void XPluginStop(void) {
}


