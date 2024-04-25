//
//  Honeycomb.h
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

#ifndef Honeycomb_h
#define Honeycomb_h

#include <stdlib.h>
#include <memory>
#include "XPlane.hpp"
#include "Bravo.hpp"

class Honeycomb {
    
public:
    Honeycomb();
    ~Honeycomb();
    void startApp();
    void finishApp();
    void setPlane(std::string thisPlane);
    void setProfile(aircraftLabel aircraft);
    void setProfile(std::string aircraft);

    /*
    void profileLaminarAeroworks103();
    void profileLaminarA330();
    void profileLaminarALIA250();
    void profileLaminarBeechcraftBaron58();
    void profileLaminarBeechcraftKingAirC90B();
    void profileLaminarBoeing737();
    void profileLaminarCessna172SP();
    void profileLaminarCessna172G1000();
    void profileLaminarCessna172Floats();
    void profileLaminarCessnaCitationX();
    void laminarCirrusSR22();
    void laminarCirrusVisionSF50();
    void laminarF4PhantonII();
    void laminarF14Tomcat();
    void laminarLancairEvolution();
    void laminarMD82();
    void laiminarPiperPA18SuperCub();
    void laminarRobinsonR22BetaII();
    void laminarSchleicherASK21();
    void laminarSikorskyS76C();
    void laminarStinsonL5Sentinel();
    void laminarVansRV10();
    void zibo737();
*/
    
protected:
    void menuHandlerA();
    void menuHandlerB();
    void menuHandlerC();
    void menuHandlerD();
    Bravo* planeProfile = NULL;
};


#endif /* Honeycomb_h */
