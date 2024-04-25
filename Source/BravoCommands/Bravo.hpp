//
//  Bravo.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 26/03/2023.
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


#ifndef Bravo_hpp
#define Bravo_hpp

#include "XPlane.hpp"
#include "BravoProfile.hpp"
#include "BravoJSON.hpp"

enum aircraftLabel {laminarAeroworks103, laminarAirbusA330, laminarALIA250, laminarBeechcraftBaron58, laminarBeechcraftKingAirC90B, laminarBoeing737, laminarCessna172SP,
    laminarCessna172G1000, laminarCessna172Floats, laminarCessnaCitationX, laminarCirrusSR22, laminarCirrusVisionSF50, laminarF4PhantonII, laminarF14Tomcat,
    laminarLancairEvolution, laminarMcDonnellDouglasMD82, laminarPiperPA18SuperCub, laminarRobinsonR22BetaII, laminarRobinsonR22BetaIIMarine, laminarSchleicherASK21,
    laminarSikorskyS76C, laminarStinsonL5Sentinel, laminarVansRV10, ziboBoeing737X, unknownAircraft
};

class Bravo {
    
public:
    
    Bravo(aircraftLabel aircraft);
    Bravo(std::string aircraft);
    ~Bravo();
    void bravoLaminarAeroworks103();
    void bravoLaminarAeroworks103Default(BravoProfile *thisAircraft);
    void bravoLaminarAirbusA330();
    void bravoLaminarAirbusA330Default(BravoProfile *thisAircraft);
    void bravoLaminarALIA250();
    void bravoLaminarALIA250Default(BravoProfile *thisAircraft);
    void bravoLaminarBeechcraftBaron58();
    void bravoLaminarBeechcraftBaron58Default(BravoProfile *thisAircraft);
    void bravoLaminarBeechcraftKingAirC90B();
    void bravoLaminarBeechcraftKingAirC90BDefault(BravoProfile *thisAircraft);
    void bravoLaminarBoeing737();
    void bravoLaminarBoeing737Default(BravoProfile *thisAircraft);
    void bravoLaminarCessna172SP();
    void bravoLaminarCessna172SPDefault(BravoProfile *thisAircraft);
    void bravoLaminarCessna172G1000();
    void bravoLaminarCessna172G1000Default(BravoProfile *thisAircraft);
    void bravoLaminarCessna172Floats();
    void bravoLaminarCessna172FloatsDefault(BravoProfile *thisAircraft);
    void bravoLaminarCessnaCitationX();
    void bravoLaminarCessnaCitationXDefault(BravoProfile *thisAircraft);
    void bravoLaminarCirrusSR22();
    void bravoLaminarCirrusSR22Default(BravoProfile *thisAircraft);
    void bravoLaminarCirrusVisionSF50();
    void bravoLaminarCirrusVisionSF50Default(BravoProfile *thisAircraft);
    void bravoLaminarF4PhantomII();
    void bravoLaminarF4PhantomIIDefault(BravoProfile *thisAircraft);
    void bravoLaminarF14Tomcat();
    void bravoLaminarF14TomcatDefault(BravoProfile *thisAircraft);
    void bravoLaminarLancairEvolution();
    void bravoLaminarLancairEvolutionDefault(BravoProfile *thisAircraft);
    void bravoLaminarMcDonnellDouglasMD82();
    void bravoLaminarMcDonnellDouglasMD82Default(BravoProfile *thisAircraft);
    void bravoLaminarPiperPA18SuperCub();
    void bravoLaminarPiperPA18SuperCubDefault(BravoProfile *thisAircraft);
    void bravoLaminarRobinsonR22BetaII();
    void bravoLaminarRobinsonR22BetaIIDefault(BravoProfile *thisAircraft);
    void bravoLaminarRobinsonR22BetaIIMarine();
    void bravoLaminarRobinsonR22BetaIIMarineDefault(BravoProfile *thisAircraft);
    void bravoLaminarSchleicherASK21();
    void bravoLaminarSchleicherASK21Default(BravoProfile *thisAircraft);
    void bravoLaminarSikorskyS76C();
    void bravoLaminarSikorskyS76CDefault(BravoProfile *thisAircraft);
    void bravoLaminarStinsonL5Sentinel();
    void bravoLaminarStinsonL5SentinelDefault(BravoProfile *thisAircraft);
    void bravoLaminarVansRV10();
    void bravoLaminarVansRV10Default(BravoProfile *thisAircraft);

    
    void bravoZiboBoeing737X();
    void bravoZiboBoeing737XDefault(BravoProfile *thisAircraft);

    void bravoUnknownAircraft(std::string aircraft);
    void bravoUnkownAircraftDefault(BravoProfile *thisAircraft);

    void JSONwrite(BravoProfile* thisProfile, const char* fileName);
    void JSONread(BravoProfile* thisProfile, const char* fileName);
    bool JSONfileExists(const char* fileName);

private:
    
    void reset();
    BravoProfile* currentAircraft = NULL;
    BravoJSON* jsonParser = NULL;
    
//    void newBlankControls();
/*
 
    HDG_Button* bHDG = NULL;
    NAV_Button* bNAV = NULL;
    APR_Button* bAPR = NULL;
    REV_Button* bREV = NULL;
    ALT_Button* bALT = NULL;
    VS_Button*  bVS  = NULL;
    IAS_Button* bIAS = NULL;
    AP_Button*  bAP  = NULL;

    StateMachine* APstateMachine = NULL;
    LightState*   APstate0       = NULL;
    LightState*   APstate1       = NULL;
    LightState*   APstate2       = NULL;
    LightState*   APstate3       = NULL;
    LightState*   APstate4       = NULL;
    LightState*   APstate5       = NULL;
    LightState*   APstate6       = NULL;
    LightState*   APstate7       = NULL;
    LightState*   APstate8       = NULL;
    LightState*   APstate9       = NULL;
    LightState*   APstate10      = NULL;
    LightState*   APstate11      = NULL;
    LightState*   APstate12      = NULL;
    LightState*   APstate13      = NULL;
    LightState*   APstate14      = NULL;
    LightState*   APstate15      = NULL;
    LightState*   APstate16      = NULL;
    LightState*   APstate17      = NULL;
    LightState*   APstate18      = NULL;
    LightState*   APstate19      = NULL;
    LightState*   APstate20      = NULL;
    LightState*   APstate21      = NULL;
    LightState*   APstate22      = NULL;
    LightState*   APstate23      = NULL;
    LightState*   APstate24      = NULL;
    LightState*   APstate25      = NULL;
    LightState*   APstate26      = NULL;
    LightState*   APstate27      = NULL;

    StateMachine* APLNAVstateMachine = NULL;
    LightState*   APLNAVstate0       = NULL;
    LightState*   APLNAVstate1       = NULL;
    LightState*   APLNAVstate2       = NULL;
    LightState*   APLNAVstate3       = NULL;
    LightState*   APLNAVstate4       = NULL;
    LightState*   APLNAVstate5       = NULL;
    LightState*   APLNAVstate6       = NULL;
    LightState*   APLNAVstate7       = NULL;
    LightState*   APLNAVstate8       = NULL;
    LightState*   APLNAVstate9       = NULL;
    LightState*   APLNAVstate10      = NULL;

    StateMachine* APVNAVstateMachine = NULL;
    LightState*   APVNAVstate0       = NULL;
    LightState*   APVNAVstate1       = NULL;
    LightState*   APVNAVstate2       = NULL;
    LightState*   APVNAVstate3       = NULL;
    LightState*   APVNAVstate4       = NULL;
    LightState*   APVNAVstate5       = NULL;
    
    XPCommand* cHDG  = NULL;
    XPCommand* cNAV  = NULL;
    XPCommand* eNAV1 = NULL;
    XPCommand* cAPR  = NULL;
    XPCommand* eAPR1 = NULL;
    XPCommand* cREV  = NULL;
    XPCommand* cALT  = NULL;
    XPCommand* cVS   = NULL;
    XPCommand* cIAS  = NULL;
    XPCommand* cAP   = NULL;
    XPCommand* eAP1  = NULL;
    XPCommand* eAP2  = NULL;
    XPCommand* eAP3  = NULL;

    Toggle* toggle1 = NULL;
    Toggle* toggle2 = NULL;
    Toggle* toggle3 = NULL;
    Toggle* toggle4 = NULL;
    Toggle* toggle5 = NULL;
    Toggle* toggle6 = NULL;
    Toggle* toggle7 = NULL;
    
    Switch* switch1 = NULL;
    Switch* switch2 = NULL;
    Switch* switch3 = NULL;
    Switch* switch4 = NULL;
    Switch* switch5 = NULL;
    Switch* switch6 = NULL;
    Switch* switch7 = NULL;
    Switch* switch8 = NULL;
    Switch* switch9 = NULL;
    Switch* switch10 = NULL;
    Switch* switch11 = NULL;
    Switch* switch12 = NULL;
    Switch* switch13 = NULL;
    Switch* switch14 = NULL;

    XPTwinCommands* eCRS1 = NULL;
    XPTwinCommands* eCRS2 = NULL;
    XPTwinCommands* eCRS3 = NULL;
    XPTwinCommands* eCRS4 = NULL;
    XPTwinCommands* eHDG1 = NULL;
    XPTwinCommands* cIAS1 = NULL;
    
    IAS_Rotary* rIAS = NULL;
    CRS_Rotary* rCRS = NULL;
    HDG_Rotary* rHDG = NULL;
    VS_Rotary*  rVS  = NULL;
    ALT_Rotary* rALT = NULL;

    IncrDecrRotary* rVAL = NULL;
    
    TrackingToggleSet* masterToggles = NULL;
    */
};



#endif /* Bravo_hpp */
