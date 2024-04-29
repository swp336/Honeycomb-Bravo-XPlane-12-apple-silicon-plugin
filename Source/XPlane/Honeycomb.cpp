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


#include "Honeycomb.h"
#include "XPlane.hpp"
#include "XPlaneEnvironment.hpp"
#include <stdlib.h>
#include <string>
#include "BravoLights.hpp"

inline constexpr auto hash_djb2a(const std::string_view sv) {
    unsigned long hash{ 5381 };
    for (unsigned char c : sv) {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

 
inline constexpr auto operator"" _sh(const char *str, size_t len) {
    return hash_djb2a(std::string_view{ str, len });
}


Honeycomb::Honeycomb() {
}

Honeycomb::~Honeycomb() {
}

void Honeycomb::menuHandlerA() {
//    xplane -> showAbout();
}


void Honeycomb::menuHandlerB() {
    //zibo737();
}

void Honeycomb::menuHandlerC() {
    //laminarBoeing737();
}

void Honeycomb::menuHandlerD() {
    //laminarMD82();
}


void Honeycomb::startApp() {
    
        if (xplane) {
            
            xplane -> createMenu("Honeycomb for Mac");
            xplane -> addMenuEntry("vBeta1.01 - Copyright 2024 Steve Proctor - swp336@gmail.com", [this] { menuHandlerA(); });
//            xplane -> addMenuEntry("Zibo 737", [this] { menuHandlerB(); });
//            xplane -> addMenuEntry("Laminar 737", [this] { menuHandlerC(); });
//            xplane -> addMenuEntry("McDonnell Douglas MD-82", [this] { menuHandlerD(); });
        }
}

void Honeycomb::finishApp() {
    lights -> allLightsOff();
    xplane -> destroyMenu();
    if (planeProfile != NULL) delete planeProfile;
}


void Honeycomb::setProfile(aircraftLabel aircraft) {
    if (planeProfile == NULL)
      planeProfile = new Bravo(aircraft);
    else {
        delete planeProfile;
        planeProfile = new Bravo(aircraft);
    }
}

void Honeycomb::setProfile(std::string aircraft) {
    if (planeProfile == NULL)
      planeProfile = new Bravo(aircraft);
    else {
        delete planeProfile;
        planeProfile = new Bravo(aircraft);
    }
}

void Honeycomb::setPlane(std::string thisPlane) {
    
    switch (hash_djb2a(thisPlane)) {
            
        //***************************************
        // Laminar Research bundled aircraft
        //***************************************
            
        case "Aero-Works Aerolite 103"_sh: setProfile(laminarAeroworks103);
            break;
        case "Airbus A330-300"_sh: setProfile(laminarAirbusA330);
            break;
        case "ALIA 250"_sh: setProfile(laminarALIA250);
            break;
        case "Beechcraft Baron 58"_sh: setProfile(laminarBeechcraftBaron58);
            break;
        case "Beechcraft King Air C90B"_sh: setProfile(laminarBeechcraftKingAirC90B);
            break;
        case "Boeing 737-800"_sh: setProfile(laminarBoeing737);
            break;
        case "Cessna Skyhawk"_sh: setProfile(laminarCessna172SP);
            break;
        case "Cessna Skyhawk (G1000)"_sh: setProfile(laminarCessna172G1000);
            break;
        case "Cessna Skyhawk (Floats)"_sh: setProfile(laminarCessna172Floats);
            break;
        case "Cessna Citation X"_sh: setProfile(laminarCessnaCitationX);
            break;
        case "Cirrus SR-22"_sh: setProfile(laminarCirrusSR22);
            break;
        case "Cirrus Vision SF50"_sh: setProfile(laminarCirrusVisionSF50);
            break;
        case "F-4 Phantom II"_sh: setProfile(laminarF4PhantonII);
            break;
        case "F-14 Tomcat"_sh: setProfile(laminarF14Tomcat);
            break;
        case "Lancair Evolution"_sh: setProfile(laminarLancairEvolution);
            break;
        case "McDonnell Douglas MD-82"_sh: setProfile(laminarMcDonnellDouglasMD82);
            break;
        case "Piper PA-18 Super Cub"_sh: setProfile(laminarPiperPA18SuperCub);
            break;
        case "Robinson R22 Beta II"_sh:setProfile(laminarRobinsonR22BetaII);
            break;
        case "Schleicher ASK 21"_sh: setProfile(laminarSchleicherASK21);
            break;
        case "Sikorsky S-76C"_sh: setProfile(laminarSikorskyS76C);
            break;
        case "Stinson L5 Sentinel"_sh: setProfile(laminarStinsonL5Sentinel);
            break;
        case "Van's RV-10"_sh: setProfile(laminarVansRV10);
            break;
                        
        //***************************************
        // Other known third party aircraft
        //***************************************

        case "Boeing 737-800X"_sh: setProfile(ziboBoeing737X);
            break;
        case "Boeing 737-800X (4k)"_sh: setProfile(ziboBoeing737X);
            break;
            /*
        case "Boeing 747-400"_sh:
            break;
        case "Boeing 747-400LCF"_sh:
            break;
        case "X-Crafts ERJ 145"_sh:
            break;
        case "X-Crafts ERJ 145XR"_sh:
            break;
        case "Robin DR401 CDI155"_sh:
            break;
             */
        default: setProfile(thisPlane);
            break;
    }
    lights -> splash(250);
}

    
    
