//
//  BravoLights.hpp
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


#ifndef BravoLights_hpp
#define BravoLights_hpp

#include <cstdint>
#include <map>
#include "BravoUSB.hpp"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include "APButtonLabel.hpp"
#include "Annunciators.hpp"

enum BravoLight { HDGLight, NAVLight, APRLight, REVLight, ALTLight, VSLight, IASLight, AutoPilotLight,
                  GreenLandingLeftLight, RedLandingLeftLight, GreenLandingNoseLight, RedLandingNoseLight, GreenLandingRightLight, RedLandingRightLight,
                  MasterWarningLight, EngineFireLight, LowOilPressureLight, LowFuelPressureLight, AntiIceLight, StarterEngagedLight, APULight,
                  MasterCautionLight, VacuumLight, LowHydPressureLight, AuxFuelPumpLight, ParkingBrakeLight, LowVoltsLight, DoorLight                   };

class BravoLights {

public:
    BravoLights();
    ~BravoLights();
    void splash(int milliseconds);
    void lightOn(BravoLight thisLight);
    void lightOff(BravoLight thisLight);
    bool lightIsOn(BravoLight thisLight);
    void allLightsOff();
    void allLandingLightsOff();
    void defaultAnnunciatorDataRefs();
    void customAnnunciatorDataRef(BravoLight thisLight, const char* dataRefName);
    const char* getAnnunciatorDataRef(BravoLight thisLight);
    void refreshBravoAnnunciators();
    void addAutopilotLightDataRef(APButtonLabel thisButton, const char* dataRefName);
    bool APLightsActive();
    CompoundAnnunciator* getAPannunciator(APButtonLabel thisButton);

private:
    BravoUSB* bravo = NULL;
    uint64_t bravoLightMask = 0;
    uint64_t lightMask(BravoLight thisLight);
    uint64_t lightMaskXOR(uint64_t thisLight, uint64_t thisMask);
    uint64_t lightMaskAND(uint64_t thisLight, uint64_t thisMask);
    void blankAnnunciators();
    void refreshLandingGearLights();
    void refreshLeftLandingGearLight(XPLandingGearStatus gearStatus);
    void refreshNoseLandingGearLight(XPLandingGearStatus gearStatus);
    void refreshRightLandingGearLight(XPLandingGearStatus gearStatus);
    void refreshMasterWarningLight();
    void refreshEngineFireLight();
    void refreshLowOilPressureLight();
    void refreshLowFuelPressureLight();
    void refreshAntiIceLight();
    void refreshStarterEngagedLight();
    void refreshAPULight();
    void refreshMasterCautionLight();
    void refreshVacuumLight();
    void refreshLowHydPressureLight();
    void refreshAuxFuelLight();
    void refreshParkingBrakeLight();
    void refreshLowVoltsLight();
    void refreshDoorLight();
    void refreshAPLights();
    void refreshAPLight(APButtonLabel thisButton);
    

    uint64_t HDGLightMask               = 1;
    uint64_t NAVLightMask               = 2;
    uint64_t APRLightMask               = 4;
    uint64_t REVLightMask               = 8;
    uint64_t ALTLightMask               = 16;
    uint64_t VSLightMask                = 32;
    uint64_t IASLightMask               = 64;
    uint64_t APLightMask                = 128;
    uint64_t GreenLandingLeftLightMask  = 256;
    uint64_t RedLandingLeftLightMask    = 512;
    uint64_t GreenLandingNoseLightMask  = 1024;
    uint64_t RedLandingNoseLightMask    = 2048;
    uint64_t GreenLandingRightLightMask = 4096;
    uint64_t RedLandingRightLightMask   = 8192;
    uint64_t MasterWarningLightMask     = 16384;
    uint64_t EngineFireLightMask        = 32768;
    uint64_t LowOilPressureLightMask    = 65536;
    uint64_t LowFuelPressureLightMask   = 131072;
    uint64_t AntiIceLightMask           = 262144;
    uint64_t StarterEngagedLightMask    = 524288;
    uint64_t APULightMask               = 1048576;
    uint64_t MasterCautionLightMask     = 2097152;
    uint64_t VacuumLightMask            = 4194304;
    uint64_t LowHydPressureLightMask    = 8388608;
    uint64_t AuxFuelPumpLightMask       = 16777216;
    uint64_t ParkingBrakeLightMask      = 33554432;
    uint64_t LowVoltsLightMask          = 67108864;
    uint64_t DoorLightMask              = 134217728;
    
    XPLMDataRef HDGLightRef;
    XPLMDataRef NAVLightRef;
    XPLMDataRef APRLightRef;
    XPLMDataRef REVLightRef;
    XPLMDataRef ALTLightRef;
    XPLMDataRef VSLightRef;
    XPLMDataRef IASLightRef;
    XPLMDataRef APLightRef;
    std::unique_ptr<LandingGearAnnunciator> LandingGearAllAnnunciator = NULL;
    std::unique_ptr<Annunciator>  MasterWarningAnnunciator = NULL;
    std::unique_ptr<Annunciator>  EngineFireAnnunciator = NULL;
    std::unique_ptr<Annunciator>  LowOilPressureAnnunciator = NULL;
    std::unique_ptr<Annunciator>  LowFuelPressureAnnunciator = NULL;
    std::unique_ptr<Annunciator>  AntiIceAnnunciator = NULL;
    std::unique_ptr<Annunciator>  StarterEngagedAnnunciator = NULL;
    std::unique_ptr<Annunciator>  APUAnnunciator = NULL;
    std::unique_ptr<Annunciator>  MasterCautionAnnunciator = NULL;
    std::unique_ptr<Annunciator>  VacuumAnnunciator = NULL;
    std::unique_ptr<Annunciator>  LowHydPressureAnnunciator = NULL;
    std::unique_ptr<Annunciator>  AuxFuelPumpAnnunciator = NULL;
    std::unique_ptr<Annunciator>  ParkingBrakeAnnunciator = NULL;
    std::unique_ptr<Annunciator>  LowVoltsAnnunciator = NULL;
    std::unique_ptr<Annunciator>  DoorLightAnnunciator = NULL;
    CompoundAnnunciator*          HDGbuttonLightMap = NULL;
    CompoundAnnunciator*          NAVbuttonLightMap = NULL;
    CompoundAnnunciator*          APRbuttonLightMap = NULL;
    CompoundAnnunciator*          REVbuttonLightMap = NULL;
    CompoundAnnunciator*          ALTbuttonLightMap = NULL;
    CompoundAnnunciator*          VSbuttonLightMap  = NULL;
    CompoundAnnunciator*          IASbuttonLightMap = NULL;
    CompoundAnnunciator*          APbuttonLightMap  = NULL;
    bool _APAnnunciatorsActive = false;
};


#endif /* BravoLights_hpp */
