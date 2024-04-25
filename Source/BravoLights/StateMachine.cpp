//
//  StateMachine.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 07/07/2023.
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


#include "StateMachine.hpp"
#include "XPLaneEnvironment.hpp"
#include "BravoLights.hpp"

LightState::LightState(int state) {
    _state = state;
}

int LightState::state() {
    return _state;
}

void LightState::addStateTransition(APButtonLabel thisButton, int moveToState) {
    stateTransitions.insert(std::make_pair(thisButton, moveToState));
}

std::tuple<bool, int> LightState::getTransitionValue(APButtonLabel thisButton, int fromThisState) {

    auto searchForState = stateTransitions.find(thisButton);
    if (searchForState != stateTransitions.end()) {
        return {true, searchForState -> second};
    }
    else return {false, 0};
}

std::set<APButtonLabel> LightState::getOnLights() {
    return onLights;
}

std::set<APButtonLabel> LightState::getOffLights() {
    return offLights;
}

int LightState::nextState(APButtonLabel thisButton) {
    auto searchForState = stateTransitions.find(thisButton);
    if (searchForState != stateTransitions.end()) {
        return searchForState -> second;
    }
    else return _state;
}

void LightState::stateTransitionActions() {
    
    for (APButtonLabel iter: onLights) {
        switch (iter) {
            case APHDG: lights -> lightOn(HDGLight); break;
            case APNAV: lights -> lightOn(NAVLight); break;
            case APAPR: lights -> lightOn(APRLight); break;
            case APREV: lights -> lightOn(REVLight); break;
            case APALT: lights -> lightOn(ALTLight); break;
            case APVS:  lights -> lightOn(VSLight);  break;
            case APIAS: lights -> lightOn(IASLight); break;
            case APAP:  lights -> lightOn(AutoPilotLight);  break;
            default: break;
        }
    }

    for (APButtonLabel iter: offLights) {
        switch (iter) {
            case APHDG: lights -> lightOff(HDGLight); break;
            case APNAV: lights -> lightOff(NAVLight); break;
            case APAPR: lights -> lightOff(APRLight); break;
            case APREV: lights -> lightOff(REVLight); break;
            case APALT: lights -> lightOff(ALTLight); break;
            case APVS:  lights -> lightOff(VSLight);  break;
            case APIAS: lights -> lightOff(IASLight); break;
            case APAP:  lights -> lightOff(AutoPilotLight);  break;
            default: break;
        }
    }
}


void LightState::theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7, APButtonLabel Light8) {
    onLights.insert(Light1);
    onLights.insert(Light2);
    onLights.insert(Light3);
    onLights.insert(Light4);
    onLights.insert(Light5);
    onLights.insert(Light6);
    onLights.insert(Light7);
    onLights.insert(Light8);
}

void LightState::theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7) {
    onLights.insert(Light1);
    onLights.insert(Light2);
    onLights.insert(Light3);
    onLights.insert(Light4);
    onLights.insert(Light5);
    onLights.insert(Light6);
    onLights.insert(Light7);
}

void LightState::theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6) {
    onLights.insert(Light1);
    onLights.insert(Light2);
    onLights.insert(Light3);
    onLights.insert(Light4);
    onLights.insert(Light5);
    onLights.insert(Light6);
}

void LightState::theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5) {
    onLights.insert(Light1);
    onLights.insert(Light2);
    onLights.insert(Light3);
    onLights.insert(Light4);
    onLights.insert(Light5);
}

void LightState::theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4) {
    onLights.insert(Light1);
    onLights.insert(Light2);
    onLights.insert(Light3);
    onLights.insert(Light4);
}

void LightState::theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3) {
    onLights.insert(Light1);
    onLights.insert(Light2);
    onLights.insert(Light3);
}

void LightState::theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2) {
    onLights.insert(Light1);
    onLights.insert(Light2);
}

void LightState::theseLightsToTurnOn(APButtonLabel Light1) {
    onLights.insert(Light1);
}


void LightState::theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7, APButtonLabel Light8) {
    offLights.insert(Light1);
    offLights.insert(Light2);
    offLights.insert(Light3);
    offLights.insert(Light4);
    offLights.insert(Light5);
    offLights.insert(Light6);
    offLights.insert(Light7);
    offLights.insert(Light8);
}

void LightState::theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7) {
    offLights.insert(Light1);
    offLights.insert(Light2);
    offLights.insert(Light3);
    offLights.insert(Light4);
    offLights.insert(Light5);
    offLights.insert(Light6);
    offLights.insert(Light7);
}

void LightState::theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6) {
    offLights.insert(Light1);
    offLights.insert(Light2);
    offLights.insert(Light3);
    offLights.insert(Light4);
    offLights.insert(Light5);
    offLights.insert(Light6);
}

void LightState::theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5) {
    offLights.insert(Light1);
    offLights.insert(Light2);
    offLights.insert(Light3);
    offLights.insert(Light4);
    offLights.insert(Light5);
}

void LightState::theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4) {
    offLights.insert(Light1);
    offLights.insert(Light2);
    offLights.insert(Light3);
    offLights.insert(Light4);
}

void LightState::theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3) {
    offLights.insert(Light1);
    offLights.insert(Light2);
    offLights.insert(Light3);
}

void LightState::theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2) {
    offLights.insert(Light1);
    offLights.insert(Light2);
}

void LightState::theseLightsToTurnOff(APButtonLabel Light1) {
    offLights.insert(Light1);
}


StateMachine::StateMachine() {
    for (int i=0; i< MAX_STATES; i++) states[i] = NULL;
}

void StateMachine::addState(LightState* newState) {
 
    if ((newState -> state() >= 0) && (newState -> state() < MAX_STATES)) {
        states[newState -> state()] = newState;
    }
}

void StateMachine::goToNextState(APButtonLabel thisButton) {
    currentState = states[currentState] -> nextState(thisButton);
    states[currentState] -> stateTransitionActions();
}

LightState* StateMachine::lightState(int thisState) {
    if ((thisState >=0) && (thisState < MAX_STATES))
        return states[thisState];
    else return NULL;
}
