//
//  Annunciators.cpp
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


#include "Annunciators.hpp"

Annunciator::Annunciator(const char* dataRefName) : DataRef(dataRefName) {
}


bool Annunciator::intArrayAnnunciatorIsActive() {
    bool active = false;
    
    for (int i=0; i < _arraySize; i++) {
        active = active || (bool) _dataValue.intArray[i];  // indicator for each 'feature' - true (i.e., 'zero') when feature is active.  check each feature in turn.  overall result is true if at least one feature is active.  False if none active
    }
    
    return active;
}


bool Annunciator::floatArrayAnnunciatorIsActive() {
    bool active = false;
    
    for (int i=0; i < _arraySize; i++) {
        active = active || (bool) _dataValue.floatArray[i];  // indicator for each 'feature' - false (i.e., 'zero') when feature is inactive.  check each feature in turn.  overall result is true if at least one feature is active.  False if none active
    }
    
    return active;
}


bool Annunciator::multiAnnunciatorIsActive() {
    
    return (_dataValue.intValue != 0) || (_dataValue.floatValue != 0) || (_dataValue.doubleValue != 0);
}

bool Annunciator::isActive() {
    getData();
    
    switch (_dataType) {
        case XPUnknown: return false; break;
        case XPInt: return (_dataValue.intValue != 0); break;
        case XPFloat: return (_dataValue.floatValue != 0); break;
        case XPDouble: return (_dataValue.doubleValue != 0); break;
        case XPFloatArray: return floatArrayAnnunciatorIsActive(); break;
        case XPIntArray: return intArrayAnnunciatorIsActive(); break;
        case XPDataBlock: return false; break;
        case XPMulti: return multiAnnunciatorIsActive(); break;
        default: return false;
    }
}

CompoundAnnunciator::CompoundAnnunciator() {
    
}

CompoundAnnunciator::CompoundAnnunciator(const char* dataRefName1) {
    addAnnuciator(dataRefName1);
}

CompoundAnnunciator::CompoundAnnunciator(const char* dataRefName1, const char* dataRefName2) {
    addAnnuciator(dataRefName1);
    addAnnuciator(dataRefName2);
}

CompoundAnnunciator::CompoundAnnunciator(const char* dataRefName1, const char* dataRefName2, const char* dataRefName3) {
    addAnnuciator(dataRefName1);
    addAnnuciator(dataRefName2);
    addAnnuciator(dataRefName3);
}

CompoundAnnunciator::CompoundAnnunciator(const char* dataRefName1, const char* dataRefName2, const char* dataRefName3, const char* dataRefName4) {
    addAnnuciator(dataRefName1);
    addAnnuciator(dataRefName2);
    addAnnuciator(dataRefName3);
    addAnnuciator(dataRefName4);
}

void CompoundAnnunciator::addAnnuciator(const char* dataRefName) {
    
    Annunciator* thisAnnunciator = new Annunciator(dataRefName);
    annunciatorList.insert(annunciatorList.begin(), thisAnnunciator);
}

bool CompoundAnnunciator::isActive() {
    
    bool active = false;
    
    std::vector<Annunciator*>::iterator it;
    
    for (it = annunciatorList.begin(); it != annunciatorList.end(); ++it ) {
        active = (active || (*it) -> isActive());
    }
    return active;
}

int CompoundAnnunciator::listSize() {
    return (int) annunciatorList.size();
}
    
    
Annunciator* CompoundAnnunciator::getAnnunciatorAt(int entry) {
        
    if ((entry >= 0) && (entry < listSize())) {
        return annunciatorList.at(entry);
    }
    else return NULL;
}

    
LandingGearAnnunciator::LandingGearAnnunciator() : Annunciator("sim/flightmodel2/gear/deploy_ratio") {
}

LandingGearAnnunciator::LandingGearAnnunciator(const char* dataRefName) : Annunciator(dataRefName) {
}

XPLandingGearStatus LandingGearAnnunciator::convertStatus(float thisValue) {
    if (thisValue == 1) return XPGearDown;
    else {
        if (thisValue == 0) return XPGearUp;
        else return XPGearTransition;
    }
}


XPLandingGearStatus LandingGearAnnunciator::leftGearStatus() {
    getData();
    return convertStatus(_dataValue.floatArray[1]);
}

XPLandingGearStatus LandingGearAnnunciator::noseGearStatus() {
    getData();
    return convertStatus(_dataValue.floatArray[0]);

}

XPLandingGearStatus LandingGearAnnunciator::rightGearStatus() {
    getData();
    return convertStatus(_dataValue.floatArray[2]);
}

