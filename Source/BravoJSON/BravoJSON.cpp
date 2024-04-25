//
//  BravoJSON.cpp
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


#include "BravoJSON.hpp"
#include <stdio.h>
#include <map>
#include "xplane.hpp"

std::string fileName;

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

struct ProfileData {
    
    std::string deviceName;
    std::string aircraftName;
};

enum LightMap { HDGLightMap, NAVLightMap, APRLightMap, REVLightMap, ALTLightMap, VSLightMap, IASLightMap, APLightMap };

BravoJSON::BravoJSON() {
    
}

namespace nlohmann {

 
void to_json(json& j, CommandSet* commandSet);


NLOHMANN_JSON_SERIALIZE_ENUM(toggleLabel, {
    {TG1, "Toggle1"},
    {TG2, "Toggle2"},
    {TG3, "Toggle3"},
    {TG4, "Toggle4"},
    {TG5, "Toggle5"},
    {TG6, "Toggle6"},
    {TG7, "Toggle7"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(APButtonLabel, {
    {APHDG, "APHDG"},
    {APNAV, "APNAV"},
    {APAPR, "APAPR"},
    {APREV, "APREV"},
    {APALT, "APALT"},
    {APVS,  "APVS" },
    {APIAS, "APIAS"},
    {APAP,  "APAP" }
})

std::string intToSpeedString(int speed) {
    
    switch (speed) {
        case 300: return std::string("slowest"); break;
        case 150: return std::string("slow"); break;
        case 100: return std::string("medium"); break;
        case 25:  return std::string("fast"); break;
        case 0:   return std::string("fastest"); break;
        default:  return std::string(std::to_string(speed));
    }
}

toggleLabel stringToToggle(std::string thisString) {
    
    switch(hash_djb2a(thisString)) {
            
        case "Toggle1"_sh: { return TG1; break; };
        case "Toggle2"_sh: { return TG2; break; };
        case "Toggle3"_sh: { return TG3; break; };
        case "Toggle4"_sh: { return TG4; break; };
        case "Toggle5"_sh: { return TG5; break; };
        case "Toggle6"_sh: { return TG6; break; };
        case "Toggle7"_sh: { return TG7; break; };
        default: return TG1; break;
    }
}

void to_json(json& j, XPCommandSpeed* speed)
{
    if (speed != NULL) {
        if (speed -> differentialSpeed()) {
            j["SPEED"]["FAST"] = intToSpeedString(speed -> fastSpeed());
            j["SPEED"]["SLOW"] = intToSpeedString(speed -> slowSpeed());
        }
        else j["SPEED"]["SINGLE_SPEED"] = intToSpeedString(speed -> defaultSpeed());
    }
}

void to_json(json& j, XPCommand* command)
{
    if (command != NULL)
        j["NAME"] = json(command -> commandName());
}

void to_json(json& j, XPTwinCommands* commands)
{
    if (commands != NULL) {
        if (commands -> command2() -> isNull() && (!commands -> command1() -> isNull())) {
            j["COMMAND"] = json(commands -> command1()); //, commands -> command1() -> speed()};
        }
        else {
            j["COMMAND1"] = {json(commands -> command1()), commands -> command1() -> speed()};
            j["COMMAND2"] = {json(commands -> command2()), commands -> command2() -> speed()};
        }
    }
}

void to_json(json& j, CommandSet* commandSet)
{
    if (commandSet -> isEmpty()) {
        j["CUSTOM"] = "NOT_USED";
    }
    else {
        for (auto toggle : {TG1, TG2, TG3, TG4, TG5, TG6, TG7}) {
            if (commandSet -> getCommands(toggle) != NULL) {
                j["CUSTOM"][json(toggle)] = json(commandSet -> getCommands(toggle));
            }
        }
    }
}

void to_json(json& j, Button* button)
{
    if (button != NULL)
        j["COMMAND"] = json{button -> defaultCommand(), button -> customCommands()};
}

void to_json(json& j, RotaryButton* button)
{
    if (button != NULL)
        j = json{button -> defaultCommands(),  button -> customCommands()};
}


void to_json(json& j, LightState* thisState)
{
    if (thisState != NULL) {
        for (auto button : {APHDG, APNAV, APAPR, APREV, APALT, APVS, APIAS, APAP}) {
            auto [found, nextState] = thisState -> getTransitionValue(button, thisState -> state());
            if (found) j[json(button)] = {thisState -> state(), nextState};
        }
        j["LIGHTS_ON"] = thisState -> getOnLights();
        j["LIGHTS_OFF"] = thisState -> getOffLights();
    }
}

void to_json(json& j, StateMachine* stateMachine)
{
    if (stateMachine != NULL) {
        for (int state = 0; state < MAX_STATES; state++) {
            if (stateMachine -> lightState(state) != NULL)
                j["LIGHTSTATE"][std::string(std::to_string(state))] = {stateMachine -> lightState(state)};
        }
    }
    else j = "NOT_USED";
}

void to_json(json& j, BravoLight thisLight)
{
    const char* refName = NULL;
    
    switch(thisLight) {
            
        case GreenLandingLeftLight:  refName = lights -> getAnnunciatorDataRef(GreenLandingLeftLight);  break;
        case RedLandingLeftLight:    refName = lights -> getAnnunciatorDataRef(RedLandingLeftLight);    break;
        case GreenLandingNoseLight:  refName = lights -> getAnnunciatorDataRef(GreenLandingNoseLight);  break;
        case RedLandingNoseLight:    refName = lights -> getAnnunciatorDataRef(RedLandingNoseLight);    break;
        case GreenLandingRightLight: refName = lights -> getAnnunciatorDataRef(GreenLandingRightLight); break;
        case RedLandingRightLight:   refName = lights -> getAnnunciatorDataRef(RedLandingRightLight);   break;
        case MasterWarningLight:     refName = lights -> getAnnunciatorDataRef(MasterWarningLight);     break;
        case EngineFireLight:        refName = lights -> getAnnunciatorDataRef(EngineFireLight);        break;
        case LowOilPressureLight:    refName = lights -> getAnnunciatorDataRef(LowOilPressureLight);    break;
        case LowFuelPressureLight:   refName = lights -> getAnnunciatorDataRef(LowFuelPressureLight);   break;
        case AntiIceLight:           refName = lights -> getAnnunciatorDataRef(AntiIceLight);           break;
        case StarterEngagedLight:    refName = lights -> getAnnunciatorDataRef(StarterEngagedLight);    break;
        case APULight:               refName = lights -> getAnnunciatorDataRef(APULight);               break;
        case MasterCautionLight:     refName = lights -> getAnnunciatorDataRef(MasterCautionLight);     break;
        case VacuumLight:            refName = lights -> getAnnunciatorDataRef(VacuumLight);            break;
        case LowHydPressureLight:    refName = lights -> getAnnunciatorDataRef(LowHydPressureLight);    break;
        case AuxFuelPumpLight:       refName = lights -> getAnnunciatorDataRef(AuxFuelPumpLight);       break;
        case ParkingBrakeLight:      refName = lights -> getAnnunciatorDataRef(ParkingBrakeLight);      break;
        case LowVoltsLight:          refName = lights -> getAnnunciatorDataRef(LowVoltsLight);          break;
        case DoorLight:              refName = lights -> getAnnunciatorDataRef(DoorLight);              break;
        default: break;
    }
    
    if (refName != NULL) {
        
        switch(thisLight) {
                
            case GreenLandingLeftLight:  j["LandingGearAnnunciator"]       = std::string(refName); break;
            case RedLandingLeftLight:    j["RedLandingLeftAnnunciator"]    = std::string(refName); break;
            case GreenLandingNoseLight:  j["GreenLandingNoseAnnunciator"]  = std::string(refName); break;
            case RedLandingNoseLight:    j["RedLandingNoseAnnunciator"]    = std::string(refName); break;
            case GreenLandingRightLight: j["GreenLandingRightAnnunciator"] = std::string(refName); break;
            case RedLandingRightLight:   j["RedLandingRightAnnunciator"]   = std::string(refName); break;
            case MasterWarningLight:     j["MasterWarningAnnunciator"]     = std::string(refName); break;
            case EngineFireLight:        j["EngineFireAnnunciator"]        = std::string(refName); break;
            case LowOilPressureLight:    j["LowOilPressureAnnunciator"]    = std::string(refName); break;
            case LowFuelPressureLight:   j["LowFuelPressureAnnunciator"]   = std::string(refName); break;
            case AntiIceLight:           j["AntiIceAnnunciator"]           = std::string(refName); break;
            case StarterEngagedLight:    j["StarterEngagedAnnunciator"]    = std::string(refName); break;
            case APULight:               j["APUAnnunciator"]               = std::string(refName); break;
            case MasterCautionLight:     j["MasterCautionAnnunciator"]     = std::string(refName); break;
            case VacuumLight:            j["VacuumAnnunciator"]            = std::string(refName); break;
            case LowHydPressureLight:    j["LowHydPressureAnnunciator"]    = std::string(refName); break;
            case AuxFuelPumpLight:       j["AuxFuelPumpAnnunciator"]       = std::string(refName); break;
            case ParkingBrakeLight:      j["ParkingBrakeAnnunciator"]      = std::string(refName); break;
            case LowVoltsLight:          j["LowVoltsAnnunciator"]          = std::string(refName); break;
            case DoorLight:              j["DoorAnnunciator"]              = std::string(refName); break;
            default: break;
        }
    }
    else {
        switch(thisLight) {
                
            case GreenLandingLeftLight:  j["LandingGearAnnunciator"]       = "NOT_SET"; break;
            case RedLandingLeftLight:    j["RedLandingLeftAnnunciator"]    = "NOT_SET"; break;
            case GreenLandingNoseLight:  j["GreenLandingNoseAnnunciator"]  = "NOT_SET"; break;
            case RedLandingNoseLight:    j["RedLandingNoseAnnunciator"]    = "NOT_SET"; break;
            case GreenLandingRightLight: j["GreenLandingRightAnnunciator"] = "NOT_SET"; break;
            case RedLandingRightLight:   j["RedLandingRightAnnunciator"]   = "NOT_SET"; break;
            case MasterWarningLight:     j["MasterWarningAnnunciator"]     = "NOT_SET"; break;
            case EngineFireLight:        j["EngineFireAnnunciator"]        = "NOT_SET"; break;
            case LowOilPressureLight:    j["LowOilPressureAnnunciator"]    = "NOT_SET"; break;
            case LowFuelPressureLight:   j["LowFuelPressureAnnunciator"]   = "NOT_SET"; break;
            case AntiIceLight:           j["AntiIceAnnunciator"]           = "NOT_SET"; break;
            case StarterEngagedLight:    j["StarterEngagedAnnunciator"]    = "NOT_SET"; break;
            case APULight:               j["APUAnnunciator"]               = "NOT_SET"; break;
            case MasterCautionLight:     j["MasterCautionAnnunciator"]     = "NOT_SET"; break;
            case VacuumLight:            j["VacuumAnnunciator"]            = "NOT_SET"; break;
            case LowHydPressureLight:    j["LowHydPressureAnnunciator"]    = "NOT_SET"; break;
            case AuxFuelPumpLight:       j["AuxFuelPumpAnnunciator"]       = "NOT_SET"; break;
            case ParkingBrakeLight:      j["ParkingBrakeAnnunciator"]      = "NOT_SET"; break;
            case LowVoltsLight:          j["LowVoltsAnnunciator"]          = "NOT_SET"; break;
            case DoorLight:              j["DoorAnnunciator"]              = "NOT_SET"; break;
            default: break;
        }
        
    }
}





void writeLightMap(json& j, APButtonLabel thisButton, Annunciator* annunciator) {
    
    if (annunciator != NULL) {
        
        nlohmann::json ap1;
        
        ap1[json(thisButton)] = std::string(annunciator -> dataRefName());
        j += ap1;
    }
}

void writeLightMapSet(json& j, APButtonLabel thisButton, CompoundAnnunciator* thisAnnunciatorSet) {
    
}


void to_json(json& j, CompoundAnnunciator* thisAnnunciator) {

    int listSize = thisAnnunciator -> listSize();
    
    for (int item = 0; item < listSize; item++) {
        Annunciator* annunciator = thisAnnunciator -> getAnnunciatorAt(item);
        j += { std::string(annunciator -> dataRefName()) };
    }
}


void to_json(json& j, LightMap thisLight)
{
    CompoundAnnunciator* APAnnunciators = NULL;
    
    switch(thisLight) {
        case HDGLightMap: { APAnnunciators = lights -> getAPannunciator(APHDG); break; };
        case NAVLightMap: { APAnnunciators = lights -> getAPannunciator(APNAV); break; };
        case APRLightMap: { APAnnunciators = lights -> getAPannunciator(APAPR); break; };
        case REVLightMap: { APAnnunciators = lights -> getAPannunciator(APREV); break; };
        case ALTLightMap: { APAnnunciators = lights -> getAPannunciator(APALT); break; };
        case VSLightMap:  { APAnnunciators = lights -> getAPannunciator(APVS);  break; };
        case IASLightMap: { APAnnunciators = lights -> getAPannunciator(APIAS); break; };
        case APLightMap:  { APAnnunciators = lights -> getAPannunciator(APAP);  break; };
        default: break;
    }

    if (APAnnunciators != NULL) {
        
        switch(thisLight) {
            case HDGLightMap: { j["APHDG"] = APAnnunciators; break; };
            case NAVLightMap: { j["APNAV"] = APAnnunciators; break; };
            case APRLightMap: { j["APAPR"] = APAnnunciators; break; };
            case REVLightMap: { j["APREV"] = APAnnunciators; break; };
            case ALTLightMap: { j["APALT"] = APAnnunciators; break; };
            case VSLightMap:  { j["APVS"]  = APAnnunciators; break; };
            case IASLightMap: { j["APIAS"] = APAnnunciators; break; };
            case APLightMap:  { j["APAP"]  = APAnnunciators; break; };
//            case HDGLightMap: { writeLightMapSet(j, APHDG, APAnnunciators); break; };
//            case NAVLightMap: { writeLightMapSet(j, APNAV, APAnnunciators); break; };
//          case APRLightMap: { writeLightMapSet(j, APAPR, APAnnunciators); break; };
//            case REVLightMap: { writeLightMapSet(j, APREV, APAnnunciators); break; };
//            case ALTLightMap: { writeLightMapSet(j, APALT, APAnnunciators); break; };
//            case VSLightMap:  { writeLightMapSet(j, APVS,  APAnnunciators); break; };
//            case IASLightMap: { writeLightMapSet(j, APIAS, APAnnunciators); break; };
//            case APLightMap:  { writeLightMapSet(j, APAP,  APAnnunciators); break; };
            default: break;
        }
    }
    else {
        switch(thisLight) {
            case HDGLightMap: { j[json(APHDG)] = "NOT_USED"; break; };
            case NAVLightMap: { j[json(APNAV)] = "NOT_USED"; break; };
            case APRLightMap: { j[json(APAPR)] = "NOT_USED"; break; };
            case REVLightMap: { j[json(APREV)] = "NOT_USED"; break; };
            case ALTLightMap: { j[json(APALT)] = "NOT_USED"; break; };
            case VSLightMap:  { j[json(APVS)]  = "NOT_USED"; break; };
            case IASLightMap: { j[json(APIAS)] = "NOT_USED"; break; };
            case APLightMap:  { j[json(APAP)]  = "NOT_USED"; break; };
            default: break;
        }
    }
}


template <>
struct adl_serializer<RotaryCommandProfile> {

    static RotaryCommandProfile from_json(const json& j) {

        json rp1;
        json rp2;
        json rp3;
        json rp4;

        std::string commandName;
        bool dualSpeed = false;
        std::string slowSpeed;
        std::string highSpeed;
        std::string singleSpeed;
        
        if (!j.is_null()) {
            
            rp1 = j[0]["NAME"];
            
            if (rp1.is_string()) {
                commandName = std::string(rp1.get<std::string>());
            }
            
            rp2 = j[1]["SPEED"];
            
            if (rp2.size() > 1) {
                rp3 = rp2["FAST"];
                rp4 = rp2["SLOW"];
                if ((rp3.is_string()) && (rp4.is_string())) {
                    dualSpeed = true;
                    highSpeed = std::string(rp3.get<std::string>());
                    slowSpeed = std::string(rp4.get<std::string>());
                }
            } else
            {
                if (rp2.size() == 1) {
                    rp3 = rp2["SINGLE_SPEED"];
                    if (rp3.is_string()) {
                        dualSpeed = false;
                        singleSpeed = std::string(rp3.get<std::string>());
                    }
                }
            }
        } return {commandName, dualSpeed, slowSpeed, highSpeed, singleSpeed};
    }
};



template <>
struct adl_serializer<APButtonProfileData> {
    
    static APButtonProfileData from_json(const json& j) {
        
        nlohmann::json ap1;
        nlohmann::json ap2;
        nlohmann::json ap3;
        nlohmann::json ap4;
        
        SingleCommandMap commandList;
        std::string commandName;
        std::string customString;
        
        if (!j.is_null()) {
            ap1 = j["COMMAND"][0]["NAME"];
            
            if (ap1.is_string()) {
                commandName = ap1.get<std::string>();
                if (commandName == "NOT_USED")
                    return {NULL, NULL, false};
            }
            
            ap2 = j["COMMAND"][1]["CUSTOM"];

            if (ap2.is_string()) {
                customString = ap2.get<std::string>();
                if (customString == "NOT_USED")
                    return {&commandName, NULL, false};
            }

            if (ap2.is_object()) {
                for (auto& x : ap2.items()) {
                    ap3 = x.key();
                    ap4 = x.value()["COMMAND"]["NAME"];
                    if (ap3.is_string() && ap4.is_string()) {
                        std::string key = ap3.get<std::string>();
                        std::string command = ap4.get<std::string>();
                        commandList[key] = command;
                    }
                }
                return {&commandName, &commandList, true};
            } else return {&commandName, NULL, false};
        } else return {NULL, NULL, false};
    }
};


template <>
struct adl_serializer<RotaryProfileData> {
    
    static RotaryProfileData from_json(const json& j) {
        
        nlohmann::json rp1;
        nlohmann::json rp2;

        DualCommandMap commandList;
        std::string *customString;

        if (!j.is_null()) {
        
            auto command1 = j[0]["COMMAND1"].get<RotaryCommandProfile>();
            auto command2 = j[0]["COMMAND2"].get<RotaryCommandProfile>();
            
            TwinRotaryProfile defaultCommands;
            defaultCommands.command1 = command1;
            defaultCommands.command2 = command2;
            
            rp1 = j[1]["CUSTOM"];
            
            if (rp1.is_string()) {
                customString = new std::string(rp1.get<std::string>());
                if (*customString == "NOT_USED")
                    return {&defaultCommands, false, NULL};
                else return {&defaultCommands, false, NULL};
            }
            
            if (rp1.is_object()) {
                for (auto& x : rp1.items()) {
                    rp2 = x.key();
                    std::string key = rp2.get<std::string>();
                    auto customCommand1 = x.value()["COMMAND1"];
                    auto customCommand2 = x.value()["COMMAND2"];
                    auto commandPair = new TwinRotaryProfile();
                    commandPair -> command1 = customCommand1;
                    commandPair -> command2 = customCommand2;
                    
                    commandList[key] = *commandPair;
                    }
                }
                return {&defaultCommands, true, &commandList};
            }
            else return {NULL, false, NULL};
    }
};


template <>
struct adl_serializer<AnnunciatorProfileData> {
    
    static AnnunciatorProfileData from_json(const json& j) {

        nlohmann::json ap1;

        AnnunciatorProfileData newProfile;
        
        newProfile.landingGearName = j[0]["LandingGearAnnunciator"].get<std::string>();
        newProfile.masterWarningName = j[1]["MasterWarningAnnunciator"].get<std::string>();
        newProfile.engineFireName = j[2]["EngineFireAnnunciator"].get<std::string>();
        newProfile.lowOilPressureName = j[3]["LowOilPressureAnnunciator"].get<std::string>();
        newProfile.lowFuelPressureName = j[4]["LowFuelPressureAnnunciator"].get<std::string>();
        newProfile.antiIceName = j[5]["AntiIceAnnunciator"].get<std::string>();
        newProfile.starterEngagedName = j[6]["StarterEngagedAnnunciator"].get<std::string>();
        newProfile.APUName = j[7]["APUAnnunciator"].get<std::string>();
        newProfile.masterCautionName = j[8]["MasterCautionAnnunciator"].get<std::string>();
        newProfile.vacuumName = j[9]["VacuumAnnunciator"].get<std::string>();
        newProfile.LowHydPressureName = j[10]["LowHydPressureAnnunciator"].get<std::string>();
        newProfile.auxFuelPumpName = j[11]["AuxFuelPumpAnnunciator"].get<std::string>();
        newProfile.parkingBrakeName = j[12]["ParkingBrakeAnnunciator"].get<std::string>();
        newProfile.lowVoltsName = j[13]["LowVoltsAnnunciator"].get<std::string>();
        newProfile.doorName = j[14]["DoorAnnunciator"].get<std::string>();

        return { &newProfile };
    }
    
};


bool stateModelPresent(const json& j) {
    
    nlohmann::json st1;

    st1 = j["STATE_TABLE"];
    
    if (st1 != NULL) {
        return (!st1.is_string());
    }
    else return false;
}


bool APAnnunciatorsPresent(const json& j) {

    nlohmann::json ap1;

    ap1 = j["AP_ANNUNCIATORS"];
    
    if (ap1 != NULL) {
        return (!ap1.is_string());
    }
    else return false;
}


void setAPAnnunciator(const json& j, APButtonLabel thisButton, BravoProfile *thisAircraftProfile) {
    
    if (j != NULL) {
        if (j.is_array()) {
            int annunciatorCount = (int) j.size();
            
            for(int annunciator = 0; annunciator < annunciatorCount; annunciator++) {
                std::string annunciatorName = j[annunciator][0].get<std::string>();
                lights -> addAutopilotLightDataRef(thisButton, annunciatorName.c_str());
            }
        }
    }
}
void setAPAnnunciators(const json& j, BravoProfile *thisAircraftProfile) {

    nlohmann::json annunciatorsList;
    nlohmann::json aphdg;
    nlohmann::json apnav;
    nlohmann::json apapr;
    nlohmann::json aprev;
    nlohmann::json apalt;
    nlohmann::json apvs;
    nlohmann::json apias;
    nlohmann::json apap;

    annunciatorsList = j["AP_ANNUNCIATORS"];
    
    aphdg = annunciatorsList[0]["APHDG"];
    apnav = annunciatorsList[1]["APNAV"];
    apapr = annunciatorsList[2]["APAPR"];
    aprev = annunciatorsList[3]["APREV"];
    apalt = annunciatorsList[4]["APALT"];
    apvs  = annunciatorsList[5]["APVS"];
    apias = annunciatorsList[6]["APIAS"];
    apap  = annunciatorsList[7]["APAP"];

    setAPAnnunciator(aphdg, APHDG, thisAircraftProfile);
    setAPAnnunciator(apnav, APNAV, thisAircraftProfile);
    setAPAnnunciator(apapr, APAPR, thisAircraftProfile);
    setAPAnnunciator(aprev, APREV, thisAircraftProfile);
    setAPAnnunciator(apalt, APALT, thisAircraftProfile);
    setAPAnnunciator(apvs,  APVS,  thisAircraftProfile);
    setAPAnnunciator(apias, APIAS, thisAircraftProfile);
    setAPAnnunciator(apap,  APAP,  thisAircraftProfile);
}

void setStateTransitions(const json& j, BravoProfile *thisAircraftProfile) {
    
    nlohmann::json st1;
    nlohmann::json st2;
    nlohmann::json st3;
    nlohmann::json st4;
    nlohmann::json st5;
    nlohmann::json st6;
    
    std::string stringState = "NOT_FOUND";
    std::string transitionButton = "NOT_FOUND";
    int intState = 0;
    APButtonLabel thisButton = APHDG;
    APButtonLabel thisLight = APHDG;
    
    st1 = j["STATE_TABLE"]["LIGHTSTATE"];
    
    for (auto& stateList: st1.items()) {
        st2=stateList.key();
        st3=stateList.value();
        st4 = st3[0];
        if (st2.is_string()) {
            stringState = st2.get<std::string>();
            intState = std::stoi(stringState);
            for (auto& transitionList: st4.items()) {
                st5 = transitionList.key();
                st6 = transitionList.value();
                if (st5.is_string()) {
                    thisButton = st5;
                    transitionButton = st5.get<std::string>();
                    
                }
                if ((st6.is_array()) && (st6.size() == 2) && (st6[0].is_number())) {
                    auto fromState = st6[0].get<int>();
                    auto toState = st6[1].get<int>();
                    thisAircraftProfile -> addStateTransition(thisButton, fromState, toState);
                } else {
                    if (st6.is_array()) {
                        for (int i = 0; i < st6.size(); i++) {
                            thisLight = st6[i];
                            std::string lightName = st6[i].get<std::string>();
                            if (transitionButton == "LIGHTS_ON") {
                                thisAircraftProfile -> addStateLightsOn(intState, thisLight);
                            }
                            if (transitionButton == "LIGHTS_OFF") {
                                thisAircraftProfile -> addStateLightsOff(intState, thisLight);
                            }
                        }
                    }
                }
            }
        }
    }
}



}  // end namespace nlohmann

void BravoJSON::jsonWrite(BravoProfile *thisProfile, const char* aircraftName) {

    
    fileName = jsonFileName(aircraftName);
    nlohmann::json jsonOutput;

    jsonOutput["Device"] = "HoneycombBravo";
    jsonOutput["AIRCRAFT"] = aircraftName;

    jsonOutput["HDG_BUTTON"] = thisProfile -> bHDG;
    jsonOutput["NAV_BUTTON"] = thisProfile -> bNAV;
    jsonOutput["APR_BUTTON"] = thisProfile -> bAPR;
    jsonOutput["REV_BUTTON"] = thisProfile -> bREV;
    jsonOutput["ALT_BUTTON"] = thisProfile -> bALT;
    jsonOutput["VS_BUTTON"]  = thisProfile -> bVS;
    jsonOutput["IAS_BUTTON"] = thisProfile -> bIAS;
    jsonOutput["AP_BUTTON"]  = thisProfile -> bAP;
    
    jsonOutput["IAS_ROTARY"] = thisProfile -> rIAS;
    jsonOutput["CRS_ROTARY"] = thisProfile -> rCRS;
    jsonOutput["HDG_ROTARY"] = thisProfile -> rHDG;
    jsonOutput["VS_ROTARY"]  = thisProfile -> rVS;
    jsonOutput["ALT_ROTARY"] = thisProfile -> rALT;
    
    jsonOutput["STATE_TABLE"] = thisProfile -> APstateMachine;
    
    if (lights -> APLightsActive()) {
        jsonOutput["AP_ANNUNCIATORS"] = { HDGLightMap, NAVLightMap, APRLightMap, REVLightMap, ALTLightMap, VSLightMap, IASLightMap, APLightMap };
    }
    else
        jsonOutput["AP_ANNUNCIATORS"] = "NOT_USED";


    jsonOutput["ANNUNCIATORS"] = {GreenLandingLeftLight, MasterWarningLight, EngineFireLight,LowOilPressureLight, LowFuelPressureLight, AntiIceLight, StarterEngagedLight, APULight, MasterCautionLight, VacuumLight, LowHydPressureLight, AuxFuelPumpLight, ParkingBrakeLight, LowVoltsLight, DoorLight};
    
    std::ofstream jsonOutStream(fileName);
    jsonOutStream << std::setw(4) << jsonOutput;
}


void setSingleCommandMap(APButtonLabel thisButton, SingleCommandMap* thisCommandMap, BravoProfile* thisAircraftProfile) {
    
    if (thisCommandMap != NULL) {
        
        SingleCommandMap::iterator it;
        
        for (it = thisCommandMap -> begin(); it != thisCommandMap -> end(); it++) {
            thisAircraftProfile -> addCustomCommand(thisButton, nlohmann::stringToToggle(it -> first), it -> second.c_str());
        }
    }
}

void BravoJSON::setAPButton(APButtonLabel thisButton, APButtonProfileData* thisAPButtonProfile, BravoProfile* thisAircraftProfile) {
    
    if (thisAPButtonProfile != NULL && (thisAircraftProfile != NULL)) {
        
        if (thisAPButtonProfile -> commandName != NULL) {
         
            thisAircraftProfile -> AutopilotButton(thisButton, thisAPButtonProfile -> commandName->c_str());
            
            if (thisAPButtonProfile -> customised)
                setSingleCommandMap(thisButton, thisAPButtonProfile -> customCommands, thisAircraftProfile);
        }
    }
 }


commandSpeed BravoJSON::stringToCommandSpeed(std::string speedString) {
    
    
    switch (hash_djb2a(speedString)) {
        case "slowest"_sh: return slowest; break;
        case "slow"_sh: return slow; break;
        case "medium"_sh: return medium; break;
        case "fast"_sh: return fast; break;
        case "fastest"_sh: return fastest; break;
        default: return slowest;
    }
}

void BravoJSON::setRotaryCommands(rotaryButtonLabel thisRotary,TwinRotaryProfile *thisTwinCommandProfile,  BravoProfile* thisAircraftProfile) {

    if ((thisTwinCommandProfile != NULL) && (thisAircraftProfile != NULL)) {
             
        const char* commandUp = thisTwinCommandProfile -> command1.commandName.c_str();
        const char* commandDown = thisTwinCommandProfile -> command2.commandName.c_str();
        
        if (thisTwinCommandProfile -> command1.dualSpeed) {
            commandSpeed slowSpeed = stringToCommandSpeed(thisTwinCommandProfile -> command1.slowSpeed);
            commandSpeed highSpeed = stringToCommandSpeed(thisTwinCommandProfile -> command1.highSpeed);
            thisAircraftProfile -> RotaryControl(thisRotary, commandUp, commandDown, slowSpeed, highSpeed);
        }
        else
        {   commandSpeed singleSpeed = stringToCommandSpeed(thisTwinCommandProfile -> command1.singleSpeed);
            thisAircraftProfile -> RotaryControl(thisRotary, commandUp, commandDown, singleSpeed);
        }
    }
}

void BravoJSON::setRotaryCustomCommands(rotaryButtonLabel thisRotary, toggleLabel thisToggle, TwinRotaryProfile *customCommands,  BravoProfile* thisAircraftProfile) {

    if ((customCommands != NULL) && (thisAircraftProfile != NULL)) {
             
        const char* commandUp = customCommands -> command1.commandName.c_str();
        const char* commandDown = customCommands -> command2.commandName.c_str();
        
        if (customCommands -> command1.dualSpeed) {
            commandSpeed slowSpeed = stringToCommandSpeed(customCommands -> command1.slowSpeed);
            commandSpeed highSpeed = stringToCommandSpeed(customCommands -> command1.highSpeed);
            thisAircraftProfile -> addCustomCommand(thisRotary, thisToggle, commandUp, commandDown, slowSpeed, highSpeed);
        }
        else
        {   commandSpeed singleSpeed = stringToCommandSpeed(customCommands -> command1.singleSpeed);
            thisAircraftProfile -> addCustomCommand(thisRotary, thisToggle, commandUp, commandDown, singleSpeed);
        }
    }
}



void BravoJSON::setRotaryCustomCommands(rotaryButtonLabel thisRotary, DualCommandMap *theseCustomCommands,  BravoProfile* thisAircraftProfile) {

    if ((theseCustomCommands != NULL) && (thisAircraftProfile != NULL)) {

        for (const auto &c : *theseCustomCommands)
        {  std::string key = c.first;
            TwinRotaryProfile commands = c.second;
            toggleLabel thisToggle = nlohmann::json(key);
            setRotaryCustomCommands(thisRotary, thisToggle, &commands, thisAircraftProfile);
        }

    }
}


void BravoJSON::setRotary(rotaryButtonLabel thisRotary, RotaryProfileData* thisRotaryProfile, BravoProfile* thisAircraftProfile) {
    
    if ((thisRotaryProfile != NULL) && (thisAircraftProfile != NULL)) {
        setRotaryCommands(thisRotary, &thisRotaryProfile -> defaultCommands, thisAircraftProfile);
        
        if (thisRotaryProfile -> customised == true) {
            setRotaryCustomCommands(thisRotary, &thisRotaryProfile -> customCommands, thisAircraftProfile);
        }
     }
}
    
void BravoJSON::setLandingAnnunciators(std::string thisName) {
    if ((thisName == "NOT_SET") || (thisName == "")) {
        lights -> customAnnunciatorDataRef(GreenLandingLeftLight, NULL);
    } else lights -> customAnnunciatorDataRef(GreenLandingLeftLight, thisName.c_str());
}


void BravoJSON::setAnnunciator(BravoLight thisLight, std::string thisName) {

    if ((thisName == "NOT_SET") || (thisName == "")) {
        lights -> customAnnunciatorDataRef(thisLight, NULL);
    }
    else lights -> customAnnunciatorDataRef(thisLight, thisName.c_str());
}

void BravoJSON::setAPAnnunciator(APButtonLabel thisLight, std::string thisName) {

    if ((thisName == "NOT_SET") || (thisName == "")) {
        lights -> addAutopilotLightDataRef(thisLight, NULL);
    }
    else lights -> addAutopilotLightDataRef(thisLight, thisName.c_str());
}


std::string BravoJSON::jsonFileName(const char* aircraftName) {
    
    return xplane -> xplaneDirectory() +  jsonDirectory + aircraftName + ".json";
}

bool BravoJSON::jsonFileExists(const char* aircraftName) {

    fileName = jsonFileName(aircraftName);

    return std::filesystem::exists(fileName);    
}


void BravoJSON::jsonRead(BravoProfile *thisAircraftProfile, const char* aircraftName) {
    
    if (jsonFileExists(aircraftName)) {
        
        fileName = jsonFileName(aircraftName);
        nlohmann::json jsonInput;
        
        std::ifstream jsonInStream(fileName);
        jsonInput = nlohmann::json::parse(jsonInStream);
        
        ProfileData *profileData = new ProfileData();
        
        profileData -> deviceName = jsonInput["Device"].get<std::string>();
        profileData -> aircraftName = jsonInput["AIRCRAFT"].get<std::string>();
        
        APButtonProfileData APHDGProfile = jsonInput["HDG_BUTTON"];
        APButtonProfileData APNAVProfile = jsonInput["NAV_BUTTON"];
        APButtonProfileData APAPRProfile = jsonInput["APR_BUTTON"];
        APButtonProfileData APREVProfile = jsonInput["REV_BUTTON"];
        APButtonProfileData APALTProfile = jsonInput["ALT_BUTTON"];
        APButtonProfileData APVSProfile  = jsonInput["VS_BUTTON"];
        APButtonProfileData APIASProfile = jsonInput["IAS_BUTTON"];
        APButtonProfileData APAPProfile  = jsonInput["AP_BUTTON"];
        
        RotaryProfileData RALT = jsonInput["ALT_ROTARY"];
        RotaryProfileData RVS  = jsonInput["VS_ROTARY"];
        RotaryProfileData RHDG = jsonInput["HDG_ROTARY"];
        RotaryProfileData RCRS = jsonInput["CRS_ROTARY"];
        RotaryProfileData RIAS = jsonInput["IAS_ROTARY"];
        
        AnnunciatorProfileData annunciators = jsonInput["ANNUNCIATORS"];
        
        setAPButton(APHDG, &APHDGProfile, thisAircraftProfile);
        setAPButton(APNAV, &APNAVProfile, thisAircraftProfile);
        setAPButton(APAPR, &APAPRProfile, thisAircraftProfile);
        setAPButton(APREV, &APREVProfile, thisAircraftProfile);
        setAPButton(APALT, &APALTProfile, thisAircraftProfile);
        setAPButton(APVS,  &APVSProfile,  thisAircraftProfile);
        setAPButton(APIAS, &APIASProfile, thisAircraftProfile);
        setAPButton(APAP,  &APAPProfile,  thisAircraftProfile);
        
        setRotary(RCALT, &RALT, thisAircraftProfile);
        setRotary(RCVS,  &RVS,  thisAircraftProfile);
        setRotary(RCHDG, &RHDG, thisAircraftProfile);
        setRotary(RCCRS, &RCRS, thisAircraftProfile);
        setRotary(RCIAS, &RIAS, thisAircraftProfile);
        
        thisAircraftProfile -> activateIncrDecrRotary();
        
        setLandingAnnunciators(annunciators.landingGearName);
        setAnnunciator(MasterWarningLight, annunciators.masterWarningName);
        setAnnunciator(EngineFireLight, annunciators.engineFireName);
        setAnnunciator(LowOilPressureLight, annunciators.lowOilPressureName);
        setAnnunciator(LowFuelPressureLight, annunciators.lowFuelPressureName);
        setAnnunciator(AntiIceLight, annunciators.antiIceName);
        setAnnunciator(StarterEngagedLight, annunciators.starterEngagedName);
        setAnnunciator(APULight, annunciators.APUName);
        setAnnunciator(MasterCautionLight, annunciators.masterCautionName);
        setAnnunciator(VacuumLight, annunciators.vacuumName);
        setAnnunciator(LowHydPressureLight, annunciators.LowHydPressureName);
        setAnnunciator(AuxFuelPumpLight, annunciators.auxFuelPumpName);
        setAnnunciator(ParkingBrakeLight, annunciators.parkingBrakeName);
        setAnnunciator(LowVoltsLight, annunciators.lowVoltsName);
        setAnnunciator(DoorLight, annunciators.doorName);
        
        if (stateModelPresent(jsonInput)) {
            setStateTransitions(jsonInput, thisAircraftProfile);
            thisAircraftProfile -> activateStateMachine();
        }
        
        if (APAnnunciatorsPresent(jsonInput)) {
            setAPAnnunciators(jsonInput, thisAircraftProfile);
        }
    }
}



