//
//  Annunciators.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 04/07/2023.
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


#ifndef Annunciators_hpp
#define Annunciators_hpp

#include "DataRef.h"
#include <set>

enum XPLandingGearStatus { XPGearDown, XPGearUp, XPGearTransition };

class Annunciator : public DataRef {

public:
    Annunciator(const char* dataRefName);
    bool isActive();
    
protected:
    bool intArrayAnnunciatorIsActive();
    bool floatArrayAnnunciatorIsActive();
    bool multiAnnunciatorIsActive();
};

class LandingGearAnnunciator : public Annunciator {
  
public:
    LandingGearAnnunciator();
    LandingGearAnnunciator(const char* dataRefName);
    XPLandingGearStatus leftGearStatus();
    XPLandingGearStatus noseGearStatus();
    XPLandingGearStatus rightGearStatus();
    
private:
    XPLandingGearStatus convertStatus(float thisValue);
};

class CompoundAnnunciator {

public:
    CompoundAnnunciator();
    CompoundAnnunciator(const char* dataRefName1);
    CompoundAnnunciator(const char* dataRefName1, const char* dataRefName2);
    CompoundAnnunciator(const char* dataRefName1, const char* dataRefName2, const char* dataRefName3);
    CompoundAnnunciator(const char* dataRefName1, const char* dataRefName2, const char* dataRefName3, const char* dataRefName4);
    void addAnnuciator(const char* dataRefName);
    bool isActive();
    int listSize();
    Annunciator* getAnnunciatorAt(int entry);
    
private:
   std::vector<Annunciator*> annunciatorList;
};


#endif /* Annunciators_hpp */
