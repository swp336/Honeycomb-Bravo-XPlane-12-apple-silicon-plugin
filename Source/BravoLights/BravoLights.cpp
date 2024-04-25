//
//  LightMap.cpp
//  BravoLights
//
//  Created by Steve Proctor on 05/06/2023.
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


#include <chrono>
#include "BravoLights.hpp"


BravoLights::BravoLights() {
 //   defaultAnnunciatorDataRefs();
    blankAnnunciators();
    bravo = new BravoUSB();
    allLightsOff();
//    splash(250);
}

BravoLights::~BravoLights() {
    allLightsOff();
    delete bravo;
}
 
void delay(int milliSeconds) {

    std::chrono::steady_clock::time_point rStartAt= std::chrono::steady_clock::now();
    auto rDuration = std::chrono::steady_clock::now() - rStartAt;

    while (std::chrono::duration_cast<std::chrono::milliseconds>(rDuration).count() < milliSeconds)
        rDuration = std::chrono::steady_clock::now() - rStartAt;
}

void BravoLights::splash(int milliSeconds) {
    
    
    allLightsOff();
    
    lightOn(REVLight);
    lightOn(LowFuelPressureLight);
    lightOn(AuxFuelPumpLight);
    
    delay(milliSeconds);
    
    lightOn(APRLight);
    lightOn(LowOilPressureLight);
    lightOn(LowHydPressureLight);
    lightOn(ALTLight);
    lightOn(AntiIceLight);
    lightOn(ParkingBrakeLight);
    
    delay (milliSeconds);
    
    lightOn(NAVLight);
    lightOn(EngineFireLight);
    lightOn(VacuumLight);
    lightOn(VSLight);
    lightOn(StarterEngagedLight);
    lightOn(LowVoltsLight);
    
    delay(milliSeconds);
    
    lightOn(HDGLight);
    lightOn(MasterWarningLight);
    lightOn(MasterCautionLight);
    lightOn(IASLight);
    lightOn(APULight);
    lightOn(DoorLight);
    
    delay(milliSeconds);

    lightOn(AutoPilotLight);
    lightOn(RedLandingLeftLight);
    lightOn(RedLandingNoseLight);
    lightOn(RedLandingRightLight);

    delay(milliSeconds*2);
    
    lightOff(RedLandingLeftLight);
    lightOff(RedLandingNoseLight);
    lightOff(RedLandingRightLight);

    lightOn(GreenLandingLeftLight);
    lightOn(GreenLandingNoseLight);
    lightOn(GreenLandingRightLight);

    delay(milliSeconds*2);

    lightOff(GreenLandingLeftLight);
    lightOff(GreenLandingNoseLight);
    lightOff(GreenLandingRightLight);
    lightOff(AutoPilotLight);
    
    delay(milliSeconds);
    
    lightOff(HDGLight);
    lightOff(MasterWarningLight);
    lightOff(MasterCautionLight);
    lightOff(IASLight);
    lightOff(APULight);
    lightOff(DoorLight);
    
    delay(milliSeconds);
    
    lightOff(NAVLight);
    lightOff(EngineFireLight);
    lightOff(VacuumLight);
    lightOff(VSLight);
    lightOff(StarterEngagedLight);
    lightOff(LowVoltsLight);
    
    delay(milliSeconds);
    
    lightOff(APRLight);
    lightOff(LowOilPressureLight);
    lightOff(LowHydPressureLight);
    lightOff(ALTLight);
    lightOff(AntiIceLight);
    lightOff(ParkingBrakeLight);
    
    delay (milliSeconds);
    
    lightOff(REVLight);
    lightOff(LowFuelPressureLight);
    lightOff(AuxFuelPumpLight);
}


uint64_t BravoLights::lightMask(BravoLight thisLight) {

    switch(thisLight) {
        case HDGLight: return HDGLightMask;
            break;
        case NAVLight: return NAVLightMask;
            break;
        case APRLight: return APRLightMask;
            break;
        case REVLight: return REVLightMask;
            break;
        case ALTLight: return ALTLightMask;
            break;
        case VSLight:  return VSLightMask;
            break;
        case IASLight: return IASLightMask;
            break;
        case AutoPilotLight: return APLightMask;
            break;
        case GreenLandingLeftLight: return GreenLandingLeftLightMask;
            break;
        case RedLandingLeftLight: return RedLandingLeftLightMask;
            break;
        case GreenLandingNoseLight: return GreenLandingNoseLightMask;
            break;
        case RedLandingNoseLight: return RedLandingNoseLightMask;
            break;
        case GreenLandingRightLight: return GreenLandingRightLightMask;
            break;
        case RedLandingRightLight: return RedLandingRightLightMask;
            break;
        case MasterWarningLight: return MasterWarningLightMask;
            break;
        case EngineFireLight: return EngineFireLightMask;
            break;
        case LowOilPressureLight: return LowOilPressureLightMask;
            break;
        case LowFuelPressureLight: return LowFuelPressureLightMask;
            break;
        case AntiIceLight: return AntiIceLightMask;
            break;
        case StarterEngagedLight: return StarterEngagedLightMask;
            break;
        case APULight: return APULightMask;
            break;
        case MasterCautionLight: return MasterCautionLightMask;
            break;
        case VacuumLight: return VacuumLightMask;
            break;
        case LowHydPressureLight: return LowHydPressureLightMask;
            break;
        case AuxFuelPumpLight: return AuxFuelPumpLightMask;
            break;
        case ParkingBrakeLight: return ParkingBrakeLightMask;
            break;
        case LowVoltsLight: return LowVoltsLightMask;
            break;
        case DoorLight: return DoorLightMask;
            break;
    }
}

bool BravoLights::lightIsOn(BravoLight thisLight) {
    return (lightMaskAND(lightMask(thisLight), bravoLightMask) > 0);
}


void BravoLights::lightOn(BravoLight thisLight) {
    
    if (!lightIsOn(thisLight)) {
        bravoLightMask = lightMaskXOR(lightMask(thisLight), bravoLightMask);
        bravo -> setLights(bravoLightMask);
    }
}

void BravoLights::lightOff(BravoLight thisLight) {
    if (lightIsOn(thisLight)) {
        bravoLightMask = lightMaskXOR(lightMask(thisLight), bravoLightMask);
        bravo -> setLights(bravoLightMask);
    }
}

void BravoLights::allLightsOff() {
    
    bravoLightMask = lightMaskXOR(bravoLightMask, bravoLightMask); // XOR with itself sets all bits to zero
    bravo -> setLights(bravoLightMask);
    allLandingLightsOff();
}


void BravoLights::allLandingLightsOff() {
    lightOff(RedLandingLeftLight);
    lightOff(GreenLandingLeftLight);
    lightOff(RedLandingNoseLight);
    lightOff(GreenLandingNoseLight);
    lightOff(RedLandingRightLight);
    lightOff(GreenLandingRightLight);
}

uint64_t BravoLights::lightMaskXOR(uint64_t thisLight, uint64_t thisMask) {
    return thisLight ^ thisMask;
}
         
uint64_t BravoLights::lightMaskAND(uint64_t thisLight, uint64_t thisMask) {
    return thisLight & thisMask;
}

void BravoLights::blankAnnunciators() {
    LandingGearAllAnnunciator.reset(new LandingGearAnnunciator(NULL));
    MasterWarningAnnunciator.reset(new Annunciator(NULL));
    EngineFireAnnunciator.reset(new Annunciator(NULL));
    LowOilPressureAnnunciator.reset(new Annunciator(NULL));
    LowFuelPressureAnnunciator.reset(new Annunciator(NULL));
    AntiIceAnnunciator.reset(new Annunciator(NULL));
    StarterEngagedAnnunciator.reset(new Annunciator(NULL));
    APUAnnunciator.reset(new Annunciator(NULL));
    MasterCautionAnnunciator.reset(new Annunciator(NULL));
    VacuumAnnunciator.reset(new Annunciator(NULL));
    LowHydPressureAnnunciator.reset(new Annunciator(NULL));
    AuxFuelPumpAnnunciator.reset(new Annunciator(NULL));
    ParkingBrakeAnnunciator.reset(new Annunciator(NULL));
    LowVoltsAnnunciator.reset(new Annunciator(NULL));
    DoorLightAnnunciator.reset(new Annunciator(NULL));
}

void BravoLights::defaultAnnunciatorDataRefs() {
    
    LandingGearAllAnnunciator.reset(new LandingGearAnnunciator());
    MasterWarningAnnunciator.reset(new Annunciator("sim/cockpit2/annunciators/master_warning"));
    EngineFireAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/engine_fire"));
    LowOilPressureAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/oil_pressure"));
    LowFuelPressureAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/fuel_pressure"));
    AntiIceAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/ice"));
    StarterEngagedAnnunciator.reset(new Annunciator("sim/cockpit2/engine/actuators/starter_hit"));
    APUAnnunciator.reset(new Annunciator("sim/cockpit/engine/APU_running"));
    MasterCautionAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/master_caution"));
    VacuumAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/low_vacuum"));
    LowHydPressureAnnunciator.reset(new Annunciator("sim/cockpit2/annunciators/hydraulic_pressure"));
    AuxFuelPumpAnnunciator.reset(new Annunciator("sim/cockpit2/fuel/showing_aux"));
    ParkingBrakeAnnunciator.reset(new Annunciator("sim/cockpit2/controls/parking_brake_ratio"));
    LowVoltsAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/low_voltage"));
    DoorLightAnnunciator.reset(new Annunciator("sim/cockpit/warnings/annunciators/cabin_door_open"));
}

void BravoLights::customAnnunciatorDataRef(BravoLight thisLight, const char* dataRefName) {
    
    switch(thisLight) {

        case GreenLandingLeftLight:  LandingGearAllAnnunciator.reset(new LandingGearAnnunciator(dataRefName)); break;
        case RedLandingLeftLight:    LandingGearAllAnnunciator.reset(new LandingGearAnnunciator(dataRefName)); break;
        case GreenLandingNoseLight:  LandingGearAllAnnunciator.reset(new LandingGearAnnunciator(dataRefName)); break;
        case RedLandingNoseLight:    LandingGearAllAnnunciator.reset(new LandingGearAnnunciator(dataRefName)); break;
        case GreenLandingRightLight: LandingGearAllAnnunciator.reset(new LandingGearAnnunciator(dataRefName)); break;
        case RedLandingRightLight:   LandingGearAllAnnunciator.reset(new LandingGearAnnunciator(dataRefName)); break;
        case MasterWarningLight:     MasterWarningAnnunciator .reset(new Annunciator(dataRefName)); break;
        case EngineFireLight:        EngineFireAnnunciator.reset(new Annunciator(dataRefName)); break;
        case LowOilPressureLight:    LowOilPressureAnnunciator.reset(new Annunciator(dataRefName)); break;
        case LowFuelPressureLight:   LowFuelPressureAnnunciator.reset(new Annunciator(dataRefName)); break;
        case AntiIceLight:           AntiIceAnnunciator.reset(new Annunciator(dataRefName)); break;
        case StarterEngagedLight:    StarterEngagedAnnunciator.reset(new Annunciator(dataRefName)); break;
        case APULight:               APUAnnunciator.reset(new Annunciator(dataRefName)); break;
        case MasterCautionLight:     MasterCautionAnnunciator.reset(new Annunciator(dataRefName)); break;
        case VacuumLight:            VacuumAnnunciator.reset(new Annunciator(dataRefName)); break;
        case LowHydPressureLight:    LowHydPressureAnnunciator.reset(new Annunciator(dataRefName)); break;
        case AuxFuelPumpLight:       AuxFuelPumpAnnunciator.reset(new Annunciator(dataRefName)); break;
        case ParkingBrakeLight:      ParkingBrakeAnnunciator.reset(new Annunciator(dataRefName)); break;
        case LowVoltsLight:          LowVoltsAnnunciator.reset(new Annunciator(dataRefName)); break;
        case DoorLight:              DoorLightAnnunciator.reset(new Annunciator(dataRefName)); break;
        default: break;
    }
}

const char* BravoLights::getAnnunciatorDataRef(BravoLight thisLight) {

    const char* dataName = NULL;
    
    switch(thisLight) {
        case GreenLandingLeftLight:  dataName = LandingGearAllAnnunciator -> dataRefName();  break;
        case RedLandingLeftLight:    dataName = LandingGearAllAnnunciator -> dataRefName();  break;
        case GreenLandingNoseLight:  dataName = LandingGearAllAnnunciator -> dataRefName();  break;
        case RedLandingNoseLight:    dataName = LandingGearAllAnnunciator -> dataRefName();  break;
        case GreenLandingRightLight: dataName = LandingGearAllAnnunciator -> dataRefName();  break;
        case RedLandingRightLight:   dataName = LandingGearAllAnnunciator -> dataRefName();  break;
        case MasterWarningLight:     dataName = MasterWarningAnnunciator -> dataRefName();   break;
        case EngineFireLight:        dataName = EngineFireAnnunciator -> dataRefName();      break;
        case LowOilPressureLight:    dataName = LowOilPressureAnnunciator -> dataRefName();  break;
        case LowFuelPressureLight:   dataName = LowFuelPressureAnnunciator -> dataRefName(); break;
        case AntiIceLight:           dataName = AntiIceAnnunciator -> dataRefName();         break;
        case StarterEngagedLight:    dataName = StarterEngagedAnnunciator -> dataRefName();  break;
        case APULight:               dataName = APUAnnunciator -> dataRefName();             break;
        case MasterCautionLight:     dataName = MasterCautionAnnunciator -> dataRefName();   break;
        case VacuumLight:            dataName = VacuumAnnunciator -> dataRefName();          break;
        case LowHydPressureLight:    dataName = LowHydPressureAnnunciator -> dataRefName();  break;
        case AuxFuelPumpLight:       dataName = AuxFuelPumpAnnunciator -> dataRefName();     break;
        case ParkingBrakeLight:      dataName = ParkingBrakeAnnunciator -> dataRefName();    break;
        case LowVoltsLight:          dataName = LowVoltsAnnunciator -> dataRefName();        break;
        case DoorLight:              dataName = DoorLightAnnunciator -> dataRefName();       break;
        default: break;
    }
    if (dataName != NULL)
        return dataName;
    else return NULL;
}


void BravoLights::addAutopilotLightDataRef(APButtonLabel thisButton, const char* dataRefName) {
    
    switch (thisButton) {
        case APHDG: { if (HDGbuttonLightMap == NULL) { HDGbuttonLightMap = new CompoundAnnunciator();} HDGbuttonLightMap -> addAnnuciator(dataRefName); break; }
        case APNAV: { if (NAVbuttonLightMap == NULL) { NAVbuttonLightMap = new CompoundAnnunciator();} NAVbuttonLightMap -> addAnnuciator(dataRefName); break; }
        case APAPR: { if (APRbuttonLightMap == NULL) { APRbuttonLightMap = new CompoundAnnunciator();} APRbuttonLightMap -> addAnnuciator(dataRefName); break; }
        case APREV: { if (REVbuttonLightMap == NULL) { REVbuttonLightMap = new CompoundAnnunciator();} REVbuttonLightMap -> addAnnuciator(dataRefName); break; }
        case APALT: { if (ALTbuttonLightMap == NULL) { ALTbuttonLightMap = new CompoundAnnunciator();} ALTbuttonLightMap -> addAnnuciator(dataRefName); break; }
        case APVS:  { if (VSbuttonLightMap  == NULL) { VSbuttonLightMap  = new CompoundAnnunciator();} VSbuttonLightMap  -> addAnnuciator(dataRefName); break; }
        case APIAS: { if (IASbuttonLightMap == NULL) { IASbuttonLightMap = new CompoundAnnunciator();} IASbuttonLightMap -> addAnnuciator(dataRefName); break; }
        case APAP:  { if (APbuttonLightMap  == NULL) { APbuttonLightMap  = new CompoundAnnunciator();} APbuttonLightMap  -> addAnnuciator(dataRefName); break; }
        default: break;
    }
    _APAnnunciatorsActive = true;
}

CompoundAnnunciator* BravoLights::getAPannunciator(APButtonLabel thisButton) {
    switch (thisButton) {
        case APHDG: { return HDGbuttonLightMap; break; }
        case APNAV: { return NAVbuttonLightMap; break; }
        case APAPR: { return APRbuttonLightMap; break; }
        case APREV: { return REVbuttonLightMap; break; }
        case APALT: { return ALTbuttonLightMap; break; }
        case APVS:  { return VSbuttonLightMap;  break; }
        case APIAS: { return IASbuttonLightMap; break; }
        case APAP:  { return APbuttonLightMap;  break; }
        default: return NULL;
    }
}

bool BravoLights::APLightsActive() {
    return _APAnnunciatorsActive;
}

void BravoLights::refreshLeftLandingGearLight(XPLandingGearStatus gearStatus) {
    switch (gearStatus) {
        case XPGearUp:         lightOff(GreenLandingLeftLight); lightOff(RedLandingLeftLight); break;
        case XPGearDown:       lightOn(GreenLandingLeftLight); lightOff(RedLandingLeftLight); break;
        case XPGearTransition: lightOff(GreenLandingLeftLight); lightOn(RedLandingLeftLight); break;
    }
}

void BravoLights::refreshNoseLandingGearLight(XPLandingGearStatus gearStatus) {
    switch (gearStatus) {
        case XPGearUp:         lightOff(GreenLandingNoseLight); lightOff(RedLandingNoseLight); break;
        case XPGearDown:       lightOn(GreenLandingNoseLight); lightOff(RedLandingNoseLight); break;
        case XPGearTransition: lightOff(GreenLandingNoseLight); lightOn(RedLandingNoseLight); break;
    }
}

void BravoLights::refreshRightLandingGearLight(XPLandingGearStatus gearStatus) {
    switch (gearStatus) {
        case XPGearUp:         lightOff(GreenLandingRightLight); lightOff(RedLandingRightLight); break;
        case XPGearDown:       lightOn(GreenLandingRightLight); lightOff(RedLandingRightLight); break;
        case XPGearTransition: lightOff(GreenLandingRightLight); lightOn(RedLandingRightLight); break;
    }
}


void BravoLights::refreshLandingGearLights() {

    refreshLeftLandingGearLight(LandingGearAllAnnunciator -> leftGearStatus());
    refreshNoseLandingGearLight(LandingGearAllAnnunciator -> noseGearStatus());
    refreshRightLandingGearLight(LandingGearAllAnnunciator -> rightGearStatus());
}

void BravoLights::refreshMasterWarningLight() {
    if (MasterWarningAnnunciator -> isActive())
         lightOn(MasterWarningLight);
    else lightOff(MasterWarningLight);
}

void BravoLights::refreshEngineFireLight() {
    if (EngineFireAnnunciator -> isActive())
         lightOn(EngineFireLight);
    else lightOff(EngineFireLight);
}

void BravoLights::refreshLowOilPressureLight() {
    if (LowOilPressureAnnunciator -> isActive())
         lightOn(LowOilPressureLight);
    else lightOff(LowOilPressureLight);
}

void BravoLights::refreshLowFuelPressureLight() {
    if (LowFuelPressureAnnunciator -> isActive())
         lightOn(LowFuelPressureLight);
    else lightOff(LowFuelPressureLight);
}

void BravoLights::refreshAntiIceLight() {
    if (AntiIceAnnunciator -> isActive())
         lightOn(AntiIceLight);
    else lightOff(AntiIceLight);
}

void BravoLights::refreshStarterEngagedLight() {

    if (StarterEngagedAnnunciator -> isActive())
         lightOn(StarterEngagedLight);
    else lightOff(StarterEngagedLight);
}

void BravoLights::refreshAPULight() {
    if (APUAnnunciator -> isActive())
         lightOn(APULight);
    else lightOff(APULight);
}

void BravoLights::refreshMasterCautionLight() {
    if (MasterCautionAnnunciator -> isActive())
         lightOn(MasterCautionLight);
    else lightOff(MasterCautionLight);
}

void BravoLights::refreshVacuumLight() {
    if (VacuumAnnunciator -> isActive())
         lightOn(VacuumLight);
    else lightOff(VacuumLight);
}

void BravoLights::refreshLowHydPressureLight() {
    if (LowHydPressureAnnunciator -> isActive())
         lightOn(LowHydPressureLight);
    else lightOff(LowHydPressureLight);
}

void BravoLights::refreshAuxFuelLight() {
    if (AuxFuelPumpAnnunciator -> isActive())
         lightOn(AuxFuelPumpLight);
    else lightOff(AuxFuelPumpLight);
}

void BravoLights::refreshParkingBrakeLight() {
    if (ParkingBrakeAnnunciator -> isActive())
         lightOn(ParkingBrakeLight);
    else lightOff(ParkingBrakeLight);
}

void BravoLights::refreshLowVoltsLight() {
    if (LowVoltsAnnunciator -> isActive())
          lightOn(LowVoltsLight);
    else lightOff(LowVoltsLight);
}

void BravoLights::refreshDoorLight() {
    if (DoorLightAnnunciator -> isActive())
         lightOn(DoorLight);
    else lightOff(DoorLight);
}

void BravoLights::refreshAPLights() {

    refreshAPLight(APHDG);
    refreshAPLight(APNAV);
    refreshAPLight(APAPR);
    refreshAPLight(APREV);
    refreshAPLight(APALT);
    refreshAPLight(APVS);
    refreshAPLight(APIAS);
    refreshAPLight(APAP);
}

void BravoLights::refreshAPLight(APButtonLabel thisButton) {
    
    switch (thisButton) {
        case APHDG: { if (HDGbuttonLightMap != NULL) { if (HDGbuttonLightMap -> isActive()) lightOn(HDGLight); else lightOff(HDGLight);  break; } break; }
        case APNAV: { if (NAVbuttonLightMap != NULL) { if (NAVbuttonLightMap -> isActive()) lightOn(NAVLight); else lightOff(NAVLight);  break; } break; }
        case APAPR: { if (APRbuttonLightMap != NULL) { if (APRbuttonLightMap -> isActive()) lightOn(APRLight); else lightOff(APRLight);  break; } break; }
        case APREV: { if (REVbuttonLightMap != NULL) { if (REVbuttonLightMap -> isActive()) lightOn(REVLight); else lightOff(REVLight);  break; } break; }
        case APALT: { if (ALTbuttonLightMap != NULL) { if (ALTbuttonLightMap -> isActive()) lightOn(ALTLight); else lightOff(ALTLight);  break; } break; }
        case APVS:  { if (VSbuttonLightMap  != NULL) { if (VSbuttonLightMap  -> isActive()) lightOn(VSLight);  else lightOff(VSLight);   break; } break; }
        case APIAS: { if (IASbuttonLightMap != NULL) { if (IASbuttonLightMap -> isActive()) lightOn(IASLight); else lightOff(IASLight);  break; } break; }
        case APAP:  { if (APbuttonLightMap  != NULL) { if (APbuttonLightMap  -> isActive()) lightOn(AutoPilotLight);  else lightOff(AutoPilotLight); break; } break; }
        default: break;
    }
}


void BravoLights::refreshBravoAnnunciators() {
    
    refreshLandingGearLights();
    refreshMasterWarningLight();
    refreshEngineFireLight();
    refreshLowOilPressureLight();
    refreshLowFuelPressureLight();
    refreshAntiIceLight();
    refreshStarterEngagedLight();
    refreshAPULight();
    refreshMasterCautionLight();
    refreshVacuumLight();
    refreshLowHydPressureLight();
    refreshAuxFuelLight();
    refreshParkingBrakeLight();
    refreshLowVoltsLight();
    
    if (_APAnnunciatorsActive) refreshAPLights();
}



