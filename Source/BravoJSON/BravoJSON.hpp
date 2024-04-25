//
//  BravoJSON.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 15/07/2023.
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


#ifndef BravoJSON_hpp
#define BravoJSON_hpp

#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>


#include "BravoProfile.hpp"

typedef std::map<std::string, std::string> SingleCommandMap;

struct APButtonProfileData {
    
    APButtonProfileData(std::string *command, SingleCommandMap *custom, bool customised) : customised(customised) {
        
        if (command != NULL)
            this -> commandName = new std::string(*command);
        else this -> commandName = NULL;
        
        if (custom != NULL) {
            this -> customCommands = new SingleCommandMap(*custom); }
        else this -> customCommands = NULL;
    };
    
    std::string *commandName;
    bool customised = false;
    SingleCommandMap *customCommands;
};

struct RotaryCommandProfile {

    RotaryCommandProfile(std::string name, bool splitSpeed, std::string lowSpeed, std::string fastSpeed, std::string oneSpeed) : commandName(name), dualSpeed(splitSpeed), slowSpeed(lowSpeed), highSpeed(fastSpeed), singleSpeed(oneSpeed) {
    }
    
    RotaryCommandProfile() {}
    
    RotaryCommandProfile(RotaryCommandProfile* thisCopy) {
        commandName = thisCopy -> commandName;
        slowSpeed = thisCopy -> slowSpeed;
        highSpeed = thisCopy -> highSpeed;
        dualSpeed = thisCopy -> dualSpeed;
    }
    
    std::string commandName;
    bool dualSpeed;
    std::string slowSpeed;
    std::string highSpeed;
    std::string singleSpeed;
};

struct TwinRotaryProfile {
  
    RotaryCommandProfile command1;
    RotaryCommandProfile command2;
};

typedef std::map<std::string, TwinRotaryProfile> DualCommandMap;


struct RotaryProfileData {
    
    RotaryProfileData(TwinRotaryProfile* defaults, bool customAdded, DualCommandMap *custom) {

        
        if (defaults != NULL) {
            this -> defaultCommands.command1 = defaults -> command1;
            this -> defaultCommands.command2 = defaults -> command2;
            customised = customAdded;
        }

        if (custom != NULL) {
            
            for (const auto &c : *custom)
            {  std::string key = c.first;
                auto values = new TwinRotaryProfile();
                values -> command1 = c.second.command1;
                values -> command2 = c.second.command2;
                this -> customCommands[key] = *values;
            }
        }
    }
    
    RotaryProfileData() {}
    
    TwinRotaryProfile defaultCommands;
    bool customised = false;
    DualCommandMap customCommands;
};


struct RotaryButtonProfileData {
    std::string commandName;
    bool customised = false;
};


struct AnnunciatorProfileData {
    
    AnnunciatorProfileData() {}
    
    AnnunciatorProfileData(AnnunciatorProfileData* thisCopy) {
        landingGearName = thisCopy -> landingGearName;
        masterWarningName = thisCopy -> masterWarningName;
        engineFireName = thisCopy -> engineFireName;
        lowOilPressureName = thisCopy -> lowOilPressureName;
        lowFuelPressureName = thisCopy -> lowFuelPressureName;
        antiIceName = thisCopy -> antiIceName;
        starterEngagedName = thisCopy -> starterEngagedName;
        APUName = thisCopy -> APUName;
        masterCautionName = thisCopy -> masterCautionName;
        vacuumName = thisCopy -> vacuumName;
        LowHydPressureName = thisCopy -> LowHydPressureName;
        auxFuelPumpName = thisCopy -> auxFuelPumpName;
        parkingBrakeName = thisCopy -> parkingBrakeName;
        lowVoltsName = thisCopy -> lowVoltsName;
        doorName = thisCopy -> doorName;
    }
    
    std::string landingGearName;
    std::string masterWarningName;
    std::string engineFireName;
    std::string lowOilPressureName;
    std::string lowFuelPressureName;
    std::string antiIceName;
    std::string starterEngagedName;
    std::string APUName;
    std::string masterCautionName;
    std::string vacuumName;
    std::string LowHydPressureName;
    std::string auxFuelPumpName;
    std::string parkingBrakeName;
    std::string lowVoltsName;
    std::string doorName;
};

struct StateTableData {
    
    StateTableData() {for (int i=0; i< MAX_STATES; i++) states[i] = NULL;}
    StateTableData(LightState* newStates[MAX_STATES]) { if (newStates != NULL) { for (int i=0; i< MAX_STATES; i++) states[i] = newStates[i]; } }
    
    LightState* states[MAX_STATES];
    bool notUsed = true;
};



class BravoJSON {

public:
    BravoJSON();
    void jsonWrite(BravoProfile *thisProfile, const char* aircraftName);
    void jsonRead(BravoProfile *newProfile, const char* aircraftName);
    bool jsonFileExists(const char* aircraftName);

private:
    const char* jsonDirectory = "Resources/plugins/Honeycomb/";
    std::string jsonFileName(const char* aircraftName);
    void setAPButton(APButtonLabel thisButton, APButtonProfileData* thisProfile, BravoProfile* thisAircraftProfile);
    void setRotary(rotaryButtonLabel thisRotary, RotaryProfileData* thisProfile, BravoProfile* thisAircraftProfile);
    void setRotaryCommands(rotaryButtonLabel thisRotary,TwinRotaryProfile *thisTwinCommandProfile,  BravoProfile* thisAircraftProfile);
    void setRotaryCustomCommands(rotaryButtonLabel thisRotary, DualCommandMap *theseCustomCommands,  BravoProfile* thisAircraftProfile);
    void setRotaryCustomCommands(rotaryButtonLabel thisRotary, toggleLabel thisToggle, TwinRotaryProfile *customCommands,  BravoProfile* thisAircraftProfile);
    void setLandingAnnunciators(std::string thisName);
    void setAnnunciator(BravoLight thisLight, std::string thisName);
    void setAPAnnunciator(APButtonLabel thisLight, std::string thisName);
    commandSpeed stringToCommandSpeed(std::string speedString);
};

#endif /* BravoJSON_hpp */
