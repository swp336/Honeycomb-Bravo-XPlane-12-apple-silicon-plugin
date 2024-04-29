//
//  Bravo.cpp
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


#include "Bravo.hpp"
#include "XPlane.hpp"


Bravo::Bravo(aircraftLabel aircraft) {
         
    currentAircraft = new BravoProfile();
    jsonParser = new BravoJSON();
    
    std::string systemDir = xplane -> xplaneDirectory();
    
    switch (aircraft)  {

        case laminarAeroworks103:
            this->bravoLaminarAeroworks103();
            break;
        case laminarAirbusA330:
            this->bravoLaminarAirbusA330();
            break;
        case laminarALIA250:
            this->bravoLaminarALIA250();
            break;
        case laminarBeechcraftBaron58:
            this->bravoLaminarBeechcraftBaron58();
            break;
        case laminarBeechcraftKingAirC90B:
            this->bravoLaminarBeechcraftKingAirC90B();
            break;
        case laminarBoeing737:
            this->bravoLaminarBoeing737();
            break;
        case laminarCessna172SP:
            this->bravoLaminarCessna172SP();
            break;
        case laminarCessna172G1000:
            this->bravoLaminarCessna172G1000();
            break;
        case laminarCessna172Floats:
            this->bravoLaminarCessna172Floats();
            break;
        case laminarCessnaCitationX:
            this->bravoLaminarCessnaCitationX();
            break;
        case laminarCirrusSR22:
            this->bravoLaminarCirrusSR22();
            break;
        case laminarCirrusVisionSF50:
            this->bravoLaminarCirrusVisionSF50();
            break;
        case laminarF4PhantonII:
            this->bravoLaminarF4PhantomII();
            break;
        case laminarF14Tomcat:
            this->bravoLaminarF14Tomcat();
            break;
        case laminarLancairEvolution:
            this->bravoLaminarLancairEvolution();
            break;
        case laminarMcDonnellDouglasMD82:
            this->bravoLaminarMcDonnellDouglasMD82();
            break;
        case laminarPiperPA18SuperCub:
            this->bravoLaminarPiperPA18SuperCub();
            break;
        case laminarRobinsonR22BetaII:
            this->bravoLaminarRobinsonR22BetaII();
            break;
        case laminarRobinsonR22BetaIIMarine:
            this->bravoLaminarRobinsonR22BetaIIMarine();
            break;
        case laminarSchleicherASK21:
            this->bravoLaminarSchleicherASK21();
            break;
        case laminarSikorskyS76C:
            this->bravoLaminarSikorskyS76C();
            break;
        case laminarStinsonL5Sentinel:
            this->bravoLaminarStinsonL5Sentinel();
            break;
        case laminarVansRV10:
            this->bravoLaminarVansRV10();
        break;

        case ziboBoeing737X:
            this->bravoZiboBoeing737X();
        break;
            
        default: break;
    }
}

Bravo::Bravo(std::string aircraft) {
    
    currentAircraft = new BravoProfile();
    jsonParser = new BravoJSON();
    
    std::string systemDir = xplane -> xplaneDirectory();
 
    this -> bravoUnknownAircraft(aircraft);
}

Bravo::~Bravo() {
}

void Bravo::reset() {

    if (currentAircraft != NULL) delete currentAircraft;
}

void Bravo::JSONwrite(BravoProfile* thisProfile, const char* fileName) {
    jsonParser -> jsonWrite(thisProfile, fileName);
}

void Bravo::JSONread(BravoProfile* thisProfile, const char* fileName) {
    jsonParser -> jsonRead(thisProfile, fileName);
}

bool Bravo::JSONfileExists(const char *fileName) {
    
    return jsonParser -> jsonFileExists(fileName);
}


//**********************************************************************************************************************************************
//
//   AEROWORKS 103
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarAeroworks103() {
    
    const char* jsonFileName = "Aeroworks 103";
    
    bool read = JSONfileExists(jsonFileName);
    
    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarAeroworks103Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarAeroworks103Default(BravoProfile *thisAircraft) {
        
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow, fastest);
    thisAircraft -> RotaryControl(RCIAS, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow, fastest);
    thisAircraft -> activateIncrDecrRotary();
}



//**********************************************************************************************************************************************
//
//   AIRBUS A300-300
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarAirbusA330Default(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/trkfpa");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  "sim/autopilot/alt_vs");
    thisAircraft -> AutopilotButton(APIAS, "laminar/A333/autopilot/a_thr_toggle");
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");
    
    thisAircraft -> addCustomCommand(APHDG, TG1, "laminar/A333/autopilot/heading_knob_push");
    thisAircraft -> addCustomCommand(APHDG, TG2, "laminar/A333/autopilot/heading_knob_pull");
    
    thisAircraft -> addCustomCommand(APAPR, TG1, "laminar/A333/buttons/capt_ils_bars_push");
    thisAircraft -> addCustomCommand(APAPR, TG2, "laminar/A333/buttons/fo_ils_bars_push");

    thisAircraft -> addCustomCommand(APALT, TG1, "laminar/A333/autopilot/altitude_knob_push");
    thisAircraft -> addCustomCommand(APALT, TG2, "laminar/A333/autopilot/altitude_knob_pull");
    thisAircraft -> addCustomCommand(APALT, TG3, "laminar/A333/pull/baro/capt_std");
    thisAircraft -> addCustomCommand(APALT, TG4, "laminar/A333/push/baro/capt_std");
    thisAircraft -> addCustomCommand(APALT, TG5, "laminar/A333/pull/baro/fo_std");
    thisAircraft -> addCustomCommand(APALT, TG6, "laminar/A333/push/baro/fo_std");

    thisAircraft -> addCustomCommand(APIAS, TG1, "laminar/A333/autopilot/speed_knob_push");
    thisAircraft -> addCustomCommand(APIAS, TG2, "laminar/A333/autopilot/speed_knob_pull");
    thisAircraft -> addCustomCommand(APIAS, TG3, "sim/autopilot/knots_mach_toggle");
    thisAircraft -> addCustomCommand(APAP, TG1, "sim/autopilot/servos2_toggle");
    
    thisAircraft -> RotaryControl(RCIAS, "sim/autopilot/airspeed_up", "sim/autopilot/airspeed_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/autopilot/vertical_speed_up", "sim/autopilot/vertical_speed_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCALT, TG6, "laminar/A333/autopilot/alt_step_right", "laminar/A333/autopilot/alt_step_left", slow);
    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG4, "sim/instruments/barometer_copilot_up", "sim/instruments/barometer_copilot_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG3, "sim/instruments/barometer_stby_up", "sim/instruments/barometer_stby_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_hold_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/EFIS/EFIS_vor_on");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APIAS, "sim/cockpit2/autopilot/speed_status");

    lights -> addAutopilotLightDataRef(APAP,  "laminar/A333/annun/autopilot/ap1_mode");
}

void Bravo::bravoLaminarAirbusA330() {

    const char* jsonFileName = "Airbus 330-300";
    
    bool read = JSONfileExists(jsonFileName);
    
    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarAirbusA330Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}


//**********************************************************************************************************************************************
//
//   ALIA 250
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarALIA250() {

    const char* jsonFileName = "ALIA 250";
    
    bool read = JSONfileExists(jsonFileName);
    
    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarALIA250Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarALIA250Default(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/GPS/g1000n1_hdg");
    thisAircraft -> AutopilotButton(APNAV, "sim/GPS/g1000n1_nav");
    thisAircraft -> AutopilotButton(APAPR, "sim/GPS/g1000n1_apr");
    thisAircraft -> AutopilotButton(APREV, "sim/GPS/g1000n1_bc");
    thisAircraft -> AutopilotButton(APALT, "sim/GPS/g1000n1_alt");
    thisAircraft -> AutopilotButton(APVS,  "sim/GPS/g1000n1_vs");
    thisAircraft -> AutopilotButton(APIAS, "sim/GPS/g1000n1_flc");
    thisAircraft -> AutopilotButton(APAP,  "sim/GPS/g1000n1_ap");
    
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g1000n1_nav12");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g1000n1_com12");
    thisAircraft -> addCustomCommand(APHDG, TG4, "sim/GPS/g1000n1_softkey6");
    thisAircraft -> addCustomCommand(APHDG, TG1, "sim/GPS/g1000n1_hdg_sync");

    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g1000n1_nav_ff");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g1000n1_com_ff");
    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/g1000n3_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG1, "sim/GPS/g1000n1_crs_sync");

    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/g1000n3_proc");

    thisAircraft -> addCustomCommand(APREV, TG4, "sim/GPS/g1000n3_direct");

    thisAircraft -> addCustomCommand(APALT, TG4, "sim/GPS/g1000n3_menu");

    thisAircraft -> addCustomCommand(APVS, TG4, "sim/GPS/g1000n3_clr");

    thisAircraft -> addCustomCommand(APIAS, TG4, "sim/GPS/g1000n3_cursor");

    thisAircraft -> addCustomCommand(APAP, TG4, "sim/GPS/g1000n3_ent");

    thisAircraft -> RotaryControl(RCALT, "sim/GPS/g1000n1_alt_inner_up", "sim/GPS/g1000n1_alt_inner_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/GPS/g1000n1_nose_up", "sim/GPS/g1000n1_nose_down", slow);
    thisAircraft -> RotaryControl(RCHDG, "sim/GPS/g1000n1_hdg_up", "sim/GPS/g1000n1_hdg_down", slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/GPS/g1000n1_crs_up", "sim/GPS/g1000n1_crs_down", slow, fastest);
    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/GPS/g1000n1_baro_up", "sim/GPS/g1000n1_baro_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/GPS/g1000n3_range_down", "sim/GPS/g1000n3_range_up", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g1000n1_nav_outer_up", "sim/GPS/g1000n1_nav_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g1000n1_com_outer_up", "sim/GPS/g1000n1_com_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g1000n3_fms_outer_up", "sim/GPS/g1000n3_fms_outer_down", slow);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g1000n1_nav_inner_up", "sim/GPS/g1000n1_nav_inner_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g1000n1_com_inner_up", "sim/GPS/g1000n1_com_inner_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g1000n3_fms_inner_up", "sim/GPS/g1000n3_fms_inner_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APREV, "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_armed");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APIAS, "sim/cockpit2/autopilot/speed_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");

}


//**********************************************************************************************************************************************
//
//   BEECHCRAFT BARON 58
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarBeechcraftBaron58() {

    const char* jsonFileName = "Beechcraft Baron 58";
    
    bool read = JSONfileExists(jsonFileName);
    
    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarBeechcraftBaron58Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarBeechcraftBaron58Default(BravoProfile *thisAircraft) {

    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/heading");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, "sim/autopilot/back_course");
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  NULL);
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g430n1_nav_com_tog");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g430n1_cdi");
    thisAircraft -> addCustomCommand(APHDG, TG4, "sim/radios/com2_standy_flip");
    thisAircraft -> addCustomCommand(APHDG, TG3, "sim/radios/nav2_standy_flip");
    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/radios/adf1_standy_flip");

    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g430n1_nav_ff");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g430n1_fpl");

    thisAircraft -> addCustomCommand(APAPR, TG6, "sim/GPS/g430n1_com_ff");
    thisAircraft -> addCustomCommand(APAPR, TG5, "sim/GPS/g430n1_proc");

    thisAircraft -> addCustomCommand(APREV, TG5, "sim/GPS/g430n1_direct");

    thisAircraft -> addCustomCommand(APALT, TG5, "sim/GPS/g430n1_menu");
    thisAircraft -> addCustomCommand(APALT, TG2, "sim/instruments/barometer_copilot_std");
    thisAircraft -> addCustomCommand(APALT, TG1, "sim/instruments/barometer_std");

    thisAircraft -> addCustomCommand(APVS, TG5, "sim/GPS/g430n1_clr");

    thisAircraft -> addCustomCommand(APIAS, TG5, "sim/GPS/g430n1_cursor");

    thisAircraft -> addCustomCommand(APAP, TG5, "sim/GPS/g430n1_ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g430n1_fine_up", "sim/GPS/g430n1_fine_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g430n1_page_up", "sim/GPS/g430n1_page_dn", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/radios/stby_com2_fine_up_833", "sim/radios/stby_com2_fine_down_833", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG3, "sim/radios/stby_nav2_fine_up", "sim/radios/stby_nav2_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG2, "sim/radios/stby_adf1_ones_tens_up", "sim/radios/stby_adf1_ones_tens_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG1, "sim/transponder/transponder_up", "sim/transponder/transponder_dn", slow);

    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs_HSI_up", "sim/radios/obs_HSI_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g430n1_coarse_up", "sim/GPS/g430n1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g430n1_chapter_up", "sim/GPS/g430n1_chapter_dn", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/radios/stby_com2_coarse_up", "sim/radios/stby_com2_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG3, "sim/radios/stby_nav2_coarse_up", "sim/radios/stby_nav2_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG2, "sim/radios/stby_adf1_hundreds_thous_up", "sim/radios/stby_adf1_hundreds_thous_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG1, "sim/radios/transponder_1000_up", "sim/radios/transponder_1000_down", slow);

    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCHDG, TG6, "sim/radios/adf1_card_up", "sim/radios/adf1_card_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCHDG, TG5, "sim/GPS/g430n1_zoom_out", "sim/GPS/g430n1_zoom_in", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG2, "sim/radios/adf1_power_mode_1", "sim/radios/adf1_power_mode_0", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG1, "sim/radios/transponder_100_up", "sim/radios/transponder_100_down", slow);

    thisAircraft -> RotaryControl(RCVS, "sim/autopilot/nose_up_pitch_mode", "sim/autopilot/nose_down_pitch_mode", slow);
    thisAircraft -> addCustomCommand(RCVS, TG1, "sim/radios/transponder_10_up", "sim/radios/transponder_10_down", slow);

    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/instruments/barometer_copilot_up", "sim/instruments/barometer_copilot_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG1, "sim/radios/transponder_ones_up", "sim/radios/transponder_ones_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_mode");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/autopilot_on");
}



//**********************************************************************************************************************************************
//
//   BEECHCRAFT KING AIR C90B
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarBeechcraftKingAirC90B() {

    const char* jsonFileName = "Beechcraft King Air C90B";
    
    bool read = JSONfileExists(jsonFileName);
    
    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarBeechcraftKingAirC90BDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarBeechcraftKingAirC90BDefault(BravoProfile *thisAircraft) {

    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/heading");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, "sim/autopilot/back_course");
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  "sim/autopilot/vertical_speed");
    thisAircraft -> AutopilotButton(APIAS, "sim/autopilot/speed_hold");
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/transponder/transponder_ident");
    thisAircraft -> addCustomCommand(APHDG, TG4, "sim/GPS/g430n2_nav_com_tog");
    thisAircraft -> addCustomCommand(APHDG, TG3, "sim/GPS/g430n2_cdi");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g430n1_cdi");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g430n1_nav_com_tog");

    thisAircraft -> addCustomCommand(APNAV, TG1, "laminar/c90/avionics/switch/crs_sel");
    thisAircraft -> addCustomCommand(APNAV, TG2, "laminar/c90/avionics/switch/crs_sync_sel");
    thisAircraft -> addCustomCommand(APNAV, TG3, "sim/GPS/g430n2_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/g430n2_nav_ff");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g430n1_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g430n1_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG3, "sim/GPS/g430n2_proc");
    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/g430n2_com_ff");
    thisAircraft -> addCustomCommand(APAPR, TG5, "sim/GPS/g430n1_proc");
    thisAircraft -> addCustomCommand(APAPR, TG6, "sim/GPS/g430n1_com_ff");

    thisAircraft -> addCustomCommand(APREV, TG3, "sim/GPS/g430n2_direct");
    thisAircraft -> addCustomCommand(APREV, TG5, "sim/GPS/g430n1_direct");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/autopilot/altitude_arm");
    thisAircraft -> addCustomCommand(APALT, TG2, "laminar/c90/autopilot/switch/altSel100");
    thisAircraft -> addCustomCommand(APALT, TG3, "sim/GPS/g430n2_menu");
    thisAircraft -> addCustomCommand(APALT, TG5, "sim/GPS/g430n1_menu");

    thisAircraft -> addCustomCommand(APVS, TG1, "sim/autopilot/climb");
    thisAircraft -> addCustomCommand(APVS, TG2, "sim/autopilot/descend");
    thisAircraft -> addCustomCommand(APVS, TG3, "sim/GPS/g430n2_clr");
    thisAircraft -> addCustomCommand(APVS, TG5, "sim/GPS/g430n1_clr");

    thisAircraft -> addCustomCommand(APIAS, TG3, "sim/GPS/g430n2_cursor");
    thisAircraft -> addCustomCommand(APIAS, TG5, "sim/GPS/g430n1_cursor");

    thisAircraft -> addCustomCommand(APAP, TG3, "sim/GPS/g430n2_ent");
    thisAircraft -> addCustomCommand(APAP, TG5, "sim/GPS/g430n1_ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g430n1_fine_up", "sim/GPS/g430n1_fine_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g430n1_page_up", "sim/GPS/g430n1_page_dn", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g430n2_fine_up", "sim/GPS/g430n2_fine_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG3, "sim/GPS/g430n2_page_up", "sim/GPS/g430n2_page_dn", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG2, "sim/transponder/transponder_12_up", "sim/transponder/transponder_12_down", slow, fastest);

    thisAircraft -> RotaryControl(RCCRS, NULL, NULL, slow, fastest);
    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g430n1_coarse_up", "sim/GPS/g430n1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g430n1_chapter_up", "sim/GPS/g430n1_chapter_dn", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g430n2_coarse_up", "sim/GPS/g430n2_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG3, "sim/GPS/g430n2_chapter_up", "sim/GPS/g430n2_chapter_dn", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG2, "sim/transponder/transponder_34_up", "sim/transponder/transponder_34_down", slow, fastest);

    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCHDG, TG6, "sim/radios/obs_HSI_up", "sim/radios/obs_HSI_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCHDG, TG5, "sim/autopilot/hsi_select_up", "sim/autopilot/hsi_select_down", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG2, "laminar/c90/avionics/ctl92_xpdr/mode_up", "laminar/c90/avionics/ctl92_xpdr/mode_dn", slow);

    thisAircraft -> RotaryControl(RCVS, "sim/autopilot/nose_up", "sim/autopilot/nose_down", slow);

    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/instruments/barometer_copilot_up", "sim/instruments/barometer_copilot_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight
    lights -> customAnnunciatorDataRef(DoorLight, "laminar/c90/lighting/annun/cabin_door");
    lights -> customAnnunciatorDataRef(DoorLight, "laminar/c90/lighting/annun/baggage_door");
    lights -> customAnnunciatorDataRef(AuxFuelPumpLight, "laminar/c90/lighting/annun/no_fuel_xfr_Lb");
    
    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_mode");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APREV, "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APIAS, "sim/cockpit2/autopilot/speed_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");
}



//**********************************************************************************************************************************************
//
//   BOEING 737
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarBoeing737() {
 
    const char* jsonFileName = "Boeing 737-800";
    
    bool read = JSONfileExists(jsonFileName);
    
    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarBoeing737Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarBoeing737Default(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "laminar/B738/autopilot/hdg_sel_press");
    thisAircraft -> AutopilotButton(APNAV, "laminar/B738/autopilot/lnav_press");
    thisAircraft -> AutopilotButton(APAPR, "laminar/B738/autopilot/app_press");
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "laminar/B738/autopilot/alt_hld_press");
    thisAircraft -> AutopilotButton(APVS,  "laminar/B738/autopilot/vs_press");
    thisAircraft -> AutopilotButton(APIAS, "laminar/B738/autopilot/speed_press");
    thisAircraft -> AutopilotButton(APAP,  "laminar/B738/autopilot/cmd_a_press");

    thisAircraft -> addCustomCommand(APHDG, TG1, "laminar/B738/EFIS_control/capt/push_button/ctr_press");    // Display selected information content on PFD
    thisAircraft -> addCustomCommand(APHDG, TG2, "laminar/B738/EFIS_control/capt/push_button/tfc_press");    // Display air traffic on PFD

    thisAircraft -> addCustomCommand(APNAV, TG1, "laminar/B738/autopilot/vnav_press");
  
    thisAircraft -> addCustomCommand(APAPR, TG1, "laminar/B738/autopilot/vorloc_press");
    
    thisAircraft -> addCustomCommand(APALT, TG1, "laminar/B738/EFIS_control/capt/push_button/std_press");     // move pilot from QNH to STD air pressure - to go back to QNH change pressure with rotary
    thisAircraft -> addCustomCommand(APALT, TG2, "laminar/B738/EFIS_control/capt/push_button/rst_press");     // reset pilot minimums - resets to zero and removes from display.  to reactivate, change minimums with rotary to required altitude
    thisAircraft -> addCustomCommand(APALT, TG3, "laminar/B738/EFIS_control/fo/push_button/std_press");       // move copilot from QNH to STD air pressure - to go back to QNH change pressure with rotary
    thisAircraft -> addCustomCommand(APALT, TG4, "laminar/B738/EFIS_control/fo/push_button/rst_press");       // reset copilot minimums - resets to zero and removes from display.  to reactivate, change minimums with rotary to required altitude

    thisAircraft -> addCustomCommand(APVS,  TG1, "laminar/B738/autopilot/lvl_chg_press");
    
    thisAircraft -> addCustomCommand(APAP,  TG1, "laminar/B738/autopilot/cmd_b_press");
    thisAircraft -> addCustomCommand(APAP,  TG2, "laminar/B738/autopilot/cws_a_press");
    thisAircraft -> addCustomCommand(APAP,  TG3, "laminar/B738/autopilot/cws_b_press");

    thisAircraft -> RotaryControl(RCIAS, "sim/autopilot/airspeed_up", "sim/autopilot/airspeed_down", slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs_HSI_up", "sim/radios/obs_HSI_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/autopilot/vertical_speed_up", "sim/autopilot/vertical_speed_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/radios/copilot_obs_HSI_up", "sim/radios/copilot_obs_HSI_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCHDG, TG6, "sim/instruments/map_zoom_out", "sim/instruments/map_zoom_in", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG5, "laminar/B738/autopilot/bank_angle_up", "laminar/B738/autopilot/bank_angle_dn", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/instruments/EFIS_mode_up", "sim/instruments/EFIS_mode_dn", slow);          // sim/instruments/EFIS_mode_up

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);                                     // set altitude barometric pressure on pilot display
    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/instruments/barometer_copilot_up", "sim/instruments/barometer_copilot_down", slow);                     // set altitude barometric pressure on copilot display
    thisAircraft -> addCustomCommand(RCALT, TG4, "sim/instruments/dh_ref_up", "sim/instruments/dh_ref_down", slow, fastest);                                  // set minimums baro and radio on pilot display
    thisAircraft -> addCustomCommand(RCALT, TG3, "sim/instruments/dh_ref_copilot_up", "sim/instruments/dh_ref_copilot_down", slow, fastest);                  // set minimums baro and radio on copilot display
    thisAircraft -> addCustomCommand(RCALT, TG2, "laminar/B738/EFIS_control/capt/baro_in_hpa_up", "laminar/B738/EFIS_control/capt/baro_in_hpa_dn", slow);     // switch captain baro between HPA and IN
    thisAircraft -> addCustomCommand(RCALT, TG1, "laminar/B738/EFIS_control/fo/baro_in_hpa_up", "laminar/B738/EFIS_control/fo/baro_in_hpa_dn", slow);         // switch copilot baro between HPA and IN

    thisAircraft -> activateIncrDecrRotary();
     
    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> addAutopilotLightDataRef(APHDG, "laminar/B738/autopilot/hdg_sel_status");
    lights -> addAutopilotLightDataRef(APNAV, "laminar/B738/autopilot/lnav_status");
    lights -> addAutopilotLightDataRef(APNAV, "laminar/B738/autopilot/vnav_status1");
    lights -> addAutopilotLightDataRef(APAPR, "laminar/B738/autopilot/app_status");
    lights -> addAutopilotLightDataRef(APAPR, "laminar/B738/autopilot/vorloc_status");
    lights -> addAutopilotLightDataRef(APALT, "laminar/B738/autopilot/alt_hld_status");
    lights -> addAutopilotLightDataRef(APVS,  "laminar/B738/autopilot/vs_status");
    lights -> addAutopilotLightDataRef(APVS,  "laminar/B738/autopilot/lvl_chg_status");
    lights -> addAutopilotLightDataRef(APIAS, "laminar/B738/autopilot/speed_status1");

    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cmd_a_status");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cmd_b_status");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cws_a_status");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cws_b_status");
    
    //laminar/B738/annunciator/eng1_valve_closed - engine cutoff switch 0 = idle 1 = cutoff
    //sim/autopilot/fdir_command_bars_toggle - pilot flight director on/off
    //sim/autopilot/fdir_command_bars_toggle - first officer flight director on/off
}



//**********************************************************************************************************************************************
//
//   CESSNA 172 SP
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarCessna172SPDefault(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/heading");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, "sim/autopilot/back_course");
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  "sim/autopilot/vertical_speed");
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");
  
    thisAircraft -> RotaryControl(RCIAS, NULL, NULL);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs1_up", "sim/radios/obs1_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/autopilot/vertical_speed_up", "sim/autopilot/vertical_speed_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);

    
    thisAircraft -> addCustomCommand(APHDG, TG3, "sim/GPS/g430n2_cdi");
    thisAircraft -> addCustomCommand(APHDG, TG4, "sim/GPS/g430n2_nav_com_tog");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g430n1_cdi");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g430n1_nav_com_tog");

    thisAircraft -> addCustomCommand(APNAV, TG3, "sim/GPS/g430n2_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/g430n2_nav_ff");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g430n1_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g430n1_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG3, "sim/GPS/g430n2_proc");
    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/g430n2_com_ff");
    thisAircraft -> addCustomCommand(APAPR, TG5, "sim/GPS/g430n1_proc");
    thisAircraft -> addCustomCommand(APAPR, TG6, "sim/GPS/g430n1_com_ff");

    thisAircraft -> addCustomCommand(APREV, TG3, "sim/GPS/g430n2_direct");
    thisAircraft -> addCustomCommand(APREV, TG5, "sim/GPS/g430n1_direct");

    thisAircraft -> addCustomCommand(APALT, TG3, "sim/GPS/g430n2_menu");
    thisAircraft -> addCustomCommand(APALT, TG5, "sim/GPS/g430n1_menu");

    thisAircraft -> addCustomCommand(APVS, TG3, "sim/GPS/g430n2_clr");
    thisAircraft -> addCustomCommand(APVS, TG5, "sim/GPS/g430n1_clr");

    thisAircraft -> addCustomCommand(APIAS, TG1, "sim/radios/adf1_standy_flip");
    thisAircraft -> addCustomCommand(APIAS, TG2, "sim/radios/adf1_standy_flip");
    thisAircraft -> addCustomCommand(APIAS, TG3, "sim/GPS/g430n2_cursor");
    thisAircraft -> addCustomCommand(APIAS, TG5, "sim/GPS/g430n1_cursor");

    thisAircraft -> addCustomCommand(APAP, TG3, "sim/GPS/g430n2_ent");
    thisAircraft -> addCustomCommand(APAP, TG5, "sim/GPS/g430n1_ent");
    
    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g430n1_fine_up", "sim/GPS/g430n1_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g430n1_page_up", "sim/GPS/g430n1_page_dn", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g430n2_fine_up", "sim/GPS/g430n2_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG3, "sim/GPS/g430n2_page_up", "sim/GPS/g430n2_page_dn", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g430n1_coarse_up", "sim/GPS/g430n1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g430n1_chapter_up", "sim/GPS/g430n1_chapter_dn", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g430n2_coarse_up", "sim/GPS/g430n2_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG3, "sim/GPS/g430n2_chapter_up", "sim/GPS/g430n2_chapter_dn", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG6, "sim/radios/obs1_up", "sim/radios/obs1_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCHDG, TG5, "sim/radios/copilot_obs2_up", "sim/radios/copilot_obs2_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/radios/adf1_card_up", "sim/radios/adf1_card_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCHDG, TG3, "sim/instruments/DG_sync_up", "sim/instruments/DG_sync_down", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG2, "sim/radios/stby_adf1_hundreds_thous_up", "sim/radios/stby_adf1_hundreds_thous_down", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG1, "sim/radios/stby_adf1_ones_tens_up", "sim/radios/stby_adf1_ones_tens_down", slow, fastest);

    thisAircraft -> activateIncrDecrRotary();
    
    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight
    lights -> customAnnunciatorDataRef(LowHydPressureLight, NULL);       // the default Cessna Skyhawk doesn't appear to update any hydraulic pressure datarefs, so turn this off to avoid spurious false alerts
    
    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/gpss_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APREV, "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/heading_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/gpss_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/vvi_status");


/*    thisAircraft -> addStateTransition(APHDG, 0, 1);
    thisAircraft -> addStateTransition(APNAV, 0, 5);
    thisAircraft -> addStateTransition(APAPR, 0, 0);
    thisAircraft -> addStateTransition(APREV, 0, 0);
    thisAircraft -> addStateTransition(APALT, 0, 0);
    thisAircraft -> addStateTransition(APVS,  0, 0);
    thisAircraft -> addStateTransition(APIAS, 0, 0);
    thisAircraft -> addStateTransition(APAP,  0, 0);
    thisAircraft -> addStateLightsOff(0, APHDG, APNAV, APAPR, APREV, APALT, APVS, APIAS, APAP);
    
    thisAircraft -> addStateTransition(APHDG, 1, 1);
    thisAircraft -> addStateTransition(APNAV, 1, 5);
    thisAircraft -> addStateTransition(APAPR, 1, 2);
    thisAircraft -> addStateTransition(APREV, 1, 4);
    thisAircraft -> addStateTransition(APALT, 1, 11);
    thisAircraft -> addStateTransition(APVS,  1, 12);
    thisAircraft -> addStateTransition(APIAS, 1, 1);
    thisAircraft -> addStateTransition(APAP,  1, 0);
    thisAircraft -> addStateLightsOn(1, APHDG, APAP);
    thisAircraft -> addStateLightsOff(1, APNAV, APAPR, APREV);

    thisAircraft -> addStateTransition(APHDG, 2, 1);
    thisAircraft -> addStateTransition(APNAV, 2, 5);
    thisAircraft -> addStateTransition(APAPR, 2, 1);
    thisAircraft -> addStateTransition(APREV, 2, 3);
    thisAircraft -> addStateTransition(APALT, 2, 13);
    thisAircraft -> addStateTransition(APVS,  2, 14);
    thisAircraft -> addStateTransition(APIAS, 2, 2);
    thisAircraft -> addStateTransition(APAP,  2, 0);
    thisAircraft -> addStateLightsOn(2, APNAV, APAPR);

    thisAircraft -> addStateTransition(APHDG, 3, 1);
    thisAircraft -> addStateTransition(APNAV, 3, 5);
    thisAircraft -> addStateTransition(APAPR, 3, 1);
    thisAircraft -> addStateTransition(APREV, 3, 1);
    thisAircraft -> addStateTransition(APALT, 3, 15);
    thisAircraft -> addStateTransition(APVS,  3, 16);
    thisAircraft -> addStateTransition(APIAS, 3, 3);
    thisAircraft -> addStateTransition(APAP,  3, 0);
    thisAircraft -> addStateLightsOn(3, APAPR);

    thisAircraft -> addStateTransition(APHDG, 4, 1);
    thisAircraft -> addStateTransition(APNAV, 4, 10);
    thisAircraft -> addStateTransition(APAPR, 4, 1);
    thisAircraft -> addStateTransition(APREV, 4, 1);
    thisAircraft -> addStateTransition(APALT, 4, 17);
    thisAircraft -> addStateTransition(APVS,  4, 18);
    thisAircraft -> addStateTransition(APIAS, 4, 4);
    thisAircraft -> addStateTransition(APAP,  4, 0);
    thisAircraft -> addStateLightsOn(4, APAPR, APNAV, APREV);

    thisAircraft -> addStateTransition(APHDG, 5, 1);
    thisAircraft -> addStateTransition(APNAV, 5, 5);
    thisAircraft -> addStateTransition(APAPR, 5, 6);
    thisAircraft -> addStateTransition(APREV, 5, 8);
    thisAircraft -> addStateTransition(APALT, 5, 19);
    thisAircraft -> addStateTransition(APVS,  5, 20);
    thisAircraft -> addStateTransition(APIAS, 5, 5);
    thisAircraft -> addStateTransition(APAP,  5, 0);
    thisAircraft -> addStateLightsOn(5, APNAV, APAP);
    thisAircraft -> addStateLightsOff(5, APHDG, APREV, APAPR);

    thisAircraft -> addStateTransition(APHDG, 6, 1);
    thisAircraft -> addStateTransition(APNAV, 6, 9);
    thisAircraft -> addStateTransition(APAPR, 6, 5);
    thisAircraft -> addStateTransition(APREV, 6, 7);
    thisAircraft -> addStateTransition(APALT, 6, 21);
    thisAircraft -> addStateTransition(APVS,  6, 22);
    thisAircraft -> addStateTransition(APIAS, 6, 6);
    thisAircraft -> addStateTransition(APAP,  6, 0);
    thisAircraft -> addStateLightsOn(6, APAPR);

    thisAircraft -> addStateTransition(APHDG, 7, 1);
    thisAircraft -> addStateTransition(APNAV, 7, 9);
    thisAircraft -> addStateTransition(APAPR, 7, 5);
    thisAircraft -> addStateTransition(APREV, 7, 5);
    thisAircraft -> addStateTransition(APALT, 7, 23);
    thisAircraft -> addStateTransition(APVS,  7, 24);
    thisAircraft -> addStateTransition(APIAS, 7, 7);
    thisAircraft -> addStateTransition(APAP,  7, 0);
    thisAircraft -> addStateLightsOn(7, APREV);

    thisAircraft -> addStateTransition(APHDG, 8, 1);
    thisAircraft -> addStateTransition(APNAV, 8, 9);
    thisAircraft -> addStateTransition(APAPR, 8, 5);
    thisAircraft -> addStateTransition(APREV, 8, 5);
    thisAircraft -> addStateTransition(APALT, 8, 23);
    thisAircraft -> addStateTransition(APVS,  8, 24);
    thisAircraft -> addStateTransition(APIAS, 8, 8);
    thisAircraft -> addStateTransition(APAP,  8, 0);
    thisAircraft -> addStateLightsOn(8, APAPR, APREV);

    thisAircraft -> addStateTransition(APHDG, 9, 1);
    thisAircraft -> addStateTransition(APNAV, 9, 9);
    thisAircraft -> addStateTransition(APAPR, 9, 5);
    thisAircraft -> addStateTransition(APREV, 9, 5);
    thisAircraft -> addStateTransition(APALT, 9, 23);
    thisAircraft -> addStateTransition(APVS,  9, 24);
    thisAircraft -> addStateTransition(APIAS, 9, 9);
    thisAircraft -> addStateTransition(APAP,  9, 0);
    thisAircraft -> addStateLightsOff(9, APREV);

    thisAircraft -> addStateTransition(APHDG, 10, 1);
    thisAircraft -> addStateTransition(APNAV, 10, 5);
    thisAircraft -> addStateTransition(APAPR, 10, 1);
    thisAircraft -> addStateTransition(APREV, 10, 7);
    thisAircraft -> addStateTransition(APALT, 10, 25);
    thisAircraft -> addStateTransition(APVS,  10, 26);
    thisAircraft -> addStateTransition(APIAS, 10, 10);
    thisAircraft -> addStateTransition(APAP,  10, 0);
    thisAircraft -> addStateLightsOff(10, APREV);

    thisAircraft -> addStateTransition(APHDG, 11, 1);
    thisAircraft -> addStateTransition(APNAV, 11, 5);
    thisAircraft -> addStateTransition(APAPR, 11, 2);
    thisAircraft -> addStateTransition(APREV, 11, 4);
    thisAircraft -> addStateTransition(APALT, 11, 11);
    thisAircraft -> addStateTransition(APVS,  11, 12);
    thisAircraft -> addStateTransition(APIAS, 11, 11);
    thisAircraft -> addStateTransition(APAP,  11, 0);
    thisAircraft -> addStateLightsOn(11, APALT);
    thisAircraft -> addStateLightsOff(11, APVS);

    thisAircraft -> addStateTransition(APHDG, 12, 1);
    thisAircraft -> addStateTransition(APNAV, 12, 5);
    thisAircraft -> addStateTransition(APAPR, 12, 2);
    thisAircraft -> addStateTransition(APREV, 12, 4);
    thisAircraft -> addStateTransition(APALT, 12, 11);
    thisAircraft -> addStateTransition(APVS,  12, 12);
    thisAircraft -> addStateTransition(APIAS, 12, 12);
    thisAircraft -> addStateTransition(APAP,  12, 0);
    thisAircraft -> addStateLightsOn(12, APVS);
    thisAircraft -> addStateLightsOff(12, APALT);

    thisAircraft -> addStateTransition(APHDG, 13, 1);
    thisAircraft -> addStateTransition(APNAV, 13, 5);
    thisAircraft -> addStateTransition(APAPR, 13, 1);
    thisAircraft -> addStateTransition(APREV, 13, 3);
    thisAircraft -> addStateTransition(APALT, 13, 13);
    thisAircraft -> addStateTransition(APVS,  13, 14);
    thisAircraft -> addStateTransition(APIAS, 13, 13);
    thisAircraft -> addStateTransition(APAP,  13, 0);
    thisAircraft -> addStateLightsOn(13, APALT);
    thisAircraft -> addStateLightsOff(13, APVS);

    thisAircraft -> addStateTransition(APHDG, 14, 1);
    thisAircraft -> addStateTransition(APNAV, 14, 5);
    thisAircraft -> addStateTransition(APAPR, 14, 1);
    thisAircraft -> addStateTransition(APREV, 14, 3);
    thisAircraft -> addStateTransition(APALT, 14, 13);
    thisAircraft -> addStateTransition(APVS,  14, 14);
    thisAircraft -> addStateTransition(APIAS, 14, 14);
    thisAircraft -> addStateTransition(APAP,  14, 0);
    thisAircraft -> addStateLightsOn(14, APVS);
    thisAircraft -> addStateLightsOff(14, APALT);

    thisAircraft -> addStateTransition(APHDG, 15, 1);
    thisAircraft -> addStateTransition(APNAV, 15, 5);
    thisAircraft -> addStateTransition(APAPR, 15, 1);
    thisAircraft -> addStateTransition(APREV, 15, 1);
    thisAircraft -> addStateTransition(APALT, 15, 15);
    thisAircraft -> addStateTransition(APVS,  15, 16);
    thisAircraft -> addStateTransition(APIAS, 15, 15);
    thisAircraft -> addStateTransition(APAP,  15, 0);
    thisAircraft -> addStateLightsOn(15, APALT);
    thisAircraft -> addStateLightsOff(15, APVS);

    thisAircraft -> addStateTransition(APHDG, 16, 1);
    thisAircraft -> addStateTransition(APNAV, 16, 5);
    thisAircraft -> addStateTransition(APAPR, 16, 1);
    thisAircraft -> addStateTransition(APREV, 16, 1);
    thisAircraft -> addStateTransition(APALT, 16, 15);
    thisAircraft -> addStateTransition(APVS,  16, 16);
    thisAircraft -> addStateTransition(APIAS, 16, 16);
    thisAircraft -> addStateTransition(APAP,  16, 0);
    thisAircraft -> addStateLightsOn(16, APVS);
    thisAircraft -> addStateLightsOff(16, APALT);

    thisAircraft -> addStateTransition(APHDG, 17, 1);
    thisAircraft -> addStateTransition(APNAV, 17, 10);
    thisAircraft -> addStateTransition(APAPR, 17, 1);
    thisAircraft -> addStateTransition(APREV, 17, 1);
    thisAircraft -> addStateTransition(APALT, 17, 17);
    thisAircraft -> addStateTransition(APVS,  17, 18);
    thisAircraft -> addStateTransition(APIAS, 17, 17);
    thisAircraft -> addStateTransition(APAP,  17, 0);
    thisAircraft -> addStateLightsOn(17, APALT);
    thisAircraft -> addStateLightsOff(17, APVS);

    thisAircraft -> addStateTransition(APHDG, 18, 1);
    thisAircraft -> addStateTransition(APNAV, 18, 10);
    thisAircraft -> addStateTransition(APAPR, 18, 1);
    thisAircraft -> addStateTransition(APREV, 18, 1);
    thisAircraft -> addStateTransition(APALT, 18, 17);
    thisAircraft -> addStateTransition(APVS,  18, 18);
    thisAircraft -> addStateTransition(APIAS, 18, 18);
    thisAircraft -> addStateTransition(APAP,  18, 0);
    thisAircraft -> addStateLightsOn(18, APVS);
    thisAircraft -> addStateLightsOff(18, APALT);

    thisAircraft -> addStateTransition(APHDG, 19, 1);
    thisAircraft -> addStateTransition(APNAV, 19, 5);
    thisAircraft -> addStateTransition(APAPR, 19, 6);
    thisAircraft -> addStateTransition(APREV, 19, 8);
    thisAircraft -> addStateTransition(APALT, 19, 19);
    thisAircraft -> addStateTransition(APVS,  19, 20);
    thisAircraft -> addStateTransition(APIAS, 19, 19);
    thisAircraft -> addStateTransition(APAP,  19, 0);
    thisAircraft -> addStateLightsOn(19, APALT);
    thisAircraft -> addStateLightsOff(19, APVS);

    thisAircraft -> addStateTransition(APHDG, 20, 1);
    thisAircraft -> addStateTransition(APNAV, 20, 5);
    thisAircraft -> addStateTransition(APAPR, 20, 6);
    thisAircraft -> addStateTransition(APREV, 20, 8);
    thisAircraft -> addStateTransition(APALT, 20, 19);
    thisAircraft -> addStateTransition(APVS,  20, 20);
    thisAircraft -> addStateTransition(APIAS, 20, 20);
    thisAircraft -> addStateTransition(APAP,  20, 0);
    thisAircraft -> addStateLightsOn(20, APVS);
    thisAircraft -> addStateLightsOff(20, APALT);

    thisAircraft -> addStateTransition(APHDG, 21, 1);
    thisAircraft -> addStateTransition(APNAV, 21, 9);
    thisAircraft -> addStateTransition(APAPR, 21, 5);
    thisAircraft -> addStateTransition(APREV, 21, 7);
    thisAircraft -> addStateTransition(APALT, 21, 21);
    thisAircraft -> addStateTransition(APVS,  21, 22);
    thisAircraft -> addStateTransition(APIAS, 21, 21);
    thisAircraft -> addStateTransition(APAP,  21, 0);
    thisAircraft -> addStateLightsOn(21, APALT);
    thisAircraft -> addStateLightsOff(21, APVS);

    thisAircraft -> addStateTransition(APHDG, 22, 1);
    thisAircraft -> addStateTransition(APNAV, 22, 9);
    thisAircraft -> addStateTransition(APAPR, 22, 5);
    thisAircraft -> addStateTransition(APREV, 22, 7);
    thisAircraft -> addStateTransition(APALT, 22, 21);
    thisAircraft -> addStateTransition(APVS,  22, 22);
    thisAircraft -> addStateTransition(APIAS, 22, 22);
    thisAircraft -> addStateTransition(APAP,  22, 0);
    thisAircraft -> addStateLightsOn(22, APVS);
    thisAircraft -> addStateLightsOff(22, APALT);

    thisAircraft -> addStateTransition(APHDG, 23, 1);
    thisAircraft -> addStateTransition(APNAV, 23, 9);
    thisAircraft -> addStateTransition(APAPR, 23, 5);
    thisAircraft -> addStateTransition(APREV, 23, 5);
    thisAircraft -> addStateTransition(APALT, 23, 23);
    thisAircraft -> addStateTransition(APVS,  23, 24);
    thisAircraft -> addStateTransition(APIAS, 23, 23);
    thisAircraft -> addStateTransition(APAP,  23, 0);
    thisAircraft -> addStateLightsOn(23, APALT);
    thisAircraft -> addStateLightsOff(23, APVS);

    thisAircraft -> addStateTransition(APHDG, 24, 1);
    thisAircraft -> addStateTransition(APNAV, 24, 9);
    thisAircraft -> addStateTransition(APAPR, 24, 5);
    thisAircraft -> addStateTransition(APREV, 24, 5);
    thisAircraft -> addStateTransition(APALT, 24, 23);
    thisAircraft -> addStateTransition(APVS,  24, 24);
    thisAircraft -> addStateTransition(APIAS, 24, 24);
    thisAircraft -> addStateTransition(APAP, 24, 0);
    thisAircraft -> addStateLightsOn(24, APVS);
    thisAircraft -> addStateLightsOff(24, APALT);

    thisAircraft -> addStateTransition(APHDG, 25, 1);
    thisAircraft -> addStateTransition(APNAV, 25, 5);
    thisAircraft -> addStateTransition(APAPR, 25, 1);
    thisAircraft -> addStateTransition(APREV, 25, 7);
    thisAircraft -> addStateTransition(APALT, 25, 25);
    thisAircraft -> addStateTransition(APVS,  25, 26);
    thisAircraft -> addStateTransition(APIAS, 25, 25);
    thisAircraft -> addStateTransition(APAP,  25, 0);
    thisAircraft -> addStateLightsOn(25, APALT);
    thisAircraft -> addStateLightsOff(25, APVS);

    thisAircraft -> addStateTransition(APHDG, 26, 1);
    thisAircraft -> addStateTransition(APNAV, 26, 5);
    thisAircraft -> addStateTransition(APAPR, 26, 1);
    thisAircraft -> addStateTransition(APREV, 26, 7);
    thisAircraft -> addStateTransition(APALT, 26, 25);
    thisAircraft -> addStateTransition(APVS,  26, 26);
    thisAircraft -> addStateTransition(APIAS, 26, 26);
    thisAircraft -> addStateTransition(APAP, 26, 0);
    thisAircraft -> addStateLightsOn(26, APVS);
    thisAircraft -> addStateLightsOff(26, APALT);

    thisAircraft -> activateStateMachine();
 
 */
}


void Bravo::bravoLaminarCessna172SP(){
    
    const char* jsonFileName = "Cessna SkyHawk 172 SP";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarCessna172SPDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}



//**********************************************************************************************************************************************
//
//   CESSNA 172 G1000
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarCessna172G1000Default(BravoProfile *thisAircraft) {

    thisAircraft -> AutopilotButton(APHDG, "sim/GPS/g1000n1_hdg");
    thisAircraft -> AutopilotButton(APNAV, "sim/GPS/g1000n1_nav");
    thisAircraft -> AutopilotButton(APAPR, "sim/GPS/g1000n1_apr");
    thisAircraft -> AutopilotButton(APREV, "sim/autopilot/back_course");
    thisAircraft -> AutopilotButton(APALT, "sim/GPS/g1000n1_alt");
    thisAircraft -> AutopilotButton(APVS,  "sim/GPS/g1000n1_vs");
    thisAircraft -> AutopilotButton(APIAS, "sim/autopilot/speed_hold");
    thisAircraft -> AutopilotButton(APAP,  "sim/GPS/g1000n1_ap");
    
    thisAircraft -> addCustomCommand(APHDG, TG1, "sim/GPS/g1000n1_hdg_sync");
    thisAircraft -> addCustomCommand(APHDG, TG4, "sim/GPS/g1000n1_softkey6");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g1000n1_com12");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g1000n1_nav12");

    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g1000n1_nav_ff");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g1000n1_com_ff");
    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/g1000n3_fpl");

    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/g1000n3_proc");

    thisAircraft -> addCustomCommand(APREV, TG4, "sim/GPS/g1000n3_direct");

    thisAircraft -> addCustomCommand(APALT, TG4, "sim/GPS/g1000n3_menu");

    thisAircraft -> addCustomCommand(APVS, TG4, "sim/GPS/g1000n3_clr");

    thisAircraft -> addCustomCommand(APIAS, TG4, "sim/GPS/g1000n3_cursor");

    thisAircraft -> addCustomCommand(APAP, TG4, "sim/GPS/g1000n3_ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g1000n1_nav_inner_up", "sim/GPS/g1000n1_nav_inner_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g1000n1_com_inner_up", "sim/GPS/g1000n1_com_inner_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g1000n3_fms_inner_up", "sim/GPS/g1000n3_fms_inner_down", slow);

    thisAircraft -> RotaryControl(RCCRS, "sim/GPS/g1000n1_crs_up", "sim/GPS/g1000n1_crs_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/GPS/g1000n1_hdg_up", "sim/GPS/g1000n1_hdg_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/GPS/g1000n1_nose_up", "sim/GPS/g1000n1_nose_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/GPS/g1000n1_alt_outer_up", "sim/GPS/g1000n1_alt_outer_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g1000n1_nav_outer_up", "sim/GPS/g1000n1_nav_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g1000n1_com_outer_up", "sim/GPS/g1000n1_com_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g1000n3_fms_outer_up", "sim/GPS/g1000n3_fms_outer_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/GPS/g1000n3_range_down", "sim/GPS/g1000n3_range_up", slow);

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/GPS/g1000n1_alt_inner_up", "sim/GPS/g1000n1_alt_inner_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/GPS/g1000n1_baro_up", "sim/GPS/g1000n1_baro_down", slow, fastest);

    thisAircraft -> activateIncrDecrRotary();
    
    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight
    lights -> customAnnunciatorDataRef(LowHydPressureLight, NULL);       // the default Cessna Skyhawk doesn't appear to update any hydraulic pressure datarefs, so turn this off to avoid spurious false alerts
    
    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/gpss_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APREV, "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/heading_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/gpss_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/vvi_status");

}

void Bravo::bravoLaminarCessna172G1000() {

    const char* jsonFileName = "Cessna Skyhawk 172 G1000";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarCessna172G1000Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}



//**********************************************************************************************************************************************
//
//   CESSNA 172 FLOATS
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarCessna172FloatsDefault(BravoProfile *thisAircraft) {

    bravoLaminarCessna172SPDefault(currentAircraft);
}

void Bravo::bravoLaminarCessna172Floats() {

    const char* jsonFileName = "Cessna Skyhawk 172 Floats";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarCessna172FloatsDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}



//**********************************************************************************************************************************************
//
//   CESSNA CITATION X
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarCessnaCitationX() {

    const char* jsonFileName = "Cessna Citation X";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarCessnaCitationXDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarCessnaCitationXDefault(BravoProfile *thisAircraft) {

    thisAircraft -> AutopilotButton(APHDG, "laminar/CitX/autopilot/cmd_hdg_mode");
    thisAircraft -> AutopilotButton(APNAV, "laminar/CitX/autopilot/cmd_nav_mode");
    thisAircraft -> AutopilotButton(APAPR, "laminar/CitX/autopilot/cmd_app_mode");
    thisAircraft -> AutopilotButton(APREV, "laminar/CitX/autopilot/cmd_bc_mode");
    thisAircraft -> AutopilotButton(APALT, "laminar/CitX/autopilot/cmd_alt_mode");
    thisAircraft -> AutopilotButton(APVS,  "laminar/CitX/autopilot/cmd_vs_mode");
    thisAircraft -> AutopilotButton(APIAS, "laminar/CitX/autopilot/cmd_flc_mode");
    thisAircraft -> AutopilotButton(APAP,  "laminar/CitX/autopilot/cmd_ap_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG1, "laminar/CitX/autopilot/cmd_bank_mode");
    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/autopilot/heading_sync_pilot");
    thisAircraft -> addCustomCommand(APHDG, TG3, "sim/radios/obs_HSI_direct");

    thisAircraft -> addCustomCommand(APNAV, TG1, "laminar/CitX/autopilot/cmd_vnav_mode");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/instruments/barometer_std");
    thisAircraft -> addCustomCommand(APALT, TG2, "sim/instruments/ra_baro");

    thisAircraft -> addCustomCommand(APVS, TG1, "laminar/CitX/autopilot/cmd_mtrim_toggle");

    thisAircraft -> addCustomCommand(APIAS, TG1, "laminar/CitX/autopilot/cmd_cngovr_mode");

    thisAircraft -> addCustomCommand(APAP, TG1, "laminar/CitX/autopilot/cmd_stby_mode");
    thisAircraft -> addCustomCommand(APAP, TG2, "laminar/CitX/autopilot/cmd_pfdsel_toggle");
    thisAircraft -> addCustomCommand(APAP, TG3, "laminar/CitX/autopilot/cmd_yd_toggle");

    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS, "laminar/CitX/autopilot/cmd_wheel1_up", "laminar/CitX/autopilot/cmd_wheel1_dwn", slow);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs_HSI_up", "sim/radios/obs_HSI_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/instruments/barometer_stby_up", "sim/instruments/barometer_stby_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG4, "sim/instruments/minimum_up", "sim/instruments/minimum_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG6, "sim/autopilot/heading_copilot_up", "sim/autopilot/heading_copilot_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/radios/copilot_obs_HSI_up", "sim/radios/copilot_obs_HSI_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight
    
    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APREV, "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APALT, "laminar/CitX/autopilot/alt_mode_on");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APIAS, "sim/cockpit2/autopilot/speed_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");
}



//**********************************************************************************************************************************************
//
//   CIRRUS SR22
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarCirrusSR22() {

    const char* jsonFileName = "Cirrus SR22";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarCirrusSR22Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarCirrusSR22Default(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/GPS/g1000n1_hdg");
    thisAircraft -> AutopilotButton(APNAV, "sim/GPS/g1000n1_nav");
    thisAircraft -> AutopilotButton(APAPR, "sim/GPS/g1000n1_apr");
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "sim/GPS/g1000n1_alt");
    thisAircraft -> AutopilotButton(APVS,  "sim/GPS/g1000n1_vs");
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/GPS/g1000n1_ap");
    
    thisAircraft -> addCustomCommand(APHDG, TG1, "sim/GPS/g1000n1_hdg_sync");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g1000n1_com12");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g1000n3_nav12");

    thisAircraft -> addCustomCommand(APNAV, TG1, "sim/GPS/g1000n1_vnv");
    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/gcu478/fpl");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g1000n1_com_ff");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g1000n3_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/gcu478/proc");

    thisAircraft -> addCustomCommand(APREV, TG4, "sim/GPS/gcu478/direct");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/autopilot/return_to_level");
    thisAircraft -> addCustomCommand(APALT, TG4, "sim/GPS/gcu478/menu");

    thisAircraft -> addCustomCommand(APVS, TG1, "sim/GPS/g1000n1_flc");
    thisAircraft -> addCustomCommand(APVS, TG4, "sim/GPS/gcu478/clr");

    thisAircraft -> addCustomCommand(APIAS, TG4, "sim/GPS/gcu479/cursor");

    thisAircraft -> addCustomCommand(APAP, TG4, "sim/GPS/gcu478/ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/GPS/g1000n1_crs_up", "sim/GPS/g1000n1_crs_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/GPS/g1000n1_hdg_up", "sim/GPS/g1000n1_hdg_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/GPS/g1000n1_nose_up", "sim/GPS/g1000n1_nose_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/GPS/g1000n1_alt_outer_up", "sim/GPS/g1000n1_alt_outer_down", slow);

    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g1000n3_fms_inner_up", "sim/GPS/g1000n3_fms_inner_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g1000n1_com_inner_up", "sim/GPS/g1000n1_com_inner_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g1000n1_nav_inner_up", "sim/GPS/g1000n1_nav_inner_down", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g1000n3_fms_outer_up", "sim/GPS/g1000n3_fms_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g1000n1_com_outer_up", "sim/GPS/g1000n1_com_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g1000n1_nav_outer_up", "sim/GPS/g1000n1_nav_outer_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/GPS/gcu478/range_down", "sim/GPS/gcu478/range_up", slow);

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/GPS/g1000n1_alt_inner_up", "sim/GPS/g1000n1_alt_inner_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/GPS/g1000n1_baro_up", "sim/GPS/g1000n1_baro_down", slow);

    thisAircraft -> activateIncrDecrRotary();
    
    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight
    
    lights -> addAutopilotLightDataRef(APHDG, "laminar/sr22/annunciators/ap/hdg");
    lights -> addAutopilotLightDataRef(APNAV, "laminar/sr22/annunciators/ap/nav");
    lights -> addAutopilotLightDataRef(APNAV, "laminar/sr22/annunciators/ap/vnv");
    lights -> addAutopilotLightDataRef(APAPR, "laminar/sr22/annunciators/ap/apr");
    lights -> addAutopilotLightDataRef(APALT, "laminar/sr22/annunciators/ap/alt");
    lights -> addAutopilotLightDataRef(APALT, "laminar/sr22/annunciators/ap/flc");
    lights -> addAutopilotLightDataRef(APVS,  "laminar/sr22/annunciators/ap/vs");
    lights -> addAutopilotLightDataRef(APVS,  "laminar/sr22/annunciators/ap/flc");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/sr22/annunciators/ap/ap");
}



//**********************************************************************************************************************************************
//
//   CIRRUS VISION SF50
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarCirrusVisionSF50() {

    const char* jsonFileName = "Cirrus Vision SF50";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarCirrusVisionSF50Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarCirrusVisionSF50Default(BravoProfile *thisAircraft) {

    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/heading");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  "sim/autopilot/vertical_speed");
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG1, "sim/autopilot/heading_sync");
    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/GPS/g1000n3_crs_sync");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g1000n1_com12");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g1000n1_nav12");

    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/g1000n3_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g1000n1_com_ff");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g1000n1_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/g1000n3_proc");

    thisAircraft -> addCustomCommand(APREV, TG4, "sim/GPS/g1000n3_direct");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/autopilot/altitude_sync");
    thisAircraft -> addCustomCommand(APALT, TG4, "sim/GPS/g1000n3_menu");

    thisAircraft -> addCustomCommand(APVS, TG1, "sim/autopilot/level_change");
    thisAircraft -> addCustomCommand(APVS, TG2, "sim/autopilot/wing_leveler");
    thisAircraft -> addCustomCommand(APVS, TG4, "sim/GPS/g1000n3_clr");

    thisAircraft -> addCustomCommand(APIAS, TG4, "sim/GPS/g1000n3_cursor");

    thisAircraft -> addCustomCommand(APAP, TG4, "sim/GPS/g1000n3_ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/GPS/g1000n3_crs_up", "sim/GPS/g1000n3_crs_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS, "sim/autopilot/nose_up", "sim/autopilot/nose_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fast);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g1000n1_nav_inner_up", "sim/GPS/g1000n1_nav_inner_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g1000n1_com_inner_up", "sim/GPS/g1000n1_com_inner_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g1000n3_fms_inner_up", "sim/GPS/g1000n3_fms_inner_down", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g1000n1_nav_outer_up", "sim/GPS/g1000n1_nav_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g1000n1_com_outer_up", "sim/GPS/g1000n1_com_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g1000n3_fms_outer_up", "sim/GPS/g1000n3_fms_outer_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/GPS/g1000n3_range_down", "sim/GPS/g1000n3_range_up", slow);

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/GPS/g1000n3_baro_up", "sim/GPS/g1000n3_baro_down", slow);
    thisAircraft -> addCustomCommand(RCALT, TG1, "sim/GPS/g1000n3_baro_up", "sim/GPS/g1000n3_baro_down", slow);

    thisAircraft -> activateIncrDecrRotary();


    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_mode");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_armed");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");
}


//**********************************************************************************************************************************************
//
//   F4 PHANTOM II
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarF4PhantomII() {

    const char* jsonFileName = "F4 Phantom II";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarF4PhantomIIDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarF4PhantomIIDefault(BravoProfile *thisAircraft) {

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs1_up", "sim/radios/obs1_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/radios/actv_nav1_fine_up", "sim/radios/actv_nav1_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/radios/actv_com1_fine_up", "sim/radios/actv_com1_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/radios/actv_com2_fine_up", "sim/radios/actv_nav1_fine_down", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/radios/actv_nav1_coarse_up", "sim/radios/actv_nav1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/radios/actv_com1_coarse_up", "sim/radios/actv_com1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/radios/actv_com2_coarse_up", "sim/radios/actv_com2_coarse_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight
}


//**********************************************************************************************************************************************
//
//   F14 TOMCAT
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarF14Tomcat() {

    const char* jsonFileName = "F14 Tomcat";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarF14TomcatDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarF14TomcatDefault(BravoProfile *thisAircraft) {
  
    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/heading_hold");
    thisAircraft -> AutopilotButton(APNAV, NULL);
    thisAircraft -> AutopilotButton(APAPR, NULL);
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  NULL);
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_on");

    thisAircraft -> addCustomCommand(APHDG, TG1, "sim/autopilot/wing_leveler");
    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/autopilot/track");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/autopilot/pitch_sync");
    thisAircraft -> addCustomCommand(APALT, TG6, "laminar/f14/inst/button/radar_alt_test");

    thisAircraft -> addCustomCommand(APAP, TG1, "sim/autopilot/disconnect");

    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs_HSI_up", "sim/radios/obs_HSI_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "laminar/f14/navg/knob/tac1_power_mode_knob_up", "laminar/f14/navg/knob/tac1_power_mode_knob_dn", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/radios/actv_tac1_channel_1up", "sim/radios/actv_tac1_channel_1down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/radios/actv_tac1_channel_10up", "sim/radios/actv_tac1_channel_10down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG6, "laminar/f14/aplt/vec_pcd_acl_switch_switch_up", "laminar/f14/aplt/vec_pcd_acl_switch_switch_dn", slow);

    thisAircraft -> addCustomCommand(RCALT, TG6, "laminar/f14/inst/knob/radar_alt_pilot_up", "laminar/f14/inst/knob/radar_alt_pilot_dn", slow);

    thisAircraft -> activateIncrDecrRotary();
    
    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

}



//**********************************************************************************************************************************************
//
//   LANCAIR EVOLUTION
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarLancairEvolution() {

    const char* jsonFileName = "Lancair Evolution";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();
 
    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarLancairEvolutionDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarLancairEvolutionDefault(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/track");
    thisAircraft -> AutopilotButton(APNAV, "laminar/n844x/ap_button_nav");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, "sim/autopilot/back_course");
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  "sim/autopilot/alt_vs");
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG1, "sim/autopilot/heading_sync");
    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/GPS/g1000n3_crs_sync");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g1000n1_com12");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g1000n1_nav12");

    thisAircraft -> addCustomCommand(APNAV, TG1, "sim/autopilot/gpss");
    thisAircraft -> addCustomCommand(APNAV, TG2, "sim/autopilot/vnav");
    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/g1000n3_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g1000n1_com_ff");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g1000n1_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/g1000n3_proc");

    thisAircraft -> addCustomCommand(APREV, TG4, "sim/GPS/g1000n3_direct");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/autopilot/altitude_sync");
    thisAircraft -> addCustomCommand(APALT, TG4, "sim/GPS/g1000n3_menu");

    thisAircraft -> addCustomCommand(APVS, TG4, "sim/GPS/g1000n3_clr");

    thisAircraft -> addCustomCommand(APIAS, TG4, "sim/GPS/g1000n3_cursor");

    thisAircraft -> addCustomCommand(APAP, TG4, "sim/GPS/g1000n3_ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/GPS/g1000n3_crs_up", "sim/GPS/g1000n3_crs_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS, "sim/autopilot/nose_up", "sim/autopilot/nose_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fast);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g1000n1_nav_inner_up", "sim/GPS/g1000n1_nav_inner_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g1000n1_com_inner_up", "sim/GPS/g1000n1_com_inner_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g1000n3_fms_inner_up", "sim/GPS/g1000n3_fms_inner_down", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g1000n1_nav_outer_up", "sim/GPS/g1000n1_nav_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g1000n1_com_outer_up", "sim/GPS/g1000n1_com_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g1000n3_fms_outer_up", "sim/GPS/g1000n3_fms_outer_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/GPS/g1000n3_range_down", "sim/GPS/g1000n3_range_up", slow);

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/GPS/g1000n3_baro_up", "sim/GPS/g1000n3_baro_down", slow);

    thisAircraft -> activateIncrDecrRotary();


    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight


 
    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_mode");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_armed");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");
}




//**********************************************************************************************************************************************
//
//   MCDONNELL DOUGLAS MD82
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarMcDonnellDouglasMD82() {
    
    const char* jsonFileName = "McDonnell Douglas MD82";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarMcDonnellDouglasMD82Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarMcDonnellDouglasMD82Default(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/gpss");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "laminar/md82cmd/autopilot/alt_hold");
    thisAircraft -> AutopilotButton(APVS,  "laminar/md82cmd/autopilot/vert_spd");
    thisAircraft -> AutopilotButton(APIAS, "laminar/md82cmd/autopilot/autothrottle_switch");
    thisAircraft -> AutopilotButton(APIAS, "laminar/md82cmd/autopilot/ias_mach");
    thisAircraft -> AutopilotButton(APAP,  "laminar/md82cmd/autopilot/servos_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG1, "laminar/md82cmd/autopilot/heading_dial_pull");

    thisAircraft -> addCustomCommand(APNAV, TG1, "laminar/md82cmd/autopilot/vnav");
    thisAircraft -> addCustomCommand(APNAV, TG2, "sim/radios/com1_standy_flip");
    thisAircraft -> addCustomCommand(APNAV, TG3, "sim/radios/com1_standy_flip");

    thisAircraft -> addCustomCommand(APAPR, TG1, "laminar/md82cmd/autopilot/autoland");

    thisAircraft -> addCustomCommand(APIAS, TG1, "sim/autopilot/spd_intv");
    thisAircraft -> addCustomCommand(APIAS, TG2, "laminar/md82cmd/autopilot/ias_mach");

    thisAircraft -> RotaryControl(RCIAS, "sim/autopilot/airspeed_up", "sim/autopilot/airspeed_down", slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs1_up", "sim/radios/obs1_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/autopilot/nose_up", "sim/autopilot/nose_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/radios/actv_nav1_fine_up", "sim/radios/actv_nav1_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/radios/actv_nav2_fine_up", "sim/radios/actv_nav2_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG3, "laminar/md82cmd/radios/com1_left_fine_up", "laminar/md82cmd/radios/com1_left_fine_dwn", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG2, "laminar/md82cmd/radios/com1_right_fine_up", "laminar/md82cmd/radios/com1_right_fine_dwn", slow, fastest);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/radios/copilot_obs2_up", "sim/radios/copilot_obs2_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/radios/actv_nav1_coarse_up", "sim/radios/actv_nav1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/radios/actv_nav2_coarse_up", "sim/radios/actv_nav2_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG3, "laminar/md82cmd/radios/com1_left_coarse_up", "laminar/md82cmd/radios/com1_left_coarse_dwn", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG2, "laminar/md82cmd/radios/com1_right_coarse_up", "laminar/md82cmd/radios/com1_right_coarse_dwn", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG6, "laminar/md82cmd/autopilot/source_2", "laminar/md82cmd/autopilot/source_1", slow);
    
    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_hold_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/EFIS/EFIS_vor_on");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_status");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APIAS, "sim/cockpit2/autopilot/speed_status");

    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");
}



//**********************************************************************************************************************************************
//
//   PIPER PA18 SUPERCUB
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarPiperPA18SuperCub() {
    
    const char* jsonFileName = "Piper PA18 SuperCub";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarPiperPA18SuperCubDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarPiperPA18SuperCubDefault(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, NULL);
    thisAircraft -> AutopilotButton(APNAV, NULL);
    thisAircraft -> AutopilotButton(APAPR, NULL);
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, NULL);
    thisAircraft -> AutopilotButton(APVS,  NULL);
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/starters/engage_start_run_1");

    thisAircraft -> addCustomCommand(APIAS, TG5, "sim/radios/nav1_standy_flip");
    thisAircraft -> addCustomCommand(APIAS, TG6, "sim/radios/com1_standy_flip");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs1_up", "sim/radios/obs1_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/instruments/DG_sync_up", "sim/instruments/DG_sync_down", slow);
    thisAircraft -> RotaryControl(RCVS,  "sim/instruments/ah_ref_up", "sim/instruments/ah_ref_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/radios/stby_com1_fine_up_833", "sim/radios/stby_com1_fine_down_833", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/radios/stby_nav1_fine_up", "sim/radios/stby_nav1_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/transponder/transponder_up", "sim/transponder/transponder_dn", slow);
    
    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/radios/stby_com1_coarse_up", "sim/radios/stby_com1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/radios/stby_nav1_coarse_up", "sim/radios/stby_nav1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/radios/transponder_1000_up", "sim/radios/transponder_1000_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG6, "sim/radios/power_com1_on", "sim/radios/power_com1_off", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG5, "sim/radios/power_nav1_on", "sim/radios/power_nav1_off", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/radios/transponder_100_up", "sim/radios/transponder_100_down", slow);

    thisAircraft -> addCustomCommand(RCVS, TG4, "sim/radios/transponder_10_up", "sim/radios/transponder_10_down", slow);

    thisAircraft -> addCustomCommand(RCALT, TG6, "laminar/pa18/fuel_selector_up", "laminar/pa18/fuel_selector_dwn", slow);
    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/magnetos/magnetos_up_1", "sim/magnetos/magnetos_down_1", slow);
    thisAircraft -> addCustomCommand(RCALT, TG4, "sim/radios/transponder_1_up", "sim/radios/transponder_1_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> customAnnunciatorDataRef(LowHydPressureLight, NULL);       //  Super Cub doesn't have any hydraulics, so all associated datarefs say zero, which triggers the annunciator light
    
    lights -> addAutopilotLightDataRef(APAP,  "sim/flightmodel2/engines/starter_is_running");
}



//**********************************************************************************************************************************************
//
//   ROBINSON R22 BETA II
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarRobinsonR22BetaII() {
    
    const char* jsonFileName = "Robinsons R22 Beta II";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarRobinsonR22BetaIIDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarRobinsonR22BetaIIDefault(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, NULL);
    thisAircraft -> AutopilotButton(APNAV, NULL);
    thisAircraft -> AutopilotButton(APAPR, NULL);
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "sim/instruments/barometer_2992");
    thisAircraft -> AutopilotButton(APVS,  NULL);
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  NULL);
  
    thisAircraft -> RotaryControl(RCIAS, NULL, NULL);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs1_up", "sim/radios/obs1_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);

    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g430n1_nav_com_tog");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g430n1_cdi");

    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g430n1_nav_ff");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g430n1_fpl");

    thisAircraft -> addCustomCommand(APAPR, TG6, "sim/GPS/g430n1_com_ff");
    thisAircraft -> addCustomCommand(APAPR, TG5, "sim/GPS/g430n1_proc");

    thisAircraft -> addCustomCommand(APREV, TG5, "sim/GPS/g430n1_direct");

    thisAircraft -> addCustomCommand(APALT, TG5, "sim/GPS/g430n1_menu");

    thisAircraft -> addCustomCommand(APVS, TG5, "sim/GPS/g430n1_clr");

    thisAircraft -> addCustomCommand(APIAS, TG5, "sim/GPS/g430n1_cursor");

    thisAircraft -> addCustomCommand(APAP, TG5, "sim/GPS/g430n1_ent");

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g430n1_fine_up", "sim/GPS/g430n1_fine_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g430n1_page_up", "sim/GPS/g430n1_page_dn", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g430n1_coarse_up", "sim/GPS/g430n1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g430n1_chapter_up", "sim/GPS/g430n1_chapter_dn", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG5, "sim/GPS/g430n1_zoom_out", "sim/GPS/g430n1_zoom_in", slow);

    thisAircraft -> activateIncrDecrRotary();
    
    lights -> defaultAnnunciatorDataRefs();
    
}


//**********************************************************************************************************************************************
//
//   ROBINSON R22 BETA II Marine
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarRobinsonR22BetaIIMarine() {
    
    const char* jsonFileName = "Robinsons R22 Beta II Marine";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarRobinsonR22BetaIIMarineDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarRobinsonR22BetaIIMarineDefault(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, NULL);
    thisAircraft -> AutopilotButton(APNAV, NULL);
    thisAircraft -> AutopilotButton(APAPR, NULL);
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "sim/instruments/barometer_2992");
    thisAircraft -> AutopilotButton(APVS,  NULL);
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  NULL);
  
    thisAircraft -> RotaryControl(RCIAS, NULL, NULL);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs1_up", "sim/radios/obs1_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);

    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g430n1_nav_com_tog");

    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g430n1_proc");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g430n1_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG5, "sim/GPS/g430n1_fpl");
    thisAircraft -> addCustomCommand(APAPR, TG6, "sim/GPS/g430n1_com_ff");

    thisAircraft -> addCustomCommand(APREV, TG5, "sim/GPS/g430n1_direct");

    thisAircraft -> addCustomCommand(APALT, TG5, "sim/GPS/g430n1_menu");

    thisAircraft -> addCustomCommand(APVS, TG5, "sim/GPS/g430n1_clr");

    thisAircraft -> addCustomCommand(APIAS, TG5, "sim/GPS/g430n1_cursor");

    thisAircraft -> addCustomCommand(APAP, TG5, "sim/GPS/g430n1_ent");

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g430n1_fine_up", "sim/GPS/g430n1_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g430n1_page_up", "sim/GPS/g430n1_page_dn", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g430n1_coarse_up", "sim/GPS/g430n1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g430n1_chapter_up", "sim/GPS/g430n1_chapter_dn", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG5, "sim/GPS/g430n1_zoom_in", "sim/GPS/g430n1_zoom_out", slow);

    thisAircraft -> activateIncrDecrRotary();
    
    lights -> defaultAnnunciatorDataRefs();
}



//**********************************************************************************************************************************************
//
//   SCHLEICHER ASK 21
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarSchleicherASK21() {
    
    const char* jsonFileName = "Schleicher ASK 21";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarSchleicherASK21Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarSchleicherASK21Default(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/flight_controls/canopy_toggle");
    thisAircraft -> AutopilotButton(APIAS, "sim/radios/com1_standy_flip");
    thisAircraft -> AutopilotButton(APAP,  "sim/flight_controls/glider_all_release");

    thisAircraft -> RotaryControl(RCIAS, "sim/radios/actv_com1_fine_up", "sim/radios/actv_com1_fine_down", slow);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/actv_com1_coarse_up", "sim/radios/actv_com1_coarse_down", slow);
    thisAircraft -> RotaryControl(RCHDG, "sim/radios/power_com1_on", "sim/radios/power_com1_off", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);
    
    thisAircraft -> activateIncrDecrRotary();

}



//**********************************************************************************************************************************************
//
//   SIKORSKY S76C
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarSikorskyS76C() {
    
    const char* jsonFileName = "Sikorsky S76C";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarSikorskyS76CDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarSikorskyS76CDefault(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/heading");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  "sim/autopilot/level_change");
    thisAircraft -> AutopilotButton(APIAS, "sim/autopilot/speed_hold");
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/radios/adf1_standy_flip");
    thisAircraft -> addCustomCommand(APHDG, TG3, "sim/radios/nav2_standy_flip");
    thisAircraft -> addCustomCommand(APHDG, TG4, "sim/radios/com2_standy_flip");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g430n1_cdi");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g430n1_nav_com_tog");

    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g430n1_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g430n1_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG1, "sim/autopilot/glide_slope");
    thisAircraft -> addCustomCommand(APAPR, TG5, "sim/GPS/g430n1_proc");
    thisAircraft -> addCustomCommand(APAPR, TG6, "sim/GPS/g430n1_com_ff");

    thisAircraft -> addCustomCommand(APREV, TG5, "sim/GPS/g430n1_direct");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/instruments/barometer_2992");
    thisAircraft -> addCustomCommand(APALT, TG5, "sim/GPS/g430n1_menu");

    thisAircraft -> addCustomCommand(APVS, TG5, "sim/GPS/g430n1_clr");

    thisAircraft -> addCustomCommand(APIAS, TG5, "sim/GPS/g430n1_cursor");

    thisAircraft -> addCustomCommand(APAP, TG5, "sim/GPS/g430n1_ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL);
    thisAircraft -> RotaryControl(RCCRS, "sim/radios/obs_HSI_up", "sim/radios/obs_HSI_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fastest);

    thisAircraft -> addCustomCommand(RCHDG, TG5, "sim/GPS/g430n1_zoom_out", "sim/GPS/g430n1_zoom_in", slow);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g430n1_fine_up", "sim/GPS/g430n1_fine_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g430n1_page_up", "sim/GPS/g430n1_page_dn", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/radios/stby_com2_fine_up_833", "sim/radios/stby_com2_fine_down_833", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG3, "sim/radios/stby_nav2_fine_up", "sim/radios/stby_nav2_fine_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG2, "sim/radios/stby_adf1_ones_tens_up", "sim/radios/stby_adf1_ones_tens_down", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g430n1_coarse_up", "sim/GPS/g430n1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g430n1_chapter_up", "sim/GPS/g430n1_chapter_dn", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/radios/stby_com2_coarse_up", "sim/radios/stby_com2_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG3, "sim/radios/stby_nav2_coarse_up", "sim/radios/stby_nav2_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG2, "sim/radios/stby_adf1_hundreds_up", "sim/radios/stby_adf1_hundreds_down", slow);

    thisAircraft -> addCustomCommand(RCALT, TG1, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);

    thisAircraft -> activateIncrDecrRotary();
    
    lights -> defaultAnnunciatorDataRefs();
    
    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_mode");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_armed");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/pitch_status");
    lights -> addAutopilotLightDataRef(APIAS, "sim/cockpit2/autopilot/speed_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");
}


//**********************************************************************************************************************************************
//
//   STINSON L5 SENTINEL
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarStinsonL5Sentinel() {
    
    const char* jsonFileName = "Stinson L5 Sentinel";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarStinsonL5SentinelDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarStinsonL5SentinelDefault(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, NULL);
    thisAircraft -> AutopilotButton(APNAV, NULL);
    thisAircraft -> AutopilotButton(APAPR, NULL);
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, NULL);
    thisAircraft -> AutopilotButton(APVS,  NULL);
    thisAircraft -> AutopilotButton(APIAS, "sim/radios/com1_standy_flip");
    thisAircraft -> AutopilotButton(APAP,  NULL);

    thisAircraft -> addCustomCommand(APIAS, TG6, "sim/radios/com1_standy_flip");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCALT, "sim/instruments/barometer_up", "sim/instruments/barometer_down", slow);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/radios/stby_com1_fine_up_833", "sim/radios/stby_com1_fine_down_833", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG1, "sim/transponder/transponder_up", "sim/transponder/transponder_dn", slow);
    
    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/radios/stby_com1_coarse_up", "sim/radios/stby_com1_coarse_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG1, "sim/radios/transponder_1000_up", "sim/radios/transponder_1000_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG6, "sim/radios/power_com1_on", "sim/radios/power_com1_off", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG1, "sim/radios/transponder_100_up", "sim/radios/transponder_100_down", slow);

    thisAircraft -> addCustomCommand(RCVS, TG1, "sim/radios/transponder_10_up", "sim/radios/transponder_10_down", slow);

    thisAircraft -> addCustomCommand(RCALT, TG5, "sim/magnetos/magnetos_up_1", "sim/magnetos/magnetos_down_1", slow);
    thisAircraft -> addCustomCommand(RCALT, TG4, "laminar/L5/fuel_selector_up", "laminar/L5/fuel_selector_dwn", slow);
    thisAircraft -> addCustomCommand(RCALT, TG1, "sim/radios/transponder_1_up", "sim/radios/transponder_1_down", slow);

    thisAircraft -> activateIncrDecrRotary();

    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> customAnnunciatorDataRef(LowHydPressureLight, NULL);       // L5 Sentinel doesn't have any hydraulics, so all associated datarefs say zero, which triggers the annunciator light
    
    lights -> addAutopilotLightDataRef(APAP,  "sim/flightmodel2/engines/starter_is_running");

}



//**********************************************************************************************************************************************
//
//   VANS RV10
//
//**********************************************************************************************************************************************

void Bravo::bravoLaminarVansRV10() {
    
    const char* jsonFileName = "Vans RV10";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoLaminarVansRV10Default(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoLaminarVansRV10Default(BravoProfile *thisAircraft) {
    
    thisAircraft -> AutopilotButton(APHDG, "sim/autopilot/track");
    thisAircraft -> AutopilotButton(APNAV, "sim/autopilot/NAV");
    thisAircraft -> AutopilotButton(APAPR, "sim/autopilot/approach");
    thisAircraft -> AutopilotButton(APREV, "sim/autopilot/back_course");
    thisAircraft -> AutopilotButton(APALT, "sim/autopilot/altitude_hold");
    thisAircraft -> AutopilotButton(APVS,  "sim/autopilot/alt_vs");
    thisAircraft -> AutopilotButton(APIAS, NULL);
    thisAircraft -> AutopilotButton(APAP,  "sim/autopilot/servos_toggle");

    thisAircraft -> addCustomCommand(APHDG, TG1, "sim/autopilot/heading_sync");
    thisAircraft -> addCustomCommand(APHDG, TG2, "sim/GPS/g1000n3_crs_sync");
    thisAircraft -> addCustomCommand(APHDG, TG5, "sim/GPS/g1000n1_com12");
    thisAircraft -> addCustomCommand(APHDG, TG6, "sim/GPS/g1000n1_nav12");

    thisAircraft -> addCustomCommand(APNAV, TG1, "sim/autopilot/gpss");
    thisAircraft -> addCustomCommand(APNAV, TG2, "sim/autopilot/vnav");
    thisAircraft -> addCustomCommand(APNAV, TG4, "sim/GPS/g1000n3_fpl");
    thisAircraft -> addCustomCommand(APNAV, TG5, "sim/GPS/g1000n1_com_ff");
    thisAircraft -> addCustomCommand(APNAV, TG6, "sim/GPS/g1000n1_nav_ff");

    thisAircraft -> addCustomCommand(APAPR, TG4, "sim/GPS/g1000n3_proc");

    thisAircraft -> addCustomCommand(APREV, TG4, "sim/GPS/g1000n3_direct");

    thisAircraft -> addCustomCommand(APALT, TG1, "sim/autopilot/altitude_sync");
    thisAircraft -> addCustomCommand(APALT, TG4, "sim/GPS/g1000n3_menu");

    thisAircraft -> addCustomCommand(APVS, TG1, "sim/autopilot/level_change");
    thisAircraft -> addCustomCommand(APVS, TG4, "sim/GPS/g1000n3_clr");

    thisAircraft -> addCustomCommand(APIAS, TG4, "sim/GPS/g1000n3_cursor");

    thisAircraft -> addCustomCommand(APAP, TG4, "sim/GPS/g1000n3_ent");

    thisAircraft -> RotaryControl(RCIAS, NULL, NULL, slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "sim/GPS/g1000n3_crs_up", "sim/GPS/g1000n3_crs_down", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "sim/autopilot/heading_up", "sim/autopilot/heading_down", slow, fastest);
    thisAircraft -> RotaryControl(RCVS, "sim/autopilot/nose_up", "sim/autopilot/nose_down", slow);
    thisAircraft -> RotaryControl(RCALT, "sim/autopilot/altitude_up", "sim/autopilot/altitude_down", slow, fast);

    thisAircraft -> addCustomCommand(RCIAS, TG6, "sim/GPS/g1000n1_nav_inner_up", "sim/GPS/g1000n1_nav_inner_down", slow);
    thisAircraft -> addCustomCommand(RCIAS, TG5, "sim/GPS/g1000n1_com_inner_up", "sim/GPS/g1000n1_com_inner_down", slow, fastest);
    thisAircraft -> addCustomCommand(RCIAS, TG4, "sim/GPS/g1000n3_fms_inner_up", "sim/GPS/g1000n3_fms_inner_down", slow);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "sim/GPS/g1000n1_nav_outer_up", "sim/GPS/g1000n1_nav_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG5, "sim/GPS/g1000n1_com_outer_up", "sim/GPS/g1000n1_com_outer_down", slow);
    thisAircraft -> addCustomCommand(RCCRS, TG4, "sim/GPS/g1000n3_fms_outer_up", "sim/GPS/g1000n3_fms_outer_down", slow);

    thisAircraft -> addCustomCommand(RCHDG, TG4, "sim/GPS/g1000n3_range_down", "sim/GPS/g1000n3_range_up", slow);

    thisAircraft -> addCustomCommand(RCALT, TG6, "sim/GPS/g1000n3_baro_up", "sim/GPS/g1000n3_baro_down", slow);

    thisAircraft -> activateIncrDecrRotary();


    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight

    lights -> customAnnunciatorDataRef(LowHydPressureLight, NULL);       // VAN's RV-10 doesn't have any hydraulics, so all associated datarefs say zero, which triggers the annunciator light

    lights -> addAutopilotLightDataRef(APHDG, "sim/cockpit2/autopilot/heading_mode");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/gpss_status");
    lights -> addAutopilotLightDataRef(APNAV, "sim/cockpit2/autopilot/nav_status");
    lights -> addAutopilotLightDataRef(APAPR, "sim/cockpit2/autopilot/approach_status");
    lights -> addAutopilotLightDataRef(APREV, "sim/cockpit2/autopilot/backcourse_status");
    lights -> addAutopilotLightDataRef(APALT, "sim/cockpit2/autopilot/altitude_hold_armed");
    lights -> addAutopilotLightDataRef(APVS,  "sim/cockpit2/autopilot/vvi_status");
    lights -> addAutopilotLightDataRef(APAP,  "sim/cockpit2/autopilot/servos_on");
}


//**********************************************************************************************************************************************
//
//   THIRD PARTY AIRCRAFT
//
//**********************************************************************************************************************************************



//**********************************************************************************************************************************************
//
//   ZIBO 737
//
//**********************************************************************************************************************************************

void Bravo::bravoZiboBoeing737X() {
    
    const char* jsonFileName = "Zibo Boeing 737-800";

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoZiboBoeing737XDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoZiboBoeing737XDefault(BravoProfile *thisAircraft) {

    thisAircraft -> AutopilotButton(APHDG, "laminar/B738/autopilot/hdg_sel_press");
    thisAircraft -> AutopilotButton(APNAV, "laminar/B738/autopilot/lnav_press");
    thisAircraft -> AutopilotButton(APAPR, "laminar/B738/autopilot/app_press");
    thisAircraft -> AutopilotButton(APREV, NULL);
    thisAircraft -> AutopilotButton(APALT, "laminar/B738/autopilot/alt_hld_press");
    thisAircraft -> AutopilotButton(APVS,  "laminar/B738/autopilot/vs_press");
    thisAircraft -> AutopilotButton(APIAS, "laminar/B738/autopilot/speed_press");
    thisAircraft -> AutopilotButton(APAP,  "laminar/B738/autopilot/cmd_a_press");

    thisAircraft -> addCustomCommand(APHDG, TG1, "laminar/B738/EFIS_control/capt/push_button/ctr_press");
    thisAircraft -> addCustomCommand(APHDG, TG2, "laminar/B738/EFIS_control/capt/push_button/tfc_press");    // Display air traffic on PFD

    thisAircraft -> addCustomCommand(APNAV, TG1, "laminar/B738/autopilot/vnav_press");
  
    thisAircraft -> addCustomCommand(APAPR, TG1, "laminar/B738/autopilot/vorloc_press");
    
    
    thisAircraft -> addCustomCommand(APALT, TG1, "laminar/B738/EFIS_control/capt/push_button/std_press");
    thisAircraft -> addCustomCommand(APALT, TG2, "laminar/B738/EFIS_control/capt/push_button/rst_press");

    thisAircraft -> addCustomCommand(APVS,  TG1, "laminar/B738/autopilot/lvl_chg_press");

    thisAircraft -> addCustomCommand(APAP,  TG1, "laminar/B738/autopilot/cmd_b_press");
    thisAircraft -> addCustomCommand(APAP,  TG2, "laminar/B738/autopilot/cws_a_press");
    thisAircraft -> addCustomCommand(APAP,  TG3, "laminar/B738/autopilot/cws_b_press");
    
    thisAircraft -> RotaryControl(RCIAS, "sim/autopilot/airspeed_up", "sim/autopilot/airspeed_down", slow, fastest);
    thisAircraft -> RotaryControl(RCCRS, "laminar/B738/autopilot/course_pilot_up", "laminar/B738/autopilot/course_pilot_dn", slow, fastest);
    thisAircraft -> RotaryControl(RCHDG, "laminar/B738/autopilot/heading_up", "laminar/B738/autopilot/heading_dn", slow, fastest);
    thisAircraft -> RotaryControl(RCVS,  "sim/autopilot/vertical_speed_up", "sim/autopilot/vertical_speed_down", slow);
    thisAircraft -> RotaryControl(RCALT, "laminar/B738/autopilot/altitude_up", "laminar/B738/autopilot/altitude_dn", slow, fastest);

    thisAircraft -> addCustomCommand(RCCRS, TG6, "laminar/B738/autopilot/course_copilot_dn", "laminar/B738/autopilot/course_copilot_up", slow, fastest);

    thisAircraft -> addCustomCommand(RCHDG, TG5, "laminar/B738/autopilot/bank_angle_up", "laminar/B738/autopilot/bank_angle_dn", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG6, "laminar/B738/EFIS_control/capt/map_range_dn", "laminar/B738/EFIS_control/capt/map_range_up", slow);
    thisAircraft -> addCustomCommand(RCHDG, TG4, "laminar/B738/EFIS_control/capt/map_mode_up", "laminar/B738/EFIS_control/capt/map_mode_dn", slow);

    thisAircraft -> addCustomCommand(RCALT, TG4, "laminar/B738/EFIS_control/capt/baro_in_hpa_up", "laminar/B738/EFIS_control/capt/baro_in_hpa_dn", slow);     // switch baro between HPA and IN
    thisAircraft -> addCustomCommand(RCALT, TG5, "laminar/B738/pfd/dh_pilot_up", "laminar/B738/pfd/dh_pilot_dn", slow, fastest);                              // set minimums baro and radio
    thisAircraft -> addCustomCommand(RCALT, TG6, "laminar/B738/pilot/barometer_up", "laminar/B738/pilot/barometer_down", slow);                               // set altitude barometric pressure


    
    thisAircraft -> activateIncrDecrRotary();
     
    lights -> defaultAnnunciatorDataRefs();                              // reset to defaults in case another plane has modified in an earlier flight
    
    lights -> addAutopilotLightDataRef(APHDG, "laminar/B738/autopilot/heading_mode");
    lights -> addAutopilotLightDataRef(APNAV, "laminar/B738/autopilot/lnav_status");
    lights -> addAutopilotLightDataRef(APNAV, "laminar/B738/autopilot/vnav_status1");
    lights -> addAutopilotLightDataRef(APAPR, "laminar/B738/autopilot/app_status");
    lights -> addAutopilotLightDataRef(APAPR, "laminar/B738/autopilot/vorloc_status");
    lights -> addAutopilotLightDataRef(APALT, "laminar/B738/autopilot/alt_hld_status");
    lights -> addAutopilotLightDataRef(APVS,  "laminar/B738/autopilot/vs_status");
    lights -> addAutopilotLightDataRef(APVS,  "laminar/B738/autopilot/lvl_chg_status");
    lights -> addAutopilotLightDataRef(APIAS, "laminar/B738/autopilot/speed_status1");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cmd_a_status");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cmd_b_status");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cws_a_status");
    lights -> addAutopilotLightDataRef(APAP,  "laminar/B738/autopilot/cws_b_status");
}


//**********************************************************************************************************************************************
//
//   UNKNOWN AIRCRAFT
//
//**********************************************************************************************************************************************

void Bravo::bravoUnknownAircraft(std::string aircraft) {
    
    const char* jsonFileName = aircraft.c_str();

    bool read = JSONfileExists(jsonFileName);

    this -> reset();

    currentAircraft = new BravoProfile();

    if (read)
        JSONread(currentAircraft, jsonFileName);
    else {
        bravoUnkownAircraftDefault(currentAircraft);
        JSONwrite(currentAircraft, jsonFileName);
    }
}

void Bravo::bravoUnkownAircraftDefault(BravoProfile *thisAircraft) {
    
}

